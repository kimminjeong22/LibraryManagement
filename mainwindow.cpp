#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "FileManager.h"
#include "Utils/DateUtils.h" // <<< THÊM THƯ VIỆN NÀY ĐỂ LẤY NGÀY VÀ TÍNH PHẠT

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
#include <QSpinBox>

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

    bool laSua = (dataIn.count() == 4);
    if (laSua) {
        leMaBD->setText(dataIn[0]);
        leHoTen->setText(dataIn[1]);
        leKhoa->setText(dataIn[2]);
        leSDT->setText(dataIn[3]);
        leMaBD->setReadOnly(true);
    }

    QPushButton* btnLuu = new QPushButton(QString::fromUtf8("Luu"), &dialog);
    QPushButton* btnHuy = new QPushButton(QString::fromUtf8("Huy"), &dialog);
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
        if (leMaBD->text().isEmpty() || leHoTen->text().isEmpty()) {
            QMessageBox::warning(&dialog, "Thiếu thông tin", "Mã bạn đọc và Họ tên không được để trống.");
            return false;
        }
        dataOut.clear();
        dataOut << leMaBD->text() << leHoTen->text() << leKhoa->text() << leSDT->text();
        return true;
    }

    return false;
}

bool MainWindow::showSachDialog(const QString& title, const QStringList& dataIn, QStringList& dataOut)
{
    QDialog dialog(this);
    dialog.setWindowTitle(title);
    dialog.setModal(true);

    QFormLayout* formLayout = new QFormLayout(&dialog);

    QLineEdit* leMaSach = new QLineEdit(&dialog);
    QLineEdit* leTenSach = new QLineEdit(&dialog);
    QLineEdit* leTacGia = new QLineEdit(&dialog);
    QLineEdit* leTheLoai = new QLineEdit(&dialog);
    QSpinBox* sbNamXB = new QSpinBox(&dialog);
    QSpinBox* sbSoLuong = new QSpinBox(&dialog);

    sbNamXB->setRange(1000, 3000);
    sbNamXB->setValue(2024);
    sbSoLuong->setRange(0, 9999);

    formLayout->addRow(new QLabel("Mã Sách:", &dialog), leMaSach);
    formLayout->addRow(new QLabel("Tên Sách:", &dialog), leTenSach);
    formLayout->addRow(new QLabel("Tác Giả:", &dialog), leTacGia);
    formLayout->addRow(new QLabel("Thể Loại:", &dialog), leTheLoai);
    formLayout->addRow(new QLabel("Năm XB:", &dialog), sbNamXB);
    formLayout->addRow(new QLabel("Số Lượng:", &dialog), sbSoLuong);

    bool laSua = (dataIn.count() == 6);
    if (laSua) {
        leMaSach->setText(dataIn[0]);
        leTenSach->setText(dataIn[1]);
        leTacGia->setText(dataIn[2]);
        leTheLoai->setText(dataIn[3]);
        sbNamXB->setValue(dataIn[4].toInt());
        sbSoLuong->setValue(dataIn[5].toInt());
        leMaSach->setReadOnly(true);
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
        if (leMaSach->text().isEmpty() || leTenSach->text().isEmpty() || leTacGia->text().isEmpty()) {
            QMessageBox::warning(&dialog, "Thiếu thông tin", "Mã, Tên Sách, Tác Giả không được để trống.");
            return false;
        }

        dataOut.clear();
        dataOut << leMaSach->text()
                << leTenSach->text()
                << leTacGia->text()
                << leTheLoai->text()
                << QString::number(sbNamXB->value())
                << QString::number(sbSoLuong->value());
        return true;
    }

    return false;
}

