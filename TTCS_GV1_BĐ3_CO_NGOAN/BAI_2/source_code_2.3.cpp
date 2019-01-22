#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <ctime>
#include <windows.h>
#define max 10
using namespace std;

fstream f;

int a[max][max], b[max][max];
int sum[max][max];	// Mang luu ma tran sau khi tong
int sub[max][max];	// Mang luu ma tran sau khi hieu
int mul[max][max];	// Mang luu ma tran sau khi nhan

void NhapMaTran(int a[max][max], int b[max][max], int &m1, int &n1, int &m2, int &n2);	// Hàm nhap ma tran tu bàn phím va ghi vao file
void XuatHaiMaTran(int a[max][max], int b[max][max], int &m1, int &n1, int &m2, int &n2);	// Hàm xuat ma tran ra màn hình
void XuatMaTranTinh(int a[max][max], int m, int n);	// Hàm xuat ma tran vua tinh ra man hinh
void tongHaiMaTran(int a[max][max], int b[max][max], int m1, int n1, int m2, int n2);	// Hàm tinh tong hai ma tran
void hieuHaiMaTran(int a[max][max], int b[max][max], int m, int n, int m2, int n2);	// Hàm tinh tong hai ma tran
void tichHaiMaTran(int a[max][max], int b[max][max], int m, int n, int m2, int n2);	// Hàm tinh tong hai ma tran
void xuatKetQua(int a[max][max], int m, int n, int k);	// Hàm xuat ket qua ma tran sau khi tinh
bool returnToMenu();	// Ham quay lai menu de chon tiep
void showMenu();	// Ham hien thi menu
void menuOption(int a[max][max], int b[max][max], int &m1, int &n1, int &m2, int &n2);	// Ham hien thi menu de chon
void Color(WORD color);	// Ham set mau
void ResizeConsole(int width, int height);	// Ham set kich thuoc cho cua so console
void GotoXY(short x,short y);	// Ham di chuyen con tro toi vi tri can den

int main() { 
	int hang1, cot1, hang2, cot2;
	
	ResizeConsole(1000, 800);
	menuOption(a, b, hang1, cot1, hang2, cot2);
}

// Set kich thu cho cua so console
void ResizeConsole(int width, int height) {
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

// Set mau
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

// Nhap ma tran bang ham ramdom va ghi vao file
void NhapMaTran(int a[max][max], int b[max][max], int &m1, int &n1, int &m2, int &n2) {
	f.open("du_lieu/input2.txt", ios::out);
	
	cout << "Nhap so hang cua ma tran 1: ";
	cin >> m1;
	f << m1 << " ";
	cout << "Nhap so cot cua ma tran 1: ";
	cin >> n1;
	f << n1 << " ";
	cout << endl << "Nhap so hang cua ma tran 2: ";
	cin >> m2;
	f << m2;	// Ghi ra file thêm hang 2 de luc doc vao kiem tra de hon
	f << endl;
	
	// Nhap vao tung giá tri cua ma tran 1 và ghi vào file
	srand(time(NULL));
	for (int i = 0; i < m1; i++) {
		for (int j = 0; j < n1; j++) {
			a[i][j] = rand() % 20 - 5;	// Random
			f << a[i][j] << " ";
		}
		f << endl;
	}
	
	f << m2 << " ";
	cout << "Nhap so cot cua ma tran 2: ";
	cin >> n2;
	f << n2;
	f << endl;
	
	// Nhap vao tung giá tri cua ma tran 2 và ghi vào file
	for (int i = 0; i < m2; i++) {
		for (int j = 0; j < n2; j++) {
			b[i][j] = rand() % 20 - 10;	// Random
			f << b[i][j] << " ";
		}
		f << endl;
	}
	
	f.close();
}

// Hien thi ma tran sau khi nhap ra màn hình
void XuatHaiMaTran(int a[max][max], int b[max][max], int &m1, int &n1, int &m2, int &n2) {
	for (int i = 0; i < m1; i++) {
		for (int j = 0; j < n1; j++)
			cout << a[i][j] << " ";
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < m2; i++) {
		for (int j = 0; j < n2; j++)
			cout << b[i][j] << " ";
		cout << endl;
	}
}

// Hien thi ma tran sau khi tinh toan
void XuatMaTranTinh(int a[max][max], int m, int n) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
			cout << a[i][j] << " ";
		cout << endl;
	}
}

