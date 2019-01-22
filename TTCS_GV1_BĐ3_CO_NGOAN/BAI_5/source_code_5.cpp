#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
using namespace std;

fstream f;

// Ve hinh chu nhat
void veHCN(int x1, int y1, int x2, int y2) {
    line(x1, y1, x1, y2);
    line(x1, y1, x2, y1);
    line(x2, y2, x2, y1);
    line(x2, y2, x1, y2);
    setfillstyle(1, 1);
    bar(x1, y1, x2, y2);
    setbkcolor(1);
    setcolor(15);
}

// In ky tu ra man hinh
void inKyTu(int &x, int y, char c[80], int color) {
	settextstyle(3, HORIZ_DIR, 2);
	outtextxy(x, y, c);
	setcolor(color);
}

main() {	
	int i = 74;
   	char file[80];
//	char *file;
   	char c[0];
   	char k;
   	int vkey;
	
    initwindow(840, 125);
    veHCN(70, 70, 760, 30);
    settextstyle(8, HORIZ_DIR, 2);
//    f.open("text.txt", ios::in);
//    	f >> file;
////		fgets(f, file);
//    	outtextxy(i, 46, file);
//    f.close();
//    getch();
    while (1) {	
    	// Nhap tu ban phim va bat len console
        k = getch();
        c[0] = k;
        vkey = k;
        
        // Nhan nut Esc thoát chuong trinh
        if (vkey == 27)
    		break;
    	if (vkey == 8){
    		i = i - 10;
    		c[0] = '_';
    		outtextxy(i, 38, c);
		}
		if (vkey == KEY_HOME) {
//			inKyTu(82, 38, "_", 15);
//			inKyTu(i, 38, "", 1);
			outtextxy(82, 38, "_");
			outtextxy(i, 38, "");
		}
		if (vkey == KEY_END) {
			outtextxy(i, 38, "_");
			outtextxy(82, 38, "");
		}
		else {  
			i = i + 10;
	    	outtextxy(i, 38, c);
			outtextxy(i + 10, 38, "_");
		}
    	cout << c;
    	fflush(stdin);
    }
    return 0;
}
