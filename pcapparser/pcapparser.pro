TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

DEFINES += WEBRTC_POSIX

INCLUDEPATH += ../filters/FecReceiver

LIBS += -lpthread

SOURCES += main.cpp \
    PcapGraph.cpp

unix:!macx: LIBS += -L$$PWD/../build-filters-Desktop-Debug/ -lfilters

INCLUDEPATH += $$PWD/../filters
DEPENDPATH += $$PWD/../filters

unix:!macx: PRE_TARGETDEPS += $$PWD/../build-filters-Desktop-Debug/libfilters.a

HEADERS += \
    PcapGraph.h
