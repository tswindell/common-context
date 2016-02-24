/****************************************************************************
** Meta object code from reading C++ file 'grpcclient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "grpcclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'grpcclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GrpcClient_t {
    QByteArrayData data[8];
    char stringdata[82];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GrpcClient_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GrpcClient_t qt_meta_stringdata_GrpcClient = {
    {
QT_MOC_LITERAL(0, 0, 10), // "GrpcClient"
QT_MOC_LITERAL(1, 11, 14), // "channelChanged"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 13), // "connectToHost"
QT_MOC_LITERAL(4, 41, 8), // "hostport"
QT_MOC_LITERAL(5, 50, 10), // "setChannel"
QT_MOC_LITERAL(6, 61, 12), // "GrpcChannel*"
QT_MOC_LITERAL(7, 74, 7) // "channel"

    },
    "GrpcClient\0channelChanged\0\0connectToHost\0"
    "hostport\0setChannel\0GrpcChannel*\0"
    "channel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GrpcClient[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       1,   36, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   30,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
       5,    1,   33,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    4,

 // methods: parameters
    QMetaType::Void, 0x80000000 | 6,    7,

 // properties: name, type, flags
       7, 0x80000000 | 6, 0x0049510b,

 // properties: notify_signal_id
       0,

       0        // eod
};

void GrpcClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GrpcClient *_t = static_cast<GrpcClient *>(_o);
        switch (_id) {
        case 0: _t->channelChanged(); break;
        case 1: _t->connectToHost((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->setChannel((*reinterpret_cast< GrpcChannel*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GrpcClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GrpcClient::channelChanged)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject GrpcClient::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GrpcClient.data,
      qt_meta_data_GrpcClient,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GrpcClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GrpcClient::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GrpcClient.stringdata))
        return static_cast<void*>(const_cast< GrpcClient*>(this));
    return QObject::qt_metacast(_clname);
}

int GrpcClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< GrpcChannel**>(_v) = channel(); break;
        default: break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setChannel(*reinterpret_cast< GrpcChannel**>(_v)); break;
        default: break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void GrpcClient::channelChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
