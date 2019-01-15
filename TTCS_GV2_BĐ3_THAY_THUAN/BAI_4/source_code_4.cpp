#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>
#define	input "du_lieu/mang_du_lieu.txt"
#define	out1 "du_lieu/du_lieu_1.txt"
#define	out2 "du_lieu/du_lieu_2.txt"
using namespace std;

void readFile();	// Hàm doc du lieu tu file
void writeFile();	// Hàm ghi du lieu vào file
void XuatFile(FILE *f, char duongdan[]);	// Hàm xuat du lieu file ra man hình
void tachTrucTiep(FILE *f0, FILE *f1, FILE *f2, int x);	// Hàm tách file du lieu chinh thành file du lieu phu
void tronTrucTiep(FILE *f0, FILE *f1, FILE *f2, int tam);	// Hàm tron truc tiep 2 du lieu phu vao file du lieu tam
void tachTuNhien(FILE *f0, FILE *f1, FILE *f2); // Hàm tách file du lieu chinh thanh file du lieu phu
void tronTuNhien();	// Hàm tron tu nhien các run f1, f2 vào f0
void CopyRun(FILE *f0, FILE	*f1);	// Hàm chép 1 run tu f0 vào f1
void TronRun();	// Hàm tron 1 tun f2 và f2 vao f0
void Copy(FILE *f0, FILE *f1);	// Hàm chép 1 phan tu tu file f0 ghi vao file f1

FILE *f0, *f1, *f2;
int n, x = 1, items, k, y, x1, x2;;
int Error;

int main() {
	int i = 1;
	
	readFile();
	cout << endl << "File du lieu sau khi nhap:";
	XuatFile(f0, input);
	
	while (x < n) {
		tachTrucTiep(f0, f1, f2, x);
		
		cout << endl << "--------------------------------------------" << endl;
		cout << "Du lieu file F1 lan " << i << ": ";
		XuatFile(f1, out1);  
		
		cout << endl << "Du lieu file F2 lan " << i  << ": ";
		XuatFile(f2, out2);  
		
		tronTrucTiep(f0, f1, f2, x);
		cout << endl << "File du lieu sau khi tron lan " << i << ": ";
		XuatFile(f0, input); 
		
		x = x * 2;
		i++;		
	}
}

// Tao file du lieu tu gom n phan tu
void readFile() {
	int tam;
	FILE *f;
	f = fopen("du_lieu/mang_du_lieu.txt", "wt");
	
	if(f == NULL) {
		printf("Khong co du lieu tron file!");
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

/*TRON TRUC TIEP*/

// Tách file du lieu chinh sang file du lieu phu
void tachTrucTiep(FILE *f0, FILE *f1, FILE *f2, int x) {
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

// tronTrucTiep x phan tu tren f1 va x phan tu tren f2 thanh 2x phan tu tren f0 den khi f1 hay f2 ket thuc
void tronTrucTiep(FILE *f0, FILE *f1, FILE *f2, int tam) {
	int	stop, x, y, l, r;
	
	f0 = fopen("du_lieu/mang_du_lieu.txt","wt"); 	
	f1 = fopen("du_lieu/du_lieu_1.txt","rt"); 	
	f2 = fopen("du_lieu/du_lieu_2.txt","rt");
	
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

/*TRON TU NHIEN*/

// Doc 1 phan tu tu file f0 ghi vao file f1
void Copy(FILE *f0, FILE *f1) {	
	fscanf(f0, "%3d", &k);
	fprintf(f1, "%3d", k);

	if  (!feof(f0)) {	
		fscanf(f0, "%d", &y);		// Doc tu fle vao bien 
		long curpos = ftell(f0) - 2;
		fseek(f0, curpos, SEEK_SET);
	}
	
	if (feof(f0)) 
		Error = 1;  // Error == 1 neu het run tren f0 hoac het f0
	else  
		Error = (k > y) ? 1 : 0;	// Gap 1 so y nho hon x thi het run
}

// Chép 1 run tu f0 vào f1
void CopyRun(FILE *f0, FILE	*f1) {
	do
		Copy(f0, f1);
	while(!Error);
}

// Tron 1 run cua f2 và f2 va f0
void TronRun() {
	do {
		fscanf(f1, "%d", &x1);		//doc tu fle vao bien 
		int curpos = ftell(f1) - 2;
		fseek(f1, curpos, SEEK_SET);
		
		fscanf(f2, "%d", &x2);		//doc tu fle vao bien 
		 	curpos = ftell(f2) - 2;
		fseek(f2, curpos, SEEK_SET);	
		
		if(x1 <= x2) {
			Copy(f1, f0);
			if (Error) 
				CopyRun(f2, f0);
		} else {
			Copy(f2, f0);
			if (Error) 
			CopyRun(f1, f0);
		}			
	} while(!Error);
}

//
void tachTuNhien(FILE *f0, FILE	*f1, FILE *f2) {
	do {
		CopyRun(f0, f1);
		
		if (!feof(f0))  
			CopyRun(f0, f2);

	} while (!feof(f0));
		
	fclose(f0);	 
	fclose(f1);		
	fclose(f2);	
}

// Tron các run cua f1 và f2 vào f0
void tronTuNhien() {
	while ((!feof(f1)) && (!feof(f2))) {
		TronRun();
		items++;
	}
	
	while (!feof(f1)) {
		CopyRun(f1, f0);
		items++;	
	}
	
	while (!feof(f2)) {
		CopyRun(f2, f0);
		items++;
	}
	
	fclose(f0);	 
	fclose(f1);		
	fclose(f2);		
}	
