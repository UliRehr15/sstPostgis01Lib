TEMPLATE = lib
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG		+= warn_on
CONFIG    -= qt
CONFIG    -= windows

# CONFIG    -= debug  # ist RELEASE aktiv
CONFIG    -= release  # ist DEBUG aktiv

CONFIG    += staticlib

INCLUDEPATH += ../sst_rec04_lib/Header
INCLUDEPATH += ../sst_misc01_lib/Header
INCLUDEPATH += ../sst_str01_lib/Header
INCLUDEPATH += ../sstMath01Lib/Header
INCLUDEPATH += ./Header


SOURCES += \
        main.cpp \
        sstPostgis01Sql1.cpp

DISTFILES += \
  README.md

HEADERS += \
  Header/sstPostgis01Lib.h


debug{
  TARGET		= sstPostgis01Lib_d
}
release{
  TARGET		= sstPostgis01Lib_r
}

DESTDIR     = ../libs
