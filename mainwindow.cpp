#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "FileManager.h"

#include <QFile>
#include <QApplication>
#include <QCoreApplication>
#include <QPushButton>
#include <QGraphicsDropShadowEffect>
#include <QMessageBox>
#include <QColor>
#include <QDialog>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QTableWidgetItem>
#include <QVBoxLayout>
#include <QDebug>
#include <QDir>
#include <QHeaderView>
#include <QFileInfo>
#include <algorithm>

// ====== HELPER METHOD IMPLEMENTATIONS ======

void MainWindow::applyButtonShadow(QPushButton* button) {
    if (!button) return;
    auto* shadow = new QGraphicsDropShadowEffect(button);
    shadow->setBlurRadius(15);
    shadow->setXOffset(0);
    shadow->setYOffset(4);
    shadow->setColor(QColor(0, 0, 0, 40));
    button->setGraphicsEffect(shadow);
}

bool MainWindow::showBanDocDialog(const QString& title, const QStringList& dataIn, QStringList& dataOut) {
    QDialog dialog(this);
    dialog.setWindowTitle(title);
    dialog.setModal(true);

    QFormLayout* formLayout = new QFormLayout(&dialog);

    QLineEdit* leMaBD = new QLineEdit(&dialog);
    QLineEdit* leHoTen = new QLineEdit(&dialog);
    QLineEdit* leKhoa = new QLineEdit(&dialog);
    QLineEdit* leSDT = new QLineEdit(&dialog);

    formLayout->addRow(new QLabel("Mã bạn đọc:", &dialog), leMaBD);
    formLayout->addRow(new QLabel("Họ tên:", &dialog), leHoTen);
    formLayout->addRow(new QLabel("Khoa:", &dialog), leKhoa);
    formLayout->addRow(new QLabel("SĐT:", &dialog), leSDT);

    if (dataIn.count() == 4) {
        leMaBD->setText(dataIn[0]);
        leHoTen->setText(dataIn[1]);
        leKhoa->setText(dataIn[2]);
        leSDT->setText(dataIn[3]);
    }

    QPushButton* btnLuu = new QPushButton("Lưu", &dialog);
    QPushButton* btnHuy = new QPushButton("Hủy", &dialog);
    btnLuu->setObjectName("btnLuuThongTin");

    QDialogButtonBox* buttonBox = new QDialogButtonBox(&dialog);
    buttonBox->addButton(btnLuu, QDialogButtonBox::AcceptRole);
    buttonBox->addButton(btnHuy, QDialogButtonBox::RejectRole);

    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    QVBoxLayout* mainLayout = new QVBoxLayout(&dialog);
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(buttonBox);

    if (dialog.exec() == QDialog::Accepted) {
        dataOut.clear();
        dataOut << leMaBD->text() << leHoTen->text() << leKhoa->text() << leSDT->text();
        return true;
    }

    return false;
}

QString MainWindow::getDataPath(const QString& filename)
{
    QString appDir = QCoreApplication::applicationDirPath();
    QString dataPath = appDir + "/Data/" + filename;

    qDebug() << "=== KIỂM TRA ĐƯỜNG DẪN FILE ===";
    qDebug() << "Thư mục ứng dụng:" << appDir;
    qDebug() << "Đường dẫn file:" << dataPath;
    qDebug() << "File tồn tại:" << QFile::exists(dataPath);

    QDir dir(appDir);
    if (!dir.exists("Data")) {
        qDebug() << "Thư mục Data chưa tồn tại, đang tạo...";
        if (dir.mkdir("Data")) {
            qDebug() << "Đã tạo thư mục Data thành công!";
        }
    }

    return dataPath;
}

void MainWindow::loadTableBanDoc()
{
    ui->tableWidget_BanDoc->clearContents();
    ui->tableWidget_BanDoc->setRowCount(0);

    for (const auto& bd : dsBanDoc) {
        int row = ui->tableWidget_BanDoc->rowCount();
        ui->tableWidget_BanDoc->insertRow(row);

        ui->tableWidget_BanDoc->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(bd.getMaBD())));
        ui->tableWidget_BanDoc->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(bd.getHoTen())));
        ui->tableWidget_BanDoc->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(bd.getKhoa())));
        ui->tableWidget_BanDoc->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(bd.getSDT())));
    }
}

void MainWindow::loadTableSach()
{
    ui->tableWidget_Sach->clearContents();
    ui->tableWidget_Sach->setRowCount(0);

    for (const auto& sach : dsSach) {
        int row = ui->tableWidget_Sach->rowCount();
        ui->tableWidget_Sach->insertRow(row);

        ui->tableWidget_Sach->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(sach.getMaSach())));
        ui->tableWidget_Sach->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(sach.getTenSach())));
        ui->tableWidget_Sach->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(sach.getTacGia())));
        ui->tableWidget_Sach->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(sach.getTheLoai())));
        ui->tableWidget_Sach->setItem(row, 4, new QTableWidgetItem(QString::number(sach.getNamXuatBan())));
        ui->tableWidget_Sach->setItem(row, 5, new QTableWidgetItem(QString::number(sach.getSoLuong())));
    }
}

