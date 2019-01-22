#include <iostream>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h> 
using namespace std;
    
// Khai báo cấu trúc ngày tháng
struct DATE {
    int day;
    int month;
    int year;
};

// Gán cứng một mảng giá trị tháng tương ứng    
int Month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

void Create(DATE &d, string &st);   // Hàm tạo ngày tháng được cắt từ chuổi nhập vào
void printDate(int n, int sum); // Hàm in ngày tháng ra màn hình console
int checkYear(DATE y);  // Hàm kiểm tra năm có phải là nhuận hay không
int calculateDayInYear(DATE n); // Hàm tính số ngày trong năm
void sumDate(DATE n, int tmp);  // Hàm cộng ngày tháng
void subDate(DATE n, int tmp);  // Hàm trừ ngày tháng

// Tạo ngày tháng được cắt từ chuổi nhập vào    
void Create(DATE &d, string &st) {
    char c[4];
        
    c[0]= st[0];
    c[1] = st[1];
    d.day = atoi(c);    // Lấy được 2 giá trá đầu tiên của chuỗi nhập gán cho ngày (Lấy giá trị 1 2)
        
    c[0]= st[3];
    c[1] = st[4];
    d.month = atoi(c);  // Lấy được 2 giá trị tiếp theo của chuỗi nhập gán cho tháng (Lấy giá trị 3 4)
        
    c[0] = st[6];
    c[1] = st[7];
    c[2] = st[8];
    c[3] = st[9];
    d.year = atoi(c);   // Lấy được 4 giá trị cuôii cùng của chuỗi nhập gán cho nam (Lấy giá trị 6 7 8 9)
}
    
// In ngày tháng ra màn hình
void printDate(int n, int sum) {
    int i = 0;
    while(sum > Month[i]) {
        sum = sum - Month[i];
        i++;
    }
    cout << "Ngay " << sum << " thang " << i << " nam " << n << endl;
}
    
// Kiểm tra năm có phải là nhuận hay không
int checkYear(DATE y) {
    if ((y.year % 4 == 0 && y.year % 100 != 0) || y.year % 400 == 0)
        return 1;
    return 0;
}
    
// Tính số ngày trong năm
int calculateDayInYear(DATE n) {
    int item = 0;
        
    for (int i = 0; i < n.month; i++)
        item += Month[i];
        item += n.day;
            
    if (checkYear(n) && n.month > 2)
        item++;
    return item;
}
    
// Cộng ngày tháng
void sumDate(DATE n, int tmp) {
    int res = 0;
    res = calculateDayInYear(n) + tmp;
        
    if(checkYear(n)) {
        if(res <= 366) {
            Month[2] = 29;
            printDate(n.year, res);
            Month[2] = 28;
        } else
            printDate(n.year + 1, res - 366);		
    } else {
        if(res <= 365)
            printDate(n.year, res);
        else {
            n.year++;
            if(checkYear(n)){
                Month[2] = 29;
                printDate(n.year, res - 365);
                Month[2] = 28;
            } else {
                printDate(n.year, res - 365);	
            }
        }
    }
}
    
// Trừ ngày tháng
void subDate(DATE n, int tmp) {
    int res = calculateDayInYear(n);
    if(res > tmp) {
        res = res - tmp;
        if(checkYear(n)) {
            Month[2] = 29;
            printDate(n.year, res);
            Month[2] = 28;
        } else {
            printDate(n.year, res);	
        }
    } else {
        if(checkYear(n)) {
            res = res - tmp + 366;
            n.year--;
            printDate(n.year, res);
        } else {
            res = res - tmp + 365;
            n.year--;
            if(checkYear(n)) {
                Month[2] = 29;
                printDate(n.year, res);
                Month[2] = 28;
            } else {
                printDate(n.year, res);
            }
        }
    }
}
    
// Chương trình chính
int main() {
    DATE d;
    string st;
    int sum, sub;
        
    cout << "Nhap chuoi ngay thang: ";
    getline(cin, st);
        
    Create(d, st);
        
    if(checkYear(d) == 1) 
        cout << d.year << " La nam nhuan!" << endl;
    else	
        cout << d.year << " La nam khong nhuan!"<< endl;
            
    cout << "----------------" << endl;
        
    cout << "STT ngay trong nam: " << calculateDayInYear(d) << endl;
        
    cout << "----------------" << endl;
        
    cout << "Nhap so cong: ";
    cin >> sum;
    cout << "----------------" << endl;
    cout << "Ngay thang sau khi cong: ";
    sumDate(d, sum); 
        
    cout << "----------------" << endl;
        
    cout << "Nhap so tru: ";
    cin >> sub;
    cout << "----------------" << endl;
    cout << "Ngay thang sau khi tru: ";
    subDate(d, sub);
        
    return 0;
}