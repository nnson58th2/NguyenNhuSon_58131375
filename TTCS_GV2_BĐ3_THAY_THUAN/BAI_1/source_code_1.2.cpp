#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#define max 10
using namespace std;

// Khai bao bat dau tu 1
//int a[5][5] = { 0, 1, 0, 1, 0,
//				0, 0, 1, 1, 1,
//				0, 0, 0, 0, 1,
//				0, 0, 0, 0, 0,
//				0, 0, 0, 0, 0 };
					
int tThai[5];
int thuTu = 2;
int a[max][max];

// Nhap ma tran bang tay
void nhapMT(int n) {
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			cout << "Nhap a[" << i << "][" << j << "] = ";
			cin >> a[i][j];
		}
	}
}

// Nhap ma tran tu file
void nhapFile(int &n) {
	fstream fi;
	string s;
	fi.open("du_lieu/input.txt", ios::in);
	getline(fi, s);
	n = atoi(s.c_str());
	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= n; j++)
			fi >> a[i][j];
	fi.close();
}

// Xoa cung den tu dinh j
void xoaCung(int j, int n) {
	for (int i = 0; i <= n; i++)
		a[j][i] = 0;
}

// Ghi nhan dinh
void ghiNhan(int j, int &thuTu, int n) {
	tThai[j] = thuTu;	
	thuTu = thuTu + 1;
	xoaCung(j, n);
}

// Ham tra ve dinh khong co cung den, -1 khong co dinh
int Dinh(int a[max][max], int n) {
	int j = 0;
	int ktra;
	while (j <= n) {
		ktra = 0;
		for (int i = 0; i <= n; i++)
			ktra = a[i][j] + ktra;
			if ((ktra == 0) && (tThai[j] == 0)) {
				ghiNhan(j, thuTu, n);
				return j;	
			}
			j = j + 1;
	}
	if (j > n)
		return -1;
}

// Kiem tra so dinh duoc chon
void kiemTra(int tThai[max], int n) {
	int dem = 0;
	for (int k = 0; k <= n; k++) 
		if (tThai[k] != 0)
			dem = dem + 1;
	if (dem != n + 1)
		cout << "Khong sap xep Topo!";
	else {
		for (int k = 2; k <= n + 2; k++)
			for (int i = 0; i <= n; i++) 
				if (tThai[i] == k)
					cout << "  " << i;
	}
}

int main() {
	int n, dinh, soDinhDC = 0;
	
	nhapFile(n);
	
	do {
		dinh = Dinh(a, n);
		if ((dinh != -1) && (soDinhDC <= n)) {
			if (tThai[dinh] != 0)
				soDinhDC = soDinhDC + 1;
		}
	} while((dinh != -1) && (soDinhDC <= n));
	kiemTra(tThai, n);
	
	return 0; 
}
