#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>
using namespace std;

class Book {
private:
    string maSach;
    string tenSach;
    string tacGia;
    string theLoai;
    int namXuatBan;
    int soLuong;

public:
    // Constructors
    Book();
    Book(string ma, string ten, string tg, string tl, int nam, int sl);

    // Getters
    string getMaSach() const;
    string getTenSach() const;
    string getTacGia() const;
    string getTheLoai() const;
    int getNamXuatBan() const;
    int getSoLuong() const;

    // Setters
    void setMaSach(const string& ma);
    void setTenSach(const string& ten);
    void setTacGia(const string& tg);
    void setTheLoai(const string& tl);
    void setNamXuatBan(int nam);
    void setSoLuong(int sl);

    // Các phương thức khác
    void nhap();
    void hienThi() const;
    void suaThongTin();
};

#endif // BOOK_H
