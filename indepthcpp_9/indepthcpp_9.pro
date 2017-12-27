TEMPLATE = app
CONFIG += console
CONFIG -= qt
CONFIG -= app_bundle
CONFIG += static_runtime

HEADERS += \
        threadpool.hpp \
        syncqueue.hpp

SOURCES += \
        main.cpp

include(../msvc.pri)
include(../utils.pri)
include(../myboost.pri)
include(../fmt.pri)
include(../evpp.pri)
include(../gflags.pri)
include(../glog.pri)
include(../gtest.pri)
