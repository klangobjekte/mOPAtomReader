######################################################################
# Automatically generated by qmake (2.01a) Mi. Jul 22 07:21:08 2015
######################################################################
QT       -= gui
QT       -= core
#TEMPLATE = app
TEMPLATE = lib
#CONFIG += staticlib #static

CONFIG += plugin
CONFIG += dll

INCLUDEPATH += .
CONFIG -= QtCore
CONFIG -= app_bundle
CONFIG   += console
CONFIG += c++11
DEPENDPATH += . \
    Common

#DEFINES = __STDC_CONSTANT_MACROS

INCLUDEPATH += .

win32{
    TARGET = mOPAtomreader
    INCLUDEPATH += "C:/bmx_build/msvc_build/libMXF++/include"
    INCLUDEPATH += "C:/bmx_build/msvc_build/libMXF/include"

    LIBS += "C:\bmx_build\msvc_build\libMXF\debug\lib/libMXF.lib"
    LIBS +=  "C:\bmx_build\msvc_build\libMXF++\debug\lib/libMXF++.lib"
    #LIBS += "C:\bmx_build\msvc_build\expat\debug\lib/libexpat.dll"
    #LIBS += "C:\bmx_build\msvc_build\uriparser\debug\lib/uriparser.lib"

    DEFINES += _USING_V110_SDK71_

    INCLUDEPATH += "C:/Program Files/Microsoft SDKs/Windows/v7.1A/include"
    LIBS += -lole32
    #LIBS += "C:/Program Files/Microsoft SDKs/Windows/v7.1A/Lib/Mfplat.lib"
    #LIBS += "C:\Program Files\Microsoft SDKs\Windows\v7.1A\Lib\mfreadwrite.lib"
    #LIBS += "C:\Program Files\Microsoft SDKs\Windows\v7.1A\Lib\mfuuid.lib"

}

macx{
TARGET = /usr/local/lib/mOPAtomreader
    #CONFIG += plugin
    #CONFIG += macx-xcode
    INCLUDEPATH += .\
                /usr/local/include \
                /usr/local/include/libMXF++-1.0/ \
                /usr/local/include/libMXF-1.0

    LIBS += -L/usr/local/lib
    #LIBS += /usr/local/lib/libMXF++/libMXF++-1.0.la

    LIBS += -lMXF-1.0 \
            -lMXF++-1.0
            #-lbmx-0.1 \
            #-lopatomreader-1.0 \
            #-ld10mxfop1awriter-1.0 \

            #-lexpat \
            #-luriparser \
            #-lavidmxfinfo-1.0 \
            #-lwritearchivemxf-1.0 \
            #-lmxfreader-1.0 \
            #-lwriteavidmxf-1.0 \
}

#include(deployment.pri)
#qtcAddDeployment()

# Input
HEADERS += FixedSizeEssenceParser.h \
           FrameOffsetIndexTable.h \
           OPAtomClipReader.h \
           OPAtomContentPackage.h \
           OPAtomTrackReader.h \
           PCMEssenceParser.h \
           RawEssenceParser.h \
           VariableSizeEssenceParser.h \
           Common/CommonTypes.h \
           Common/DynamicByteArray.h

SOURCES += \
    main.cpp \
    FixedSizeEssenceParser.cpp \
    FrameOffsetIndexTable.cpp \
    OPAtomClipReader.cpp \
    OPAtomContentPackage.cpp \
    OPAtomTrackReader.cpp \
    PCMEssenceParser.cpp \
    RawEssenceParser.cpp \
    VariableSizeEssenceParser.cpp \
    Common/DynamicByteArray.cpp
