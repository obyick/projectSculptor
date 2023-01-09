QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += \
    dialog.cpp \
    main.cpp \
    mainwindow.cpp \
    plotter.cpp \
    sculptor.cpp

HEADERS += \
    dialog.h \
    mainwindow.h \
    plotter.h \
    sculptor.h

FORMS += \
    dialog.ui \
    mainwindow.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc
