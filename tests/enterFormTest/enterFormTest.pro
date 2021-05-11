QT += gui
QT += widgets core network
QT += testlib
CONFIG += qt warn_on depend_includepath testcase
#CONFIG += c++17
#greaterThan(QT_MAJOR_VERSION, 5): QT += testlib widgets network

TEMPLATE = app

INCLUDEPATH = ../../src

SOURCES +=  tst_enterformtest.cpp \
            ../../src/enterformwidget.cpp \
            ../../src/session.cpp \
            ../../src/requester.cpp

HEADERS += ../../src/enterformwidget.h \
           ../../src/forms.h \
           ../../src/session.h \
           ../../src/requester.h

FORMS += ../../src/enterformwidget.ui
