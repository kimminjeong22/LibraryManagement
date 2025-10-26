#include "Book.h"
#include <iostream>
using namespace std;

// Constructors
Book::Book() {
    maSach = tenSach = tacGia = theLoai = "";
    namXuatBan = soLuong = 0;
}

Book::Book(string ma, string ten, string tg, string tl, int nam, int sl)
    : maSach(ma), tenSach(ten), tacGia(tg), theLoai(tl), namXuatBan(nam), soLuong(sl) {
}

// Getters
string Book::getMaSach() const { return maSach; }
string Book::getTenSach() const { return tenSach; }
string Book::getTacGia() const { return tacGia; }
string Book::getTheLoai() const { return theLoai; }
int Book::getNamXuatBan() const { return namXuatBan; }
int Book::getSoLuong() const { return soLuong; }

// Setters
void Book::setMaSach(const string& ma) { maSach = ma; }
void Book::setTenSach(const string& ten) { tenSach = ten; }
void Book::setTacGia(const string& tg) { tacGia = tg; }
void Book::setTheLoai(const string& tl) { theLoai = tl; }
void Book::setNamXuatBan(int nam) { namXuatBan = nam; }
void Book::setSoLuong(int sl) { soLuong = sl; }

// Các phương thức khác
void Book::nhap() {
    cout << "Nhap ma sach: "; getline(cin, maSach);
    cout << "Nhap ten sach: "; getline(cin, tenSach);
    cout << "Nhap tac gia: "; getline(cin, tacGia);
    cout << "Nhap the loai: "; getline(cin, theLoai);
    cout << "Nhap nam xuat ban: "; cin >> namXuatBan;
    cout << "Nhap so luong: "; cin >> soLuong;
    cin.ignore();
}

void Book::hienThi() const {
    cout << "Ma sach: " << maSach << " | "
         << "Ten sach: " << tenSach << " | "
         << "Tac gia: " << tacGia << " | "
         << "The loai: " << theLoai << " | "
         << "Nam XB: " << namXuatBan << " | "
         << "So luong: " << soLuong << endl;
}

void Book::suaThongTin() {
    cout << "Sua ten sach: "; getline(cin, tenSach);
    cout << "Sua tac gia: "; getline(cin, tacGia);
    cout << "Sua the loai: "; getline(cin, theLoai);
    cout << "Sua nam XB: "; cin >> namXuatBan;
    cout << "Sua so luong: "; cin >> soLuong;
    cin.ignore();
}
