QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Coordinates.cpp \
    GeoSimulationMap.cpp \
    UserEquipment.cpp \
    base_functions.cpp \
    distribution.cpp \
    main.cpp \
    mainwindow.cpp \
    output.cpp \
    simulationmap.cpp \
    simulationobject.cpp

HEADERS += \
    Coordinates.hpp \
    GeoSimulationMap.hpp \
    UserEquipment.hpp \
    base_functions.hpp \
    distribution.hpp \
    mainwindow.h \
    output.hpp \
    simulationmap.hpp \
    simulationobject.hpp

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resourse.qrc
