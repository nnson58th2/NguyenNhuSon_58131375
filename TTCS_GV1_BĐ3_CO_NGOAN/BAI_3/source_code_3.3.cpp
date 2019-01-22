#include <iostream>
#include <fstream>
#include <string.h>
#include <iomanip>
#include <ctime>
#include <windows.h>
#include <stdlib.h>
#include <vector>
using namespace std;

ifstream fi("du_lieu/nhan_vien.txt");
fstream f;

// Khi bao lop nhan vien
class NhanVien {
	protected: 
		string hoTen, gioiTinh, ngayVaoLam;
		int soCon;
		float heSoLuong;
		static int luongCB;
	public:
		void NhapNV();
		void NhapNVFile();
		void XuatNV();
		void XuatNVFile();
		int namLamViec();
		int tinhTienThuongNV();
		friend class NhanVienVP;
		friend class NhanVienSX;
};

int NhanVien::luongCB = 1250;

// Nhap nhan vien tu ban phim
void NhanVien::NhapNV() {	
	fflush(stdin);
	cout << endl << "Ten nhan vien: ";
	getline(cin, hoTen);
	cout << "Gioi tinh: ";
	cin >> gioiTinh;
	cout << "Ngay vao lam: ";
	cin >> ngayVaoLam;
	cout << "He so luong: ";
	cin >> heSoLuong;
	cout << "So con: ";
	cin >> soCon;
}

// Nhap nhan vien tu file
void NhanVien::NhapNVFile(){
	string s;
	getline(fi, s); hoTen = s;
	getline(fi, s); gioiTinh = s;
	getline(fi, s); ngayVaoLam = s;
	getline(fi, s); heSoLuong = atof(s.c_str());
	getline(fi, s); soCon = atoi(s.c_str());
	getline(fi, s); luongCB = atoi(s.c_str());
}

// Xuat nhan vien ra man hình
void NhanVien::XuatNV() {
	cout << "Ho ten" << setw(15) << "Gioi tinh" << setw(20) << "Ngay lam viec" << setw(12) << "So con" << endl;
	cout << hoTen << setw(15) << gioiTinh << setw(20) << ngayVaoLam << setw(12) << soCon << endl;
}

// Xuat nhan vien ra file
void NhanVien::XuatNVFile() {
	f << "Ho ten: " << hoTen << endl;
	f << "Gioi tinh: " << gioiTinh << endl;
	f << "Ngay lam viec: " << ngayVaoLam << endl;	
	f << "So con: " << soCon << endl;
}

// Tinh nam lam viec
int NhanVien::namLamViec(){
	time_t now = time(0);
	tm *ltm = localtime(&now);
	int namHienTai;
	namHienTai = 1900 + ltm->tm_year;
	int x = (ngayVaoLam[6] - 48) * 1000 + (ngayVaoLam[7] - 48) * 100 + (ngayVaoLam[8] - 48) * 10 + (ngayVaoLam[9] - 48);
	int y = namHienTai - x;
	return y;
}

// Tinh tien thuong
int NhanVien::tinhTienThuongNV() {
	return namLamViec() * 1000000;
}

// Khai bao lop nhan vien van phong
class NhanVienVP:public NhanVien {
	int soNgayVang;
	static int dinhMucVang;
	static float donGiaPhat;	
	
	public:
		void NhapNVVP() {
			NhanVien::NhapNV();
			cout << "So ngay vang: ";
			cin >> soNgayVang;
		}
		void NhapNVVPFile(){
			string s;
			NhanVien::NhapNVFile();
			getline(fi, s); soNgayVang = atoi(s.c_str());
		}
		int tinhTienPhatNVVP() {
			if(soNgayVang > dinhMucVang)
				return soNgayVang * donGiaPhat;
			else
				return 0;
		}
		float tinhTroCapNVVP() {
			if(gioiTinh == "Nu")
				return 200000 * soCon * 1.5;
			else
				return 200000 * soCon;
		}
		float tinhLuongNVVP() { 
			return luongCB * heSoLuong - tinhTienPhatNVVP();
		}
		void XuatNVVP() {
			NhanVien::XuatNV();
			cout << "So ngay vang" << setw(15) << "Tien luong" << setw(15) << "Tien thuong" << endl; 
			cout << soNgayVang << setw(22) << tinhLuongNVVP() << setw(15) << tinhTienThuongNV() << endl; 
			
			if (tinhTienPhatNVVP() != 0)
				cout << "Tien phat: " << tinhTienPhatNVVP() << endl;
			else
				cout << "Nhan vien khong bi phat" << endl;
			
			cout << "Tien tro cap: " << tinhTroCapNVVP() << endl;
		}
		void XuatNVVPFile() {
			NhanVien::XuatNVFile();
			f << "So ngay vang: " << soNgayVang << endl;
			f << "Tien luong: " << tinhLuongNVVP() << endl;
			f << "Tien thuong: " << tinhTienThuongNV() << endl;
			
			if (tinhTienPhatNVVP() != 0)
				f << "Tien phat: " << tinhTienPhatNVVP() << endl;
			else
				f << "Nhan vien khong bi phat" << endl;
			
			f << "Tien tro cap: " << tinhTroCapNVVP() << endl;
		}
};

