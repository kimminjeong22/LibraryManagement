#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

// ==================== BOOK ====================
vector<Book> docSachTuFile(const string& tenFile) {
    vector<Book> ds;
    ifstream fin(tenFile);
    if (!fin.is_open()) {
        cout << "Khong mo duoc file: " << tenFile << endl;
        return ds;
    }

    string line;
    // Bỏ qua 2 dòng đầu (header và dòng gạch ngang)
    getline(fin, line);
    getline(fin, line);

    while (getline(fin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string ma, ten, tg, tl;
        int nam, sl;

        getline(ss, ma, '|');
        getline(ss, ten, '|');
        getline(ss, tg, '|');
        getline(ss, tl, '|');
        ss >> nam;
        ss.ignore(1); // bỏ dấu |
        ss >> sl;

        // Trim khoảng trắng
        ma.erase(0, ma.find_first_not_of(" \t"));
        ma.erase(ma.find_last_not_of(" \t") + 1);
        ten.erase(0, ten.find_first_not_of(" \t"));
        ten.erase(ten.find_last_not_of(" \t") + 1);
        tg.erase(0, tg.find_first_not_of(" \t"));
        tg.erase(tg.find_last_not_of(" \t") + 1);
        tl.erase(0, tl.find_first_not_of(" \t"));
        tl.erase(tl.find_last_not_of(" \t") + 1);

        ds.emplace_back(ma, ten, tg, tl, nam, sl);
    }

    fin.close();
    return ds;
}

void luuSachVaoFile(const vector<Book>& ds, const string& tenFile) {
    ofstream fout(tenFile);
    if (!fout.is_open()) {
        cout << "Khong mo duoc file de ghi: " << tenFile << endl;
        return;
    }

    // Ghi header
    fout << "Ma sach | Ten sach                                | Tac gia                      | Nha xuat ban      | Nam xuat ban | So luong\n";
    fout << "-------|------------------------------------------|------------------------------|-------------------|--------------|----------\n";

    for (const auto& b : ds) {
        fout << b.getMaSach() << "|"
             << b.getTenSach() << "|"
             << b.getTacGia() << "|"
             << b.getTheLoai() << "|"
             << b.getNamXuatBan() << "|"
             << b.getSoLuong() << endl;
    }

    fout.close();
}

// ==================== BAN DOC ====================
vector<BanDoc> docBanDocTuFile(const string& tenFile) {
    vector<BanDoc> ds;
    ifstream file(tenFile);
    if (!file.is_open()) {
        cout << "Khong the mo file: " << tenFile << endl;
        return ds;
    }

    string line, ma, ten, lop, sdt;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        getline(ss, ma, '|');
        getline(ss, ten, '|');
        getline(ss, lop, '|');
        getline(ss, sdt);
        ds.emplace_back(ma, ten, lop, sdt);
    }

    file.close();
    return ds;
}

void luuBanDocVaoFile(const vector<BanDoc>& ds, const string& tenFile) {
    ofstream file(tenFile);
    if (!file.is_open()) {
        cout << "Khong the mo file de ghi: " << tenFile << endl;
        return;
    }

    for (const auto& bd : ds) {
        file << bd.getMaBD() << "|"
             << bd.getHoTen() << "|"
             << bd.getLop() << "|"
             << bd.getSDT() << "\n";
    }

    file.close();
}

// ==================== PHIEU MUON ====================
vector<PhieuMuon> docPhieuMuonTuFile(const string& tenFile) {
    vector<PhieuMuon> ds;
    ifstream file(tenFile);
    if (!file.is_open()) {
        cout << "Khong the mo file: " << tenFile << endl;
        return ds;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string maPhieu, maBD, maSach, ngayMuon, ngayTra;
        int daTra;

        getline(ss, maPhieu, '|');
        getline(ss, maBD, '|');
        getline(ss, maSach, '|');
        getline(ss, ngayMuon, '|');
        getline(ss, ngayTra, '|');
        ss >> daTra;

        PhieuMuon pm(maPhieu, maBD, maSach, ngayMuon);
        if (daTra) {
            pm.traSach(ngayTra);
        }
        ds.push_back(pm);
    }

    file.close();
    return ds;
}

void luuPhieuMuonVaoFile(const vector<PhieuMuon>& ds, const string& tenFile) {
    ofstream file(tenFile);
    if (!file.is_open()) {
        cout << "Khong the mo file de ghi: " << tenFile << endl;
        return;
    }

    for (const auto& pm : ds) {
        file << pm.getMaPhieu() << "|"
             << pm.getMaBD() << "|"
             << pm.getMaSach() << "|"
             << pm.getNgayMuon() << "|"
             << pm.getNgayTra() << "|"
             << (pm.getDaTra() ? 1 : 0) << "\n";
    }

    file.close();
}
