#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

// Khai báo dữ liệu cấu trúc lưu biến
struct saveVariable {
	int name;   // Tên
	int sum;    // Tổng
	int flag;   // Cái cờ (đánh dấu)
};

void ImportTheGraph(int a[10][10], int &n);  // Hàm nhập đồ thi ma trận từ bàn phím
void writeTheGraph(int a[10][10], int &n);   // Hàm xuất đồ thị ma trận ra file
void readTheGraph(int a[10][10], int &n);    // Hàm đọc đồ thị ma trận từ file
void showTheGraph(int a[10][10], int n);    // Hàm hiển thị đồ thị ma trận
void Compare(saveVariable &vc, saveVariable &vp); // Hàm so sánh kiểm tra biến
void Browser(saveVariable vc[10], int &index, int n);   // Hàm duyệt ma trận chọn diểm có tổng nhỏ nhất
void Router(saveVariable a[10], int x, int y); // Hàm hiển thị ra đường đi ngắn nhất từ mảng ma trận
void findTheWay(int a[10][10], int n);  // Hàm tìm đường đi ngắn nhất

fstream fi;

// Chương trình chính
int main(){
	int a[10][10];
    int n;
	
//	ImportTheGraph(a, n);
//	writeTheGraph(a, n);

	readTheGraph(a, n);
	showTheGraph(a, n);
	cout << "------------" << endl;
	findTheWay(a, n);
}

// Nhập đồ thị ma trận từ bàn phím
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

// Ghi ma trận vào trong file
void writeTheGraph(int a[10][10], int &n) {
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

// Đọc ma trận trong file ra mảng
void readTheGraph(int a[10][10], int &n) {
	fi.open("du_lieu/do_thi.txt", ios::in);
	fi >> n;

	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			fi >> a[i][j];
	fi.close();
}

// Xuất mảng ma trận ra màn hình
void showTheGraph(int a[10][10], int n) {
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++)
			cout << a[i][j] << " ";
		cout << endl;
	}		
}

// Hàm kiểm tra (so sánh) điều kiện - gán biến phụ cho biến chính 
void Compare(saveVariable &vc, saveVariable &vp) {
	if (vc.flag != 1) {
		if (vc.sum == 0) {
			vc.name = vp.name;
			vc.sum = vp.sum;
		} else {
			if (vp.sum != 0 && vc.sum > vp.sum) {
				vc.name = vp.name;
				vc.sum = vp.sum;
			}
		}
	}
}

// Chọn điểm có tổng nhỏ nhất và dựng cờ lên
void Browser(saveVariable vc[10], int &index, int n) {
	int print = 1000;
	
	for (int i = 0; i < n; i++) {	
		if (vc[i].flag != 1 && vc[i].sum != 0) {
			if (vc[i].sum < print) {
				index = i;
				print = vc[i].sum;
			}
		}
	}
	vc[index].flag = 1;	// Trả về giá trị hàng cho lần duyệt ma trận tiếp theo
}

// Hiển thi ra lộ trình đường đi ngắn nhất từ mảng ma trận (saveVariable)
void Router(saveVariable a[10], int x, int y){
	cout << "Do dai duong di ngan nhat: " << a[y].sum << endl;
	cout << "lo trinh:  " << y;
	
	while(y != x){
		y = a[y].name;
		cout << " <-- " << y;
	}
}

// Tìm đường đi ngắn nhất
void findTheWay(int a[10][10], int n) {
	saveVariable vc[n];
	saveVariable vp;
	
    int start, end;
    
    vp.flag = 0;    // Cờ nằm
	
    // Khởi tạo cho hàng đầu tiên
	for (int i = 0; i < n; i++) {
		vc[i].name = 0;
		vc[i].sum = 0;
		vc[i].flag = 0;
	}
	
	cout << "Nhap diem bat dau di: ";
    cin >> start;
    cout << "Nhap diem ket thuc di: ";
    cin >> end;
    cout << "--------------------------" << endl;
	cout << "Qua trinh thay doi gia tri" << endl;
	
	int itemS = start;	// Vị trí bắt đầu
	int itemE = end;	// Vị trí kết thúc
	int i = itemS;	// Đọc ma trận từ hàng đầu (itemS) - Vị trí bắt đầu tìm đường
	
    // Bật cờ, đánh dấu vị trí ban đầu
	vc[itemS].flag = 1;
	
	do {
		for (int j = 0; j < n; j++) {
            // Gán cho biến phụ cái tên và giá trị tổng cho nó
			if (a[i][j] != 0) {
				vp.name = itemS;
				vp.sum = a[i][j] + vc[itemS].sum;
			} else {
                // Xử lý giá trị của ma trận tại hàng i cột j khi giá trị bằng 0
				vp.name = 0;
				vp.sum = 0;
			}
            Compare(vc[j], vp);
        }
        // Xuất ra quá trình thay đổi giá trị của mảng vc 
        for (int k = 0; k < n; k++) {
            cout << vc[k].name << "," << vc[k].sum << "\t";
        }
        cout << endl;
        
        // Đánh dấu lại vị trí đã đi qua
        Browser(vc, itemS, n);
        
        i = itemS; // Đưa i đến hàng tiếp theo để đọc tiếp ma trận
	} while(itemS != itemE);
	
	cout << "--------------------------------------------" << endl;

    // Hiển thị ra lộ trình đường đi
	Router(vc, start, end);
}