TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Globals.cpp \
        animation.cpp \
        engine.cpp \
        gameobject.cpp \
        gun.cpp \
        loader.cpp \
        main.cpp \
        mouse.cpp \
        player.cpp \
        render.cpp

HEADERS += \
    Globals.h \
    animation.h \
    animation_struct.h \
    camera.h \
    engine.h \
    gameobject.h \
    gun.h \
    loader.h \
    mouse.h \
    player.h \
    render.h

DISTFILES += \
    resourсes/animations/pistol_move_left.txt \
    resourсes/animations/pistol_move_right.txt \
    resourсes/animations/pistol_shoot_left1.txt \
    resourсes/animations/pistol_shoot_left2.txt \
    resourсes/animations/pistol_shoot_right1.txt \
    resourсes/animations/pistol_shoot_right2.txt \
    resourсes/animations/pistol_stand.txt
