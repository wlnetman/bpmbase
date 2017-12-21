TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += static_runtime

 
HEADERS += \
    template_compile.h \
    iterator.h \
    impl.h \
    range.h

SOURCES += \
    main.cpp \
    iterator.cpp \
    impl.cpp

include(../msvc.pri)
include(../utils.pri)
include(../fmt.pri)
include(../zeromq.pri)
include(../nana.pri)
include(../libevent.pri)
include(../myboost.pri)

