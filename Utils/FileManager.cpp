#include "FileManager.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <QDebug>  // ✅ THÊM DÒNG NÀY

using namespace std;

// ==================== BOOK ====================

vector<Book> docSachTuFile(const string& tenFile) {
    vector<Book> ds;
    qDebug() << "[SACH] Đang mở file:" << QString::fromStdString(tenFile);

    ifstream fin(tenFile);
    if (!fin.is_open()) {
        qWarning() << "[SACH] KHÔNG MỞ ĐƯỢC FILE:" << QString::fromStdString(tenFile);
        return ds;
    }

    qDebug() << "[SACH] Đã mở file thành công!";

    string line;
    // Bỏ qua 2 dòng đầu (header và dòng gạch ngang)
    getline(fin, line);
    qDebug() << "[SACH] Header:" << QString::fromStdString(line);
    getline(fin, line);

    int lineNum = 2;
    while (getline(fin, line)) {
        lineNum++;
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
        ma.erase(0, ma.find_first_not_of(" \t\r\n"));
        ma.erase(ma.find_last_not_of(" \t\r\n") + 1);
        ten.erase(0, ten.find_first_not_of(" \t\r\n"));
        ten.erase(ten.find_last_not_of(" \t\r\n") + 1);
        tg.erase(0, tg.find_first_not_of(" \t\r\n"));
        tg.erase(tg.find_last_not_of(" \t\r\n") + 1);
        tl.erase(0, tl.find_first_not_of(" \t\r\n"));
        tl.erase(tl.find_last_not_of(" \t\r\n") + 1);

        if (!ma.empty()) {
            ds.emplace_back(ma, ten, tg, tl, nam, sl);
        }
    }

    fin.close();
    qDebug() << "[SACH] ✓ Đã đọc" << ds.size() << "sách từ" << lineNum << "dòng";
    return ds;
}

void luuSachVaoFile(const vector<Book>& ds, const string& tenFile) {
    qDebug() << "[SACH] Đang lưu" << ds.size() << "sách vào file...";

    ofstream fout(tenFile);
    if (!fout.is_open()) {
        qWarning() << "[SACH] KHÔNG GHI ĐƯỢC FILE:" << QString::fromStdString(tenFile);
        return;
    }

    // Ghi header
    fout << "Ma sach | Ten sach | Tac gia | Nha xuat ban | Nam xuat ban | So luong\n";
    fout << "-------|------------------------------------------|------------------------------|-------------------|--------------|----------\n";

    for (const auto& b : ds) {
        fout << b.getMaSach() << "|"
             << b.getTenSach() << "|"
             << b.getTacGia() << "|"
             << b.getTheLoai() << "|"
             << b.getNamXuatBan() << "|"
             << b.getSoLuong() << "\n";
    }

    fout.close();
    qDebug() << "[SACH] ✓ Đã lưu thành công!";
}

// ==================== BAN DOC ====================

vector<BanDoc> docBanDocTuFile(const string& tenFile) {
    vector<BanDoc> ds;
    qDebug() << "[BANDOC] Đang mở file:" << QString::fromStdString(tenFile);

    ifstream file(tenFile);
    if (!file.is_open()) {
        qWarning() << "[BANDOC] KHÔNG MỞ ĐƯỢC FILE:" << QString::fromStdString(tenFile);
        return ds;
    }

    qDebug() << "[BANDOC] Đã mở file thành công!";

    string line;
    int lineNum = 0;

    while (getline(file, line)) {
        lineNum++;

        // Bỏ qua dòng trống
        if (line.empty()) {
            qDebug() << "[BANDOC] Dòng" << lineNum << ": trống, bỏ qua";
            continue;
        }

        stringstream ss(line);
        string ma, ten, khoa, sdt;

        getline(ss, ma, '|');
        getline(ss, ten, '|');
        getline(ss, khoa, '|');
        getline(ss, sdt);

        // Trim khoảng trắng
        ma.erase(0, ma.find_first_not_of(" \t\r\n"));
        ma.erase(ma.find_last_not_of(" \t\r\n") + 1);
        ten.erase(0, ten.find_first_not_of(" \t\r\n"));
        ten.erase(ten.find_last_not_of(" \t\r\n") + 1);
        khoa.erase(0, khoa.find_first_not_of(" \t\r\n"));
        khoa.erase(khoa.find_last_not_of(" \t\r\n") + 1);
        sdt.erase(0, sdt.find_first_not_of(" \t\r\n"));
        sdt.erase(sdt.find_last_not_of(" \t\r\n") + 1);

        // Kiểm tra dữ liệu hợp lệ
        if (!ma.empty() && !ten.empty()) {
            ds.emplace_back(ma, ten, khoa, sdt);
            if (ds.size() <= 3) {  // Chỉ in 3 dòng đầu
                qDebug() << "[BANDOC] Dòng" << lineNum << ":" << QString::fromStdString(ma)
                         << "|" << QString::fromStdString(ten);
            }
        } else {
            qWarning() << "[BANDOC] Dòng" << lineNum << ": dữ liệu không hợp lệ";
        }
    }

    file.close();
    qDebug() << "[BANDOC] ✓ Đã đọc" << ds.size() << "bạn đọc từ" << lineNum << "dòng";
    return ds;
}

