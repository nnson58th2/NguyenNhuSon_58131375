#include <iostream>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h> 
using namespace std;
    
// Khai b�o c?u tr�c ng�y th�ng
struct DATE {
    int day;
    int month;
    int year;
};
    
// G�n c?ng m?t m?ng gi� tr? th�ng tuong ?ng
int Month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
// H�m t?o ng�y th�ng du?c c?t t? chu?i nh?p v�o
void Create(DATE &d, string &st) {
    char c[4];
        
    c[0]= st[0];
    c[1] = st[1];
    d.day = atoi(c);    // L?y du?c 2 gi� tr? d?u ti�n c?a chu?i nh?p g�n cho ng�y (L?y gi� tr? 1 2)
        
    c[0]= st[3];
    c[1] = st[4];
    d.month = atoi(c);  // L?y du?c 2 gi� tr? ti?p theo c?a chu?i nh?p g�n cho th�ng (L?y gi� tr? 3 4)
        
    c[0] = st[6];
    c[1] = st[7];
    c[2] = st[8];
    c[3] = st[9];
    d.year = atoi(c);   // L?y du?c 4 gi� tr? cu?i c�ng c?a chu?i nh?p g�n cho nam (L?y gi� tr? 6 7 8 9)
}
    
// H�m in ng�y th�ng ra m�n h�nh
void printDate(int n, int sum){
    int i = 0;
    while(sum > Month[i]) {
        sum = sum - Month[i];
        i++;
    }
    cout << "Ngay " << sum << " thang " << i << " nam " << n << endl;
}
    
// H�m ki?m tra nam c� ph?i l� nhu?n hay kh�ng
int checkYear(DATE y) {
    if ((y.year % 4 == 0 && y.year % 100 != 0) || y.year % 400 == 0)
        return 1;
    return 0;
}
    
// H�m t�nh s? ng�y trong nam
int calculateDayInYear(DATE n) {
    int item = 0;
        
    for (int i = 0; i < n.month; i++)
        item += Month[i];
        item += n.day;
            
    if (checkYear(n) && n.month > 2)
        item++;
    return item;
}
    
// H�m c?ng ng�y th�ng
void addDate(DATE n, int tmp) {
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
    
// H�m tr? ng�y th�ng
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
    
// H�m ch�nh
int main() {
    DATE d;
    string st;
    int add, sub;
        
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
    cin >> add;
    cout << "----------------" << endl;
    cout << "Ngay thang sau khi cong: ";
    addDate(d, add); 
        
    cout << "----------------" << endl;
        
    cout << "Nhap so tru: ";
    cin >> sub;
    cout << "----------------" << endl;
    cout << "Ngay thang sau khi tru: ";
    subDate(d, sub);
        
    return 0;
}
