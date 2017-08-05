#-------------------------------------------------
#
# Project created by QtCreator 2016-03-03T22:56:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyCalculator
TEMPLATE = app


SOURCES += main.cpp\
        calculatorwindow.cpp \
    calculator.cpp

HEADERS  += calculatorwindow.h \
    calculator.h

FORMS    += calculatorwindow.ui

RESOURCES += \
    images.qrc
