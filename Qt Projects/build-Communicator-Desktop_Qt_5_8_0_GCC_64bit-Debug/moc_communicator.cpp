/****************************************************************************
** Meta object code from reading C++ file 'communicator.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Documents/Player-With-Robot-Sensors/Qt Projects/Left Robot Code/Communicator/communicator.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'communicator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Communicator_t {
    QByteArrayData data[15];
    char stringdata0[126];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Communicator_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Communicator_t qt_meta_stringdata_Communicator = {
    {
QT_MOC_LITERAL(0, 0, 12), // "Communicator"
QT_MOC_LITERAL(1, 13, 11), // "bidReceived"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 2), // "rn"
QT_MOC_LITERAL(4, 29, 1), // "s"
QT_MOC_LITERAL(5, 31, 1), // "d"
QT_MOC_LITERAL(6, 33, 12), // "taskReceived"
QT_MOC_LITERAL(7, 46, 13), // "startReceived"
QT_MOC_LITERAL(8, 60, 13), // "readyReceived"
QT_MOC_LITERAL(9, 74, 13), // "errorReceived"
QT_MOC_LITERAL(10, 88, 5), // "char*"
QT_MOC_LITERAL(11, 94, 4), // "emsg"
QT_MOC_LITERAL(12, 99, 12), // "moveReceived"
QT_MOC_LITERAL(13, 112, 1), // "m"
QT_MOC_LITERAL(14, 114, 11) // "startListen"

    },
    "Communicator\0bidReceived\0\0rn\0s\0d\0"
    "taskReceived\0startReceived\0readyReceived\0"
    "errorReceived\0char*\0emsg\0moveReceived\0"
    "m\0startListen"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Communicator[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   49,    2, 0x06 /* Public */,
       6,    0,   56,    2, 0x06 /* Public */,
       7,    0,   57,    2, 0x06 /* Public */,
       8,    0,   58,    2, 0x06 /* Public */,
       9,    1,   59,    2, 0x06 /* Public */,
      12,    1,   62,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    0,   65,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    3,    4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, QMetaType::Int,   13,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void Communicator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Communicator *_t = static_cast<Communicator *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->bidReceived((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->taskReceived(); break;
        case 2: _t->startReceived(); break;
        case 3: _t->readyReceived(); break;
        case 4: _t->errorReceived((*reinterpret_cast< char*(*)>(_a[1]))); break;
        case 5: _t->moveReceived((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->startListen(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Communicator::*_t)(int , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Communicator::bidReceived)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Communicator::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Communicator::taskReceived)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Communicator::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Communicator::startReceived)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Communicator::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Communicator::readyReceived)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (Communicator::*_t)(char * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Communicator::errorReceived)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (Communicator::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Communicator::moveReceived)) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject Communicator::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Communicator.data,
      qt_meta_data_Communicator,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Communicator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Communicator::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Communicator.stringdata0))
        return static_cast<void*>(const_cast< Communicator*>(this));
    return QObject::qt_metacast(_clname);
}

int Communicator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void Communicator::bidReceived(int _t1, int _t2, int _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Communicator::taskReceived()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void Communicator::startReceived()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void Communicator::readyReceived()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void Communicator::errorReceived(char * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Communicator::moveReceived(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
