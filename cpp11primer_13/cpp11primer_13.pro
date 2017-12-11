TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += static_runtime

 
HEADERS += \
    sales_data.h \
    hasptr.h \
    message.h \
    folder.h \
    strvec.h


SOURCES += \
    main.cpp \
    sales_data.cpp \
    hasptr.cpp \
    message.cpp \
    folder.cpp \
    strvec.cpp

include(../msvc.pri)
include(../utils.pri)
include(../fmt.pri)
include(../zeromq.pri)
include(../nana.pri)
include(../libevent.pri)
include(../myboost.pri)

