QT       += core gui core5compat

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

FORMS += \
    src/mainwindow.ui \
    src/wgtimage.ui

HEADERS += \
    src/mainwindow.h \
    src/quazip/quazip/JlCompress.h \
    src/quazip/quazip/ioapi.h \
    src/quazip/quazip/minizip_crypt.h \
    src/quazip/quazip/quaadler32.h \
    src/quazip/quazip/quachecksum32.h \
    src/quazip/quazip/quacrc32.h \
    src/quazip/quazip/quagzipfile.h \
    src/quazip/quazip/quaziodevice.h \
    src/quazip/quazip/quazip.h \
    src/quazip/quazip/quazip_global.h \
    src/quazip/quazip/quazip_qt_compat.h \
    src/quazip/quazip/quazipdir.h \
    src/quazip/quazip/quazipfile.h \
    src/quazip/quazip/quazipfileinfo.h \
    src/quazip/quazip/quazipnewinfo.h \
    src/quazip/quazip/unzip.h \
    src/quazip/quazip/zip.h \
    src/wgtimage.h

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/quazip/quazip/JlCompress.cpp \
    src/quazip/quazip/qioapi.cpp \
    src/quazip/quazip/quaadler32.cpp \
    src/quazip/quazip/quachecksum32.cpp \
    src/quazip/quazip/quacrc32.cpp \
    src/quazip/quazip/quagzipfile.cpp \
    src/quazip/quazip/quaziodevice.cpp \
    src/quazip/quazip/quazip.cpp \
    src/quazip/quazip/quazipdir.cpp \
    src/quazip/quazip/quazipfile.cpp \
    src/quazip/quazip/quazipfileinfo.cpp \
    src/quazip/quazip/quazipnewinfo.cpp \
    src/quazip/quazip/unzip.c \
    src/quazip/quazip/zip.c \
    src/wgtimage.cpp

LIBS += -lz

#TRANSLATIONS += \
#    untitled_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

ICON = logo.icns

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    src/quazip/quazip/QuaZipConfig.cmake.in \
    src/quazip/quazip/quazip.pc.cmakein
