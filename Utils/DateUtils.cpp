#include "DateUtils.h"
#include <sstream>
#include <iomanip>
#include <cmath>
#include <algorithm>

// Chuyển chuỗi thành chữ thường
string toLowerStr(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

// Hàm phụ: tách chuỗi ngày "dd/mm/yyyy" thành tm
tm parseDate(const string& dateStr) {
    tm date = {};
    char sep;
    stringstream ss(dateStr);
    ss >> date.tm_mday >> sep >> date.tm_mon >> sep >> date.tm_year;

    // Cấu trúc tm lưu tháng từ 0–11 và năm tính từ 1900
    date.tm_mon -= 1;
    date.tm_year -= 1900;
    date.tm_hour = 0;
    date.tm_min = 0;
    date.tm_sec = 0;

    return date;
}

// Chuyển chuỗi "dd/mm/yyyy" thành time_t
time_t stringToDate(const string& dateStr) {
    tm date = parseDate(dateStr);
    return mktime(&date);
}

// Tính số ngày giữa hai ngày
int tinhSoNgayGiua(const string& start, const string& end) {
    time_t t1 = stringToDate(start);
    time_t t2 = stringToDate(end);
    double diff = difftime(t2, t1) / (60 * 60 * 24);
    return static_cast<int>(round(diff));
}

// Tính phí phạt
int tinhPhiPhat(const string& ngayMuon, const string& ngayTra, int hanMuon, int phiMoiNgay) {
    int soNgay = tinhSoNgayGiua(ngayMuon, ngayTra);
    int tre = soNgay - hanMuon;
    return (tre > 0) ? tre * phiMoiNgay : 0;
}

// Lấy ngày hiện tại dạng "dd/mm/yyyy"
string layNgayHienTai() {
    time_t now = time(0);
    tm* local = localtime(&now);

    stringstream ss;
    ss << setw(2) << setfill('0') << local->tm_mday << "/"
       << setw(2) << setfill('0') << (local->tm_mon + 1) << "/"
       << (1900 + local->tm_year);

    return ss.str();
}

// Tính ngày trả dự kiến sau X ngày
string tinhNgayTraDuKien(int soNgay) {
    time_t now = time(0);
    now += soNgay * 24 * 60 * 60;
    tm* local = localtime(&now);

    stringstream ss;
    ss << setw(2) << setfill('0') << local->tm_mday << "/"
       << setw(2) << setfill('0') << (local->tm_mon + 1) << "/"
       << (1900 + local->tm_year);

    return ss.str();
}
