#include "BanDoc.h"

#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

void BanDoc::nhap(const vector<BanDoc>& dsBanDoc) {
    while (true) {
        cout << "Nhap ma ban doc: ";
        cin >> maBD;

        bool trung = false;
        for (const auto& bd : dsBanDoc) {
            if (bd.getMaBD() == maBD) {
                trung = true;
                break;
            }
        }

        if (trung)
            cout << "Ma ban doc da ton tai! Vui long nhap ma khac.\n";
        else
            break;
    }

    cin.ignore();
    cout << "Nhap ho ten: ";
    getline(cin, hoTen);
    cout << "Nhap khoa: ";
    getline(cin, khoa);
    cout << "Nhap SDT: ";
    getline(cin, sdt);
}

void BanDoc::suaThongTin() {
    cin.ignore();
    cout << "\n--- Sua thong tin ban doc (Ma: " << maBD << ") ---\n";
    cout << "Ho ten moi (Enter bo qua): ";
    string tenMoi;
    getline(cin, tenMoi);
    if (!tenMoi.empty()) hoTen = tenMoi;

    cout << "Khoa moi (Enter bo qua): ";
    string khoaMoi;
    getline(cin, khoaMoi);
    if (!khoaMoi.empty()) khoa = khoaMoi;

    cout << "SDT moi (Enter bo qua): ";
    string sdtMoi;
    getline(cin, sdtMoi);
    if (!sdtMoi.empty()) sdt = sdtMoi;

    cout << "Da cap nhat.\n";
}

void BanDoc::hienThi() const {
    cout << left << setw(10) << maBD
         << setw(25) << hoTen
         << setw(15) << khoa
         << sdt << endl;
}
