
OBJECTS_DIR = ./.obj
MOC_DIR = ./.moc

TEMPLATE = lib

VERSION = 1.0.0

HEADERS += \
    factory.h \
    item.h \
    constructor.h

SOURCES += \
    factory.cpp \
    constructor.cpp

target.path = /usr/local/lib
includes.files = $$HEADERS
includes.path = /usr/local/include

INSTALLS += target includes









