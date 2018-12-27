#include <iostream>
#include <fstream>

using namespace std;

// --- doc ma tran trong file ra mang 2 chieu ---
// Doc ma tran trong file ra mang
void readTheGraph(int a[6][6]){
	fstream fi;
	fi.open("du_lieu/do_thi.txt", ios::in);
	for(int i = 0; i < 6; i++)
		for(int j = 0; j < 6; j++)
			fi >> a[i][j];
	fi.close();
}

// --- test du lieu mang 2 chieu ---
// Xuat du lieu mang
void showTheGraph(int a[6][6]){
	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 6; j++)
			cout << a[i][j] << " ";
		cout << endl;
	}		
}

int main(){
	int a[6][6];
	
	readTheGraph(a);
	showTheGraph(a);
}
