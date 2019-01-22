#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <Windows.h>
using namespace std;

// Khai bao cau truc du lieu quan ly van ban
struct nut {
	char dong[50];
	nut *sau, *truoc;	// Da lien ket
};
typedef nut Node;
Node *dau, *dau1;

void khoiTao(Node *&dau);	// Ham khoi tao
void nhapVanBan(Node *&dau);	// Ham nhap van ban
void duyetVB(Node *dau);	// Ham duyet van ban
void inDongI(Node *dau, int i);	// Ham in dong thu i
void inDongIJ(Node *dau, int i, int j);	// Ham in dong thu i den thu j
void chenCuoi(Node *dau);	// Ham chen 1 dong vao cuoi van ban
void XoaDongI(Node *&dau, int i);	// Ham xoa dong i
void XoaDongIJ(Node *&dau, int i, int j);	// Ham xoa dong thu i den dong thu j
void ChepIJ(Node *dau, int i, int j, Node *&dau1);	// Ham chep tu dong i den dong j
void chenDongIJK(Node *&dau, int i, int j, int k);	// Ham chen tu dong i den dong j vao sau dong k
void Choise();	// Hàm chon chuc nang de thuc hien yêu cau bài toán
void GotoXY(short x,short y);	// Hàm dua con tro tro vi trí can xuat

// Dua con tro toi vi tri can
void GotoXY(short x,short y) {
    HANDLE hConsoleOutput;
    COORD Cursor_an_Pos = { x,y};
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput , Cursor_an_Pos);
}

// Khoi tao
void khoiTao(Node *&dau) {
	dau = NULL;
}

// Nhap van ban vao danh sach
void nhapVanBan(Node *&dau) {
	Node *p, *q;
	char tam[50];
	int i = 1;
	
	cout << "Nhap du lieu cho danh sach | Nhan Enter de dung" << endl;
	do {
		cout << "Nhap vao dong van ban thu " << i << ": ";
		fflush(stdin);
		gets(tam);
		i++;
		if (strlen(tam) != 0) {
			p = new Node;
			strcpy(p->dong, tam);
			p->sau = NULL;
			p->truoc = NULL;
			if (dau == NULL)
			 	dau = p;
			else {
			 	q->sau = p;
			 	p->truoc = q;
			}
			q = p;
		}
	} while(strlen(tam) != 0);
}

// Duyet van ban
void duyetVB(Node *dau) {
	if (dau != NULL) {
		cout << dau->dong << endl;
		duyetVB(dau->sau);
	}
}

// In dong thu i
void inDongI(Node *dau, int i) {
	Node *p;
	int dong = 1;
	p = dau;
	while (p->truoc != NULL && dong != i) {
		p = p->truoc;
		dong = dong + 1;
	}
	if (p != NULL) 
		cout << "Dong thu " << i << ": " << p->dong;
}

// In dong thu i den thu j
void inDongIJ(Node *dau, int i, int j) {
	Node *p, *q;
	
	if (j >= i) {	
		int dem = 1;
		p = dau;
		
		while ((p != NULL) && (dem != i)) {
			p = p->sau;
			dem = dem + 1;
		}
		if (p != NULL) {
			// p tro den dong i va dem = i
			if (i <= j) {
				q = p;
				while ((q != NULL) && (dem != j)) {
					q = q ->sau;
					dem = dem + 1;
				}
				if (q != NULL)
					while (p != q ->sau) {
						cout << p->dong << endl;
						p = p->sau;
					}
				else
					cout << "Gia tri j khong phu hop!";
			} else 
				cout << "Khong co doan can in!";
		}
	}
}

void chenCuoi(Node *dau){
	char tam[50];
	Node *p, *q;
	fflush(stdin);
	cout << "Nhap doan van ban can chen: ";
	gets(tam);
	
	while(dau != NULL){
		p = dau;
		dau = dau->sau;
	}
	q = new Node;
	strcpy(q->dong, tam);
	p->sau = q;
	q->truoc = p;
	q->sau = NULL;
}

// Xoa dong thu i
void XoaDongI(Node *&dau, int i) {
	Node *p, *q, *t;
	int dem = 1;
	p = dau;
	
	while ((p != NULL) && (dem < i)) {
		p = p->sau;
		dem = dem + 1;
	}
	if (p != NULL) {
		// Truong hop p = dau
		if (p == dau) {
			dau = dau->sau;
			dau->truoc == NULL;
			delete p;
		} else
			// Truong hop p = cuoi
			if (p->sau == NULL) {
				q = p->truoc;
				q->sau = NULL;
				delete p;
			} else {
				// Truong hop p o giua
				q = p->truoc;
				t = p->sau;
				q->sau = t;
				t->truoc = q;
				delete p;
			}
	}
}

// Xoa tu dong i den dong j
void XoaDongIJ(Node *&dau, int i, int j) {
	for (int k = i; k <= j; k++)
		XoaDongI(dau, i);
}

// Chep tu dong i den dong j
void ChepIJ(Node *dau, int i, int j, Node *&dau1) {
	int dem;
	Node *p, *q, *t, *l;
	if(j >= i) {
		// Tim i
		dem = 1;
		p = dau;
		while(p != NULL && dem != i) {
			p = p->sau;
			dem = dem + 1;
		}
		if(p != NULL) {
			// Tim j
			q = p;
			while(q != NULL && dem != j) {
				q = q->sau;
				dem = dem + 1;
			}
			// In ra dong i den dong j.
			if(q != NULL)
				while(p != q->sau) {
					t = new Node;
					strcpy(t->dong, p->dong);
					t->sau = NULL;
					t->truoc = NULL; 
					
					if (dau1 == NULL)
						dau1 = t;
					else {
					    l->sau = t;
					    t->truoc = l;
					}
					l = t;
					p = p->sau;
				}	
		}	
	}
}

