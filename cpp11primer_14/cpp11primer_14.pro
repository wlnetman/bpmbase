TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += static_runtime

 

HEADERS += \
    sales_data.h \
    strvec.h \
    strblob.h \
    strblobptr.h


SOURCES += \
    strvec.cpp \
    sales_data.cpp \
    main.cpp \
    strblob.cpp \
    strblobptr.cpp


include(../msvc.pri)
include(../utils.pri)
include(../fmt.pri)
include(../zeromq.pri)
include(../nana.pri)
include(../libevent.pri)
include(../myboost.pri)

