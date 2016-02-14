TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    weather_system.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    weather_system.hpp

QMAKE_CXXFLAGS += -std=c++14
