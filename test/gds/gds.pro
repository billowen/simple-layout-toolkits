include(gtest_dependency.pri)
include(../../src/gds/gds.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread

HEADERS += \
        tst_boundary.h \
        tst_path.h

SOURCES += \
        main.cpp

INCLUDEPATH += ../../src/gds/