int NhanVienVP::dinhMucVang = 7;
float NhanVienVP::donGiaPhat = 150;

// Khai bao lop nhan vien san xuat
class NhanVienSX:public NhanVien {
	int soSanPham;
	static int dinhMucSanPham;
	static int donGiaSanPham;
	public:
		void NhapNVSX() {
			NhanVien::NhapNV();
			cout << "So san pham: ";
			cin >> soSanPham;
		}
		void NhapNVSXFile() {
			string s;
			NhanVien::NhapNVFile();
			getline(fi, s); soSanPham = atoi(s.c_str());
		}
		float tinhTienThuongNVSX() {
			if(soSanPham > dinhMucSanPham)
				return (soSanPham - dinhMucSanPham) * donGiaSanPham * 0.03;
		}
		float tinhTroCapNVSX() {
			return soCon * 120000;
		}
		
		// Hoi cô có can thêm tinh tien thuong cua nhân viên vào nua hay không
		float tinhTienLuongNVSX() {
			return (soSanPham * donGiaSanPham) + tinhTienThuongNVSX();
//			return (soSanPham * donGiaSanPham) + tinhTienThuongNVSX() + tinhTienThuongNV();
		}
		void XuatNVSX() {
			NhanVien::XuatNV();
			cout << "So san pham" << setw(15) << "Tien thuong" << setw(15) << "Tien tro cap" << setw(15) << "Tien luong" << endl; 
			cout << soSanPham << setw(22) << tinhTienThuongNVSX() << setw(15) << tinhTroCapNVSX() << setw(15) << tinhTienLuongNVSX() << endl;
		}
		void XuatNVSXFile() {
			NhanVien::XuatNVFile();
			f <<"So san pham: "<< soSanPham << endl;
			f << "Tien thuong: " << tinhTienThuongNVSX() << endl;
			f << "Tien tro cap: " << tinhTroCapNVSX() << endl;
			f << "Tien luong: " << tinhTienLuongNVSX() << endl;
		}
};

int NhanVienSX::dinhMucSanPham = 10;
int NhanVienSX::donGiaSanPham = 2000;

bool returnToMenu();	// Ham quay lai menu de chon tiep
void showMenu();	// Ham hien thi menu
void menuOption();	// Ham hien thi menu de chon
void Color(WORD color);	// Ham set mau
void ResizeConsole(int width, int height);	// Ham set kich thuoc cho cua so console
void GotoXY(short x,short y);	// Ham di chuyen con tro toi vi tri can den
int delay(int);	// Ham delay

