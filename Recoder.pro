QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
QT += multimedia
INCLUDEPATH+=C:/Qt/opencv-release/include/opencv2\
C:/Qt/opencv-release/include\
$$PWD/ffmpeg-4.2.2/include





LIBS+=C:\Qt\opencv-release\lib\libopencv_calib3d420.dll.a\
C:\Qt\opencv-release\lib\libopencv_core420.dll.a\
C:\Qt\opencv-release\lib\libopencv_features2d420.dll.a\
C:\Qt\opencv-release\lib\libopencv_flann420.dll.a\
C:\Qt\opencv-release\lib\libopencv_highgui420.dll.a\
C:\Qt\opencv-release\lib\libopencv_imgproc420.dll.a\
C:\Qt\opencv-release\lib\libopencv_ml420.dll.a\
C:\Qt\opencv-release\lib\libopencv_objdetect420.dll.a\
C:\Qt\opencv-release\lib\libopencv_video420.dll.a\
C:\Qt\opencv-release\lib\libopencv_videoio420.dll.a\
$$PWD/ffmpeg-4.2.2/lib/avcodec.lib\
$$PWD/ffmpeg-4.2.2/lib/avdevice.lib\
$$PWD/ffmpeg-4.2.2/lib/avfilter.lib\
$$PWD/ffmpeg-4.2.2/lib/avformat.lib\
$$PWD/ffmpeg-4.2.2/lib/avutil.lib\
$$PWD/ffmpeg-4.2.2/lib/postproc.lib\
$$PWD/ffmpeg-4.2.2/lib/swresample.lib\
$$PWD/ffmpeg-4.2.2/lib/swscale.lib

SOURCES += \
    MD5/md5.cpp \
    audio_read.cpp \
    logindialog.cpp \
    main.cpp \
    netapi/mediator/INetMediator.cpp \
    netapi/mediator/TcpClientMediator.cpp \
    netapi/mediator/TcpServerMediator.cpp \
    netapi/mediator/UdpMediator.cpp \
    netapi/net/INet.cpp \
    netapi/net/TcpClient.cpp \
    netapi/net/TcpServer.cpp \
    netapi/net/UdpNet.cpp \
    picinpic_read.cpp \
    recorddialog.cpp \
    savevideofile.cpp \
    screenrecorder.cpp \
    videoshow.cpp

HEADERS += \
    MD5/md5.h \
    audio_read.h \
    common.h \
    logindialog.h \
    netapi/mediator/INetMediator.h \
    netapi/mediator/TcpClientMediator.h \
    netapi/mediator/TcpServerMediator.h \
    netapi/mediator/UdpMediator.h \
    netapi/net/INet.h \
    netapi/net/TcpClient.h \
    netapi/net/TcpServer.h \
    netapi/net/UdpNet.h \
    netapi/net/packdef.h \
    picinpic_read.h \
    recorddialog.h \
    savevideofile.h \
    screenrecorder.h \
    videoshow.h

FORMS += \
    logindialog.ui \
    recorddialog.ui \
    videoshow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    MD5/md5.pri \
    netapi/netapi.pri \
    netapi/netapi.pri
    QT       += network
    LIBS += -lpthread libwsock32 libws2_32
    LIBS += -lpthread libMswsock libMswsock


    INCLUDEPATH+=$$PWD/net/
    INCLUDEPATH+=$$PWD/mediator/

    HEADERS += \
        $$PWD/mediator/INetMediator.h \
        $$PWD/mediator/TcpClientMediator.h \
        $$PWD/mediator/TcpServerMediator.h \
        $$PWD/mediator/UdpMediator.h \
        $$PWD/net/INet.h \
        $$PWD/net/TcpClient.h \
        $$PWD/net/TcpServer.h \
        $$PWD/net/UdpNet.h \
        $$PWD/net/packdef.h
        HEADERS += \
            $$PWD/md5.h

        SOURCES += \
            $$PWD/md5.cpp


    SOURCES += \
        $$PWD/mediator/INetMediator.cpp \
        $$PWD/mediator/TcpClientMediator.cpp \
        $$PWD/mediator/TcpServerMediator.cpp \
        $$PWD/mediator/UdpMediator.cpp \
        $$PWD/net/INet.cpp \
        $$PWD/net/TcpClient.cpp \
        $$PWD/net/TcpServer.cpp \
        $$PWD/net/UdpNet.cpp
