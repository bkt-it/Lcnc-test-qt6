#-------------------------------------------------
#
# Project created by QtCreator 2022-01-12T12:11:31
#
#-------------------------------------------------

QT += core gui widgets sql network multimedia multimediawidgets designer charts webenginewidgets webview

CONFIG += c++17
CONFIG += use_gold_linker


TARGET = LcncQt6
TEMPLATE = app

HOME_DIR = $$system(echo $HOME)

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#QT_PLUGIN_PATH += $$HOME_DIR/Qt/Tools/QtCreator/lib/Qt/plugins/designer

#INCLUDEPATH += $$PWD/../../../../../../data/plc \
INCLUDEPATH += /usr/include/linuxcnc
INCLUDEPATH += /usr/include/linuxcnc/
INCLUDEPATH += /usr/include
INCLUDEPATH += /usr/lib
INCLUDEPATH += /usr/share/linuxcnc
INCLUDEPATH += /usr/lib/linuxcnc/modules
INCLUDEPATH += $$HOME_DIR/linuxcnc-source-dir/src/hal/utils
INCLUDEPATH += $$HOME_DIR/linuxcnc-source-dir/src/hal
INCLUDEPATH += $$HOME_DIR/linuxcnc-source-dir/src
INCLUDEPATH+=  $$HOME_DIR/Qt/Tools/QtCreator/lib/Qt/plugins/designer
INCLUDEPATH+=  $$PWD/wled-designer-plugin
INCLUDEPATH+=  $$PWD/Lcnc-test-qt6/resources#INCLUDEPATH += $$PWD/Lcnc-test-qt6/src/plugins/opcua/open62541


LIBS+=-L $$HOME_DIR/Qt/Tools/QtCreator/lib/Qt/plugins/designer -lhalwidgetsplugin
LIBS+=  -Iinclude -I/usr/lib/linuxcnc/canterp.so
#LIBS += -L/usr/lib -lnml -llinuxcnchal -llinuxcnc -llinuxcncini -DULAPI -lposemath -Isrc/emc/rs274ngc -ltirpc #-llinuxcnc
LIBS += -Iinclude -Isrc/emc/rs274ngc -Llib -lnml -llinuxcnc  -llinuxcnchal -llinuxcncini -llinuxcnchal  -DULAPI -lposemath -ltirpc
LIBS += -lGLU -lGL
LIBS += -Iinclude-I/usr/lib/x86_64-linux-gnu/libopen62541.so


SOURCES += \
        main.cpp \
        mainwindow.cpp


HEADERS += \
        get_command.h \
        hal_priv.h \
        mainwindow.h \
        send_command.h


FORMS += \
        mainwindow.ui


RESOURCES += \
    stylessheet.qrc

#install
target.path = $$PWD/Lcnc-test-qt6/Lcnc-test-qt6
INSTALLS += target

