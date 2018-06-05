/****************************************************************************
** Meta object code from reading C++ file 'HelpBoard.hh'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../HelpBoard.hh"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'HelpBoard.hh' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_HelpBoard_t {
    QByteArrayData data[8];
    char stringdata0[70];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HelpBoard_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HelpBoard_t qt_meta_stringdata_HelpBoard = {
    {
QT_MOC_LITERAL(0, 0, 9), // "HelpBoard"
QT_MOC_LITERAL(1, 10, 10), // "handleUndo"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 11), // "handleSolve"
QT_MOC_LITERAL(4, 34, 10), // "handleHelp"
QT_MOC_LITERAL(5, 45, 10), // "handleMove"
QT_MOC_LITERAL(6, 56, 8), // "GameMove"
QT_MOC_LITERAL(7, 65, 4) // "move"

    },
    "HelpBoard\0handleUndo\0\0handleSolve\0"
    "handleHelp\0handleMove\0GameMove\0move"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HelpBoard[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x0a /* Public */,
       3,    0,   35,    2, 0x0a /* Public */,
       4,    0,   36,    2, 0x0a /* Public */,
       5,    1,   37,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,

       0        // eod
};

void HelpBoard::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HelpBoard *_t = static_cast<HelpBoard *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->handleUndo(); break;
        case 1: _t->handleSolve(); break;
        case 2: _t->handleHelp(); break;
        case 3: _t->handleMove((*reinterpret_cast< GameMove(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject HelpBoard::staticMetaObject = {
    { &PlayerBoard::staticMetaObject, qt_meta_stringdata_HelpBoard.data,
      qt_meta_data_HelpBoard,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *HelpBoard::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HelpBoard::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_HelpBoard.stringdata0))
        return static_cast<void*>(this);
    return PlayerBoard::qt_metacast(_clname);
}

int HelpBoard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PlayerBoard::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