// Chen dong i den dong j vào sau dong k
void chenDongIJK(Node *&dau, int i, int j, int k) {
	int m = 1;
	Node *p, *q, *t; // v, u, w
	p = dau;
	ChepIJ(dau, i , j, dau1);
	while(p != NULL && m!= k) {
		p = p->sau;
		m = m + 1;
	}
	if(p != NULL) {   
		// p tro den dong k
		q = dau1;
		while(q->sau != NULL)
		q = q->sau;
		
		// p la dong cuoi cua ds dau1
		t = p->sau;	// dong sau dong k
		p->sau = dau1;
		dau1->truoc = p;
		q->sau = t;
		t->truoc = q;
	}
}

// Quy lai menu de chon tiep
bool returnToMenu(){
	char rtnMenu;
	cout << "------------------------------" << endl;
    cout << "Enter z to return to the menu:> "; 
	cin >> rtnMenu;

    if (rtnMenu == 'z' || rtnMenu == 'Z') {
        return true;
    } return false;
}

// Hien thi menu nguoi chon
void showMenu() {
	cout << "\t\t\t\t1. Nhap van ban va hien thi" << endl;
	cout << "\t\t\t\t2. In ra dong van ban tu i -> j" << endl;
	cout << "\t\t\t\t3. Chen 1 dong vao cuoi van ban" << endl;
	cout << "\t\t\t\t4. Xoa tu dong i -> j" << endl;
	cout << "\t\t\t\t5. Chen dong i -> j vao sau dong k" << endl;
    cout << "\t\t\t\t6. Thoát" << endl;
	cout << "\t\t\t\tEnter:> ";
}

// Chon chuc nang de thu hien yeu cau
void Choise() {
	int x;
	int i, j, m, l, g, h, k;
	
	do {
		showMenu();
		cin >> x;
		if (x < 1 || x > 5)
			cout << "Chon sai | Chon lai!" << endl;
			cout << "--------------------" << endl;
	} while(x < 1 || x > 6);
	
	switch(x) {
		case 1:
			system("cls");
			// Nhap van ban va hien thien van ban da nhap
			nhapVanBan(dau);
			cout << "----------------" << endl;
			cout << "Van ban da nhap" << endl;
			duyetVB(dau);
			
			if (returnToMenu()) {
                system("cls");
                Choise();
            } else {
                cout << "Thoát!" << endl;
            }
			break;
		case 2:
			system("cls");
			cout << "Van ban da nhap" << endl;
			duyetVB(dau);
			cout << "-------------------------" << endl;
			cout << "Nhap dong i can hien thi: ";
			cin >> i;
			cout << "Nhap dong j can hien thi: ";
			cin >> j;
			cout << "--------------------------" << endl;
			// Hien thi van ban tu dong i den dong j
			cout << "Van ban tu dong thu i -> j" << endl;
			inDongIJ(dau, i, j);
			
			if (returnToMenu()) {
                system("cls");
                Choise();
            } else {
                cout << "Thoát!" << endl;
            }
			break;
		case 3:
			system("cls");
			cout << "Van ban da nhap" << endl;
			duyetVB(dau);
			// Chen vao cuoi va hien thi noi dung van ban
			cout << "---------------------------" << endl;
			chenCuoi(dau);
			cout << "-----------------------------" << endl;
			cout << "Noi dung van ban sau khi chen" << endl;
			duyetVB(dau);
			
			if (returnToMenu()) {
                system("cls");
                Choise();
            } else {
                cout << "Thoát!" << endl;
            }
			break;
		case 4:
			system("cls");
			cout << "Van ban truoc khi xoa" << endl;
			duyetVB(dau);
			cout << "---------------------" << endl;
			cout << "Nhap dong i can xoa: ";
			cin >> m;
			cout << "Nhap dong j can xoa: ";
			cin >> l;
			// Xoa va hien thi van ban sau khi xoa
			cout << "------------------------------------" << endl;
			cout << "Van ban sau khi xoa dong i -> dong j" << endl;
			XoaDongIJ(dau, m, l);
			duyetVB(dau);
			
			if (returnToMenu()) {
                system("cls");
                Choise();
            } else {
                cout << "Thoát!" << endl;
            }
			break;
		case 5:
			system("cls");
			cout << "Van ban da nhap" << endl;
			duyetVB(dau);
			cout << "----------------------" << endl;
			cout << "Nhap dong i can chep: ";
			cin >> g;
			cout << "Nhap dong j can chep: ";
			cin >> h;
			cout << "Nhap dong k can chen: ";
			cin >> k;
			// Chen dong i den dong i vao sau dong k
			cout << "----------------------------------------------------" << endl;
			cout << "Van ban sau khi chep dong i -> dong j vao sau dong k" << endl;
			chenDongIJK(dau, g, h, k);
			duyetVB(dau);
			
			if (returnToMenu()) {
                system("cls");
                Choise();
            } else {
                cout << "Thoát!" << endl;
            }
			break;
		case 6:
			system("cls");
			cout << "Thoát!" << endl;
			break;
		default: 
			cout << "Nhap sai | Nhap lai!";
			
			if(returnToMenu()) {
                system("cls");
                Choise();
            } else {
                cout << "Thoát!!!" << endl;
            }
			break;
	}
}

int main() {
	
	// Khoi tao van ban
	khoiTao(dau);
	
	Choise();
	
}