void luuBanDocVaoFile(const vector<BanDoc>& ds, const string& tenFile) {
    qDebug() << "[BANDOC] Đang lưu" << ds.size() << "bạn đọc vào file...";

    ofstream file(tenFile);
    if (!file.is_open()) {
        qWarning() << "[BANDOC] KHÔNG GHI ĐƯỢC FILE:" << QString::fromStdString(tenFile);
        return;
    }

    for (const auto& bd : ds) {
        file << bd.getMaBD() << "|"
             << bd.getHoTen() << "|"
             << bd.getKhoa() << "|"
             << bd.getSDT() << "\n";
    }

    file.close();
    qDebug() << "[BANDOC] ✓ Đã lưu thành công!";
}

// ==================== PHIEU MUON ====================

vector<PhieuMuon> docPhieuMuonTuFile(const string& tenFile) {
    vector<PhieuMuon> ds;
    qDebug() << "[PHIEUMUON] Đang mở file:" << QString::fromStdString(tenFile);

    ifstream file(tenFile);
    if (!file.is_open()) {
        qWarning() << "[PHIEUMUON] KHÔNG MỞ ĐƯỢC FILE:" << QString::fromStdString(tenFile);
        return ds;
    }

    qDebug() << "[PHIEUMUON] Đã mở file thành công!";

    string line;
    int lineNum = 0;

    while (getline(file, line)) {
        lineNum++;

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

        // Trim khoảng trắng
        maPhieu.erase(0, maPhieu.find_first_not_of(" \t\r\n"));
        maPhieu.erase(maPhieu.find_last_not_of(" \t\r\n") + 1);
        maBD.erase(0, maBD.find_first_not_of(" \t\r\n"));
        maBD.erase(maBD.find_last_not_of(" \t\r\n") + 1);
        maSach.erase(0, maSach.find_first_not_of(" \t\r\n"));
        maSach.erase(maSach.find_last_not_of(" \t\r\n") + 1);
        ngayMuon.erase(0, ngayMuon.find_first_not_of(" \t\r\n"));
        ngayMuon.erase(ngayMuon.find_last_not_of(" \t\r\n") + 1);
        ngayTra.erase(0, ngayTra.find_first_not_of(" \t\r\n"));
        ngayTra.erase(ngayTra.find_last_not_of(" \t\r\n") + 1);

        // Kiểm tra dữ liệu hợp lệ
        if (!maPhieu.empty() && !maBD.empty() && !maSach.empty()) {
            PhieuMuon pm(maPhieu, maBD, maSach, ngayMuon);
            if (daTra && !ngayTra.empty()) {
                pm.traSach(ngayTra);
            }
            ds.push_back(pm);

            if (ds.size() <= 3) {  // Chỉ in 3 dòng đầu
                qDebug() << "[PHIEUMUON] Dòng" << lineNum << ":" << QString::fromStdString(maPhieu);
            }
        }
    }

    file.close();
    qDebug() << "[PHIEUMUON] ✓ Đã đọc" << ds.size() << "phiếu mượn từ" << lineNum << "dòng";
    return ds;
}

void luuPhieuMuonVaoFile(const vector<PhieuMuon>& ds, const string& tenFile) {
    qDebug() << "[PHIEUMUON] Đang lưu" << ds.size() << "phiếu mượn vào file...";

    ofstream file(tenFile);
    if (!file.is_open()) {
        qWarning() << "[PHIEUMUON] KHÔNG GHI ĐƯỢC FILE:" << QString::fromStdString(tenFile);
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
    qDebug() << "[PHIEUMUON] ✓ Đã lưu thành công!";
}
