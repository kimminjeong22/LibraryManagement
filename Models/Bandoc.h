#ifndef BANDOC_H
#define BANDOC_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class BanDoc {
private:
    string maBD;
    string hoTen;
    string khoa;
    string sdt;

public:
    // Constructor
    BanDoc(string ma = "", string ten = "", string k = "", string soDT = "")
        : maBD(ma), hoTen(ten), khoa(k), sdt(soDT) {}

    // Getters
    string getMaBD() const { return maBD; }
    string getHoTen() const { return hoTen; }
    string getKhoa() const { return khoa; }  // ✅ ĐỔI TỪ "getLop()"
    string getSDT() const { return sdt; }

    // Setters
    void setMaBD(const string& ma) { maBD = ma; }
    void setHoTen(const string& ten) { hoTen = ten; }
    void setKhoa(const string& k) { khoa = k; }  // ✅ ĐỔI TỪ "setLop()"
    void setSDT(const string& soDT) { sdt = soDT; }

    // Các phương thức
    void nhap(const vector<BanDoc>& dsBanDoc);
    void suaThongTin();
    void hienThi() const;

};

// Các hàm tiện ích

#endif // BANDOC_H
