/****************************************************************************
** Meta object code from reading C++ file 'Player.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Player.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Player.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AudioPlay_t {
    const uint offsetsAndSize[42];
    char stringdata0[473];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_AudioPlay_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_AudioPlay_t qt_meta_stringdata_AudioPlay = {
    {
QT_MOC_LITERAL(0, 9), // "AudioPlay"
QT_MOC_LITERAL(10, 32), // "on_tableWidget_cellDoubleClicked"
QT_MOC_LITERAL(43, 0), // ""
QT_MOC_LITERAL(44, 3), // "row"
QT_MOC_LITERAL(48, 6), // "column"
QT_MOC_LITERAL(55, 30), // "on_PushButton_OpenFile_clicked"
QT_MOC_LITERAL(86, 30), // "on_PushButton_PlayStop_clicked"
QT_MOC_LITERAL(117, 30), // "on_PushButton_Previous_clicked"
QT_MOC_LITERAL(148, 26), // "on_PushButton_Next_clicked"
QT_MOC_LITERAL(175, 29), // "on_Slider_Volume_valueChanged"
QT_MOC_LITERAL(205, 5), // "value"
QT_MOC_LITERAL(211, 20), // "do_getduration_slots"
QT_MOC_LITERAL(232, 8), // "playtime"
QT_MOC_LITERAL(241, 23), // "do_updatePosition_slots"
QT_MOC_LITERAL(265, 8), // "position"
QT_MOC_LITERAL(274, 36), // "on_Slider_ProgressBar_sliderR..."
QT_MOC_LITERAL(311, 30), // "on_PushButton_PlayMode_clicked"
QT_MOC_LITERAL(342, 33), // "on_PushButton_DeleteMusic_cli..."
QT_MOC_LITERAL(376, 31), // "on_pushButton_WindowMin_clicked"
QT_MOC_LITERAL(408, 31), // "on_pushButton_WindowMax_clicked"
QT_MOC_LITERAL(440, 32) // "on_pushButton_WindowExit_clicked"

    },
    "AudioPlay\0on_tableWidget_cellDoubleClicked\0"
    "\0row\0column\0on_PushButton_OpenFile_clicked\0"
    "on_PushButton_PlayStop_clicked\0"
    "on_PushButton_Previous_clicked\0"
    "on_PushButton_Next_clicked\0"
    "on_Slider_Volume_valueChanged\0value\0"
    "do_getduration_slots\0playtime\0"
    "do_updatePosition_slots\0position\0"
    "on_Slider_ProgressBar_sliderReleased\0"
    "on_PushButton_PlayMode_clicked\0"
    "on_PushButton_DeleteMusic_clicked\0"
    "on_pushButton_WindowMin_clicked\0"
    "on_pushButton_WindowMax_clicked\0"
    "on_pushButton_WindowExit_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AudioPlay[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   98,    2, 0x08,    1 /* Private */,
       5,    0,  103,    2, 0x08,    4 /* Private */,
       6,    0,  104,    2, 0x08,    5 /* Private */,
       7,    0,  105,    2, 0x08,    6 /* Private */,
       8,    0,  106,    2, 0x08,    7 /* Private */,
       9,    1,  107,    2, 0x08,    8 /* Private */,
      11,    1,  110,    2, 0x08,   10 /* Private */,
      13,    1,  113,    2, 0x08,   12 /* Private */,
      15,    0,  116,    2, 0x08,   14 /* Private */,
      16,    0,  117,    2, 0x08,   15 /* Private */,
      17,    0,  118,    2, 0x08,   16 /* Private */,
      18,    0,  119,    2, 0x08,   17 /* Private */,
      19,    0,  120,    2, 0x08,   18 /* Private */,
      20,    0,  121,    2, 0x08,   19 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::LongLong,   12,
    QMetaType::Void, QMetaType::LongLong,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void AudioPlay::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AudioPlay *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_tableWidget_cellDoubleClicked((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 1: _t->on_PushButton_OpenFile_clicked(); break;
        case 2: _t->on_PushButton_PlayStop_clicked(); break;
        case 3: _t->on_PushButton_Previous_clicked(); break;
        case 4: _t->on_PushButton_Next_clicked(); break;
        case 5: _t->on_Slider_Volume_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->do_getduration_slots((*reinterpret_cast< std::add_pointer_t<qint64>>(_a[1]))); break;
        case 7: _t->do_updatePosition_slots((*reinterpret_cast< std::add_pointer_t<qint64>>(_a[1]))); break;
        case 8: _t->on_Slider_ProgressBar_sliderReleased(); break;
        case 9: _t->on_PushButton_PlayMode_clicked(); break;
        case 10: _t->on_PushButton_DeleteMusic_clicked(); break;
        case 11: _t->on_pushButton_WindowMin_clicked(); break;
        case 12: _t->on_pushButton_WindowMax_clicked(); break;
        case 13: _t->on_pushButton_WindowExit_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject AudioPlay::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_AudioPlay.offsetsAndSize,
    qt_meta_data_AudioPlay,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_AudioPlay_t
, QtPrivate::TypeAndForceComplete<AudioPlay, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<qint64, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<qint64, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *AudioPlay::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AudioPlay::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AudioPlay.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int AudioPlay::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