int main() {
	ResizeConsole(1000, 800);
	menuOption();
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

// Delay dung lai de xem
int delay(int s) {
	clock_t t;
   	t = clock() + s * CLOCKS_PER_SEC;
    while (clock() < t) {}
    	return 0;
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
	GotoXY(20, 0); Color(12);
	cout << "Nhap tuong ung voi 1, 2, 3, 4 | Chon 5 de thoat!" << endl;
	GotoXY(20, 1); Color(14);		
	cout << "1. (Muc 1)Nhap thong tin cua 1 nhan vien bat ky | Tinh va hien thi thong tin" << endl;
	GotoXY(20, 2); Color(10);
	cout << "2. (Muc 2)Nhap n nhan vien tu tap tin | Tinh tien luong tb cua nv van phong" << endl;
	GotoXY(20, 3); Color(15);
    cout << "3. Thoát" << endl;
    GotoXY(20, 4); Color(7);
	cout << "Enter:> ";
}

// Menu tuy chon
void menuOption() {
	vector <NhanVienVP> VP;
	vector <NhanVienSX> SX;
	NhanVienVP vp;
	NhanVienSX sx;
	int x, n;
	string s;
	
	float luongTB;
	int luong = 0;
	int loai, kiemTra, chon;
	
	do {
		showMenu();
		cin >> x;
		
		if (x < 1 || x > 4)
			cout << "Chon sai | Chon lai!" << endl;
			cout << "--------------------" << endl;
	} while(x < 1 || x > 4);
	
	switch(x) {
		case 1:
			do {
				system("cls");
				cout << "Nhap loai nhan vien" << endl;
				cout << "1. Nhan vien van phong" << endl;
				cout << "2. Nhan vien van san xuat" << endl;
				cout << "3. Tinh va hien thi thong tin" << endl;
				cout << "0. Quay tro lai menu chinh" << endl;
				cout << "Enter:> ";
				cin >> loai;
				
				if (loai == 1) {
					int luu1;
					vp.NhapNVVP();
					VP.push_back(vp);
					cout << "------------------------------------" << endl;
					do {
						cout << "Chon 1 de luu | Chon 2 de khong luu" << endl;
						cout << "Enter:> ";
						cin >> luu1;
						if (luu1 < 1 || luu1 > 2)
							cout << "Nhap lai" << endl;
					} while(luu1 < 1 || luu1 > 2);
					if (luu1 == 1) {
						f.open("du_lieu/out_nhan_vien_VP.txt", ios::out);
						
						for(int i = 0; i < VP.size(); i++) {
							f << "Nhan vien van phong "<< i + 1 << endl;
							VP[i].XuatNVVPFile();
							f << "-----------------------------------" << endl;
						}
						cout << "Luu thanh cong | Mo file de xem ket qua" << endl;
						delay(1);
						
						f.close();
					}
				} 
				if(loai == 2) {
					int luu2;
					sx.NhapNVSX();
					SX.push_back(sx);
					cout << "------------------------------------" << endl;
					do {
						cout << "Chon 1 de luu | Chon 2 de khong luu" << endl;
						cout << "Enter:> ";
						cin >> luu2;
						if (luu2 < 1 || luu2 > 2)
							cout << "Nhap lai" << endl;
					} while(luu2 < 1 || luu2 > 2);
					if (luu2 == 1) {
						f.open("du_lieu/out_nhan_vien_SX.txt", ios::out);
						
						for(int j = 0; j < SX.size(); j++) {
							f << "Nhan vien san xuat " << j + 1 << endl;
							SX[j].XuatNVSXFile();
							f << "----------------------------" << endl;
						}
						cout << "Luu thanh cong | Mo file de xem ket qua" << endl;
						
						f.close();
					}
				} 
				if (loai == 3) {
					for(int i = 0; i < VP.size(); i++) {
						cout << "----------------------------------------------------" << endl;
						cout<<"Nhan vien van phong "<< i + 1 << endl;
						VP[i].XuatNVVP();
					}
					
					for(int j = 0; j < SX.size(); j++) {
						cout << "----------------------------------------------------" << endl;
						cout << "Nhan vien san xuat " << j + 1 << endl;
						SX[j].XuatNVSX();
					}
					
					if(returnToMenu()) {
		                system("cls");
		                menuOption();
		            } else {
		                cout << "Exited!" << endl;
		            }
				}
				if (loai == 0) {
		            system("cls");
		            menuOption();
				}	
			} while(loai != 0);
			break;
		case 2:
			system("cls");
			getline(fi, s); n = atoi(s.c_str());
			for (int i = 0; i < n; i++) {
				getline(fi, s); loai = atoi(s.c_str());
				/* 1 la nhan vien van phong
				   2 la nhan vien san xuat
				*/
				if (loai == 1) {
					vp.NhapNVVPFile();
					VP.push_back(vp);
				} else {
					sx.NhapNVSXFile();
					SX.push_back(sx);
				}
			}
			
			for(int i = 0; i < VP.size(); i++) {
				cout<<"Nhan vien van phong "<< i + 1 << endl;
				VP[i].XuatNVVP();
				cout << "----------------------------------------------------" << endl;
			}
			
			for(int j = 0; j < SX.size(); j++) {
				cout << "Nhan vien san xuat " << j + 1 << endl;
				SX[j].XuatNVSX();
				cout << "----------------------------------------------------" << endl;
			}
			
			if (VP.size() != 0) {
				for(int i = 0; i < n; i++)
					luong += VP[i].tinhLuongNVVP();
				luongTB = 1.0 * luong / VP.size();
			} else 
				luongTB = 0;
			
			cout << "Tong luong nhan vien van phong: " << luong << endl;
			cout << "Luong trung binh cua nhan vien van phong: " << luongTB << endl;
			
			if(returnToMenu()) {
                system("cls");
                menuOption();
            } else {
                cout << "Exited!" << endl;
            }
			break;
		case 3:
			system("cls");
			cout << "Exited!";
			break;
		default:
			cout << "Nhap sai tuy chon | Nhap lai!";
			
			if(returnToMenu()) {
                system("cls");
                menuOption();
            } else {
                cout << "Exited!" << endl;
            }
			break;
	}
}
