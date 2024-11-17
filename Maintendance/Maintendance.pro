QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    attendanceentry.cpp \
    attendancelog.cpp \
    employee.cpp \
    generalemployeelogin.cpp \
    guard.cpp \
    guardlogin.cpp \
    leaveapplication.cpp \
    leaveapplicationform.cpp \
    leavebalance.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    markattendancescreen.cpp \
    supervisorlogin.cpp \
    user.cpp \
    loginpass.cpp \
    viewattendance.cpp

HEADERS += \
    attendanceentry.h \
    attendancelog.h \
    employee.h \
    generalemployeelogin.h \
    guard.h \
    guardlogin.h \
    leaveapplication.h \
    leaveapplicationform.h \
    leavebalance.h \
    logindialog.h \
    mainwindow.h \
    markattendancescreen.h \
    supervisorlogin.h \
    user.h \
    utils.h \
    viewattendance.h

FORMS += \
    generalemployeelogin.ui \
    guardlogin.ui \
    leaveapplicationform.ui \
    logindialog.ui \
    mainwindow.ui \
    markattendancescreen.ui \
    supervisorlogin.ui \
    viewattendance.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    pic.png

RESOURCES += \
    attendancelogs.qrc \
    resources.qrc
