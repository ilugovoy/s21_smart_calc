QT       += core gui widgets charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../functions/part_1_smartcalc/*.c \
    ../functions/stack/*.c \
    ../functions/part_2_credit_calc/*.c \
	../functions/part_3_deposit_calc/*.c \
    *.cpp

HEADERS += \
    ../functions/headers/part_1.h \
    *.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DEFINES += 
