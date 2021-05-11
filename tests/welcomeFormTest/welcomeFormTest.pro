QT += testlib
QT += gui widgets
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

INCLUDEPATH = ../../src

SOURCES +=  tst_welcomeformtest.cpp \
            ../../src/welcomeformwidget.cpp

HEADERS += ../../src/welcomeformwidget.h

FORMS += ../../src/welcomeformwidget.ui
