QT       += core gui network
QMAKE_CXXFLAGS += -Wa,-mbig-obj

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++23

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    choosetheproject.cpp \
    createaccountdlg.cpp \
    main.cpp \
    mainwindow.cpp \
    server.cpp \
    signindlg.cpp \
    socket.cpp \
    workwindow.cpp

HEADERS += \
    choosetheproject.h \
    createaccountdlg.h \
    mainwindow.h \
    server.h \
    signindlg.h \
    socket.h \
    workwindow.h

FORMS += \
    choosetheproject.ui \
    createaccountdlg.ui \
    mainwindow.ui \
    signindlg.ui \
    workwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
