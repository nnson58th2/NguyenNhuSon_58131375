#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <windows.h>
using namespace std;

#define max 55

int jackpot[7] = {31, 22, 15, 35, 50, 15, 6};	// Ket qua xo so gan san
int p[6];	// Mang xo so nguoi choi
int a[max];	// Mang xo so ngau nhien tu 01 -> 55

void taoVeKQ(int a[max]);	// Ham tao ket qua ve xo ngau nhien
void SapXep(int a[]);	// Ham sap xep ve so
void nhapXuatXS();	// Ham nhap ve so nguoi choi tu ban phim va xuat ra man hinh
void XuatXS();	// Ham xuat ket qua xo so ngay hom nay
void KetQua();	// Ham hien thi ket qua nguoi choi trung thuong
void Color(WORD color);	// Ham set mau
void ResizeConsole(int width, int height);	// Ham set kich thuoc cho cua so console
void GotoXY(short x, short y);	// Ham di chuyen con tro toi vi tri can

// Chuong trinh chinh
int main(){
	ResizeConsole(800, 900);	// Set man hinh console co chieu rong: 800px va chieu cao: 900px
	taoVeKQ(a);	// Goi ham tao ve so ngau nhien
	XuatXS();	// Goi ham xuat ket qua xo so ngay hom nay ra man hinh
	nhapXuatXS();	// Goi ham nhap ve so nguoi choi va hien thi ket qua nhap va man hinh
	KetQua();	// Goi ham hien thi ket qua nguoi choi trung thuong
}

