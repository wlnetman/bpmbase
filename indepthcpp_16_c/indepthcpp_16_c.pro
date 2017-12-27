CONFIG += app
CONFIG -= qt
CONFIG += app_bundle
CONFIG += static_runtime

SOURCE += \
        main.cpp

include(../msvc.pri)
include(../utils.pri)
include(../fmt.pri)
include(../evpp.pri)
include(../gflags.pri)
include(../glogs.pri)
include(../libevent.pri)
include(../zeromq.pri)
include(../myboost.pri)
