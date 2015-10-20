# Config

TEMPLATE = lib
TARGET   = qmlgantt
QT      += qml quick
CONFIG  += qt

DEFINES += Q_GANTT
DEFINES += Q_GANTT_LIB

# Destination

win32:CONFIG(debug, debug|release): DLLDESTDIR = $$quote($$OUT_PWD/../build/debug)
else:win32:CONFIG(release, debug|release): DLLDESTDIR = $$quote($$OUT_PWD/../build/release)
else:unix: TARGET = $$quote($$OUT_PWD/../build/qmlgantt)

# Files

INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/qganttglobal.h \
    $$PWD/qrangeview.h \
    $$PWD/qabstractrangemodel.h \
    $$PWD/qganttmodel.h \
    $$PWD/qganttmodelitem.h

SOURCES += \
    $$PWD/qrangeview.cpp \
    $$PWD/qabstractrangemodel.cpp \
    $$PWD/qganttmodel.cpp \
    $$PWD/qganttmodelitem.cpp
