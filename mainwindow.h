#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "Models/BanDoc.h"
#include "Models/Book.h"
#include "Models/PhieuMuon.h"

// === THÊM 2 DÒNG NÀY VÀO ===
#include <QStringList>
class QPushButton;
// =============================

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // ===== BẠN ĐỌC SLOTS =====
    void on_btnThem_BanDoc_clicked();
    void on_btnSua_BanDoc_clicked();
    void on_btnXoa_BanDoc_clicked();
    void on_lineEdit_TimKiem_BanDoc_textChanged(const QString &text);

    // ===== SÁCH SLOTS =====
    void on_btnThem_Sach_clicked();
    void on_btnSua_Sach_clicked();
    void on_btnXoa_Sach_clicked();
    void on_lineEdit_TimKiem_Sach_textChanged(const QString &text);

    // ===== PHIẾU MƯỢN SLOTS =====
    void on_btnMuonSach_clicked();
    void on_btnTraSach_clicked();
    void on_btnXoaPhieu_clicked();
    void on_lineEdit_TimKiem_Phieu_textChanged(const QString &text);

private:
    Ui::MainWindow *ui;
    std::vector<BanDoc> dsBanDoc;
    std::vector<Book> dsSach;
    std::vector<PhieuMuon> dsPhieuMuon;

    // Helper functions
    QString getDataPath(const QString& filename);
    void loadTableBanDoc();
    void loadTableSach();
    void loadTablePhieuMuon();

    // === VÀ THÊM 2 HÀM NÀY VÀO ===
    // (Đây là 2 hàm bị thiếu khai báo)
    void applyButtonShadow(QPushButton* button);
    bool showBanDocDialog(const QString& title, const QStringList& dataIn, QStringList& dataOut);
    // ================================
};

#endif // MAINWINDOW_H