void MainWindow::loadTablePhieuMuon()
{
    ui->tableWidget_PhieuMuon->clearContents();
    ui->tableWidget_PhieuMuon->setRowCount(0);

    for (const auto& pm : dsPhieuMuon) {
        int row = ui->tableWidget_PhieuMuon->rowCount();
        ui->tableWidget_PhieuMuon->insertRow(row);

        ui->tableWidget_PhieuMuon->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(pm.getMaPhieu())));
        ui->tableWidget_PhieuMuon->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(pm.getMaBD())));
        ui->tableWidget_PhieuMuon->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(pm.getMaSach())));
        ui->tableWidget_PhieuMuon->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(pm.getNgayMuon())));
        ui->tableWidget_PhieuMuon->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(pm.getNgayTra())));
        ui->tableWidget_PhieuMuon->setItem(row, 5, new QTableWidgetItem(pm.getDaTra() ? "Đã trả" : "Chưa trả"));
    }
}

// ====== CONSTRUCTOR / DESTRUCTOR ======

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qDebug() << "\n========================================";
    qDebug() << "KHỞI TẠO MAINWINDOW";
    qDebug() << "========================================\n";

    // Load QSS từ Qt Resource
    QFile f(":/styles.qss");
    if (f.open(QFile::ReadOnly | QFile::Text)) {
        QString style = QString::fromUtf8(f.readAll());
        qApp->setStyleSheet(style);
        f.close();
        qDebug() << "✓ Đã load styles.qss thành công";
    } else {
        qWarning() << "✗ Không thể tải file styles.qss từ resource!";
    }

    // Áp dụng bóng đổ cho các nút
    applyButtonShadow(ui->btnThem_BanDoc);
    applyButtonShadow(ui->btnSua_BanDoc);
    applyButtonShadow(ui->btnXoa_BanDoc);

    // Cài đặt cho bảng Bạn Đọc
    if (ui->tableWidget_BanDoc) {
        ui->tableWidget_BanDoc->setColumnCount(4);
        QStringList headers;
        headers << "Mã Bạn Đọc" << "Họ Tên" << "Khoa" << "Số Điện Thoại";
        ui->tableWidget_BanDoc->setHorizontalHeaderLabels(headers);
        ui->tableWidget_BanDoc->horizontalHeader()->setStretchLastSection(true);
        ui->tableWidget_BanDoc->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableWidget_BanDoc->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableWidget_BanDoc->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tableWidget_BanDoc->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }

    // Cài đặt cho bảng Sách
    if (ui->tableWidget_Sach) {
        ui->tableWidget_Sach->setColumnCount(6);
        QStringList headersSach;
        headersSach << "Mã Sách" << "Tên Sách" << "Tác Giả" << "Thể Loại" << "Năm XB" << "Số Lượng";
        ui->tableWidget_Sach->setHorizontalHeaderLabels(headersSach);
        ui->tableWidget_Sach->horizontalHeader()->setStretchLastSection(true);
        ui->tableWidget_Sach->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableWidget_Sach->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableWidget_Sach->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tableWidget_Sach->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }

    // Cài đặt cho bảng Phiếu Mượn
    if (ui->tableWidget_PhieuMuon) {
        ui->tableWidget_PhieuMuon->setColumnCount(6);
        QStringList headersPhieu;
        headersPhieu << "Mã Phiếu" << "Mã Bạn Đọc" << "Mã Sách" << "Ngày Mượn" << "Ngày Trả" << "Đã Trả";
        ui->tableWidget_PhieuMuon->setHorizontalHeaderLabels(headersPhieu);
        ui->tableWidget_PhieuMuon->horizontalHeader()->setStretchLastSection(true);
        ui->tableWidget_PhieuMuon->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableWidget_PhieuMuon->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableWidget_PhieuMuon->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tableWidget_PhieuMuon->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }

    // ========================================
    // LOAD DỮ LIỆU TỪ FILE
    // ========================================

    qDebug() << "\n===== BẮT ĐẦU LOAD DỮ LIỆU =====\n";

    QString fileBanDoc = getDataPath("bandoc.txt");
    QString fileSach = getDataPath("sach.txt");
    QString filePhieuMuon = getDataPath("phieumuon.txt");

    // Load bạn đọc
    qDebug() << ">> Đang load Bạn Đọc...";
    dsBanDoc = docBanDocTuFile(fileBanDoc.toStdString());
    loadTableBanDoc();
    qDebug() << "✓ Đã load" << dsBanDoc.size() << "bạn đọc\n";

    // Load sách
    qDebug() << ">> Đang load Sách...";
    dsSach = docSachTuFile(fileSach.toStdString());
    loadTableSach();
    qDebug() << "✓ Đã load" << dsSach.size() << "sách\n";

    // Load phiếu mượn
    qDebug() << ">> Đang load Phiếu Mượn...";
    dsPhieuMuon = docPhieuMuonTuFile(filePhieuMuon.toStdString());
    loadTablePhieuMuon();
    qDebug() << "✓ Đã load" << dsPhieuMuon.size() << "phiếu mượn\n";

    qDebug() << "===== HOÀN THÀNH LOAD DỮ LIỆU =====\n";

    qDebug() << "========================================";
    qDebug() << "MAINWINDOW ĐÃ SẴN SÀNG!";
    qDebug() << "========================================\n";
}

