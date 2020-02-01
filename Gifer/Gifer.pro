TEMPLATE = app

QT += qml quick core widgets
CONFIG += c++11

macx{
    message("compile for mac os x")
    ICON = Images/logo.icns
}

win32{
    message("compile for windows")
    RC_ICONS = Images/logo.ico
    LIBS += "-Wl,--subsystem,windows"
    CONFIG -= console
}

INCLUDEPATH += "Include"

SOURCES += Source/main.cpp \
    Source/pointmanager.cpp \
    Source/windowgrabber.cpp \
    Source/waitwindowanimation.cpp \
    Source/imagescombiner.cpp \
    Source/waitimageprovider.cpp

HEADERS += \
    Include/pointmanager.h \
    Include/windowgrabber.h \
    Include/logprinter.hpp \
    Include/waitwindowanimation.h \
    Include/imagescombiner.h \
    Include/waitimageprovider.h

RESOURCES += qml.qrc

# Custom output directory and use it.
OUTPUT_DIR = "Output"
UI_DIR = $${OUTPUT_DIR}
MOC_DIR = $${OUTPUT_DIR}
OBJECTS_DIR = $${OUTPUT_DIR}
RCC_DIR = $${OUTPUT_DIR}

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS QT_MESSAGELOGCONTEXT

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

