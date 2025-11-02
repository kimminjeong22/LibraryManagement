/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QLabel *label;
    QLineEdit *lineEdit_TimKiem_BanDoc;
    QTableWidget *tableWidget_BanDoc;
    QPushButton *btnThem_BanDoc;
    QPushButton *btnSua_BanDoc;
    QPushButton *btnXoa_BanDoc;
    QWidget *tab_3;
    QLabel *label_2;
    QLineEdit *lineEdit_TimKiem_Sach;
    QTableWidget *tableWidget_Sach;
    QPushButton *btnThem_Sach;
    QPushButton *btnSua_Sach;
    QPushButton *btnXoa_Sach;
    QWidget *tab_2;
    QLabel *label_3;
    QPushButton *btnLapPhieu;
    QPushButton *btnTraSach;
    QPushButton *btnXoaPhieu;
    QTableWidget *tableWidget_PhieuMuon;
    QLineEdit *lineEdit_TimKiem_PhieuMuon;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName("gridLayout_2");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setMinimumSize(QSize(778, 0));
        tab = new QWidget();
        tab->setObjectName("tab");
        label = new QLabel(tab);
        label->setObjectName("label");
        label->setGeometry(QRect(250, 10, 63, 20));
        lineEdit_TimKiem_BanDoc = new QLineEdit(tab);
        lineEdit_TimKiem_BanDoc->setObjectName("lineEdit_TimKiem_BanDoc");
        lineEdit_TimKiem_BanDoc->setGeometry(QRect(60, 40, 461, 28));
        tableWidget_BanDoc = new QTableWidget(tab);
        tableWidget_BanDoc->setObjectName("tableWidget_BanDoc");
        tableWidget_BanDoc->setGeometry(QRect(10, 140, 591, 241));
        btnThem_BanDoc = new QPushButton(tab);
        btnThem_BanDoc->setObjectName("btnThem_BanDoc");
        btnThem_BanDoc->setGeometry(QRect(140, 400, 90, 29));
        btnSua_BanDoc = new QPushButton(tab);
        btnSua_BanDoc->setObjectName("btnSua_BanDoc");
        btnSua_BanDoc->setGeometry(QRect(250, 400, 90, 29));
        btnXoa_BanDoc = new QPushButton(tab);
        btnXoa_BanDoc->setObjectName("btnXoa_BanDoc");
        btnXoa_BanDoc->setGeometry(QRect(360, 400, 90, 29));
        tabWidget->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        label_2 = new QLabel(tab_3);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(260, 20, 63, 20));
        lineEdit_TimKiem_Sach = new QLineEdit(tab_3);
        lineEdit_TimKiem_Sach->setObjectName("lineEdit_TimKiem_Sach");
        lineEdit_TimKiem_Sach->setGeometry(QRect(60, 40, 461, 28));
        tableWidget_Sach = new QTableWidget(tab_3);
        tableWidget_Sach->setObjectName("tableWidget_Sach");
        tableWidget_Sach->setGeometry(QRect(30, 100, 591, 241));
        btnThem_Sach = new QPushButton(tab_3);
        btnThem_Sach->setObjectName("btnThem_Sach");
        btnThem_Sach->setGeometry(QRect(130, 420, 90, 29));
        btnSua_Sach = new QPushButton(tab_3);
        btnSua_Sach->setObjectName("btnSua_Sach");
        btnSua_Sach->setGeometry(QRect(270, 420, 90, 29));
        btnXoa_Sach = new QPushButton(tab_3);
        btnXoa_Sach->setObjectName("btnXoa_Sach");
        btnXoa_Sach->setGeometry(QRect(420, 420, 90, 29));
        tabWidget->addTab(tab_3, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        label_3 = new QLabel(tab_2);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(11, 11, 63, 20));
        btnLapPhieu = new QPushButton(tab_2);
        btnLapPhieu->setObjectName("btnLapPhieu");
        btnLapPhieu->setGeometry(QRect(330, 350, 123, 29));
        btnTraSach = new QPushButton(tab_2);
        btnTraSach->setObjectName("btnTraSach");
        btnTraSach->setGeometry(QRect(200, 350, 101, 29));
        btnXoaPhieu = new QPushButton(tab_2);
        btnXoaPhieu->setObjectName("btnXoaPhieu");
        btnXoaPhieu->setGeometry(QRect(40, 350, 111, 29));
        tableWidget_PhieuMuon = new QTableWidget(tab_2);
        tableWidget_PhieuMuon->setObjectName("tableWidget_PhieuMuon");
        tableWidget_PhieuMuon->setGeometry(QRect(0, 130, 601, 192));
        lineEdit_TimKiem_PhieuMuon = new QLineEdit(tab_2);
        lineEdit_TimKiem_PhieuMuon->setObjectName("lineEdit_TimKiem_PhieuMuon");
        lineEdit_TimKiem_PhieuMuon->setGeometry(QRect(20, 50, 581, 28));
        tabWidget->addTab(tab_2, QString());

        gridLayout_2->addWidget(tabWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "T\303\254m Ki\341\272\277m", nullptr));
        btnThem_BanDoc->setText(QCoreApplication::translate("MainWindow", "Th\303\252m", nullptr));
        btnSua_BanDoc->setText(QCoreApplication::translate("MainWindow", "S\341\273\255a", nullptr));
        btnXoa_BanDoc->setText(QCoreApplication::translate("MainWindow", "X\303\263a", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Qu\341\272\243n L\303\275 B\341\272\241n \304\220\341\273\215c", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "T\303\254m Ki\341\272\277m", nullptr));
        btnThem_Sach->setText(QCoreApplication::translate("MainWindow", "Th\303\252m", nullptr));
        btnSua_Sach->setText(QCoreApplication::translate("MainWindow", "S\341\273\255a", nullptr));
        btnXoa_Sach->setText(QCoreApplication::translate("MainWindow", "X\303\263a", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("MainWindow", "Qu\341\272\243n L\303\275 S\303\241ch", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "T\303\254m Ki\341\272\277m", nullptr));
        btnLapPhieu->setText(QCoreApplication::translate("MainWindow", "L\341\272\255p Phi\341\272\277u M\306\260\341\273\243n", nullptr));
        btnTraSach->setText(QCoreApplication::translate("MainWindow", "Tr\341\272\243 S\303\241ch", nullptr));
        btnXoaPhieu->setText(QCoreApplication::translate("MainWindow", "X\303\263a Phi\341\272\277u", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Qu\341\272\243n L\303\275 Phi\341\272\277u M\306\260\341\273\243n", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
