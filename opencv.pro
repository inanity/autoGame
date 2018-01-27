QT += core
QT -= gui

CONFIG += c++11

TARGET = opencv
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    readlayer.cpp \
    calladb.cpp \
    choosecard.cpp \
    globalnum.cpp \
    other.cpp \
    clickgame.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH+=F:\coding\game3\opencv_qt\include\opencv2\
                    F:\coding\game3\opencv_qt\include\opencv\
                    F:\coding\game3\opencv_qt\include

LIBS+=F:\coding\game3\opencv_qt\lib\libopencv_calib3d320.dll.a\
        F:\coding\game3\opencv_qt\lib\libopencv_core320.dll.a \
        F:\coding\game3\opencv_qt\lib\libopencv_features2d320.dll.a \
        F:\coding\game3\opencv_qt\lib\libopencv_flann320.dll.a \
        F:\coding\game3\opencv_qt\lib\libopencv_highgui320.dll.a \
        F:\coding\game3\opencv_qt\lib\libopencv_imgcodecs320.dll.a \
        F:\coding\game3\opencv_qt\lib\libopencv_imgproc320.dll.a\
        F:\coding\game3\opencv_qt\lib\libopencv_ml320.dll.a\
        F:\coding\game3\opencv_qt\lib\libopencv_objdetect320.dll.a\
        F:\coding\game3\opencv_qt\lib\libopencv_photo320.dll.a\
        F:\coding\game3\opencv_qt\lib\libopencv_shape320.dll.a\
        F:\coding\game3\opencv_qt\lib\libopencv_stitching320.dll.a\
        F:\coding\game3\opencv_qt\lib\libopencv_superres320.dll.a\
        F:\coding\game3\opencv_qt\lib\libopencv_video320.dll.a\
        F:\coding\game3\opencv_qt\lib\libopencv_videoio320.dll.a\
        F:\coding\game3\opencv_qt\lib\libopencv_videostab320.dll.a

HEADERS += \
    readlayer.h \
    calladb.h \
    globalnum.h \
    choosecard.h \
    other.h \
    clickgame.h


