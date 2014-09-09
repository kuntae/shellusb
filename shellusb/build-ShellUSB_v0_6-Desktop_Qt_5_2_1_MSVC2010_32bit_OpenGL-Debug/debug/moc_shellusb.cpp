/****************************************************************************
** Meta object code from reading C++ file 'shellusb.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ShellUSB_v0_6/shellusb.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'shellusb.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ShellUSB_t {
    QByteArrayData data[12];
    char stringdata[199];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_ShellUSB_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_ShellUSB_t qt_meta_stringdata_ShellUSB = {
    {
QT_MOC_LITERAL(0, 0, 8),
QT_MOC_LITERAL(1, 9, 18),
QT_MOC_LITERAL(2, 28, 0),
QT_MOC_LITERAL(3, 29, 18),
QT_MOC_LITERAL(4, 48, 19),
QT_MOC_LITERAL(5, 68, 20),
QT_MOC_LITERAL(6, 89, 26),
QT_MOC_LITERAL(7, 116, 5),
QT_MOC_LITERAL(8, 122, 19),
QT_MOC_LITERAL(9, 142, 9),
QT_MOC_LITERAL(10, 152, 21),
QT_MOC_LITERAL(11, 174, 23)
    },
    "ShellUSB\0on_enc_btn_clicked\0\0"
    "on_dnc_btn_clicked\0on_back_btn_clicked\0"
    "on_front_btn_clicked\0on_tableView_doubleClicked\0"
    "index\0on_treeView_clicked\0treeIndex\0"
    "on_toolButton_clicked\0on_toolButton_2_clicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ShellUSB[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08,
       3,    0,   55,    2, 0x08,
       4,    0,   56,    2, 0x08,
       5,    0,   57,    2, 0x08,
       6,    1,   58,    2, 0x08,
       8,    1,   61,    2, 0x08,
      10,    0,   64,    2, 0x08,
      11,    0,   65,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    7,
    QMetaType::Void, QMetaType::QModelIndex,    9,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ShellUSB::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ShellUSB *_t = static_cast<ShellUSB *>(_o);
        switch (_id) {
        case 0: _t->on_enc_btn_clicked(); break;
        case 1: _t->on_dnc_btn_clicked(); break;
        case 2: _t->on_back_btn_clicked(); break;
        case 3: _t->on_front_btn_clicked(); break;
        case 4: _t->on_tableView_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 5: _t->on_treeView_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 6: _t->on_toolButton_clicked(); break;
        case 7: _t->on_toolButton_2_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject ShellUSB::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ShellUSB.data,
      qt_meta_data_ShellUSB,  qt_static_metacall, 0, 0}
};


const QMetaObject *ShellUSB::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ShellUSB::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ShellUSB.stringdata))
        return static_cast<void*>(const_cast< ShellUSB*>(this));
    return QDialog::qt_metacast(_clname);
}

int ShellUSB::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
