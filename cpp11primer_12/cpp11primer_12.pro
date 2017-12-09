TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += static_runtime

HEADERS += \
    strblob.h \
    strblobptr.h \
    textquery.h \
    queryresult.h

SOURCES += \
    main.cpp \
    strblob.cpp \
    strblobptr.cpp \
    textquery.cpp \
    queryresult.cpp

include(../msvc.pri)
include(../utils.pri)
include(../fmt.pri)
include(../zeromq.pri)
include(../nana.pri)
include(../libevent.pri)
include(../myboost.pri)