// >>> HÀM MỚI: HỘP THOẠI CHO MƯỢN SÁCH
bool MainWindow::showMuonSachDialog(const QString& title, QStringList& dataOut)
{
    QDialog dialog(this);
    dialog.setWindowTitle(title);
    dialog.setModal(true);




    QFormLayout* formLayout = new QFormLayout(&dialog);

    QLineEdit* leMaPhieu = new QLineEdit(&dialog);
    QLineEdit* leMaBD = new QLineEdit(&dialog);
    QLineEdit* leMaSach = new QLineEdit(&dialog);

    formLayout->addRow(new QLabel("Mã Phiếu:", &dialog), leMaPhieu);
    formLayout->addRow(new QLabel("Mã Bạn Đọc:", &dialog), leMaBD);
    formLayout->addRow(new QLabel("Mã Sách:", &dialog), leMaSach);

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
        if (leMaPhieu->text().isEmpty() || leMaBD->text().isEmpty() || leMaSach->text().isEmpty()) {
            QMessageBox::warning(&dialog, "Thiếu thông tin", "Vui lòng nhập đầy đủ Mã phiếu, Mã bạn đọc và Mã sách.");
            return false;
        }
        dataOut.clear();
        dataOut << leMaPhieu->text() << leMaBD->text() << leMaSach->text();
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

    // Load QSS
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

    applyButtonShadow(ui->btnThem_Sach);
    applyButtonShadow(ui->btnSua_Sach);
    applyButtonShadow(ui->btnXoa_Sach);

    // <<< THÊM CÁC NÚT CỦA PHIẾU MƯỢN
    applyButtonShadow(ui->btnLapPhieu);
    applyButtonShadow(ui->btnTraSach);
    applyButtonShadow(ui->btnXoaPhieu);


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
        BanDoc bdMoi(dataOut[0].toStdString(), dataOut[1].toStdString(), dataOut[2].toStdString(), dataOut[3].toStdString());
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
    reply = QMessageBox::question(this, "Xác nhận xóa", QString("Bạn có chắc chắn muốn xóa bạn đọc \"%1\" không?").arg(tenBanDoc), QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        std::string maBD = maBanDoc.toStdString();
        dsBanDoc.erase(std::remove_if(dsBanDoc.begin(), dsBanDoc.end(), [&maBD](const BanDoc& bd) { return bd.getMaBD() == maBD; }), dsBanDoc.end());
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
    QStringList dataOut;
    bool ok = showSachDialog("Thêm Sách mới", {}, dataOut);
    if (ok) {
        std::string maSach = dataOut[0].toStdString();
        for (const auto& s : dsSach) {
            if (s.getMaSach() == maSach) {
                QMessageBox::warning(this, "Lỗi", "Mã sách đã tồn tại!");
                return;
            }
        }
        Book sachMoi(dataOut[0].toStdString(), dataOut[1].toStdString(), dataOut[2].toStdString(), dataOut[3].toStdString(), dataOut[4].toInt(), dataOut[5].toInt());
        dsSach.push_back(sachMoi);
        int newRow = ui->tableWidget_Sach->rowCount();
        ui->tableWidget_Sach->insertRow(newRow);
        ui->tableWidget_Sach->setItem(newRow, 0, new QTableWidgetItem(dataOut[0]));
        ui->tableWidget_Sach->setItem(newRow, 1, new QTableWidgetItem(dataOut[1]));
        ui->tableWidget_Sach->setItem(newRow, 2, new QTableWidgetItem(dataOut[2]));
        ui->tableWidget_Sach->setItem(newRow, 3, new QTableWidgetItem(dataOut[3]));
        ui->tableWidget_Sach->setItem(newRow, 4, new QTableWidgetItem(dataOut[4]));
        ui->tableWidget_Sach->setItem(newRow, 5, new QTableWidgetItem(dataOut[5]));
        QString fileSach = getDataPath("sach.txt");
        luuSachVaoFile(dsSach, fileSach.toStdString());
        QMessageBox::information(this, "Thành công", "Đã thêm sách mới!");
    }
}

void MainWindow::on_btnSua_Sach_clicked()
{
    int currentRow = ui->tableWidget_Sach->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Chưa chọn", "Vui lòng chọn một cuốn sách để sửa.");
        return;
    }
    QStringList dataIn;
    dataIn << ui->tableWidget_Sach->item(currentRow, 0)->text();
    dataIn << ui->tableWidget_Sach->item(currentRow, 1)->text();
    dataIn << ui->tableWidget_Sach->item(currentRow, 2)->text();
    dataIn << ui->tableWidget_Sach->item(currentRow, 3)->text();
    dataIn << ui->tableWidget_Sach->item(currentRow, 4)->text();
    dataIn << ui->tableWidget_Sach->item(currentRow, 5)->text();
    QStringList dataOut;
    bool ok = showSachDialog("Sửa thông tin sách", dataIn, dataOut);
    if (ok) {
        std::string maSach = dataIn[0].toStdString();
        for (auto& s : dsSach) {
            if (s.getMaSach() == maSach) {
                s.setTenSach(dataOut[1].toStdString());
                s.setTacGia(dataOut[2].toStdString());
                s.setTheLoai(dataOut[3].toStdString());
                s.setNamXuatBan(dataOut[4].toInt());
                s.setSoLuong(dataOut[5].toInt());
                break;
            }
        }
        ui->tableWidget_Sach->setItem(currentRow, 1, new QTableWidgetItem(dataOut[1]));
        ui->tableWidget_Sach->setItem(currentRow, 2, new QTableWidgetItem(dataOut[2]));
        ui->tableWidget_Sach->setItem(currentRow, 3, new QTableWidgetItem(dataOut[3]));
        ui->tableWidget_Sach->setItem(currentRow, 4, new QTableWidgetItem(dataOut[4]));
        ui->tableWidget_Sach->setItem(currentRow, 5, new QTableWidgetItem(dataOut[5]));
        QString fileSach = getDataPath("sach.txt");
        luuSachVaoFile(dsSach, fileSach.toStdString());
        QMessageBox::information(this, "Thành công", "Đã cập nhật thông tin sách!");
    }
}

