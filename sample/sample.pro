TEMPLATE = app
TARGET   = sample

QT += qml quick widgets

RESOURCES += $$PWD/resource/qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =


# Configure Dependencies

INCLUDEPATH += $$PWD/../lib
DEPENDPATH  += $$PWD/../lib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../lib/release/ -lqmlgantt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../lib/debug/ -lqmlgantt
else:unix: LIBS += -L$$OUT_PWD/../build/ -lqmlgantt

include($$PWD/src/src.pri)

# Default rules for deployment.
include($$PWD/deployment.pri)
