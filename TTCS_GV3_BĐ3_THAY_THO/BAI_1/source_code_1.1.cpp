#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <string.h>
using namespace std;

fstream fi("dulieu/input.dat", ios::in | ios::binary);
fstream fo("dulieu/output.dat", ios::out | ios::binary );

// Khai báo kiểu dữ liệu cấu trúc danh bạ
typedef struct {
	char name[30]; 
	char phone[11]; 
	char email[30]; 
	char address[50]; 
	char sex[5];
} CONTACT;

vector <CONTACT> db;	// Khởi tạo 1 vector danh bạ và đặt tên là db

void readFileContact();	// Hàm đọc dữ liệu từ file
void writeFileContact();	// Hàm ghi dữ liệu vào file
void showContact();	// Hàm hiển thị danh bạ ra màn hình console
void addContact();	// Hàm thêm danh bạ từ bàn phím
void addContactC();	// Hàm thêm danh bạ sẵn
void editByPhone();	// Hàm chỉnh sửa danh bạ theo số điện thoại
void deleteByPhone();	// Hàm xóa danh bạ theo số điện thoại
void searchByName();	// Hàm tìm kiếm danh bạ theo tên
bool returnToMenu();	// Hàm quay lại menu để chọn
void showMenu();	// Hàm hiển thị menu
void menuOption();	// Hàm menu các tùy chọn

// Chương trình chính
//int main() {
//	readFileContact();	// Gọi hàm đọc dữ liệu từ file vào
//	addContact();	// Gọi hàm thêm danh bạ nhập từ bàn phím
//	addContactC();	// Gọi hàm thêm danh bạ cứng gán sẵn
//	showMenu();	// Gọi hàm hiển thị menu
//	menuOption();	// Gọi hàm tùy chọn menu
//	writeFileContact();	// Gọi hàm ghi dữ liệu vào file danh bạ
//}

// Chương trình chính
int main() {
	menuOption();	// Gọi hàm tùy chọn các menu chức năng
	return 0;
}

// Đọc dữ liệu từ file
void readFileContact() {
	CONTACT c;
	
	while(!fi.eof()) {
		fi.read(c.name, 30);
		fi.read(c.sex, 5);
		fi.read(c.phone, 10);
		fi.read(c.email, 30);
		fi.read(c.address, 50);
		
		db.push_back(c);
	}
	fi.close();
	db.pop_back();
}

// Ghi file .dat contact
void writeFileContact() {
	for (int i = 0; i < db.size(); i++) {
		fo.write(db[i].name, sizeof(db[i].name));
		fo.write(db[i].sex, sizeof(db[i].sex));
		fo.write(db[i].phone, sizeof(db[i].phone));
		fo.write(db[i].email, sizeof(db[i].email));
		fo.write(db[i].address, sizeof(db[i].address));	
	}
	fo.close(); 
}

// Hiển thị contact ra màn hình console
void showContact() {
	for (int i = 0; i < db.size(); i++) {
		cout << "----------------" << endl;
		cout << db[i].name << endl;
		cout << db[i].sex << endl;
		cout << db[i].phone << endl;
		cout << db[i].email << endl;
		cout << db[i].address << endl;
	}
}

// Thêm danh bạ từ bàn phím
void addContact() {
	CONTACT addNew;
	cout << "Add name: ";
	cin >> addNew.name;
	cout << "Add gender: ";
	cin >> addNew.sex;
	cout << "Add phone: ";
	cin >> addNew.phone;
	cout << "Add email: ";
	cin >> addNew.email;
	cout << "Add address: ";
	cin >> addNew.address;
	
	db.push_back(addNew);
}

