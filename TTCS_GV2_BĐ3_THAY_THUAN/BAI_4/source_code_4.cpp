#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>
#define	input "mang_du_lieu.txt"
#define	out1 "du_lieu_1.txt"
#define	out2 "du_lieu_2.txt"
using namespace std;

void readFile();	// Hàm doc du lieu tu file
void writeFile();	// Hàm ghi du lieu vào file
void XuatFile(FILE *f, char duongdan[]);	// Hàm xuat du lieu file ra man hình
void Tach(FILE *f0, FILE *f1, FILE *f2, int x);	// Hàm tách file du lieu chinh thành file du lieu phu
void Tron(FILE *f0, FILE *f1, FILE *f2, int tam);	// Hàm tron 2 du lieu phu vao file du lieu tam

FILE *f0, *f1, *f2;
int n, x = 1;

int main() {
	int i = 1;
	
	readFile();
	cout << endl << "File du lieu sau khi nhap:";
	XuatFile(f0, input);
	
	while (x < n) {
		Tach(f0, f1, f2, x);
		
		cout << endl << "--------------------------------------------" << endl;
		cout << "Du lieu file F1 lan " << i << ": ";
		XuatFile(f1, out1);  
		
		cout << endl << "Du lieu file F2 lan " << i  << ": ";
		XuatFile(f2, out2);  
		
		Tron(f0, f1, f2, x);
		cout << endl << "File du lieu sau khi tron lan " << i << ": ";
		XuatFile(f0, input); 
		
		x = x * 2;
		i++;		
	}
}

// Doc du lieu tu file vao
void readFile() {
	int tam;
	FILE *f;
	f = fopen("mang_du_lieu.txt", "wt");
	
	if(f == NULL) {
		printf("Khong co du lieu trong file!");
	} 
	
	printf("Nhap n so phan tu: "); 	
	scanf("%d", &n);
		
	for (int i = 0; i < n; i++) {
		printf("Nhap so phan tu %d: ", i + 1);
		scanf("%d", &tam);	// Nhap tam tu ban phím
		fprintf(f, "%3d", tam); 	// Ghi tam vao file 
	}
	
	fclose(f);	
}

// Xuat file du lieu ra man hinh
void XuatFile(FILE *f, char duongdan[]) {
	int i, tam;
	f = fopen(duongdan, "rt");
	
	if(f == NULL) {
		printf("Khong co du lieu trong file!");
	}
	i = 0, n = 0;
	while (!feof(f)) {
		fscanf(f, "%d", &tam);		// Doc tu fle vao bien tam 
		printf("%3d", tam);			// Xuat ra man hinh
		n++;
	}
	
	fclose(f); 
}

// Tách file du lieu chinh sang file du lieu phu
void Tach(FILE *f0, FILE *f1, FILE *f2, int x) {
	int dem, tam;
	
	f0 = fopen(input, "rt");
	f1 = fopen(out1, "wt"); 
	f2 = fopen(out2, "wt");
	
	while (!feof(f0)) {
		// Tách x phan tu cho f1
		dem	= 0;
		while ((dem < x) && (!feof(f0))) {
			fscanf(f0,"%3d", &tam);			// Doc tu file f0 ra tam
			fprintf(f1,"%3d", tam);			// Ghi tam ra file f1
			dem++;			
		}
		
		// Tách x phan tu cho f2
		dem	= 0;
		while ((dem < x) && (!feof(f0))) {
			fscanf(f0,"%3d", &tam);			//doc tu file f0 ra tam
			fprintf(f2,"%3d", tam);			//ghi tam ra file	f2
			dem++;			
		}
	
	}
	
	fclose(f0);
	fclose(f1);
	fclose(f2);  
}

// Tron x phan tu tren f1 va x phan tu tren f2 thanh 2x phan tu tren f0 den khi f1 hay f2 ket thuc
void Tron(FILE *f0, FILE *f1, FILE *f2, int tam) {
	int	stop, x, y, l, r;
	
	f0 = fopen("mang_du_lieu.txt","wt"); 	
	f1 = fopen("du_lieu_1.txt","rt"); 	
	f2 = fopen("du_lieu_2.txt","rt");
	
	while ((!feof(f1))&& (!feof(f2))) {
		l = 0;	// So phan tu cua f1 da ghi len f0
		r = 0;	// So phan tu cua f2 da ghi len f0
		
		fscanf(f1, "%3d", &x);		// Doc 1 phan tu tu f1 vao bien x
		fscanf(f2, "%3d", &y);		// Doc 1 phan tu tu f2 vao bien y
		
		stop = 0;
		
		while ((l != tam)&& (r != tam) && (!stop)) {
			if (x < y) {					// Ghi file f1 (da doc ra bien x) vao truoc
				fprintf(f0,"%3d", x);			// Ghi x ra file f0
				l++;
				
				if ((l < tam) && (!feof(f1)))			// Chua du tam phan tu va chua het file f1
					fscanf(f1, "%3d", &x);		// Doc tiep 1 phan tu tu f1 vao bien x, de lan sau lap sau ghi vao f0
				else {						// Da xong f1 (du tam phan tu hoac ket thuc), ==> ghi f2 vao f0
					fprintf(f0,"%3d", y);			// Ghi y ra file f0
					r++;
					if (feof(f1))			// Neu f1 da ket thuc thi dung viec phan phoi
						stop =1;
				}
			} else {		// Ghi file f2 (da doc ra bien y) vao truoc				
				fprintf(f0,"%3d", y);			// Ghi y ra file f0
				r++;
				
				if ((r < tam)&& (!feof(f2)))			// Chua du tam phan tu va chua het file f1
					fscanf(f2, "%3d", &y);		// Doc tiep 1 phan tu tu f1 vao bien x, de lan sau lap sau ghi vao f0
				else {						// Da xong f2 (du tam phan tu hoac ket thuc), ==> ghi f1 vao f0
					fprintf(f0,"%3d", x);			// Ghi x ra file f0
					l++;
					if (feof(f2))			// Neu f1 da ket thuc thi dung viec phan phoi
						stop =1;
				}							
			}	
		}
		// Ghi tiep phan con lai cua tam phan tu tren f1 vao f0
		while ((l < tam)&& (!feof(f1)))	
		{
			fscanf(f1, "%3d", &x);
			fprintf(f0,"%3d", x);	
			l++;
		}
		
		// Ghi tiep phan con lai cua tam phan tu tren f2 vao f0
		while ((r < tam)&& (!feof(f2)))	
		{
			fscanf(f2, "%3d", &y);
			fprintf(f0,"%3d", y);	
			r++;
		}		
	}
	
	if(!feof(f1)) {			// f1 con phan tu
		// Chep phan con lai cua f1 len f0
			while (!feof(f1))
			{	
				fscanf(f1, "%3d", &x);
				fprintf(f0,"%3d", x);	
			}
	}
	
	if(!feof(f2)) {			// f2 con phan tu
		// Chep phan con lai cua f2 len f0
			while (!feof(f2)) {	
				fscanf(f2, "%3d", &y);
				fprintf(f0,"%3d", y);	
			}
	}
	fclose(f0);
	fclose(f1);
	fclose(f2); 
}
