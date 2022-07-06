/****************************************************************************
** Meta object code from reading C++ file 'WaKAwaka.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../WaKAwaka.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WaKAwaka.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WaKAwaka_t {
    QByteArrayData data[18];
    char stringdata0[255];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WaKAwaka_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WaKAwaka_t qt_meta_stringdata_WaKAwaka = {
    {
QT_MOC_LITERAL(0, 0, 8), // "WaKAwaka"
QT_MOC_LITERAL(1, 9, 23), // "listWidgetItemActivated"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(4, 51, 13), // "activatedItem"
QT_MOC_LITERAL(5, 65, 16), // "trigerImportMenu"
QT_MOC_LITERAL(6, 82, 8), // "QAction*"
QT_MOC_LITERAL(7, 91, 3), // "act"
QT_MOC_LITERAL(8, 95, 17), // "controlPlay_pause"
QT_MOC_LITERAL(9, 113, 8), // "playNext"
QT_MOC_LITERAL(10, 122, 8), // "playBack"
QT_MOC_LITERAL(11, 131, 15), // "controlPlayMode"
QT_MOC_LITERAL(12, 147, 18), // "mediaStatusChanged"
QT_MOC_LITERAL(13, 166, 25), // "QMediaPlayer::MediaStatus"
QT_MOC_LITERAL(14, 192, 6), // "status"
QT_MOC_LITERAL(15, 199, 16), // "sliderMovedEvent"
QT_MOC_LITERAL(16, 216, 18), // "sliderPressedEvent"
QT_MOC_LITERAL(17, 235, 19) // "sliderReleasedEvent"

    },
    "WaKAwaka\0listWidgetItemActivated\0\0"
    "QListWidgetItem*\0activatedItem\0"
    "trigerImportMenu\0QAction*\0act\0"
    "controlPlay_pause\0playNext\0playBack\0"
    "controlPlayMode\0mediaStatusChanged\0"
    "QMediaPlayer::MediaStatus\0status\0"
    "sliderMovedEvent\0sliderPressedEvent\0"
    "sliderReleasedEvent"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WaKAwaka[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x08 /* Private */,
       5,    1,   67,    2, 0x08 /* Private */,
       8,    0,   70,    2, 0x08 /* Private */,
       9,    0,   71,    2, 0x08 /* Private */,
      10,    0,   72,    2, 0x08 /* Private */,
      11,    0,   73,    2, 0x08 /* Private */,
      12,    1,   74,    2, 0x08 /* Private */,
      15,    0,   77,    2, 0x08 /* Private */,
      16,    0,   78,    2, 0x08 /* Private */,
      17,    0,   79,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void WaKAwaka::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WaKAwaka *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->listWidgetItemActivated((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 1: _t->trigerImportMenu((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 2: _t->controlPlay_pause(); break;
        case 3: _t->playNext(); break;
        case 4: _t->playBack(); break;
        case 5: _t->controlPlayMode(); break;
        case 6: _t->mediaStatusChanged((*reinterpret_cast< QMediaPlayer::MediaStatus(*)>(_a[1]))); break;
        case 7: _t->sliderMovedEvent(); break;
        case 8: _t->sliderPressedEvent(); break;
        case 9: _t->sliderReleasedEvent(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QMediaPlayer::MediaStatus >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WaKAwaka::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_WaKAwaka.data,
    qt_meta_data_WaKAwaka,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WaKAwaka::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WaKAwaka::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WaKAwaka.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int WaKAwaka::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
