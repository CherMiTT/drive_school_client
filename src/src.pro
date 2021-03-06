QT       += core gui

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets network

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addcardialog.cpp \
    addlessondialog.cpp \
    addtestdialog.cpp \
    adminpanelformwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    menuformwidget.cpp \
    requester.cpp \
    session.cpp \
    testdialog.cpp \
    welcomeformwidget.cpp \
    enterformwidget.cpp \
    validator.cpp

HEADERS += \
    addcardialog.h \
    addlessondialog.h \
    addtestdialog.h \
    adminpanelformwidget.h \
    mainwindow.h \
    menuformwidget.h \
    requester.h \
    session.h \
    testdialog.h \
    welcomeformwidget.h \
    enterformwidget.h \
    forms.h \
    validator.h

FORMS += \
    addcardialog.ui \
    addlessondialog.ui \
    addtestdialog.ui \
    adminpanelformwidget.ui \
    mainwindow.ui \
    mainwindow.ui \
    menuformwidget.ui \
    testdialog.ui \
    welcomeformwidget.ui \
    enterformwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