// Set kich thuoc cho cua so console
void ResizeConsole(int width, int height) {
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

// Set mau chu
void Color(WORD color) {
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
 
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
 
    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0;
    wAttributes |= color;
 
    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

// Di chuyen con tro toi vi tri can
void GotoXY(short x,short y) {
    HANDLE hConsoleOutput;
    COORD Cursor_an_Pos = { x,y};
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput , Cursor_an_Pos);
}

// Ham tao ket qua xo so ngau nhien
void taoVeKQ(int a[max]) {
	// Tao mang 55 phan tu tu 1 -> 55
	for (int i = 0; i < max; i++)
		a[i] = i + 1;
	srand(time(NULL));
    // Tron mang phan tu do
	random_shuffle(a, a + max);
    // Lay 7 phan tu ngau nhien dau tien
	for (int i = 0; i < 7; i++) {
		jackpot[i] = a[i];
	}		
}

// Sap xep ve so
void SapXep(int a[]) {
	for (int i = 0 ; i < 6 ; i++)    
        for (int j = i + 1 ; j < 6 ; j++)     
            if (a[i] > a[j]) {
                swap(a[i], a[j]);
            }
}

// Nhap ve so nguoi choi va xuat ra man hinh
void nhapXuatXS() {
	int temp, check;
	int i = 0;
	
	cout << "Nhap cac so trong ve so cua ban" << endl;
	cout << "So thu "<< i + 1 << " : ";
	cin >> temp;
	
	// Kiem tra neu nguoi choi nhap vao so be hon 1 hoac lon hon 55 thi bat nguoi choi nhap lai
	while (temp < 1 || temp > 55) {
		cout << "Ban nhap sai so!!" << endl;
		cout << "Nhap lai so thu " << i + 1 << " : ";
		cin >> temp;	
	}
	
	p[i] = temp; // Gan bien nguoi choi da nhap vao tuong ung voi cac phan tu trong mang xo so nguoi choi
	for (int i = 1; i < 6; i++) {
		cout << "So thu "<< i + 1 << " : ";
		cin >> temp;
		check = 1;	// Gan gia tri cho bien kiem tra

		// Trong khi bien kiem tra nay van bang gia tri da gan o tren thi lap
		while (check == 1) {
			check = 0;
			for (int j = 0; j <= i; j++)
				if (temp == p[j])	// Kiem tra gia tri trung nhau
					check = 1;
			if (temp < 1 || temp > 55) // KKiem tra gioi han so nhap vao 01 -> 55
					check = 1;
			// Nguoi choi nhap trung so da nhap truoc do thi bat nguoi choi nhap lai
			if (check == 1) {
				cout << "Ban nhap trung so!!" << endl;
				cout << "Nhap lai so thu "<< i + 1 << " : ";
				cin >> temp;	
			}
		}
		p[i] = temp;
	}
	cout << "Cac so trong ve so cua ban: ";
	SapXep(p);	// Sap xep ve so cua nguoi choi theo thu tu
//	Color(12); 
	for(int i = 0; i < 6; i++)
		if (p[i] < 10)	// Neu gia tri phan tu trong mang be hon 10 thi them so 0 o dang truoc
			cout << "0" << p[i] << " ";
		else
			cout << p[i] << " ";
	
//	Color(15); 
	cout << endl << "---------------------------------------------" << endl;
}

 // Xuat ket qua xo so ngay hom nay (theo yeu cau cua co)
 void XuatXS() {
 	SapXep(jackpot);
// 	Color(15);
 	GotoXY(22, 1);
 	cout << "---------------------------------" << endl;
 	GotoXY(22, 2); 
 	cout << "|   Ket Qua Xo So Ngay Hom Nay  |" << endl;
 	GotoXY(22, 3);
// 	Color(15);
 	cout << "|     "; 
 	for (int i = 0; i < 6; i++)
 		if (jackpot[i] < 10) {
// 			Color(12);
 			cout << "0" << jackpot[i] << " ";
 		}
 		else
 			cout << jackpot[i] << " ";
// 	Color(14); 
 	if (jackpot[6] > 9) {
// 		Color(15);
 		cout << "| ";
// 		Color(14); 
 		cout <<  jackpot[6];
		
 	}
 	else {
 		cout << "| 0"<<jackpot[6];
 	}
 	GotoXY(54, 3);
// 	Color(15);
 	cout << "|   "; 
// 	Color(15);
 	GotoXY(22, 4);
 	cout << "---------------------------------" << endl;
 }

//// Xuat ket qua xo so ngay hom nay (theo yeu cau cua de bai)
//void XuatXS() {
//	SapXep(jackpot);
////	Color(15);
//	GotoXY(22, 10);
//	cout << "---------------------------------" << endl;
//	GotoXY(22, 11); 
//	cout << "|   Ket Qua Xo So Ngay Hom Nay  |" << endl;
//	GotoXY(22, 12);
////	Color(15);
//	cout << "|     "; 
//	for (int i = 0; i < 6; i++)
//		if (jackpot[i] < 10) {
////			Color(12);
//			cout << "0" << jackpot[i] << " ";
//		}
//		else
//			cout << jackpot[i] << " ";
////	Color(14); 
//	if (jackpot[6] > 9) {
////		Color(15);
//		cout << "| ";
////		Color(14); 
//		cout << jackpot[6];
//		
//	}
//	else {
//		cout << "| 0"<<jackpot[6];
//	}
//	GotoXY(54, 12);
////	Color(15);
//	cout << "|   "; 
////	Color(15);
//	GotoXY(22, 13);
//	cout << "---------------------------------" << endl;
//}

// Ket qua nguoi choi trung
void KetQua() {
	int count = 0;
	int temp = 0;
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; j++)
			if (p[i] == jackpot[j])
				count++;
//	Color(3);
	cout << "Ban trung (" << count << " so) so voi ket qua cua chung toi" << endl;
//	Color(15);
	cout << "---------------------------------------------" << endl;
//	Color(14);
	switch (count) {
		case 6:
			cout << "Chuc mung ban da trung Giai Jackpot 1";
			break;
		case 5: {
			for (int i = 0; i < 6; i++)
				if (p[i] == jackpot[6])
					temp = 1;
			if (temp == 1)
				cout << "Chuc mung ban da trung Giai Jackpot 2";
			else
				cout << "Chuc mung ban da trung Giai Nhat";
			break;
		}
		case 4:
			cout << "Chuc mung ban da trung Giai Nhi";
			break;
		case 3:
			cout << "Chuc mung ban da trung Giai Ba";
			break;
		default:
			cout << "Chuc ban may man lan sau | Nho mua ve de có co hoi trung nhieu hon!";
			break;
	}
//	Color(7);
}
