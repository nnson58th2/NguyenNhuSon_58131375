#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

// Khai b�o c?u tr�c luu bi?n
struct saveVariable {
	int name;   // T�n
	int sum;    // T?ng
	int flag;   // C�i c?
};

void ImportTheGraph(int a[10][10], int &n);  // H�m nh?p d? th?
void writeTheGraph(int a[10][10], int &n);   // H�m xu?t d? thi ra file
void readTheGraph(int a[10][10], int &n);    // H�m d?c d? th? t? file
void showTheGraph(int a[10][10], int n);    // H�m hi?n th? ma tr?n
void Compare(saveVariable &vc, saveVariable &vp); // H�m so s�nh ki?m tra bi?n
void Browser(saveVariable vc[10], int &index, int n);   // H�m duy?t ma tr?n ch?n di?m c� t?ng nh? nh?t
void Router(saveVariable a[10], int x, int y); // H�m hi?n th? ra du?ng di ng?n nh?t t? m?ng ma tr?n
void findTheWay(int a[10][10], int n);  // H�m t�m du?ng di ng?n nh?t
int main(); // H�m ch�nh

fstream fi;

// H�m nh?p d? thi c� d?ng ma tr?n
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

// Ghi ma tr?n v�o trong file
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

// �?c ma tr?n trong file ra m?ng
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

// H�m ki?m tra di?u ki?n - g�n bi?n ph? cho bi?n ch�nh
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

// Ch?n di?m c� t?ng nh? nh?t v� d?ng c? l�n
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
	vc[index].flag = 1;	// Tr? v? gi� tr? h�ng cho l?n duy?t ma tr?n ti?p theo
}

// Hi?n th? ra l? tr�nh du?ng di ng?n nh?t t? m?ng ma tr?n (saveVariable)
void Router(saveVariable a[10], int x, int y){
	cout << "Do dai duong di ngan nhat: " << a[y].sum << endl;
	cout << "lo trinh:  " << y;
	
	while(y != x){
		y = a[y].name;
		cout << " <-- " << y;
	}
}

// T�m du?ng di ng?n nh?t
void findTheWay(int a[10][10], int n) {
	saveVariable vc[n];
	saveVariable vp;
	
    int start, end;
    
    vp.flag = 0;    // C? n?m
	
	// Kh?i t?o cho h�ng d?u ti�n
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
	
	int itemS = start;	// V? tr� b?t d?u
	int itemE = end;	// V? tr� k?t th�c
	int i = itemS;	// �?c ma tr?n t? h�ng d?u(itemS) - V? tr� b?t d?u t�m du?ng
	
    // B?t c? , d�nh d?u v? tr� ban d?u
	vc[itemS].flag = 1;
	
	do {
		for (int j = 0; j < n; j++) {
            // G�n cho bi?n ph? c�i t�n v� gi� tr? t?ng
			if (a[i][j] != 0) {
				vp.name = itemS;
				vp.sum = a[i][j] + vc[itemS].sum;
			} else {
                // X? l� gi� tr? c?a ma tr?n t?i h�ng i c?t j khi gi� tr? b?ng 0
				vp.name = 0;
				vp.sum = 0;
			}
            Compare(vc[j], vp);
        }
        // Xu?t ra qu� tr�nh thay d?i gi� tr? c?a m?ng vc 
        for (int k = 0; k < n; k++) {
            cout << vc[k].name << "," << vc[k].sum << "\t";
        }
        cout << endl;
        
        // ��nh d?u l?i v? tr� d� di qua
        Browser(vc, itemS, n);
        
        i = itemS; // �ua i d?n h�ng ti?p theo d? d?c ti?p ma tr?n	
	} while(itemS != itemE);
	
	cout << "--------------------------------------------" << endl;

    // Hi?n th? ra l? tr�nh du?ng di
	Router(vc, start, end);
}

// H�m ch�nh
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
