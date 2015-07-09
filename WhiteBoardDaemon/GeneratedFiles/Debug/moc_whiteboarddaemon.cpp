/****************************************************************************
** Meta object code from reading C++ file 'whiteboarddaemon.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../whiteboarddaemon.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'whiteboarddaemon.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_WhiteBoardDaemon_t {
    QByteArrayData data[17];
    char stringdata[208];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WhiteBoardDaemon_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WhiteBoardDaemon_t qt_meta_stringdata_WhiteBoardDaemon = {
    {
QT_MOC_LITERAL(0, 0, 16), // "WhiteBoardDaemon"
QT_MOC_LITERAL(1, 17, 9), // "configure"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 11), // "startCamara"
QT_MOC_LITERAL(4, 40, 9), // "readFarme"
QT_MOC_LITERAL(5, 50, 10), // "stopCamara"
QT_MOC_LITERAL(6, 61, 15), // "spotMeasurement"
QT_MOC_LITERAL(7, 77, 15), // "autoCalibration"
QT_MOC_LITERAL(8, 93, 13), // "setCameraMode"
QT_MOC_LITERAL(9, 107, 12), // "setLaserMode"
QT_MOC_LITERAL(10, 120, 10), // "setUseMode"
QT_MOC_LITERAL(11, 131, 11), // "updateSpots"
QT_MOC_LITERAL(12, 143, 3), // "Mat"
QT_MOC_LITERAL(13, 147, 5), // "frame"
QT_MOC_LITERAL(14, 153, 13), // "iconActivated"
QT_MOC_LITERAL(15, 167, 33), // "QSystemTrayIcon::ActivationRe..."
QT_MOC_LITERAL(16, 201, 6) // "reason"

    },
    "WhiteBoardDaemon\0configure\0\0startCamara\0"
    "readFarme\0stopCamara\0spotMeasurement\0"
    "autoCalibration\0setCameraMode\0"
    "setLaserMode\0setUseMode\0updateSpots\0"
    "Mat\0frame\0iconActivated\0"
    "QSystemTrayIcon::ActivationReason\0"
    "reason"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WhiteBoardDaemon[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x08 /* Private */,
       3,    0,   70,    2, 0x08 /* Private */,
       4,    0,   71,    2, 0x08 /* Private */,
       5,    0,   72,    2, 0x08 /* Private */,
       6,    0,   73,    2, 0x08 /* Private */,
       7,    0,   74,    2, 0x08 /* Private */,
       8,    0,   75,    2, 0x08 /* Private */,
       9,    0,   76,    2, 0x08 /* Private */,
      10,    0,   77,    2, 0x08 /* Private */,
      11,    1,   78,    2, 0x08 /* Private */,
      14,    1,   81,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 15,   16,

       0        // eod
};

void WhiteBoardDaemon::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WhiteBoardDaemon *_t = static_cast<WhiteBoardDaemon *>(_o);
        switch (_id) {
        case 0: _t->configure(); break;
        case 1: _t->startCamara(); break;
        case 2: _t->readFarme(); break;
        case 3: _t->stopCamara(); break;
        case 4: _t->spotMeasurement(); break;
        case 5: _t->autoCalibration(); break;
        case 6: _t->setCameraMode(); break;
        case 7: _t->setLaserMode(); break;
        case 8: _t->setUseMode(); break;
        case 9: _t->updateSpots((*reinterpret_cast< Mat(*)>(_a[1]))); break;
        case 10: _t->iconActivated((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject WhiteBoardDaemon::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_WhiteBoardDaemon.data,
      qt_meta_data_WhiteBoardDaemon,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *WhiteBoardDaemon::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WhiteBoardDaemon::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_WhiteBoardDaemon.stringdata))
        return static_cast<void*>(const_cast< WhiteBoardDaemon*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int WhiteBoardDaemon::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
