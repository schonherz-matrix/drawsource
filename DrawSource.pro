######################################################################
# Automatically generated by qmake (3.0) Sun Sep 20 15:14:39 2015
######################################################################

TEMPLATE = app
TARGET = DrawSource
QT += core gui widgets
INCLUDEPATH += .
QMAKE_CXXFLAGS += -std=c++11 -Wall -pedantic
QMAKE_LFLAGS += -lm

# Input
HEADERS += drawsender.h mainwindow.h griddrawer.h timer.h matrix.h rpc.h rgb.h array2D.hpp
SOURCES += main.cpp drawsender.cpp mainwindow.cpp griddrawer.cpp timer.cpp rpc.cpp
