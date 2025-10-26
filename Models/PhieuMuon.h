#ifndef PHIEUMUON_H
#define PHIEUMUON_H

#include <iostream>
#include <string>
using namespace std;

class PhieuMuon {
private:
    string maPhieu;
    string maBD;
    string maSach;
    string ngayMuon;
    string ngayTra;
    bool daTra;

public:
    // Constructors
    PhieuMuon();
    PhieuMuon(string _maPhieu, string _maBD, string _maSach, string _ngayMuon);

    // Getters
    string getMaPhieu() const;
    string getMaBD() const;
    string getMaSach() const;
    string getNgayMuon() const;
    string getNgayTra() const;
    bool getDaTra() const;

    // Setters
    void setMaPhieu(const string& _maPhieu);
    void setMaBD(const string& _maBD);
    void setMaSach(const string& _maSach);
    void setNgayMuon(const string& _ngayMuon);
    void setNgayTra(const string& _ngayTra);
    void setDaTra(bool _daTra);

    // Phương thức nghiệp vụ
    void traSach(const string& _ngayTra);
    void hienThi() const;
};

#endif // PHIEUMUON_H
