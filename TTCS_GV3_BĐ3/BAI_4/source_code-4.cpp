#include <iostream>
#include <fstream>

using namespace std;

struct saveVariable {
	int name;
	int sum;
	int flag;
};

fstream fi;
int n;

void ImportTheGraph(int a[10][10], int &n) {
	cout << "Nhap so dinh: ";
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << "Nhap A[" << i << "][" << j << "]: ";
			cin >> a[i][j];
		}
	}
}

// Ghi ma tran vao trong file
void writeTheGraph(int a[10][10], int &n){
	fi.open("du_lieu/do_thi.txt", ios::out);
	fi << n;
	fi << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			fi << a[i][j] << " ";
		fi << endl;
	}
	fi.close();
}

// Doc ma tran trong file ra mang
void readTheGraph(int a[10][10], int &n){
	fi.open("du_lieu/do_thi.txt", ios::in);
	fi >> n;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			fi >> a[i][j];
	fi.close();
}

// Xuat du lieu mang
void showTheGraph(int a[10][10]){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++)
			cout << a[i][j] << " ";
		cout << endl;
	}		
}

int Dijkstra(int a[10][10], int n) {
	saveVariable vc[n];
	saveVariable vp;
	
	vp.flag = 0;
	
	// Khoi tao hang dau tien
	for (int i = 0; i < n; i++) {
		vc[i].name = 0;
		vc[i].sum = 0;
		vc[i].flag = 0;
	}
	
	int itemS = 0;	// Vi tri bat dau la 0
	int itemE = n - 1;	// Vi tri ket thu la so diem - 1
	int i = itemS;	// Doc ma tran tu hang dau tien - Vi tri bat dau
	
	// Bat co, danh dau vi tri ban dau
	vc[itemS].flag = 1;
	
	do {
		for (int j = 0; j < n; j++) {
			// Gan cho bien phu cai ten va gia tri tong
			if (a[i][j] != 0) {
				vp.name = itemS;
				vp.sum = a[i][j] + vc[itemS].sum;
			} else {
				// Xu ly gia tri cua ma tran tai hang i cot j khi bang 0
				vp.name = 0;
				vp.sum = 0;
			}
			Compare(vc[j], vp);
			
			// Xuat ra qua trinh thay doi gia tri cua mang vc 
			for (int k = 0; k < n; k++) {\
				cout << vc[k].name << "," << vc[k].sum << "/t";
			}
			cout << endl;
			
			// Danh dau lai vi tri da di qua
			Browser(vc, itemS);
			
			i = itemS; // Chi so den hang tiep theo de doc tiep ma tran
		}
	} while(itemS != itemE);
	
	// Hien thi ra lo trinh duong di
	Router(vc, itemS, itemE);
}

int main(){
	int a[10][10];
	
//	ImportTheGraph(a, n);
//	writeTheGraph(a, n);

	readTheGraph(a, n);
	showTheGraph(a);
	
	cout << "--------------------";
	
	Dijkstra(a, n);
}
