#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
#define max 10
using namespace std;

// Khi bao kieu du lieu cong viec de quan ly
struct PhanViec {
	int chiSo;	// Chi so cong viec ung voi so thu tu oto
	int TGSua;	// Thoi gian sua chua
	int TGGiao;	// Thoi gian ban giao
};

vector <int> quaHan;// vector cac oto bi qua han

void Color(int x);	// Hàm sét màu
void nhapVaXuatPhanViec(PhanViec pv[], int &soPhanViec);	// Hàm nhap phan viec
void readFile(PhanViec pv[], int &soPhanViec);	// Hàm doc du lieu tu file
void writeFile(PhanViec pv[], int soPhanViec);	// Hàm ghi du lieu vao file
void sapXepPhanViec(PhanViec pv[], int soPhanViec);	// Hàm sap xep phan viec
void xepLichPhanViec(PhanViec pv[], int soPhanViec);	// Hàm sap xep va ghi ket qua ra file
void xuatQuaTrinh(PhanViec pv[], int soPhanViec);	// Hàm xuat qua trinh thu tu oto

//5
//6 3 5 7 2
//8 4 15 20 3

int main() {
	PhanViec pv[max];
	int n;
	
//	nhapVaXuatPhanViec(pv, n);	
	readFile(pv, n);
	Color(10);
	cout << "Bang cong viec ban dau" << endl;
	xuatQuaTrinh(pv, n);
	
	cout << endl;
	
	sapXepPhanViec(pv, n);
	Color(11);
	cout << "Bang cong viec sau khi sap xep" << endl;
	xuatQuaTrinh(pv, n);
	
	cout << endl;
	
	Color(14);
	xepLichPhanViec(pv, n);
	
	writeFile(pv, n);
	Color(7);
}

// Sét màu
void Color(int x) {
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}

// Nhap phan viec
void nhapVaXuatPhanViec(PhanViec pv[], int &soPhanViec) {
	fstream f;
	f.open("du_lieu/INPUT.txt", ios::out);
	
	cout << "Nhap n so phan viec: ";
	cin >> soPhanViec;
	f << soPhanViec << endl;
	
	for (int i = 0; i < soPhanViec; i++) {
		cout << "TGS[" << i + 1 << "]: ";
		cin >> pv[i].TGSua;
		f << pv[i].TGSua << " ";
	}
	cout << endl;
	f << endl;
	for (int j = 0; j < soPhanViec; j++) {
		cout << "TGG[" << j + 1 << "]: ";
		cin >> pv[j].TGGiao;
		f << pv[j].TGGiao << " ";
	}
	f.close();
	
	cout << endl << "Da nhap xong du lieu cong viec va ghi vao file !";
}

// Doc du lieu tu file
void readFile(PhanViec pv[], int &soPhanViec) {
	fstream f;
	f.open("du_lieu/INPUT.txt", ios::in);
	
	while (!f.eof()) {
		f >> soPhanViec;	// Doc vao so luong oto
		for (int item = 0; item < soPhanViec; item++)
			pv[item].chiSo = item + 1;	// Danh chi so thu tu cho oto
		for (int i = 0; i < soPhanViec; i++)
			f >> pv[i].TGSua;	// Doc vao thoi gian sua oto
		for (int j = 0; j < soPhanViec; j++)
			f >> pv[j].TGGiao;	// Doc vao thoi gian giao oto
	}
	f.close();
}

// Ghi du lieu vao file
void writeFile(PhanViec pv[], int soPhanViec) {
	fstream f;
	f.open("du_lieu/KETQUA.txt", ios::out);
	
	quaHan.clear();	// Xóa het tat ca phan tu co trong vector quaHan
	
	int temp;
	f << "Thu tu sua chua oto: ";
	temp = pv[0].TGSua;
	f << pv[0].chiSo << " ";

	for (int i = 1; i < soPhanViec; i++) 
		if (pv[i].TGGiao >= temp + pv[i].TGSua) {	// Thoi gian giao cua oto thu 2 >= thoi gian sua oto truoc + thoi gian sua oto tiep theo
			temp += pv[i].TGSua;
			f << pv[i].chiSo << " ";
		}
	f << endl << "Oto tre han : ";
	
	/* 
		Thoi gian giao cua oto thu 2 < thoi gian sua cua oto truoc + thoi gian sua oto tiep theo
		thi ra chen vao vector qua han sau khi xuat ra
	*/
	int tre = pv[0].TGSua;
	for (int i = 1; i < soPhanViec; i++) {
		if (pv[i].TGGiao < tre + pv[i].TGSua) 
			quaHan.push_back(pv[i].chiSo);
	}
	if (quaHan.size() == 0)
		f << "Khong co oto nao" << endl;
	else
		for(int i = 0; i< quaHan.size(); i++)
			f << quaHan[i] << " ";
				
	f.close();
	
	cout << endl << "Ghi vao file thanh cong | Mo file de xem ket qua";
}

// Sap xep cong viec theo thu tu tang dan ve thoi gian ban giao va tuong ung
void sapXepPhanViec(PhanViec pv[], int soPhanViec) {
	for (int i = 0; i < soPhanViec - 1; i++)
		for (int j = i + 1; j < soPhanViec; j++)
			if (pv[i].TGGiao > pv[j].TGGiao)
				swap(pv[i], pv[j]);
}

// Xuat qua trinh thu tu oto
void xuatQuaTrinh(PhanViec pv[], int soPhanViec) {	
	cout << "-----------------------------------------" << endl;
	for (int i = 0; i < soPhanViec; i++)
		cout << "| " << pv[i].chiSo << "\t";
	cout << "| " << endl;
	cout << "-----------------------------------------" << endl;
	for(int j = 0; j < soPhanViec; j++)
		cout << "| " << pv[j].TGSua << "\t";
	cout << "| " << endl;
	cout << "-----------------------------------------" << endl;
	for(int k = 0; k < soPhanViec; k++)
		cout << "| " << pv[k].TGGiao << "\t";
	cout << "| " << endl;
	cout << "-----------------------------------------";
}

// Sap xep va ghi ket qua ra file
void xepLichPhanViec(PhanViec pv[], int soPhanViec) {
	int temp;
	cout << "Thu tu sua chua oto dung han :";
	temp = pv[0].TGSua;
	cout << " " << pv[0].chiSo << " | ";

	for (int i = 1; i < soPhanViec; i++) 
		if (pv[i].TGGiao >= temp + pv[i].TGSua) {	// Thoi gian giao cua oto thu 2 >= thoi gian sua oto truoc + thoi gian sua oto tiep theo
			temp += pv[i].TGSua;
			cout << pv[i].chiSo << " | ";
		}
	cout << endl << "Oto tre han : ";
	
	/* 
		Thoi gian giao cua oto thu 2 < thoi gian sua cua oto truoc + thoi gian sua oto tiep theo
		thi ra chen vao vector qua han sau khi xuat ra
	*/
	int tre = pv[0].TGSua;
	for (int i = 1; i < soPhanViec; i++) {
		if (pv[i].TGGiao < tre + pv[i].TGSua) 
			quaHan.push_back(pv[i].chiSo);
	}
	if (quaHan.size() == 0)
		cout << "Khong co oto nao" << endl;
	else
		for(int i = 0; i< quaHan.size(); i++)
				cout << quaHan[i] << " ";
}
