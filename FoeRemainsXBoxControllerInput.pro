TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lXInput

SOURCES += main.cpp \
    Keyboard.cpp \
    WindowsFunctions.cpp

HEADERS += \
    Keyboard.h \
    WindowsConstants.h \
    WindowsFunctions.h
