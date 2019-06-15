#-------------------------------------------------
#
# Project created by QtCreator 2018-11-29T14:54:33
#
#-------------------------------------------------

QT       += core gui
QT       += network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = weatherapp
TEMPLATE = app
LIBS += -lcurl

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    backend/pugixml-1.9/pugixml.cpp \
    backend/Connection.cpp \
    backend/Controller.cpp \
    backend/Model.cpp \
    backend/MSCParser.cpp \
    backend/MSCUrl.cpp

HEADERS  += mainwindow.h \
    backend/pugixml-1.9/pugiconfig.hpp \
    backend/pugixml-1.9/pugixml.hpp \
    backend/Connection.h \
    backend/Controller.h \
    backend/Model.h \
    backend/MSCParser.h \
    backend/MSCUrl.h

RESOURCES += \
    image.qrc \

FORMS    += mainwindow.ui
