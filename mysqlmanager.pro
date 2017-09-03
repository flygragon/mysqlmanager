#-------------------------------------------------
#
# Project created by QtCreator 2017-05-17T22:55:46
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mysqlmanager
TEMPLATE = app

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
        widget.cpp \
    mysql.cpp \
    createconnection.cpp \
    newaddtion.cpp \
    newuser.cpp \
    modifypasswd.cpp \
    newconnection.cpp \
    additionnew.cpp \
    adduser.cpp \
    resetpwd.cpp \
    deleteuser.cpp \
    newtable.cpp \
    newinsert.cpp \
    tablealter.cpp \
    setbackuppath.cpp

HEADERS  += widget.h \
    mysql.h \
    createconnection.h \
    newaddtion.h \
    newuser.h \
    modifypasswd.h \
    newconnection.h \
    additionnew.h \
    adduser.h \
    resetpwd.h \
    deleteuser.h \
    newtable.h \
    newinsert.h \
    tablealter.h \
    setbackuppath.h

FORMS    += widget.ui \
    createconnection.ui \
    newaddtion.ui \
    newuser.ui \
    modifypasswd.ui \
    newconnection.ui \
    additionnew.ui \
    adduser.ui \
    resetpwd.ui \
    deleteuser.ui \
    newtable.ui \
    newinsert.ui \
    tablealter.ui \
    setbackuppath.ui
