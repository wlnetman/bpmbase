TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += static_runtime

SOURCES += \
        main.cpp \
    marketcollection.cpp
        
include(../msvc.pri)
include(../utils.pri)
include(../fmt.pri)
include(../glog.pri)
include(../gtest.pri)
include(../myboost.pri)
include(../ctpsdk.pri)

HEADERS += \
    marketcollection.h \
    simplequeue.h
