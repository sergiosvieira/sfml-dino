TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
INCLUDEPATH += "/usr/local/opt/sfml/include"
LIBS += -L"/usr/local/opt/sfml/lib"
LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
SOURCES += \
        animation.cpp \
        cactus.cpp \
        cloud.cpp \
        frame.cpp \
        game.cpp \
        ground.cpp \
        main.cpp \
        player.cpp \
        pterodactyl.cpp

HEADERS += \
    animation.h \
    cactus.h \
    cloud.h \
    frame.h \
    game-consts.h \
    game-random.h \
    game.h \
    ground.h \
    object.h \
    player.h \
    pterodactyl.h