void MainWindow::on_btnXoa_Sach_clicked()
{
    int currentRow = ui->tableWidget_Sach->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Chưa chọn", "Vui lòng chọn một cuốn sách để xóa.");
        return;
    }
    QString tenSach = ui->tableWidget_Sach->item(currentRow, 1)->text();
    QString maSach = ui->tableWidget_Sach->item(currentRow, 0)->text();
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Xác nhận xóa", QString("Bạn có chắc chắn muốn xóa sách \"%1\" không?").arg(tenSach), QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        std::string maS = maSach.toStdString();
        dsSach.erase(std::remove_if(dsSach.begin(), dsSach.end(), [&maS](const Book& s) { return s.getMaSach() == maS; }), dsSach.end());
        ui->tableWidget_Sach->removeRow(currentRow);
        QString fileSach = getDataPath("sach.txt");
        luuSachVaoFile(dsSach, fileSach.toStdString());
        QMessageBox::information(this, "Thành công", "Đã xóa sách!");
    }
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

// <<< CODE MỚI CHO NÚT MƯỢN SÁCH (ĐÃ SỬA TÊN)
void MainWindow::on_btnLapPhieu_clicked()
{
    QStringList dataOut;
    bool ok = showMuonSachDialog("Lập Phiếu Mượn Mới", dataOut);
    if (!ok) return; // Người dùng nhấn Hủy

    std::string maPhieu = dataOut[0].toStdString();
    std::string maBD = dataOut[1].toStdString();
    std::string maSach = dataOut[2].toStdString();

    // === BẮT ĐẦU XÁC THỰC ===
    // 1. Kiểm tra Mã phiếu trùng
    for (const auto& pm : dsPhieuMuon) {
        if (pm.getMaPhieu() == maPhieu) {
            QMessageBox::warning(this, "Lỗi", "Mã phiếu đã tồn tại. Vui lòng nhập mã khác.");
            return;
        }
    }

    // 2. Kiểm tra Bạn đọc có tồn tại không
    auto bdIt = std::find_if(dsBanDoc.begin(), dsBanDoc.end(),
                             [&maBD](const BanDoc& bd) { return bd.getMaBD() == maBD; });
    if (bdIt == dsBanDoc.end()) {
        QMessageBox::warning(this, "Lỗi", "Mã bạn đọc không tồn tại.");
        return;
    }

    // 3. Kiểm tra Sách có tồn tại và còn hàng không
    auto sachIt = std::find_if(dsSach.begin(), dsSach.end(),
                               [&maSach](const Book& s) { return s.getMaSach() == maSach; });
    if (sachIt == dsSach.end()) {
        QMessageBox::warning(this, "Lỗi", "Mã sách không tồn tại.");
        return;
    }
    if (sachIt->getSoLuong() <= 0) {
        QMessageBox::warning(this, "Lỗi", QString("Sách \"%1\" đã hết hàng (Số lượng: 0).").arg(QString::fromStdString(sachIt->getTenSach())));
        return;
    }
    // === XÁC THỰC THÀNH CÔNG ===

    // Lấy ngày hiện tại
    std::string ngayMuon = layNgayHienTai();

    // 1. Giảm số lượng sách
    sachIt->setSoLuong(sachIt->getSoLuong() - 1);

    // 2. Tạo phiếu mượn mới
    PhieuMuon pmMoi(maPhieu, maBD, maSach, ngayMuon);
    dsPhieuMuon.push_back(pmMoi);

    // 3. Lưu file
    luuSachVaoFile(dsSach, getDataPath("sach.txt").toStdString());
    luuPhieuMuonVaoFile(dsPhieuMuon, getDataPath("phieumuon.txt").toStdString());

    // 4. Cập nhật lại 2 bảng
    loadTableSach();
    loadTablePhieuMuon(); // Cập nhật cả bảng phiếu mượn

    QMessageBox::information(this, "Thành công", "Đã lập phiếu mượn thành công!");
}

