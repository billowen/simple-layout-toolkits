QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  \
    gdstest.cpp \
    main.cpp

HEADERS += \
    gdstest.h

include(../../src/gds/gds.pri)

INCLUDEPATH += ../../src/gds/
