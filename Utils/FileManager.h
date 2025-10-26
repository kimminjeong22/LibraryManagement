#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>
#include <string>
#include "../Models/Book.h"
#include "../Models/BanDoc.h"
#include "../Models/PhieuMuon.h"

using namespace std;

// Hàm đọc/ghi file cho Book
vector<Book> docSachTuFile(const string& tenFile);
void luuSachVaoFile(const vector<Book>& ds, const string& tenFile);

// Hàm đọc/ghi file cho BanDoc
vector<BanDoc> docBanDocTuFile(const string& tenFile);
void luuBanDocVaoFile(const vector<BanDoc>& ds, const string& tenFile);

// Hàm đọc/ghi file cho PhieuMuon
vector<PhieuMuon> docPhieuMuonTuFile(const string& tenFile);
void luuPhieuMuonVaoFile(const vector<PhieuMuon>& ds, const string& tenFile);

#endif // FILEMANAGER_H
