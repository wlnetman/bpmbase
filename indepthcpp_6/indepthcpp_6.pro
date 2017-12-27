TEMPLATE = app
CONFIG += console
CONFIG -= qt

#The following options take an effect only on macOS:
#app_bundle Puts the executable into a bundle (this is the default).
#lib_bundle Puts the library into a library bundle.
CONFIG -= app_bundle
CONFIG += static_runtime

SOURCES += \
        main.cpp

include(../msvc.pri)
include(../utils.pri)
include(../fmt.pri)
include(../zeromq.pri)
include(../nana.pri)
include(../libevent.pri)
include(../myboost.pri)

HEADERS += \
    timer.h

