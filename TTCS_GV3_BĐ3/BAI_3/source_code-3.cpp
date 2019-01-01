#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;

fstream fi;
fstream go;

bool getAnswer(string a, string b); // H�m ki?m tra k?t qu?
void saveScores(int scores);    // H�m luu di?m ngu?i thi
void openQuestion();    // H�m m? c�u h?i b? d?
void showScores();  // H�m hi?n th? di?m c?a ngu?i thi
void choiseThreads();   // H�m ch?n 1 b? d? trong c�c b? d?
int main(); // H�m ch�nh

// H�m ki?m tra c�u h?i
bool getAnswer(string a, string b){
	if (a.compare(b) == 0)
		return true;
	else
		return false;
}

// H�m luu di?m | 5 di?m/c�u h?i
void saveScores(int scores){
	int x;
	
	do {
		cout << "Enter 1 save scores / Enter 2 do not save scores" << endl << "Enter> ";
		cin >> x;
		if(x < 0 || x > 2)
			cout << "Reselect > " << endl;
	} while(x < 0 || x > 2);
	
    // N?u ngu?i thi ch?n luu th� di?u ki?n m?i th?c hi?n
	if (x == 1){
		string s;
		cout << endl << "Enter name save scores: ";
		fflush(stdin);
		getline(cin, s);
		go.open("du_lieu/diem/luu_diem.txt", ios::out | ios::app);
		go << s << "\t" << scores << "\n";
		go.close();
		cout << "Save scores successfull!";
	}
}

// H�m m? c�u h?i trong b? d?
void openQuestion(){
	string s;
	string x;
	int scores = 0;
	
	getline(fi, s);
	cout << s << endl;
	getline(fi, s);
	for (int i = atoi(s.c_str()); i > 0; i--){
		getline(fi, s);		// C�u h?i
		cout << s << endl;
		getline(fi, s);		// ��p �n A
		cout << s << endl;
		getline(fi, s);		// ��p �n B 
		cout << s << endl;
		getline(fi, s);		// ��p �n C 
		cout << s << endl;
		getline(fi, s);		// ��p �n d�ng
		cout << "Cau tra loi la: ";
		fflush(stdin);
		getline(cin, x);	// ��p �n ngu?i thi 
		cout << endl;
		
        // Ki?m tra d�p �n d�ng v?i d�p �n ngu?i thi r?i c?ng di?m
		if (getAnswer(s, x) == true)
			scores += 5;
	}
	cout << "Hoan thanh bai kiem tra!" << endl << endl;
	cout << "Diem so la: " << scores << endl << endl;
	saveScores(scores);	
}

// Hi?n th? di?m c?a ngu?i choi trong file Luu_diem.txt
void showScores(){
	string s;
	go.open("du_lieu/diem/luu_diem.txt", ios::in);
	cout << "Diem nguoi choi la:" << endl;
	getline(go, s);
	do {
		cout << s << endl;
		getline(go, s);
	} while(s.compare("") != 0);
	go.close();
}

// Quay l?i menu d? ch?n ti?p
bool returnToMenu(){
	char rtnMenu;
	cout << "-----------------------------" << endl;
    cout << "Enter z to return to the menu:> "; 
	cin >> rtnMenu;

    if (rtnMenu == 'z' || rtnMenu == 'Z') {
        return true;
    } return false;
}

// Hi?n th? menu ch?n b? d? v� xem di?m ngu?i choi
void showMenu() {
	cout << "Nhap bo de tuong ung voi 1, 2, 3 | Chon 4 de xem diem da luu!" << endl;	
	cout << "1. Bo de 1" << endl;
	cout << "2. Bo de 2" << endl;
	cout << "3. Bo de 3" << endl;
	cout << "4. Xem diem" << endl;
    cout << "5. Tho�t" << endl;
	cout << "Enter:> ";
}

// Ch?n 1 b? d? trong c�c b? d?
void choiseQuestion(){
	int x;
	
	do {
		showMenu();
		cin >> x;
		if (x < 1 || x > 5)
			cout << "Chon sai | Chon lai!" << endl;
			cout << "--------------------" << endl;
	} while(x < 1 || x > 5);
	
	switch(x) {
		case 1:
			system("cls");
			fi.open("du_lieu/bo_de/de_1.txt", ios::in);
			openQuestion(); // M? b? d? 1
			fi.close();
			
			if (returnToMenu()) {
                system("cls");
                choiseQuestion();
            } else {
                cout << "Exited!" << endl;
            }
			break;
		case 2:
			system("cls");
			fi.open("du_lieu/bo_de/de_2.txt", ios::in);
			openQuestion(); // M? b? d? 2
			fi.close();
			
			if (returnToMenu()) {
                system("cls");
                choiseQuestion();
            } else {
                cout << "Exited!" << endl;
            }
			break;
		case 3:
			system("cls");
			fi.open("du_lieu/bo_de/de_3.txt", ios::in);
			openQuestion(); // M? b? d? 3
			fi.close();
			
			if (returnToMenu()) {
                system("cls");
                choiseQuestion();
            } else {
                cout << "Exited!" << endl;
            }
			break;
		case 4:
			system("cls");
			showScores();
			
			if (returnToMenu()) {
                system("cls");
                choiseQuestion();
            } else {
                cout << "Exited!" << endl;
            }
            
			break;
        case 5:
        	system("cls");
			cout << "Exited!" << endl;
			break;
        default: 
			cout << "Nhap sai de | Nhap lai!";
			
			if(returnToMenu()) {
                system("cls");
                choiseQuestion();
            } else {
                cout << "Exited!" << endl;
            }
			break;
	}
}

// H�m ch�nh
int main(){
	choiseQuestion();
}
