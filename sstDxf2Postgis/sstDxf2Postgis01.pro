TEMPLATE	  = app
CONFIG	 	 += warn_on
CONFIG       -= qt
CONFIG       -= windows

# CONFIG       -= debug  # RELEASE ist aktiv
CONFIG       -= release  # DEBUG ist aktiv

INCLUDEPATH += ../../sst_dxf03_lib/Header
INCLUDEPATH += ../../sst_rec04_lib/Header
INCLUDEPATH += ../../sst_misc01_lib/Header
INCLUDEPATH += ../../sst_str01_lib/Header
INCLUDEPATH += ../../sstMath01Lib/Header
INCLUDEPATH +=  ../../dxflib/src
INCLUDEPATH +=  ../../sstLibreCAD2Lib/Header
INCLUDEPATH += ../Header
INCLUDEPATH += .

debug{
  LIBS        += ../../libs/libsst_dxf03_lib_d.a
  LIBS        += ../../libs/libsstPostgis01Lib_d.a
  LIBS        += ../../libs/libsst_rec04_lib_d.a
  LIBS        += ../../libs/libsst_misc01_lib_d.a
  LIBS        += ../../libs/libsst_str01_lib_d.a
  LIBS        += ../../libs/libsstMath01Lib_d.a
  LIBS        += ../../libs/libdxflib_d.a
}
release{

  win32-g++:QMAKE_LFLAGS += -static
  win32-g++:QMAKE_LFLAGS -= -mthreads
  win32-g++:QMAKE_LFLAGS_EXCEPTIONS_ON -= -mthreads
  win32-g++:QMAKE_CXXFLAGS_EXCEPTIONS_ON -= -mthreads

  LIBS        += ../../libs/libsst_dxf03_lib_r.a
  LIBS        += ../../libs/libsstPostgis01Lib_r.a
  LIBS        += ../../libs/libsst_rec04_lib_r.a
  LIBS        += ../../libs/libsst_misc01_lib_r.a
  LIBS        += ../../libs/libsst_str01_lib_r.a
  LIBS        += ../../libs/libsstMath01Lib_r.a
  LIBS        += ../../libs/libdxflib_r.a
}

HEADERS    += \
  sstDxf2Postgis01.h

SOURCES    += \
  sstDxf2Postgis01.cpp

TARGET	  	= sstDxf2Postgis01

# copy to deployment directory
# DESTDIR     = ../../../local_deploy

