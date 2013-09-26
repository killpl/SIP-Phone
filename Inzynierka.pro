#-------------------------------------------------
#
# Project created by QtCreator 2013-03-05T19:00:40
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Inzynierka
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        okno.cpp \
    phonemanager.cpp \
    phonesipendpoint.cpp \
    phonepcssendpoint.cpp \
    observer.cpp \
    logger.cpp \
    contactsmodel.cpp \
    configuration.cpp \
    settings.cpp \
    ContactDelegate.cpp

HEADERS  += okno.h \
    phonemanager.h \
    phonesipendpoint.h \
    phonepcssendpoint.h \
    observer.h \
    logger.h \
    contactsmodel.h \
    configuration.h \
    structs.h \
    settings.h \
    ContactDelegate.h

FORMS    += okno.ui \
    settings.ui


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../usr/local/lib/release/ -lopal
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../usr/local/lib/debug/ -lopal
else:symbian: LIBS += -lopal
else:unix: LIBS += -L$$PWD/../../../usr/local/lib/ -lopal

INCLUDEPATH += $$PWD/../../../usr/local/include/opal
DEPENDPATH += $$PWD/../../../usr/local/include/opal

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../usr/local/lib/release/ -lpt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../usr/local/lib/debug/ -lpt
else:symbian: LIBS += -lpt
else:unix: LIBS += -L$$PWD/../../../usr/local/lib/ -lpt

INCLUDEPATH += $$PWD/../../../usr/local/include
DEPENDPATH += $$PWD/../../../usr/local/include
