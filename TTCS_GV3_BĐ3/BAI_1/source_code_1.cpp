#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

typedef struct {
	string name; 
	string phone; 
	string email; 
	string address; 
	string sex;
} CONTACT;

void addContact();
void showFileContact();
void editByName();
void deleteByPhone();
void searchByName();

// Them danh ba vao danh sach
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
	} while(s.compare(" ") != 0);
	cout << "Them thanh cong!";
	fo.close();
	ai.close();
}

// Hien thi danh sach danh ba
void showFileContact(){
	fstream fContact;
	string s;
	
	CONTACT co;
	fContact.open("du_lieu/danh_ba.txt", ios::in);
	
	getline(fContact, s);
	cout << "Danh sach danh ba:" << endl;
	
	do{
		co.name = s;
		getline(fContact, co.sex);
		getline(fContact, co.phone);
		getline(fContact, co.email);
		getline(fContact, co.address);
		cout << co.name << "\t" << co.sex << "\t" << co.phone << "\t" << co.email << "\t" << co.address << endl;
		getline(fContact, s);
	}while(s.compare("") != 0);
	fContact.close();
}

// Chinh su danh ba boi ten
void editByName(){
	CONTACT co;
	string x;
	string s;
	fstream fi;
	fstream eo;
	fstream ci;
	
	fi.open("du_lieu/danh_ba.txt", ios::in);
	eo.open("du_lieu/danh_ba_chinh_su.txt .txt", ios::out);
	ci.open("du_lieu/du_lieu_chinh_sua.txt", ios::in);
	
	cout << "Nhap ten lien lac muon chinh sua: ";
	
	getline(cin, x);
	fflush(stdin);
	getline(fi, s);
	do {
		co.name = s;
		if(x.compare(co.name) == 0) {
			for(int i = 1; i <= 4; i++)
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
	} while(s.compare("") != 0);
	cout << "Chinh sua thanh cong!" << endl;
	fi.close();
	eo.close();
	ci.close();
}

// Xoa danh ba boi ten
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
	
	do{
		co.name = s;
		if(x.compare(co.name) == 0)
			for(int i = 1; i <= 5; i++)
				getline(fi, s);
		else{
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
	}while(s.compare("") != 0);
	cout << "Xoa thanh cong!" << endl;
	fi.close();
	go.close();
}

// Tim kiem danh ba boi ten
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
		if(x.compare(co.name) == 0)
			cout << co.name << "\t" << co.sex << "\t" << co.phone << "\t" << co.email << "\t" << co.address << endl;
		getline(fi, s);
	}while(s.compare("") != 0);
	fi.close();
}

int main() {
	addContact();
	showFileContact();
	searchByName();
	editByName();
	deleteByPhone();
}