// <<< CODE MỚI CHO NÚT TRẢ SÁCH
void MainWindow::on_btnTraSach_clicked()
{
    int currentRow = ui->tableWidget_PhieuMuon->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Chưa chọn", "Vui lòng chọn một phiếu mượn để trả sách.");
        return;
    }

    QString maPhieu = ui->tableWidget_PhieuMuon->item(currentRow, 0)->text();
    std::string maPhieuStd = maPhieu.toStdString();

    // Tìm phiếu mượn trong vector
    auto pmIt = std::find_if(dsPhieuMuon.begin(), dsPhieuMuon.end(),
                             [&maPhieuStd](const PhieuMuon& pm) { return pm.getMaPhieu() == maPhieuStd; });
    if (pmIt == dsPhieuMuon.end()) return; // Không tìm thấy (lỗi hi hữu)

    // === XÁC THỰC ===
    if (pmIt->getDaTra()) {
        QMessageBox::warning(this, "Lỗi", "Phiếu này đã được trả sách rồi.");
        return;
    }
    // === KẾT THÚC XÁC THỰC ===

    std::string ngayHienTai = layNgayHienTai();
    std::string ngayMuon = pmIt->getNgayMuon();

    // 1. Tính phí phạt (mặc định 7 ngày, 5000đ/ngày)
    int phiPhat = tinhPhiPhat(ngayMuon, ngayHienTai);

    // 2. Cập nhật phiếu mượn (đánh dấu đã trả, set ngày trả)
    pmIt->traSach(ngayHienTai);

    // 3. Tăng lại số lượng sách
    std::string maSach = pmIt->getMaSach();
    auto sachIt = std::find_if(dsSach.begin(), dsSach.end(),
                               [&maSach](const Book& s) { return s.getMaSach() == maSach; });
    if (sachIt != dsSach.end()) {
        sachIt->setSoLuong(sachIt->getSoLuong() + 1);
    }

    // 4. Lưu file
    luuSachVaoFile(dsSach, getDataPath("sach.txt").toStdString());
    luuPhieuMuonVaoFile(dsPhieuMuon, getDataPath("phieumuon.txt").toStdString());

    // 5. Cập nhật lại 2 bảng
    loadTableSach();
    loadTablePhieuMuon();

    // 6. Hiển thị thông báo
    QString thongBao = "Trả sách thành công!";
    if (phiPhat > 0) {
        thongBao += QString("\nPhí phạt trễ hạn: %1 VND.").arg(phiPhat);
    }
    QMessageBox::information(this, "Thành công", thongBao);
}

// <<< CODE MỚI CHO NÚT XÓA PHIẾU
void MainWindow::on_btnXoaPhieu_clicked()
{
    int currentRow = ui->tableWidget_PhieuMuon->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Chưa chọn", "Vui lòng chọn một phiếu mượn để xóa.");
        return;
    }

    QString maPhieu = ui->tableWidget_PhieuMuon->item(currentRow, 0)->text();
    std::string maPhieuStd = maPhieu.toStdString();

    // Tìm phiếu mượn
    auto pmIt = std::find_if(dsPhieuMuon.begin(), dsPhieuMuon.end(),
                             [&maPhieuStd](const PhieuMuon& pm) { return pm.getMaPhieu() == maPhieuStd; });
    if (pmIt == dsPhieuMuon.end()) return;

    // === XÁC THỰC ===
    if (!pmIt->getDaTra()) {
        QMessageBox::warning(this, "Lỗi", "Không thể xóa phiếu mượn chưa trả sách.\nVui lòng trả sách trước khi xóa.");
        return;
    }

    // === XÁC NHẬN XÓA ===
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Xác nhận xóa",
                                  QString("Bạn có chắc chắn muốn xóa phiếu %1 không?").arg(maPhieu),
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // 1. Xóa khỏi vector
        dsPhieuMuon.erase(pmIt);

        // 2. Lưu file
        luuPhieuMuonVaoFile(dsPhieuMuon, getDataPath("phieumuon.txt").toStdString());

        // 3. Xóa khỏi bảng
        ui->tableWidget_PhieuMuon->removeRow(currentRow);

        QMessageBox::information(this, "Thành công", "Đã xóa phiếu mượn.");
    }
}

// <<< SỬA LẠI TÊN HÀM TÌM KIẾM CHO KHỚP
void MainWindow::on_lineEdit_TimKiem_Phieu_textChanged(const QString &text)
{
    // Đổi tên hàm này trong mainwindow.h từ
    // on_lineEdit_TimKiem_Phieu_textChanged
    // thành
    // on_lineEdit_TimKiem_PhieuMuon_textChanged
    // (để khớp với tên đối tượng trong .ui)

    // Tạm thời mình sẽ code ở đây, nhưng bạn nên đổi lại tên hàm cho đúng

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
