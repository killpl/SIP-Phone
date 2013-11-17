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
    registrationsmodel.cpp \
    contactdelegate.cpp \
    historymodel.cpp \
    addcontact.cpp

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
    contactdelegate.h \
    registrationsmodel.h \
    historymodel.h \
    addcontact.h

FORMS    += okno.ui \
    settings.ui \
    addcontact.ui


RESOURCES += \
    Resources.qrc

OTHER_FILES += \
    style.qss

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../usr/lib64/ -lopal
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../usr/lib64/ -lopald
else:symbian: LIBS += -lopal
else:unix: LIBS += -L$$PWD/../../../usr/lib64/ -lopal

INCLUDEPATH += $$PWD/../../../usr/include/opal
DEPENDPATH += $$PWD/../../../usr/include/opal

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../usr/lib64/ -lpt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../usr/lib64/ -lptd
else:symbian: LIBS += -lpt
else:unix: LIBS += -L$$PWD/../../../usr/lib64/ -lpt

INCLUDEPATH += $$PWD/../../../usr/lib64
DEPENDPATH += $$PWD/../../../usr/lib64
