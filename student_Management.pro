QT       += core gui
//加入SQL模块
QT += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    add_user.cpp \
    dlg_addstu.cpp \
    main.cpp \
    mainwindow.cpp \
    page_login.cpp \
    stusql.cpp \
    update_user.cpp

HEADERS += \
    add_user.h \
    dlg_addstu.h \
    mainwindow.h \
    page_login.h \
    stusql.h \
    update_user.h

FORMS += \
    add_user.ui \
    dlg_addstu.ui \
    mainwindow.ui \
    page_login.ui \
    update_user.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES +=
