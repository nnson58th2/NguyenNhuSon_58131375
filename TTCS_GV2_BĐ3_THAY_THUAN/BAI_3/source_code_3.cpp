#include <iostream>
using namespace std;

struct AVL{
	int value;
	int bal;   // Yeu to can bang: -1 ,0 ,1 can bang; 2 lech ben trai; -2 lech ben phai
	AVL *left, *right;
};

AVL *goc;

void KhoiTao(AVL *&goc);   // H�m tao goc cho c�y AVL
void TaoCay(AVL *&goc, AVL *p);   // Ham tao dinh cua c�y AVL
void NhapNut(AVL *&goc);   // H�m nhap nut cho c�y AVL
void XuatCay(AVL *goc);   // H�m xuat c�y AVL
int ChieuCao(AVL *p);   // H�m x�c dinh chieu cao c�y tai 1 n�t do
void xoayTraiTrai(AVL *&p);   // H�m quay trai trai
void xoayTraPhai(AVL *&p);   // H�m quay trai phai 
void xoayPhaiPhai(AVL *&p);   // H�m quay phai phai
void xoayPhaiTrai(AVL *&p);   // H�m quay phai trai
void xuLyXoay(AVL *&p) ;   // h�m xu ly xoay
void nutCanBang(AVL *goc);   // H�m xac dinh yeu to c�n bang cua 1 n�t
void KiemTraCB(AVL *&goc);	// H�m kiem tra c�n bang

int main(){

	KhoiTao(goc);
	NhapNut(goc);
	cout << endl << "---Cay AVL sau khi can bang---" << endl;
	XuatCay(goc);
	
}

// Khoi tao
void KhoiTao(AVL *&goc) {
	goc = NULL;
}

// Tao cay
void TaoCay(AVL *&goc, AVL *p) {
	if (goc == NULL) {
		p->left = NULL;
		p->right = NULL;
		goc = p;
	} else {
		if(p->value <= goc->value)
			TaoCay(goc->left, p);
		else
			TaoCay(goc->right, p);
	}
}

// Nhap nut cho cay
void NhapNut(AVL *&goc){
	AVL *p;
	int i = 1;
	
	cout << "Nhap gia tri | Nhap 0 de ket thuc!!!" << endl;
	do {
		p = new AVL;
		cout << "Nhap gia tri " << i << ": ";
		cin >> p->value;
		if (p->value != 0) {
			TaoCay(goc, p);
			nutCanBang(goc);
			KiemTraCB(goc);
			nutCanBang(goc);
		}
		i++;
	} while(p->value != 0);
}

// Xuat cay
void XuatCay(AVL *goc) {
	if (goc != NULL) {
		XuatCay(goc->left);
		cout << goc->value << "," << goc->bal << "\t";
		XuatCay(goc->right);
	}
}

//Xac dinh chieu cao cua cay
int ChieuCao(AVL *p) {
	if (p == NULL)
		return 0;
	else
		return 1 + max(ChieuCao(p->left), ChieuCao(p->right));
}

// Xoay trai trai
void xoayTraiTrai(AVL *&p) {
	AVL *t, *l, *s;
	t = p;
	l = p->left;
	s = l->right;
	l->right = t;
	t->left = s;
	p = l;
}

// Xoay trai phai
void xoayTraiPhai(AVL *&p) {
	AVL *a, *b, *c ,*t, *s;
	a = p;
	b = p->left;
	c = b->right;
	t = c->left;
	s = c->right;
	b->right = t;
	c->left = b;
	a->left = s;
	c->right = a;
	p = c;
}

// Xoay phai phai
void xoayPhaiPhai(AVL *&p) {
	AVL *a, *b, *s;
	a = p;
	b = p->right;
	s = b->left;
	b->left = a;
	a->right = s;
	p = b;
}

// Xoay phai tr�i
void xoayPhaiTrai(AVL *&p) {
	AVL *a, *b, *c ,*t, *s;
	a = p;
	b = p->right;
	c = b->left;
	t = c->left;
	s = c->right;
	b->left = s;
	c->right = b;
	a->right = t;
	c->left = a;
	p = c;
}

// Xu l� xoay
void xuLyXoay(AVL *&p) {
	AVL *x;
	if(p != NULL){
		if(p->bal == 2){
			x = p->left;
			if(x->left != NULL)
				xoayTraiTrai(p);
			else
				xoayTraiPhai(p);
		}
		if(p->bal == -2){
			x = p->right;
			if(x->left != NULL)
				xoayPhaiTrai(p);
			else
				xoayPhaiPhai(p);
		}
	}
}

// Xac dinh yeu to can bang
void nutCanBang(AVL *goc) {
	if(goc != NULL){
		goc->bal = ChieuCao(goc->left) - ChieuCao(goc->right);
		nutCanBang(goc->left);
		nutCanBang(goc->right);
	}
}

// Kiem tra can bang cay
void KiemTraCB(AVL *&goc){
	AVL *t;
	if (goc->bal == 2) {
		t = goc->left;
		if (t->bal == 2)
			KiemTraCB(goc->left);
		else {
			t = goc;
			xuLyXoay(t);
			goc = t;
		}
	}
	else {
		if(goc->bal == -2){
			t = goc->right;
			if(t->bal == -2)
				KiemTraCB(goc->right);
			else {
				t = goc;
				xuLyXoay(t);
				goc = t;
			}
		}
	}
}
