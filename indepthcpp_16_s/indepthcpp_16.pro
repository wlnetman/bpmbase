CONFIG += app
CONFIG -= qt
CONFIG += app_bundle
CONFIG += static_runtime

SOURCE += \
        main.cpp

include(../msvc.pri)
include(../utils.pri)
include(../myboost.pri)
include(../fmt.pri)
include(../evpp.pri)
include(../gflags.pri)
include(../glog.pri)
include(../gtest.pri)

