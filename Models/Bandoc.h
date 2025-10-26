#ifndef BANDOC_H
#define BANDOC_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class BanDoc {
private:
    string maBD;
    string hoTen;
    string lop;
    string sdt;

public:
    // Constructor
    BanDoc(string ma = "", string ten = "", string l = "", string soDT = "")
        : maBD(ma), hoTen(ten), lop(l), sdt(soDT) {}

    // Getters
    string getMaBD() const { return maBD; }
    string getHoTen() const { return hoTen; }
    string getLop() const { return lop; }
    string getSDT() const { return sdt; }

    // Setters (THÊM MỚI - cần cho Qt)
    void setMaBD(const string& ma) { maBD = ma; }
    void setHoTen(const string& ten) { hoTen = ten; }
    void setLop(const string& l) { lop = l; }
    void setSDT(const string& soDT) { sdt = soDT; }

    // Các phương thức
    void nhap(const vector<BanDoc>& dsBanDoc);
    void suaThongTin();
    void hienThi() const;
};

// Các hàm tiện ích


#endif // BANDOC_H