// Tinh tong hai ma tran
void tongHaiMaTran(int a[max][max], int b[max][max], int m1, int n1, int m2, int n2) {	
	if (m1 == m2 && n1 == n2) {
		for (int i = 0; i < m1; i++) {
			for (int j = 0; j < n1; j++) {
				sum[i][j] = a[i][j] + b[i][j];	
			}
		}	
	} else 
		cout << "Khong cong duoc hai ma tran | Quay lai Menu de nhap lai dang ma tran dung" << endl;
}

// Hieu hai ma tran
void hieuHaiMaTran(int a[max][max], int b[max][max], int m1, int n1, int m2, int n2) {	
	if (m1 == m2 && n1 == n2) {
		for (int i = 0; i < m1; i++) {
			for (int j = 0; j < n1; j++) {
				sub[i][j] = a[i][j] - b[i][j];	
			}
		}
	} else
		cout << "Khong tru duoc hai ma tran | Quay lai Menu de nhap lai dang ma tran dung" << endl;
}

// Tich hai ma tran
void tichHaiMaTran(int a[max][max], int b[max][max], int m1, int n1, int m2, int n2) {	
	if (n1 == m2) {
		for (int i = 0; i < m1; i++) {
			for (int j = 0; j < n2; j++) {
				mul[i][j] = 0;
				for (int l = 0; l < n1; l++) {
					mul[i][j] += a[i][l] * b[l][j];
				}
			}
		}
	} else 
		cout << "Khong nhan duoc hai ma tran | Quay lai Menu de nhap lai dang ma tran dung" << endl;
}

// Xuat ket qua ma tran sau khi thu hien
void xuatKetQua(int a[max][max], int m, int n){
	f.open("du_lieu/output2.txt", ios::out | ios::app);
	
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n ; j++){
			f << a[i][j] << " ";
		}
		f << endl;
	}
	f << endl;
	
	f.close();
}

// Quay lai menu de chon tiep
bool returnToMenu() {
	char rtnMenu;
	cout << "-----------------------------" << endl;
    cout << "Enter z to return to the menu:> "; 
	cin >> rtnMenu;

    if (rtnMenu == 'z' || rtnMenu == 'Z') {
        return true;
    } return false;
}

// Hien thi menu
void showMenu() {
	GotoXY(25, 0); Color(12);
	cout << "Nhap tuong ung voi 1, 2, 3, 4, 5 | Chon 6 de thoat!" << endl;
	GotoXY(25, 1); Color(11);	
	cout << "1. Nhap vao hai ma tran va ghi vào tap tin input2.txt" << endl;
	GotoXY(25, 2); Color(14);
	cout << "2. Tinh tong hai ma tran(+) | Chon luu vao file hay khong" << endl;
	GotoXY(25, 3); Color(9);
	cout << "3. Tinh hieu hai ma tran(-) | Chon luu vao file hay khong" << endl;
	GotoXY(25, 4); Color(13);
	cout << "4. Tinh tich hai ma tran(*) | Chon luu vao file hay khong" << endl;
	GotoXY(25, 5); Color(15);
    cout << "5. Thoát" << endl;
    GotoXY(25, 6); Color(7);
	cout << "Enter:> ";
}

