QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DESTDIR = app_build
TARGET = test

SOURCES += \
    main.cpp \
    projdrill.cpp \
    src/action/ConstructionButton.cpp \
    src/action/RotateButton.cpp \
    src/action/SaveHelper.cpp \
    src/item/ItemBase.cpp \
    src/item/MachineShadow.cpp \
    src/machine/ItemGetter.cpp \
    src/machine/ItemSender.cpp \
    src/machine/MachineBase.cpp \
    src/machine/MachineCenter.cpp \
    src/machine/MachineConveyor.cpp \
    src/machine/MachineCutter.cpp \
    src/machine/MachineDriller.cpp \
    src/machine/MachineRubbishBin.cpp \
    src/map/MapBlockItem.cpp \
    src/map/MapCreator.cpp \
    src/map/MapDisplayWidget.cpp

HEADERS += \
    projdrill.h \
    src/BaseDefinitions.h \
    src/action/ConstructionButton.h \
    src/action/RotateButton.h \
    src/action/SaveHelper.h \
    src/item/ItemsBase.h \
    src/item/MachineShadow.h \
    src/machine/ItemGetter.h \
    src/machine/ItemSender.h \
    src/machine/MachineBase.h \
    src/machine/MachineCenter.h \
    src/machine/MachineConveyor.h \
    src/machine/MachineCutter.h \
    src/machine/MachineDriller.h \
    src/machine/MachineRubbishBin.h \
    src/map/MapBlockItem.h \
    src/map/MapCreator.h \
    src/map/MapDisplayWidget.h

FORMS += \
    projdrill.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
