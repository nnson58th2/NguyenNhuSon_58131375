#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

// Khai báo c?u trúc danh b?
typedef struct {
	string name; 
	string phone; 
	string email; 
	string address; 
	string sex;
} CONTACT;

void addContact();  // Hàm thêm danh b?
void showFileContact(); // Hàm hi?n th? danh b?
void editByName();  // Hàm ch?nh s?a danh b? theo tên
void deleteByPhone();   // Hàm xóa danh b? theo s? di?n tho?i
void searchByName();    // Hàm tìm ki?m danh b? theo tên
bool returnToMenu();	// Hàm quay tr? l?i menu
void showMenu();	// Hàm hi?n th? menu
void menuOption();	// Hàm menu tùy ch?n

// Thêm danh b? vào danh sách
void addContact(){
	fstream fo;
	fstream ai;
	string s;
	
	fo.open("du_lieu/danh_ba.txt", ios::out | ios::app);
	ai.open("du_lieu/them_danh_ba.txt", ios::in);
	
	fflush(stdin);
	getline(ai, s);
	
	do {
		fo << s << endl;
		fflush(stdin);
		getline(ai, s);
	} while (s.compare("") != 0);
	fo << endl;
	cout << "Them thanh cong!" << endl;
	fo.close();
	ai.close();
}

// Hi?n th? danh sách danh b?
void showFileContact(){
	fstream fContact;
	string s;
	
	CONTACT co;
	fContact.open("du_lieu/danh_ba.txt", ios::in);
	
	getline(fContact, s);
	cout << "Danh sach danh ba:" << endl;
	
	do {
		co.name = s;
		getline(fContact, co.sex);
		getline(fContact, co.phone);
		getline(fContact, co.email);
		getline(fContact, co.address);
		cout << co.name << "\t" << co.sex << "\t" << co.phone << "\t" << co.email << "\t" << co.address << endl;
		getline(fContact, s);
	} while (s.compare("") != 0);
	fContact.close();
}

// Ch?nh s?a danh b? b?i tên
void editByName(){
	CONTACT co;
	string x, s;
	fstream fi;
	fstream eo;
	fstream ci;
	
	fi.open("du_lieu/danh_ba.txt", ios::in);
	eo.open("du_lieu/danh_ba_chinh_su.txt", ios::out);
	ci.open("du_lieu/du_lieu_chinh_sua.txt", ios::in);
	
	cout << "Nhap ten lien lac muon chinh sua: ";
	
	getline(cin, x);
	fflush(stdin);
	getline(fi, s);
	do {
		co.name = s;
		if (x.compare(co.name) == 0) {
			for (int i = 1; i <= 4; i++)
				getline(fi, s);
				fflush(stdin);
				getline(ci, s);
				eo << s << endl;
				fflush(stdin);
				getline(ci, s);
				eo << s << endl;
				fflush(stdin);
				getline(ci, s);
				eo << s << endl;
				fflush(stdin);
				getline(ci, s);
				eo << s << endl;
				fflush(stdin);
				getline(ci, s);
				eo << s << endl;
				fflush(stdin);	
		} else {
			eo << s << endl;
			fflush(stdin);
			getline(fi, s);
			eo << s << endl;
			fflush(stdin);
			getline(fi, s);
			eo << s << endl;
			fflush(stdin);
			getline(fi, s);
			eo << s << endl;
			fflush(stdin);
			getline(fi, s);
			eo << s << endl;
			fflush(stdin);
		}
		
		getline(fi, s);
	} while (s.compare("") != 0);
	cout << "Chinh sua thanh cong!" << endl;
	fi.close();
	eo.close();
	ci.close();
}

