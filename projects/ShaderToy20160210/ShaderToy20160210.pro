#-------------------------------------------------
#
# Project created by QtCreator 2016-02-10T02:55:30
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ShaderToy20160210
TEMPLATE = app


SOURCES += main.cpp\
		mainwin.cpp \
    oglwgt.cpp \
    shaderprogram.cpp

HEADERS  += mainwin.h \
    oglwgt.h \
    shaderprogram.h

FORMS    += mainwin.ui \
    oglwgt.ui
QMAKE_CXXFLAGS += -std=c++11

RESOURCES += \
    resources.qrc