// Thêm danh bạ sẵn
void addContactC() { 
	CONTACT c1;
	strcpy(c1.name, "Son");
	strcpy(c1.sex, "Nam");
	strcpy(c1.phone, "0985407705");
	strcpy(c1.email, "nhuson2306@gmail.com");
	strcpy(c1.address, "QuangTri");
	db.push_back(c1);
	
	CONTACT c2;
	strcpy(c2.name, "Suong");
	strcpy(c2.sex, "Nu");
	strcpy(c2.phone, "0336692745");
	strcpy(c2.email, "xuansuonga3@gmail.com");
	strcpy(c2.address, "CamLam");
	db.push_back(c2);
	
	CONTACT c3;
	strcpy(c3.name, "Vy");
	strcpy(c3.sex, "Nam");
	strcpy(c3.phone, "0384722549");
	strcpy(c3.email, "nguyentrieuvy@gmail.com");
	strcpy(c3.address, "CamRanh");
	db.push_back(c3);
}

// Chỉnh sửa danh bạ theo số điện thoại
void editByPhone() {
	CONTACT cEdit;
	
	int item;
	char ePhone[11];
	
	cout << "Enter the phone number to fix: ";
	cin >> ePhone;
	
	for (int i = 0; i < db.size(); i++) {
		if (strcmp(ePhone, db[i].phone) == 0) {
			item = i;
			db.erase(db.begin() + item);
			cout << "New name: ";
			cin >> cEdit.name;
			cout << "New sex: ";
			cin >> cEdit.sex;
			cout << "New phone: ";
			cin >> cEdit.phone;
			cout << "New email: ";
			cin >> cEdit.email;
			cout << "New address: ";
			cin >> cEdit.address;
			db.insert(db.begin() + item , cEdit);
		}
	}
}

// Xóa danh bạ theo số điện thoại
void deleteByPhone() {
	int item;
	char dePhone[11];
	
	cout << "Enter the phone to delete: ";
	cin >> dePhone;
	
	for (int i = 0; i < db.size(); i++) {
		if (strcmp(dePhone, db[i].phone) == 0) {
			item = i;
			db.erase(db.begin() + item);		
		}
	}
}

// Tìm kiếm danh bạ theo tên
void searchByName() {
	int item;
	char sName[20];	
	cout << "Enter name: ";
	cin >> sName;
	
	for (int i = 0; i < db.size(); i++) {
		if(strcmp(sName, db[i].name) == 0){
			item = i;
			cout << "----------------" << endl;
			cout << db[item].name << endl;
			cout << db[item].sex << endl;
			cout << db[item].phone << endl;
			cout << db[item].email << endl;
			cout << db[item].address << endl;
		}
		
	}
}

// Quay lai menu để chọn
bool returnToMenu() {
	char rtnMenu;
	cout << "-----------------------------" << endl;
    cout << "Enter z to return to the menu:> "; 
	cin >> rtnMenu;

    if(rtnMenu == 'z' || rtnMenu == 'Z') {
        return true;
    } return false;
}

// Hiển thị menu
void showMenu() {
	cout << "1. Add contact" << endl;
	cout << "2. Show contact" << endl;
	cout << "3. Edit contact" << endl;
	cout << "4. Delete contact" << endl;
	cout << "5. Find contact" << endl;
	cout << "6. Exit contact" << endl;
	cout << "Enter your choice:> ";
}

// Menu các tùy chọn
void menuOption() {
	int x;

	do {
		showMenu();
		cin >> x;
		if (x < 1 || x > 6)
			cout << "Choose wrong | choose again!" << endl;
			cout << "--------------------" << endl;
	} while(x < 1 || x > 6);
	
	switch(x) {
		case 1:
			system("cls");
			addContact();
			writeFileContact();
			cout << "Add contact successfully!" << endl;
			
			if(returnToMenu()) {
                system("cls");
                menuOption();
            } else {
                cout << "Exited!" << endl;
            }
			break;
		case 2: 
			system("cls");
			showContact();
			
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
			editByPhone();
			cout << "Edit successfully!" << endl;
			
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
			cout << "Delete successfully!" << endl;
			
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
			cout << "Choose wrong | choose again!";
			
			if(returnToMenu()) {
                system("cls");
                menuOption();
            } else {
                cout << "Exited!" << endl;
            }
			break;
	}
}
