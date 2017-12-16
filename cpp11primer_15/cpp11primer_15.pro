TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += static_runtime

 

HEADERS += \
    quote.h \
    bulk_quote.h \
    base.h \
    disc_quote.h \
    basket.h \
    query.h \
    textquery.h \
    queryresult.h


SOURCES += \
    main.cpp \
    quote.cpp \
    bulk_quote.cpp \
    base.cpp \
    disc_quote.cpp \
    basket.cpp \
    query.cpp \
    textquery.cpp \
    queryresult.cpp


include(../msvc.pri)
include(../utils.pri)
include(../fmt.pri)
include(../zeromq.pri)
include(../nana.pri)
include(../libevent.pri)
include(../myboost.pri)

