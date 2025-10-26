#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Utils/FileManager.h"
#include "Utils/DateUtils.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QCoreApplication>
#include <QFileInfo>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Thiết lập bảng
    ui->tableWidget->setColumnCount(4);
    QStringList headers = {"Mã BD", "Họ Tên", "Lớp", "SĐT"};
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    // Tìm đường dẫn đến thư mục Data
    QString dataPath = QCoreApplication::applicationDirPath() + "/Data/bandoc.txt";

    // Nếu không tìm thấy, thử tìm ở thư mục gốc project
    QFileInfo checkFile(dataPath);
    if (!checkFile.exists()) {
        // Lùi 3 cấp từ build/Desktop_.../debug/ về thư mục gốc
        dataPath = QCoreApplication::applicationDirPath() + "/../../../Data/bandoc.txt";
    }

    // Đọc dữ liệu từ file
    dsBanDoc = docBanDocTuFile(dataPath.toStdString());
    loadTableBanDoc();
}

MainWindow::~MainWindow()
{
    // Lưu dữ liệu khi đóng chương trình
    QString dataPath = QCoreApplication::applicationDirPath() + "/Data/bandoc.txt";
    QFileInfo checkFile(dataPath);
    if (!checkFile.exists()) {
        dataPath = QCoreApplication::applicationDirPath() + "/../../../Data/bandoc.txt";
    }
    luuBanDocVaoFile(dsBanDoc, dataPath.toStdString());
    delete ui;
}

// Hiển thị bảng Bạn Đọc
void MainWindow::loadTableBanDoc()
{
    ui->tableWidget->setRowCount(0);
    for (const auto& bd : dsBanDoc) {
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(bd.getMaBD())));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(bd.getHoTen())));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(bd.getLop())));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(bd.getSDT())));
    }

    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resizeRowsToContents();
}

// Nút Thêm
void MainWindow::on_btnThem_clicked()
{
    QString ma = QInputDialog::getText(this, "Thêm bạn đọc", "Nhập mã bạn đọc:");
    if (ma.isEmpty()) return;

    // Kiểm tra trùng mã
    for (const auto& bd : dsBanDoc) {
        if (bd.getMaBD() == ma.toStdString()) {
            QMessageBox::warning(this, "Lỗi", "Mã bạn đọc đã tồn tại!");
            return;
        }
    }

    QString ten = QInputDialog::getText(this, "Thêm bạn đọc", "Nhập họ tên:");
    QString lop = QInputDialog::getText(this, "Thêm bạn đọc", "Nhập lớp:");
    QString sdt = QInputDialog::getText(this, "Thêm bạn đọc", "Nhập SĐT:");

    if (ten.isEmpty()) {
        QMessageBox::warning(this, "Lỗi", "Họ tên không được để trống!");
        return;
    }

    dsBanDoc.push_back(BanDoc(ma.toStdString(), ten.toStdString(), lop.toStdString(), sdt.toStdString()));
    loadTableBanDoc();

    // Lưu file
    QString dataPath = QCoreApplication::applicationDirPath() + "/Data/bandoc.txt";
    QFileInfo checkFile(dataPath);
    if (!checkFile.exists()) {
        dataPath = QCoreApplication::applicationDirPath() + "/../../../Data/bandoc.txt";
    }
    luuBanDocVaoFile(dsBanDoc, dataPath.toStdString());

    QMessageBox::information(this, "Thành công", "Đã thêm bạn đọc!");
}

// Nút Sửa
void MainWindow::on_btnSua_clicked()
{
    QString ma = QInputDialog::getText(this, "Sửa bạn đọc", "Nhập mã bạn đọc cần sửa:");
    if (ma.isEmpty()) return;

    for (auto& bd : dsBanDoc) {
        if (bd.getMaBD() == ma.toStdString()) {
            QString ten = QInputDialog::getText(this, "Sửa bạn đọc", "Tên mới:",
                                                QLineEdit::Normal, QString::fromStdString(bd.getHoTen()));
            QString lop = QInputDialog::getText(this, "Sửa bạn đọc", "Lớp mới:",
                                                QLineEdit::Normal, QString::fromStdString(bd.getLop()));
            QString sdt = QInputDialog::getText(this, "Sửa bạn đọc", "SĐT mới:",
                                                QLineEdit::Normal, QString::fromStdString(bd.getSDT()));

            bd.setHoTen(ten.toStdString());
            bd.setLop(lop.toStdString());
            bd.setSDT(sdt.toStdString());

            loadTableBanDoc();
            luuBanDocVaoFile(dsBanDoc, "Data/bandoc.txt");
            QMessageBox::information(this, "Thành công", "Đã cập nhật thông tin!");
            return;
        }
    }

    QMessageBox::warning(this, "Lỗi", "Không tìm thấy bạn đọc!");
}

// Nút Xóa
void MainWindow::on_btnXoa_clicked()
{
    QString ma = QInputDialog::getText(this, "Xóa bạn đọc", "Nhập mã bạn đọc cần xóa:");
    if (ma.isEmpty()) return;

    auto it = remove_if(dsBanDoc.begin(), dsBanDoc.end(), [&](const BanDoc& bd) {
        return bd.getMaBD() == ma.toStdString();
    });

    if (it != dsBanDoc.end()) {
        dsBanDoc.erase(it, dsBanDoc.end());
        loadTableBanDoc();
        luuBanDocVaoFile(dsBanDoc, "Data/bandoc.txt");
        QMessageBox::information(this, "Thành công", "Đã xóa bạn đọc!");
    } else {
        QMessageBox::warning(this, "Lỗi", "Không tìm thấy bạn đọc!");
    }
}

// Tìm kiếm realtime
void MainWindow::on_lineEdit_TimKiem_textChanged(const QString &text)
{
    QString keyword = text.trimmed().toLower();
    ui->tableWidget->setRowCount(0);

    for (const auto& bd : dsBanDoc) {
        QString ten = QString::fromStdString(bd.getHoTen()).toLower();
        QString ma = QString::fromStdString(bd.getMaBD()).toLower();

        if (ten.contains(keyword) || ma.contains(keyword)) {
            int row = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(row);
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(bd.getMaBD())));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(bd.getHoTen())));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(bd.getLop())));
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(bd.getSDT())));
        }
    }
}
