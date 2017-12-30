CTPSDK_DIR = $$PWD/ctpsdk

INCLUDEPATH += \
    $$CTPSDK_DIR/include

HEADERS += \
        $$CTPSDK_DIR/include/ctpsdk/ThostFtdcUserApiDataType.h \
        $$CTPSDK_DIR/include/ctpsdk/ThostFtdcUserApiStruct.h \
        $$CTPSDK_DIR/include/ctpsdk/ThostFtdcMdApi.h \
        $$CTPSDK_DIR/include/ctpsdk/ThostFtdcTraderApi.h

#$$CTPSDK_DIR\lib\*.lib
LIBS += \
        $$CTPSDK_DIR/lib/thosttraderapi.lib \
        $$CTPSDK_DIR/lib/thostmduserapi.lib
