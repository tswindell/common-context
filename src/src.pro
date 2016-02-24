TEMPLATE = app

TARGET = qml-common-runtime

QT += qml quick
CONFIG += qt c++11 link_pkgconfig

INCLUDEPATH += \
    ../proto \
    /home/tswindell/Projects/github/qml-runtime/src/3rdparty/grpc/include/

LIBS += -L/home/tswindell/Projects/github/qml-runtime/build/src/3rdparty/protobuf/cmake/
LIBS += -L/home/tswindell/Projects/github/qml-runtime/build/src/3rdparty/cmake/grpc/ -lgrpc++ -lgrpc -lgpr -lssl -lcrypto -lprotobuf -lz

HEADERS += \
    crdt/common.h \
    crdt/crdt.grpc.pb.h \
    crdt/crdt.pb.h \
    crdt/crdtclient.h \
    crdt/growonlysetclient.h \
    crdt/grpcchannel.h \
    crdt/grpcchannel_p.h \
    crdt/grpcclient.h \
    crdt/grpcpendingcall.h \
    crdt/twophasesetclient.h \
    ../proto/context.pb.h \
    stateobject.h \
    stateproperty.h \
    context.h \
    resource.h \
    resourcemodel.h \
    resourcefactory.h \
    context_p.h \
    contextresourcefactory.h \
    contextresource.h \
    stateobjectresource.h \
    stateobjectresourcefactory.h \
    quickresource.h \
    quickresourcefactory.h \
    crdtgrowonlysetresource.h \
    crdtgrowonlysetresourcefactory.h \
    crdttwophasesetresource.h \
    crdttwophasesetresourcefactory.h

SOURCES += \
    crdt/crdt.grpc.pb.cc \
    crdt/crdt.pb.cc \
    crdt/crdtclient.cpp \
    crdt/growonlysetclient.cpp \
    crdt/grpcchannel.cpp \
    crdt/grpcclient.cpp \
    crdt/twophasesetclient.cpp \
    ../proto/context.pb.cc \
    stateobject.cpp \
    stateproperty.cpp \
    main.cpp \
    context.cpp \
    resource.cpp \
    resourcemodel.cpp \
    contextresourcefactory.cpp \
    contextresource.cpp \
    stateobjectresource.cpp \
    stateobjectresourcefactory.cpp \
    quickresource.cpp \
    quickresourcefactory.cpp \
    crdtgrowonlysetresource.cpp \
    crdtgrowonlysetresourcefactory.cpp \
    crdttwophasesetresource.cpp \
    crdttwophasesetresourcefactory.cpp

unix:!android {
    isEmpty(target.path) {
        qnx {
            target.path = /tmp/$${TARGET}/bin
        } else {
            target.path = /opt/$${TARGET}/bin
        }
        export(target.path)
    }
    INSTALLS += target
}

DISTFILES += \
    main.qml