// Xóa danh b? b?i s? di?n tho?i
void deleteByPhone(){
	CONTACT co;
	string x;
	string s;
	fstream fi;
	fstream go;
	
	fi.open("du_lieu/danh_ba.txt", ios::in);
	go.open("du_lieu/danh_ba_xoa.txt", ios::out);
	
	cout << "Nhap ten lien lac muon xoa:  ";
	getline(cin, x);
	fflush(stdin);
	getline(fi, s);
	
	do {
		co.name = s;
		if (x.compare(co.name) == 0)
			for (int i = 1; i <= 5; i++)
				getline(fi, s);
		else {
			go << s << endl;
			fflush(stdin);
			getline(fi, s);
			go << s << endl;
			fflush(stdin);
			getline(fi, s);
			go << s << endl;
			fflush(stdin);
			getline(fi, s);
			go << s << endl;
			fflush(stdin);
			getline(fi, s);
			go << s << endl;
			fflush(stdin);
		}
		getline(fi, s);
	} while (s.compare("") != 0);
	cout << "Xoa thanh cong!" << endl;
	fi.close();
	go.close();
}

// Tìm ki?m danh b? b?i tên
void searchByName(){
	CONTACT co;
	string x;
	string s;
	fstream fi;
	
	fi.open("du_lie/danh_ba.txt", ios::in);
	cout << "Nhap ten muon tim kiem: ";
	getline(cin, x);
	fflush(stdin);
	getline(fi, s);
	
	do {
		co.name = s;
		getline(fi, co.sex);
		getline(fi, co.phone);
		getline(fi, co.email);
		getline(fi, co.address);
		if (x.compare(co.name) == 0)
			cout << co.name << "\t" << co.sex << "\t" << co.phone << "\t" << co.email << "\t" << co.address << endl;
		getline(fi, s);
	} while (s.compare("") != 0);
	fi.close();
}

bool returnToMenu() {
	char rtnMenu;
	cout << "-----------------------------" << endl;
    cout << "Enter z to return to the menu:> "; 
	cin >> rtnMenu;

    if(rtnMenu == 'z' || rtnMenu == 'Z') {
        return true;
    } return false;
}

void showMenu() {
	cout << "1. Add contact" << endl;
	cout << "2. Show contact" << endl;
	cout << "3. Edit contact" << endl;
	cout << "4. Delete contact" << endl;
	cout << "5. Find contact" << endl;
	cout << "6. Exit contact" << endl;
	cout << "Enter your choice:> ";
}

void menuOption() {
	int x;
	
	do {
		showMenu();
		cin >> x;
		if (x < 1 || x > 6)
			cout << "Chon sai | Chon lai!" << endl;
			cout << "--------------------" << endl;
	} while(x < 1 || x > 6);
	
	switch(x) {
		case 1:
			system("cls");
			addContact();
			
			if(returnToMenu()) {
                system("cls");
                menuOption();
            } else {
                cout << "Exited!" << endl;
            }
			break;
		case 2: 
			system("cls");
			showFileContact();
			
			if(returnToMenu()) {
                system("cls");
                menuOption();
            } else {
                cout << "Exited!" << endl;
            }
			break;
		case 3: 
			system("cls");
			cout << "------ Edit ------" << endl;
			editByName();
			
			if(returnToMenu()) {
                system("cls");
                menuOption();
            } else {
                cout << "Exited!" << endl;
            }
			break;
		case 4: 
			system("cls");
			cout << "------ Delete ------" << endl;
			deleteByPhone();
			
			if(returnToMenu()) {
                system("cls");
                menuOption();
            } else {
                cout << "Exited!" << endl;
            }
			break;
		case 5: 
			system("cls");
			cout << "------ Search ------" << endl;
			searchByName();
			
			if(returnToMenu()) {
                system("cls");
                menuOption();
            } else {
                cout << "Exited!" << endl;
            }
			break;
		case 6: 
			cout << "Exited!" << endl;
            break;
		default:
            system("cls");
            showMenu();
            cout << "Wrong option!" << endl;
            menuOption();
	}
}

int main() {
	menuOption();
}
