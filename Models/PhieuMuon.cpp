#include "PhieuMuon.h"
#include <iostream>
#include <iomanip>
using namespace std;

// Constructors
PhieuMuon::PhieuMuon() {
    daTra = false;
}

PhieuMuon::PhieuMuon(string _maPhieu, string _maBD, string _maSach, string _ngayMuon) {
    maPhieu = _maPhieu;
    maBD = _maBD;
    maSach = _maSach;
    ngayMuon = _ngayMuon;
    ngayTra = "";
    daTra = false;
}

// Getters
string PhieuMuon::getMaPhieu() const { return maPhieu; }
string PhieuMuon::getMaBD() const { return maBD; }
string PhieuMuon::getMaSach() const { return maSach; }
string PhieuMuon::getNgayMuon() const { return ngayMuon; }
string PhieuMuon::getNgayTra() const { return ngayTra; }
bool PhieuMuon::getDaTra() const { return daTra; }

// Setters
void PhieuMuon::setMaPhieu(const string& _maPhieu) { maPhieu = _maPhieu; }
void PhieuMuon::setMaBD(const string& _maBD) { maBD = _maBD; }
void PhieuMuon::setMaSach(const string& _maSach) { maSach = _maSach; }
void PhieuMuon::setNgayMuon(const string& _ngayMuon) { ngayMuon = _ngayMuon; }
void PhieuMuon::setNgayTra(const string& _ngayTra) { ngayTra = _ngayTra; }
void PhieuMuon::setDaTra(bool _daTra) { daTra = _daTra; }

// Phương thức nghiệp vụ
void PhieuMuon::traSach(const string& _ngayTra) {
    ngayTra = _ngayTra;
    daTra = true;
}

void PhieuMuon::hienThi() const {
    cout << left << setw(10) << maPhieu
         << setw(10) << maBD
         << setw(10) << maSach
         << setw(15) << ngayMuon
         << setw(15) << (daTra ? ngayTra : "Chua tra")
         << setw(10) << (daTra ? "Da tra" : "Chua tra")
         << endl;
}
