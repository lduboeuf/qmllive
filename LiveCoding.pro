TEMPLATE = app
TARGET = livecoding

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    filewatcher.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    filewatcher.h

UBUNTU_TOUCH {
    message("building for Ubuntu Touch")


    target.path = /
    click_files.path = /
    click_files.files = $$PWD/packaging/ubuntu_touch/*

    INSTALLS+=click_files
}
