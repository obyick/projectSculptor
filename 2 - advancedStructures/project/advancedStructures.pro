TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        cutBox.cpp \
        cutEllipsoid.cpp \
        cutSphere.cpp \
        cutVoxel.cpp \
        geometricFigure.cpp \
        main.cpp \
        putBox.cpp \
        putEllipsoid.cpp \
        putSphere.cpp \
        putVoxel.cpp \
        readerFile.cpp \
        sculptor.cpp

HEADERS += \
    cutBox.h \
    cutEllipsoid.h \
    cutSphere.h \
    cutVoxel.h \
    geometricFigure.h \
    putBox.h \
    putEllipsoid.h \
    putSphere.h \
    putVoxel.h \
    readerFile.h \
    sculptor.h \
    voxel.h
