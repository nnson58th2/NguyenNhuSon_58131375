#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;

fstream fi;
fstream go;

bool getAnswer(string a, string b);
void saveScores(int scores);
void openQuestion();
void showScores();
void choiseThreads();
int main();

// function check answer
bool getAnswer(string a, string b){
	if(a.compare(b) == 0)
		return true;
	else
		return false;
}

// function save scores | 5 scores/question
void saveScores(int scores){
	int x;
	
	do{
		cout << "Enter 1 save scores / Enter 2 do not save scores" << endl << "Enter> ";
		cin >> x;
		if(x < 0 || x > 2)
			cout << "Reselect > " << endl;
	} while(x < 0 || x > 2);
	
	if(x == 1){
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

// function open question in folder bo_de
void openQuestion(){
	string s;
	string x;
	int scores = 0;
	
	getline(fi, s);
	cout << s << endl;
	getline(fi, s);
	for(int i = atoi(s.c_str()); i > 0; i--){
		getline(fi, s);		// cau hoi
		cout << s << endl;
		getline(fi, s);		// dap an A 
		cout << s << endl;
		getline(fi, s);		// dap an B 
		cout << s << endl;
		getline(fi, s);		// dap an C 
		cout << s << endl;
		getline(fi, s);		// dap an dung
		cout << "Cau tra loi la: ";
		fflush(stdin);
		getline(cin, x);	// dap an nguoi thi 
		cout << endl;
		
		// kiem tra dap an dung voi dap an nguoi thi va cong diem
		if(getAnswer(s, x) == true)
			scores += 5;
	}
	cout << "Hoan thanh bai kiem tra!" << endl << endl;
	cout << "Diem so la: " << scores << endl << endl;
	saveScores(scores);	
}

// Show scores saved in luu_diem.txt
void showScores(){
	string s;
	go.open("du_lieu/diem/luu_diem.txt", ios::in);
	cout << "Diem nguoi choi la:" << endl;
	getline(go, s);
	do{
		cout << s << endl;
		getline(go, s);
	} while(s.compare("") != 0);
	go.close();
}

// Come back menu
bool returnToMenu(){
	char rtnMenu;
	cout << "-----------------------------" << endl;
    cout << "Enter z to return to the menu:> "; 
	cin >> rtnMenu;

    if(rtnMenu == 'z' || rtnMenu == 'Z') {
        return true;
    } return false;
}

void showMenu() {
	cout << "Nhap bo de tuong ung voi 1, 2, 3 | Chon 4 de xem diem da luu!" << endl;
	
	cout << "1. Bo de 1" << endl;
	cout << "2. Bo de 2" << endl;
	cout << "3. Bo de 3" << endl;
	cout << "4. Xem diem" << endl;
	cout << "Enter:> ";
}

// function choise 1 in the threads
void choiseThreads(){
	int x;
	
	do {
		showMenu();
		cin >> x;
		if(x < 1 || x > 4)
			cout << "Chon sai | Chon lai!" << endl;
			cout << "--------------------" << endl;
	} while(x < 1 || x > 4);
	
	switch(x) {
		case 1:
			fi.open("du_lieu/bo_de/de_1.txt", ios::in);
			openQuestion(); // mo de 1
			fi.close();
			
			if(returnToMenu()) {
                system("cls");
                showMenu();
            } else {
                cout << "Exited!" << endl;
            }
			break;
		case 2:
			fi.open("du_lieu/bo_de/de_2.txt", ios::in);
			openQuestion(); // mo de 2
			fi.close();
			break;
		case 3:
			fi.open("du_lieu/bo_de/de_3.txt", ios::in);
			openQuestion(); // mo de 3
			fi.close();
			break;
		case 4:
			showScores();
			break;
	}
}

int main(){
	choiseThreads();
}
