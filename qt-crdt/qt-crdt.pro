TEMPLATE = lib
TARGET = crdt-qt

QT += core
QT -= gui

CONFIG += c++11 staticlib

DEFINES += WANT_TRACE

INCLUDEPATH += ../proto \
    /home/tswindell/Projects/github/qml-runtime/src/3rdparty/grpc/include/

LIBS += -L/home/tswindell/Projects/github/qml-runtime/build/src/3rdparty/protobuf/cmake/
LIBS += -L/home/tswindell/Projects/github/qml-runtime/build/src/3rdparty/cmake/grpc/ -lgrpc++ -lgrpc -lgpr -lssl -lcrypto -lprotobuf -lz

HEADERS += \
    common.h \
    grpcchannel.h \
    grpcchannel_p.h \
    grpcclient.h \
    crdt.pb.h \
    crdt.grpc.pb.h \
    crdtclient.h \
    growonlysetclient.h \
    grpcpendingcall.h \
    twophasesetclient.h

SOURCES += \
    grpcchannel.cpp \
    grpcclient.cpp \
    growonlysetclient.cpp \
    crdt.pb.cc \
    crdt.grpc.pb.cc \
    crdtclient.cpp \
    twophasesetclient.cpp
