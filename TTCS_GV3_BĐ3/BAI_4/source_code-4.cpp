#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

// Khai báo c?u trúc luu bi?n
struct saveVariable {
	int name;   // Tên
	int sum;    // T?ng
	int flag;   // Cái c?
};

void ImportTheGraph(int a[10][10], int &n);  // Hàm nh?p d? th?
void writeTheGraph(int a[10][10], int &n);   // Hàm xu?t d? thi ra file
void readTheGraph(int a[10][10], int &n);    // Hàm d?c d? th? t? file
void showTheGraph(int a[10][10], int n);    // Hàm hi?n th? ma tr?n
void Compare(saveVariable &vc, saveVariable &vp); // Hàm so sánh ki?m tra bi?n
void Browser(saveVariable vc[10], int &index, int n);   // Hàm duy?t ma tr?n ch?n di?m có t?ng nh? nh?t
void Router(saveVariable a[10], int x, int y); // Hàm hi?n th? ra du?ng di ng?n nh?t t? m?ng ma tr?n
void findTheWay(int a[10][10], int n);  // Hàm tìm du?ng di ng?n nh?t
int main(); // Hàm chính

fstream fi;

// Hàm nh?p d? thi có d?ng ma tr?n
void ImportTheGraph(int a[10][10], int &n) {
	cout << "Nhap so dinh: ";
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << "Nhap A[" << i << "][" << j << "]: ";
			cin >> a[i][j];
		}
	}
}

// Ghi ma tr?n vào trong file
void writeTheGraph(int a[10][10], int &n) {
	fi.open("du_lieu/do_thi.txt", ios::out);
	fi << n;
	fi << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			fi << a[i][j] << " ";
		fi << endl;
	}
	fi.close();
}

// Ð?c ma tr?n trong file ra m?ng
void readTheGraph(int a[10][10], int &n) {
	fi.open("du_lieu/do_thi.txt", ios::in);
	fi >> n;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			fi >> a[i][j];
	fi.close();
}

// Xu?t m?ng ma tr?n
void showTheGraph(int a[10][10], int n) {
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++)
			cout << a[i][j] << " ";
		cout << endl;
	}		
}

// Hàm ki?m tra di?u ki?n - gán bi?n ph? cho bi?n chính
void Compare(saveVariable &vc, saveVariable &vp) {
	if (vc.flag != 1) {
		if (vc.sum == 0) {
			vc.name = vp.name;
			vc.sum = vp.sum;
		} else {
			if (vp.sum != 0 && vc.sum > vp.sum) {
				vc.name = vp.name;
				vc.sum = vp.sum;
			}
		}
	}
}

// Ch?n di?m có t?ng nh? nh?t và d?ng c? lên
void Browser(saveVariable vc[10], int &index, int n) {
	int print = 1000;
	
	for (int i = 0; i < n; i++) {	
		if (vc[i].flag != 1 && vc[i].sum != 0) {
			if (vc[i].sum < print) {
				index = i;
				print = vc[i].sum;
			}
		}
	}
	vc[index].flag = 1;	// Tr? v? giá tr? hàng cho l?n duy?t ma tr?n ti?p theo
}

// Hi?n th? ra l? trình du?ng di ng?n nh?t t? m?ng ma tr?n (saveVariable)
void Router(saveVariable a[10], int x, int y){
	cout << "Do dai duong di ngan nhat: " << a[y].sum << endl;
	cout << "lo trinh:  " << y;
	
	while(y != x){
		y = a[y].name;
		cout << " <-- " << y;
	}
}

// Tìm du?ng di ng?n nh?t
void findTheWay(int a[10][10], int n) {
	saveVariable vc[n];
	saveVariable vp;
	
    int start, end;
    
    vp.flag = 0;    // C? n?m
	
	// Kh?i t?o cho hàng d?u tiên
	for (int i = 0; i < n; i++) {
		vc[i].name = 0;
		vc[i].sum = 0;
		vc[i].flag = 0;
	}
	
	cout << "Nhap diem bat dau di: ";
    cin >> start;
    cout << "Nhap diem ket thuc di: ";
    cin >> end;
    cout << "--------------------------" << endl;
	cout << "Qua trinh thay doi gia tri" << endl;
	
	int itemS = start;	// V? trí b?t d?u
	int itemE = end;	// V? trí k?t thúc
	int i = itemS;	// Ð?c ma tr?n t? hàng d?u(itemS) - V? trí b?t d?u tìm du?ng
	
    // B?t c? , dánh d?u v? trí ban d?u
	vc[itemS].flag = 1;
	
	do {
		for (int j = 0; j < n; j++) {
            // Gán cho bi?n ph? cái tên và giá tr? t?ng
			if (a[i][j] != 0) {
				vp.name = itemS;
				vp.sum = a[i][j] + vc[itemS].sum;
			} else {
                // X? lý giá tr? c?a ma tr?n t?i hàng i c?t j khi giá tr? b?ng 0
				vp.name = 0;
				vp.sum = 0;
			}
            Compare(vc[j], vp);
        }
        // Xu?t ra quá trình thay d?i giá tr? c?a m?ng vc 
        for (int k = 0; k < n; k++) {
            cout << vc[k].name << "," << vc[k].sum << "\t";
        }
        cout << endl;
        
        // Ðánh d?u l?i v? trí dã di qua
        Browser(vc, itemS, n);
        
        i = itemS; // Ðua i d?n hàng ti?p theo d? d?c ti?p ma tr?n	
	} while(itemS != itemE);
	
	cout << "--------------------------------------------" << endl;

    // Hi?n th? ra l? trình du?ng di
	Router(vc, start, end);
}

// Hàm chính
int main(){
	int a[10][10];
    int n;
	
//	ImportTheGraph(a, n);
//	writeTheGraph(a, n);

	readTheGraph(a, n);
	showTheGraph(a, n);
	cout << "------------" << endl;
	findTheWay(a, n);
}
