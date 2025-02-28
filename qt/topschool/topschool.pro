QT       += core gui
QT       += sql
#QT       += network

ICON = ./logo.icns

#LIBS     += /opt/homebrew/opt/openssl@3/lib/libcrypto.a \
#            /opt/homebrew/opt/openssl@3/lib/libssl.a

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    commondelegate.cpp \
    commontools.cpp \
    customsqltablemodel.cpp \
    frmfilteroption.cpp \
    frmschooldetial.cpp \
    main.cpp \
    mainwindow.cpp \
    sqltool.cpp

HEADERS += \
    commondelegate.h \
    commontools.h \
    customsqltablemodel.h \
    frmfilteroption.h \
    frmschooldetial.h \
    mainwindow.h \
    sqltool.h

FORMS += \
    frmfilteroption.ui \
    frmschooldetial.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

#COPY_DIR=$$PWD
#cp_kk.file += \
#          gaokao.sqlite
#cp_kk.path  += $$OUT_PWD
#COPIES +=  cp_kk

#QMAKE_APPLE_DEVICE_ARCHS = x86_64 arm64

mac:QMAKE_POST_LINK += cp -f $$PWD/gaokao2025.sqlite $${OUT_PWD}/$${TARGET}.app/Contents/MacOS
SRC_FILE=$$PWD/gaokao.sqlite
SRC_FILE=$$replace(SRC_FILE,/,\\)
DST_FILE=$$OUT_PWD/release
DST_FILE=$$replace(DST_FILE,/,\\)
win32:QMAKE_POST_LINK += copy  $$SRC_FILE $$DST_FILE /y
#win64:QMAKE_POST_LINK +=echo $$PWD
# QMAKE_POST_LINK +=echo $$PWD;echo $${OUT_PWD}