MainWindow::~MainWindow()
{
    qDebug() << "\n===== BẮT ĐẦU LƯU DỮ LIỆU =====";

    QString fileBanDoc = getDataPath("bandoc.txt");
    QString fileSach = getDataPath("sach.txt");
    QString filePhieuMuon = getDataPath("phieumuon.txt");

    luuBanDocVaoFile(dsBanDoc, fileBanDoc.toStdString());
    qDebug() << "✓ Đã lưu" << dsBanDoc.size() << "bạn đọc";

    luuSachVaoFile(dsSach, fileSach.toStdString());
    qDebug() << "✓ Đã lưu" << dsSach.size() << "sách";

    luuPhieuMuonVaoFile(dsPhieuMuon, filePhieuMuon.toStdString());
    qDebug() << "✓ Đã lưu" << dsPhieuMuon.size() << "phiếu mượn";

    qDebug() << "===== HOÀN THÀNH LƯU DỮ LIỆU =====\n";

    delete ui;
}

// ====== BẠN ĐỌC SLOTS ======

void MainWindow::on_btnThem_BanDoc_clicked()
{
    QStringList dataOut;
    bool ok = showBanDocDialog("Thêm bạn đọc mới", {}, dataOut);

    if (ok) {
        std::string maBD = dataOut[0].toStdString();
        for (const auto& bd : dsBanDoc) {
            if (bd.getMaBD() == maBD) {
                QMessageBox::warning(this, "Lỗi", "Mã bạn đọc đã tồn tại!");
                return;
            }
        }

        BanDoc bdMoi(
            dataOut[0].toStdString(),
            dataOut[1].toStdString(),
            dataOut[2].toStdString(),
            dataOut[3].toStdString()
            );
        dsBanDoc.push_back(bdMoi);

        int newRow = ui->tableWidget_BanDoc->rowCount();
        ui->tableWidget_BanDoc->insertRow(newRow);
        ui->tableWidget_BanDoc->setItem(newRow, 0, new QTableWidgetItem(dataOut[0]));
        ui->tableWidget_BanDoc->setItem(newRow, 1, new QTableWidgetItem(dataOut[1]));
        ui->tableWidget_BanDoc->setItem(newRow, 2, new QTableWidgetItem(dataOut[2]));
        ui->tableWidget_BanDoc->setItem(newRow, 3, new QTableWidgetItem(dataOut[3]));

        QString fileBanDoc = getDataPath("bandoc.txt");
        luuBanDocVaoFile(dsBanDoc, fileBanDoc.toStdString());

        QMessageBox::information(this, "Thành công", "Đã thêm bạn đọc mới!");
    }
}

void MainWindow::on_btnSua_BanDoc_clicked()
{
    int currentRow = ui->tableWidget_BanDoc->currentRow();

    if (currentRow < 0) {
        QMessageBox::warning(this, "Chưa chọn", "Vui lòng chọn một bạn đọc để sửa.");
        return;
    }

    QStringList dataIn;
    dataIn << ui->tableWidget_BanDoc->item(currentRow, 0)->text();
    dataIn << ui->tableWidget_BanDoc->item(currentRow, 1)->text();
    dataIn << ui->tableWidget_BanDoc->item(currentRow, 2)->text();
    dataIn << ui->tableWidget_BanDoc->item(currentRow, 3)->text();

    QStringList dataOut;
    bool ok = showBanDocDialog("Sửa thông tin bạn đọc", dataIn, dataOut);

    if (ok) {
        std::string maBD = dataIn[0].toStdString();
        for (auto& bd : dsBanDoc) {
            if (bd.getMaBD() == maBD) {
                bd.setHoTen(dataOut[1].toStdString());
                bd.setKhoa(dataOut[2].toStdString());
                bd.setSDT(dataOut[3].toStdString());
                break;
            }
        }

        ui->tableWidget_BanDoc->setItem(currentRow, 0, new QTableWidgetItem(dataOut[0]));
        ui->tableWidget_BanDoc->setItem(currentRow, 1, new QTableWidgetItem(dataOut[1]));
        ui->tableWidget_BanDoc->setItem(currentRow, 2, new QTableWidgetItem(dataOut[2]));
        ui->tableWidget_BanDoc->setItem(currentRow, 3, new QTableWidgetItem(dataOut[3]));

        QString fileBanDoc = getDataPath("bandoc.txt");
        luuBanDocVaoFile(dsBanDoc, fileBanDoc.toStdString());

        QMessageBox::information(this, "Thành công", "Đã cập nhật thông tin!");
    }
}

