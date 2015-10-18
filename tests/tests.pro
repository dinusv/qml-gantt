
TARGET   = test_qmlgantt
TEMPLATE = app
QT      += qml quick testlib
CONFIG  += console testcase

# Configure Dependencies

INCLUDEPATH += $$PWD/../lib
DEPENDPATH  += $$PWD/../lib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../lib/release/ -lqmlgantt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../lib/debug/ -lqmlgantt
else:unix: LIBS += -L$$OUT_PWD/../build/ -lqmlgantt

HEADERS += \
    qtestrunner.h \
    qganttmodeltest.h \
    qrangeviewtest.h \
    qviewportbenchmarktest.h

SOURCES += \
    main.cpp \
    qtestrunner.cpp \
    qganttmodeltest.cpp \
    qrangeviewtest.cpp \
    qviewportbenchmarktest.cpp

