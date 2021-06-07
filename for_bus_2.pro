QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    info_bus.cpp \
    main.cpp \
    mainwindow.cpp \
    pay_bus.cpp \
    settings_bus.cpp \
    tcp_client_card.cpp \
    tcp_server_reader.cpp

HEADERS += \
    info_bus.h \
    mainwindow.h \
    pay_bus.h \
    settings_bus.h \
    tcp_client_card.h \
    tcp_server_reader.h

FORMS += \
    info_bus.ui \
    mainwindow.ui \
    pay_bus.ui \
    settings_bus.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    res_f.qrc
