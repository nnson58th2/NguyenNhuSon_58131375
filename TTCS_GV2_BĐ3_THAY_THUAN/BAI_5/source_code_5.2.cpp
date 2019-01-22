#include <iostream>
#include <fstream>
#define max 20
using namespace std;

// Khai bao kieu du lieu cau truc PHANSO
struct PHANSO{
	int tu;
	int mau;
};

void docFile(int &n, int &p, int &q);	// Ham doc du lieu tu file
void luuKetQua(PHANSO ps[max], int n);	// Ham sap xep ket qua va luu vao file
void kiemTra(int n, int p, int q);	// Ham kiem tra voi dieu kien bai toan

// Doc du lieu tu file va gan gia tri cho cac bien
void docFile(int &n, int &p, int &q) {
	fstream f;
	f.open("du_lieu/FRACTIONS.INP.txt", ios::in);
	f >> n;
	f >> p;
	f >> q;
	f.close();
}

// Sap xep day so ket qua va luu vao file
void luuKetQua(PHANSO ps[max], int n) {
	// Sap xep day so
	for(int i = 0; i < n - 1; i++){
		for(int j = i; j < n; j++){
			if((float)ps[i].tu / ps[i].mau > (float)ps[j].tu / ps[j].mau){
				swap(ps[i], ps[j]);
			}
		}
	}
	
	// Luu day so ket qua vao file
	fstream f;
	f.open("du_lieu/FRACTIONS.OUT.txt", ios::out);
	for(int i = 0; i < n; i++){
		f << ps[i].tu << "/" << ps[i].mau << endl;
	}
	f.close();
}

// --- ham kiem tra theo dieu kien bai toan ---
void kiemTra(int n, int p, int q) {
	PHANSO ps[(n / 2) - 1];
	int vt = 0;
	for (float i = n / 2; i < n; i++){
		for(float j = 1; j < n / 2; j++){
			if(j / i > (float) 1 / p && j / i < (float)1 / q) {
				ps[vt].tu = j;
				ps[vt].mau = i;
				vt++;
			}
		}
	}
	luuKetQua(ps, (n / 2) - 1);
	cout << "Luu thanh cong | Mo file de xem ket qua!";
}

int main(){
	int n, p, q;
		
	docFile(n, p, q);
	
	kiemTra(n, p, q);
}
