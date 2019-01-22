#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;

fstream fi;
fstream go;

bool getAnswer(string a, string b); // Hàm kiểm tra kết quả
void saveScores(int scores);    // Hàm lưu điểm người thi
void openQuestion();    // Hàm mở câu hỏi bộ đề
void showScores();  // Hàm hiển thị điểm của người thi
void choiseThreads();   // Hàm chọn 1 bộ đề trong các bộ đề
bool returnToMenu();    // Hàm quay lại menu để chọn tiếp
void showMenu();    // Hàm hiển thị menu ra màn hình
void choiseQuestion();  // Hàm chọn bộ đề câu hỏi

// Chương trình chính
int main(){
	choiseQuestion();
}

// Kiếm tra kết quả
bool getAnswer(string a, string b){
	if (a.compare(b) == 0)
		return true;
	else
		return false;
}

// Lưu điểm | 5 diểm/câu hỏi
void saveScores(int scores) {
	int x;
	
	do {
		cout << "Enter 1 save scores / Enter 2 do not save scores" << endl << "Enter> ";
		cin >> x;
		if(x < 0 || x > 2)
			cout << "Reselect > " << endl;
	} while(x < 0 || x > 2);
	
    // Nếu người thi chọn lưu thì điều kiện mới thực hiện
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

// Mở câu hỏi trong bộ đề
void openQuestion() {
	string s;
	string x;
	int scores = 0;
	
	getline(fi, s);
	cout << s << endl;
	getline(fi, s);
	for (int i = atoi(s.c_str()); i > 0; i--){
		getline(fi, s);		// Câu hỏi
		cout << s << endl;
		getline(fi, s);		// Ðáp án A
		cout << s << endl;
		getline(fi, s);		// Ðáp án B 
		cout << s << endl;
		getline(fi, s);		// Ðáp án C 
		cout << s << endl;
		getline(fi, s);		// Ðáp án đúng
		cout << "Cau tra loi la: ";
		fflush(stdin);
		getline(cin, x);	// Ðáp án người thi 
		cout << endl;
		
        // Kiểm tra đáp án đúng với đáp án người thi rồi cộng điểm
		if (getAnswer(s, x) == true)
			scores += 5;
	}

	cout << "Hoan thanh bai kiem tra!" << endl << endl;
	cout << "Diem so la: " << scores << endl << endl;
	saveScores(scores);	
}

// Hiển thị điểm của người chơi trong file Luu_diem.txt
void showScores() {
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

// Quay lại menu để chọn tiếp
bool returnToMenu() {
	char rtnMenu;
	cout << "-----------------------------" << endl;
    cout << "Enter z to return to the menu:> "; 
	cin >> rtnMenu;

    if (rtnMenu == 'z' || rtnMenu == 'Z') {
        return true;
    } return false;
}

// Hiển thị menu chọn bộ đề, xem điểm người thi và thoát chương trình
void showMenu() {
	cout << "Nhap bo de tuong ung voi 1, 2, 3 | Chon 4 de xem diem da luu!" << endl;	
	cout << "1. Bo de 1" << endl;
	cout << "2. Bo de 2" << endl;
	cout << "3. Bo de 3" << endl;
	cout << "4. Xem diem" << endl;
    cout << "5. Thoat" << endl;
	cout << "Enter:> ";
}

// Chọn 1 bộ đề trong các bộ đề
void choiseQuestion() {
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
			openQuestion(); // Mở bộ đề số 1
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
			openQuestion(); // Mở bộ đề số 2
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
			openQuestion(); // Mở bộ đề số 3
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
			showScores();   // Hiển thị điểm tất cả người thi
			
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
