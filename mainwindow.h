#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "Models/Book.h"
#include "Models/BanDoc.h"
#include "Models/PhieuMuon.h"

using namespace std;

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
    // Slots cho Bạn Đọc
    void on_btnThem_clicked();
    void on_btnSua_clicked();
    void on_btnXoa_clicked();
    void on_lineEdit_TimKiem_textChanged(const QString &text);

private:
    Ui::MainWindow *ui;
    vector<BanDoc> dsBanDoc;

    // Hàm load bảng
    void loadTableBanDoc();
};

#endif // MAINWINDOW_H