void menuOption(int a[max][max], int b[max][max], int &hang1, int &cot1, int &hang2, int &cot2) {
	int x;
	
	do {
		showMenu();
		cin >> x;
		
		if (x < 1 || x > 6)
			GotoXY(25, 8); Color(12);
			cout << "Chon sai | Chon lai!" << endl;
			GotoXY(25, 9); Color(15);
			cout << "--------------------" << endl;
	} while(x < 1 || x > 6);
	
	switch(x) {
		case 1:
			system("cls");
			NhapMaTran(a, b, hang1, cot1, hang2, cot2);
			cout << endl << "Hai ma tran sau khi nhap" << endl;
			XuatHaiMaTran(a, b, hang1, cot1, hang2, cot2);
			cout << endl << "Tao ma tran thanh cong | Mo file de xem!!" << endl;
			
			if(returnToMenu()) {
                system("cls");
                menuOption(a, b, hang1, cot1, hang2, cot2);
            } else {
                cout << "Exited!" << endl;
            }
			break;
		case 2: {
			system("cls");
			tongHaiMaTran(a, b, hang1, cot1, hang2, cot2);
			cout << "Ma tran sau khi cong" << endl;
			XuatMaTranTinh(sum, hang1, cot1);
			cout << "------------------------------------" << endl;
			int luu;
			do {
				cout << "Chon 1 de luu | Chon 2 de khong luu" << endl;
				cout << "Enter:> ";
				cin >> luu;
				if (luu < 1 || luu > 2)
					cout << "Nhap lai" << endl;
			} while(luu < 1 || luu > 2);
			
			if (luu == 1) {
				xuatKetQua(sum, hang1, cot1);	
				cout << "Luu thanh cong | Mo file de xem ket qua" << endl;
			}
			
			if(luu == 2) {
                system("cls");
                menuOption(a, b, hang1, cot1, hang2, cot2);
            }
			
			if(returnToMenu()) {
                system("cls");
                menuOption(a, b, hang1, cot1, hang2, cot2);
            } else {
                cout << "Exited!" << endl;
            } 
			break;
		}
		case 3: {
			system("cls");
			hieuHaiMaTran(a, b, hang1, cot1, hang2, cot2);
			cout << "Ma tran sau khi tru" << endl;
			XuatMaTranTinh(sub, hang1, cot1);
			
			cout << "------------------------------------" << endl;
			int luu;
			do {
				cout << "Chon 1 de luu | Chon 2 de khong luu" << endl;
				cout << "Enter:> ";
				cin >> luu;
				if (luu < 1 || luu > 2)
				cout << "Nhap lai" << endl;
			} while(luu < 1 || luu > 2);
			
			if (luu == 1) {
				xuatKetQua(sub, hang1, cot1);
				cout << "Luu thanh cong | Mo file de xem ket qua" << endl;
			}
			
			if(luu == 2) {
                system("cls");
                menuOption(a, b, hang1, cot1, hang2, cot2);
            }
			
			if(returnToMenu()) {
                system("cls");
                menuOption(a, b, hang1, cot1, hang2, cot2);
            } else {
                cout << "Exited!" << endl;
            } 
			break;
		}
		case 4:
			system("cls");
			tichHaiMaTran(a, b, hang1, cot1, hang2, cot2);
			cout << "Ma tran sau khi nhan" << endl;
			XuatMaTranTinh(mul, hang1, cot2);
			
			cout << "------------------------------------" << endl;
			int luu;
			do {
				cout << "Chon 1 de luu | Chon 2 de khong luu" << endl;
				cout << "Enter:> ";
				cin >> luu;
				if (luu < 1 || luu > 2)
				cout << "Nhap lai" << endl;
			} while(luu < 1 || luu > 2);
			
			if (luu == 1) {
				xuatKetQua(mul, hang1, cot2);			
				cout << "Luu thanh cong | Mo file de xem ket qua" << endl;
			}
			
			if(luu == 2) {
                system("cls");
                menuOption(a, b, hang1, cot1, hang2, cot2);
            }
			
			if(returnToMenu()) {
                system("cls");
                menuOption(a, b, hang1, cot1, hang2, cot2);
            } else {
                cout << "Exited!" << endl;
            } 
			break;
		case 5:
			system("cls");
			cout << "Exited!";
			break;
		default:
			system("cls");
			cout << "Nhap sai tuy chon | Nhap lai!";
			
			if(returnToMenu()) {
                system("cls");
                menuOption(a, b, hang1, cot1, hang2, cot2);
            } else {
                cout << "Exited!" << endl;
            }
			break;
	}
}

