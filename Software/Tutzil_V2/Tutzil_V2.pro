QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0



# Modules
QT += network
SOURCES += \
    clickablelabel.cpp \
    main.cpp \
    mainwindow.cpp \
    worker.cpp

HEADERS += \
    clickablelabel.h \
    mainwindow.h \
    worker.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    utils6.py

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../Documents/Opencv41/opencv/build/x64/vc16/lib/ -lopencv_world4100
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../Documents/Opencv41/opencv/build/x64/vc16/lib/ -lopencv_world4100

INCLUDEPATH += $$PWD/../../../../Documents/Opencv41/opencv/build/include
DEPENDPATH += $$PWD/../../../../Documents/Opencv41/opencv/build/include