void MainWindow::on_btnXoa_BanDoc_clicked()
{
    int currentRow = ui->tableWidget_BanDoc->currentRow();

    if (currentRow < 0) {
        QMessageBox::warning(this, "Chưa chọn", "Vui lòng chọn một bạn đọc để xóa.");
        return;
    }

    QString tenBanDoc = ui->tableWidget_BanDoc->item(currentRow, 1)->text();
    QString maBanDoc = ui->tableWidget_BanDoc->item(currentRow, 0)->text();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Xác nhận xóa",
                                  QString("Bạn có chắc chắn muốn xóa bạn đọc \"%1\" không?").arg(tenBanDoc),
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        std::string maBD = maBanDoc.toStdString();
        dsBanDoc.erase(
            std::remove_if(dsBanDoc.begin(), dsBanDoc.end(),
                           [&maBD](const BanDoc& bd) { return bd.getMaBD() == maBD; }),
            dsBanDoc.end()
            );

        ui->tableWidget_BanDoc->removeRow(currentRow);

        QString fileBanDoc = getDataPath("bandoc.txt");
        luuBanDocVaoFile(dsBanDoc, fileBanDoc.toStdString());

        QMessageBox::information(this, "Thành công", "Đã xóa bạn đọc!");
    }
}

void MainWindow::on_lineEdit_TimKiem_BanDoc_textChanged(const QString &text)
{
    for (int i = 0; i < ui->tableWidget_BanDoc->rowCount(); ++i) {
        bool match = false;
        for (int j = 0; j < ui->tableWidget_BanDoc->columnCount(); ++j) {
            QTableWidgetItem* item = ui->tableWidget_BanDoc->item(i, j);
            if (item && item->text().contains(text, Qt::CaseInsensitive)) {
                match = true;
                break;
            }
        }
        ui->tableWidget_BanDoc->setRowHidden(i, !match);
    }
}

// ====== SÁCH SLOTS ======

void MainWindow::on_btnThem_Sach_clicked()
{
    QMessageBox::information(this, "Thông báo", "Chức năng Thêm Sách đang được phát triển.");
}

void MainWindow::on_btnSua_Sach_clicked()
{
    QMessageBox::information(this, "Thông báo", "Chức năng Sửa Sách đang được phát triển.");
}

void MainWindow::on_btnXoa_Sach_clicked()
{
    QMessageBox::information(this, "Thông báo", "Chức năng Xóa Sách đang được phát triển.");
}

void MainWindow::on_lineEdit_TimKiem_Sach_textChanged(const QString &text)
{
    for (int i = 0; i < ui->tableWidget_Sach->rowCount(); ++i) {
        bool match = false;
        for (int j = 0; j < ui->tableWidget_Sach->columnCount(); ++j) {
            QTableWidgetItem* item = ui->tableWidget_Sach->item(i, j);
            if (item && item->text().contains(text, Qt::CaseInsensitive)) {
                match = true;
                break;
            }
        }
        ui->tableWidget_Sach->setRowHidden(i, !match);
    }
}

// ====== PHIẾU MƯỢN SLOTS ======

void MainWindow::on_btnMuonSach_clicked()
{
    QMessageBox::information(this, "Thông báo", "Chức năng Mượn Sách đang được phát triển.");
}

void MainWindow::on_btnTraSach_clicked()
{
    QMessageBox::information(this, "Thông báo", "Chức năng Trả Sách đang được phát triển.");
}

void MainWindow::on_btnXoaPhieu_clicked()
{
    QMessageBox::information(this, "Thông báo", "Chức năng Xóa Phiếu đang được phát triển.");
}

void MainWindow::on_lineEdit_TimKiem_Phieu_textChanged(const QString &text)
{
    for (int i = 0; i < ui->tableWidget_PhieuMuon->rowCount(); ++i) {
        bool match = false;
        for (int j = 0; j < ui->tableWidget_PhieuMuon->columnCount(); ++j) {
            QTableWidgetItem* item = ui->tableWidget_PhieuMuon->item(i, j);
            if (item && item->text().contains(text, Qt::CaseInsensitive)) {
                match = true;
                break;
            }
        }
        ui->tableWidget_PhieuMuon->setRowHidden(i, !match);
    }
}
