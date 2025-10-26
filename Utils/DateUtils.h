#ifndef DATEUTILS_H
#define DATEUTILS_H

#include <string>
#include <ctime>
using namespace std;

// Chuyển chuỗi thành chữ thường
string toLowerStr(string s);

// Chuyển chuỗi "dd/mm/yyyy" thành time_t
time_t stringToDate(const string& dateStr);

// Tính số ngày giữa hai ngày
int tinhSoNgayGiua(const string& start, const string& end);

// Tính phí phạt (hanMuon mặc định 7 ngày, phiMoiNgay mặc định 5000đ)
int tinhPhiPhat(const string& ngayMuon, const string& ngayTra, int hanMuon = 7, int phiMoiNgay = 5000);

// Lấy ngày hiện tại dạng "dd/mm/yyyy"
string layNgayHienTai();

// Tính ngày trả dự kiến sau X ngày
string tinhNgayTraDuKien(int soNgay);

#endif // DATEUTILS_H
