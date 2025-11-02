QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# Định nghĩa ứng dụng executable (BẮT BUỘC)
TEMPLATE = app
TARGET = LibraryManagement

# ===== ĐỊNH NGHĨA ĐƯỜNG DẪN DATA =====
# Đường dẫn đến thư mục Data từ thư mục .pro
DEFINES += DATAPATH=\\\"$$PWD/Data/\\\"

# File nguồn chính
SOURCES += \
    main.cpp \
    mainwindow.cpp \
    Models/BanDoc.cpp \
    Models/Book.cpp \
    Models/PhieuMuon.cpp \
    Utils/DateUtils.cpp \
    Utils/FileManager.cpp

# File header
HEADERS += \
    mainwindow.h \
    Models/BanDoc.h \
    Models/Book.h \
    Models/PhieuMuon.h \
    Utils/DateUtils.h \
    Utils/FileManager.h

# File UI
FORMS += \
    mainwindow.ui

# Đường dẫn thư mục chứa header files
INCLUDEPATH += Models Utils

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
