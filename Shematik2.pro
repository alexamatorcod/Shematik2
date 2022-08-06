QT           += sql widgets
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
add_db_elements/add_capacitor.cpp \
    add_db_elements/add_diodes.cpp \
    add_db_elements/add_resistor.cpp \
    add_db_elements/add_transistor.cpp \
    addtodbaseelem.cpp \
    dotsignal.cpp \
    elementitem.cpp \
    insert_elemets/insertcondensator.cpp \
    insert_elemets/insertdiode.cpp \
    insert_elemets/insertelement.cpp \
    insert_elemets/insertresistor.cpp \
    insert_elemets/inserttransistor.cpp \
    line.cpp \
    main.cpp \
    mainwindow.cpp \
    mygv.cpp \
    myscene.cpp \
    radio_elements/condensatorclass.cpp \
    radio_elements/diodeclass.cpp \
    radio_elements/resistorclass.cpp \
    radio_elements/transistorclass.cpp \
    textgen.cpp

HEADERS += \
add_db_elements/add_capacitor.h \
    add_db_elements/add_diodes.h \
    add_db_elements/add_resistor.h \
    add_db_elements/add_transistor.h \
    addtodbaseelem.h \
    dotsignal.h \
    elementitem.h \
    insert_elemets/insertcondensator.h \
    insert_elemets/insertdiode.h \
    insert_elemets/insertelement.h \
    insert_elemets/insertresistor.h \
    insert_elemets/inserttransistor.h \
    line.h \
    mainwindow.h \
    mygv.h \
    myscene.h \
    radio_elements/condensatorclass.h \
    radio_elements/diodeclass.h \
    radio_elements/resistorclass.h \
    radio_elements/transistorclass.h \
    textgen.h


FORMS += \
    addtodbaseelem.ui \
    insertelement.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QMAKE_EXTRA_TARGETS += before_build makefilehook

makefilehook.target = $(MAKEFILE)
makefilehook.depends = .beforebuild

PRE_TARGETDEPS += .beforebuild

before_build.target = .beforebuild
before_build.depends = FORCE
before_build.commands = chcp 1251
