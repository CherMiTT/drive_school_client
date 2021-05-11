QT += testlib
QT += gui
QT += widgets core
CONFIG += qt warn_on depend_includepath testcase

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

#CONFIG += c++17

INCLUDEPATH = ../../src

TEMPLATE = app

SOURCES +=  tst_enterformwidget.cpp \
            ../../src/enterformwidget.cpp

HEADERS += ../../src/enterformwidget.h

FORMS += ../../src/enterformwidget.ui
