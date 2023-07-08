QT += core gui
QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    difficulty_choose.cpp \
    hero.cpp \
    main.cpp \
    magic_tower.cpp \
    map.cpp \
    monster.cpp \
    monsterinformation.cpp

HEADERS += \
    difficulty_choose.h \
    hero.h \
    magic_tower.h \
    map.h \
    monster.h \
    monsterinformation.h

FORMS +=

TRANSLATIONS += \
    magic_tower_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    magic_tower_resource.qrc
