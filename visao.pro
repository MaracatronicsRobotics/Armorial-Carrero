QT -= gui
QT += network
QT += widgets

CONFIG += c++14 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
LIBS *= -lprotobuf -lGLU -pthread -lsfml-graphics -lsfml-window -lsfml-system -lGEARSystem -lomniORB4 -lomnithread -lQt5Core -lpthread

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH *= include/3rd_party
SOURCES += \
	include/3rd_party/messages_robocup_ssl_detection.pb.cc \
	include/3rd_party/netraw.cpp \
	include/3rd_party/robocup_ssl_client.cpp \
	include/3rd_party/messages_robocup_ssl_geometry.pb.cc \
	include/3rd_party/messages_robocup_ssl_refbox_log.pb.cc \
	include/3rd_party/messages_robocup_ssl_wrapper.pb.cc \
	include/3rd_party/grSim_Commands.pb.cc \
	include/3rd_party/grSim_Packet.pb.cc \
	include/3rd_party/grSim_Replacement.pb.cc \
	include/3rd_party/referee.pb.cc \
    Ball/ball.cpp \
    KalmanFilter/kalman.cpp \
    KalmanFilter/kalmanstate.cpp \
    KalmanFilter/matrix.cpp \
    LossFilter/loss.cpp \
    MultiObjectFilter/multiobject.cpp \
    MultiObjectFilter/multiobjectfilter.cpp \
	NoiseFilter/noise.cpp \
    grsSimulator/grsSimulator.cpp \
    Robot/robot.cpp \
    types/object.cpp \
    vision.cpp \
    types/frame.cpp \
    samico.cpp \
    mrctimer.cpp \
    entity/entity.cpp \
    entity/armorialvisionupdater/armorialvisionupdater.cpp \
    entity/armorialvisionupdater/robottracker.cpp \
    utils/fieldareas.cpp \
    utils/fieldtypes.cpp \
    exithandler.cpp \
	entity/armorialvisionclient/armorialvisionclient.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    visao.pro

DISTFILES += \
    src/License \
    include/3rd_party/protobuf/messages_robocup_ssl_detection.proto \
    include/3rd_party/protobuf/messages_robocup_ssl_refbox_log.proto \
    include/3rd_party/protobuf/messages_robocup_ssl_wrapper.proto \
    include/3rd_party/protobuf/messages_robocup_ssl_geometry.proto \
    include/3rd_party/protobuf/grSim_Commands.proto \
    include/3rd_party/protobuf/grSim_Packet.proto \
    include/3rd_party/protobuf/grSim_Replacement.proto \
    include/3rd_party/protobuf/referee.proto \
    include/3rd_party/protobuf/protobuf.sh \
    utils/arial.ttf \
    utils/bluerobot.png \
    utils/yellowrobot.png \
    utils/arial.ttf \
    textures/sky/arabian_nights_bk.png \
    textures/sky/arabian_nights_dn.png \
    textures/sky/arabian_nights_ft.png \
    textures/sky/arabian_nights_lf.png \
    textures/sky/arabian_nights_rt.png \
    textures/sky/arabian_nights_up.png \
    textures/b0.png \
    textures/b1.png \
    textures/b10.png \
    textures/b11.png \
    textures/b2.png \
    textures/b3.png \
    textures/b4.png \
    textures/b5.png \
    textures/b6.png \
    textures/b7.png \
    textures/b8.png \
    textures/b9.png \
    textures/grass.png \
    textures/qt.png \
    textures/wheel.png \
    textures/y0.png \
    textures/y1.png \
    textures/y10.png \
    textures/y11.png \
    textures/y2.png \
    textures/y3.png \
    textures/y4.png \
    textures/y5.png \
    textures/y6.png \
    textures/y7.png \
    textures/y8.png \
    textures/y9.png



HEADERS += \
	include/3rd_party/netraw.h \
	include/3rd_party/robocup_ssl_client.h \
	include/3rd_party/util.h \
	include/filters.h \
	include/3rd_party/messages_robocup_ssl_detection.pb.h \
	include/3rd_party/messages_robocup_ssl_geometry.pb.h \
	include/3rd_party/messages_robocup_ssl_wrapper.pb.h \
	include/3rd_party/messages_robocup_ssl_refbox_log.pb.h \
	include/3rd_party/referee.pb.h \
	include/3rd_party/grSim_Commands.pb.h \
	include/3rd_party/grSim_Packet.pb.h \
	include/3rd_party/grSim_Replacement.pb.h \
    Ball/ball.h \
    MultiObjectFilter/multiobject.h \
    MultiObjectFilter/multiobjectfilter.h \
    include/filters.h \
    include/timer.h \
    KalmanFilter/kalman.hpp \
    KalmanFilter/kalmanstate.h \
	KalmanFilter/matrix.h \
    grsSimulator/grsSimulator.h \
    LossFilter/loss.h \
    NoiseFilter/noise.h \
    Robot/robot.h \
    types/frame.h \
    mrctimer.h \
    types/object.h \
    samico.h \
    exithandler.h \
    entity/entity.h \
    entity/armorialvisionclient/armorialvisionclient.h \
    utils/fieldareas.h \
    utils/fieldtypes.h \
    utils/color.h \
    entity/armorialvisionupdater/armorialvisionupdater.h \
    entity/armorialvisionupdater/robottracker.h \
	entity/eyebase.hh

