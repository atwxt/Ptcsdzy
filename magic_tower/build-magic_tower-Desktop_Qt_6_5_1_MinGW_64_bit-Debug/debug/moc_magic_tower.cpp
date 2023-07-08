/****************************************************************************
** Meta object code from reading C++ file 'magic_tower.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../magic_tower/magic_tower.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'magic_tower.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSMagicTowerENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSMagicTowerENDCLASS = QtMocHelpers::stringData(
    "MagicTower",
    "startGame",
    "",
    "startGameWithLevel",
    "show_monster_information",
    "read_situation",
    "enter_store"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSMagicTowerENDCLASS_t {
    uint offsetsAndSizes[14];
    char stringdata0[11];
    char stringdata1[10];
    char stringdata2[1];
    char stringdata3[19];
    char stringdata4[25];
    char stringdata5[15];
    char stringdata6[12];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSMagicTowerENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSMagicTowerENDCLASS_t qt_meta_stringdata_CLASSMagicTowerENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "MagicTower"
        QT_MOC_LITERAL(11, 9),  // "startGame"
        QT_MOC_LITERAL(21, 0),  // ""
        QT_MOC_LITERAL(22, 18),  // "startGameWithLevel"
        QT_MOC_LITERAL(41, 24),  // "show_monster_information"
        QT_MOC_LITERAL(66, 14),  // "read_situation"
        QT_MOC_LITERAL(81, 11)   // "enter_store"
    },
    "MagicTower",
    "startGame",
    "",
    "startGameWithLevel",
    "show_monster_information",
    "read_situation",
    "enter_store"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMagicTowerENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   44,    2, 0x0a,    1 /* Public */,
       3,    1,   45,    2, 0x0a,    2 /* Public */,
       4,    0,   48,    2, 0x0a,    4 /* Public */,
       5,    0,   49,    2, 0x0a,    5 /* Public */,
       6,    0,   50,    2, 0x0a,    6 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject MagicTower::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSMagicTowerENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMagicTowerENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMagicTowerENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MagicTower, std::true_type>,
        // method 'startGame'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'startGameWithLevel'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'show_monster_information'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'read_situation'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'enter_store'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MagicTower::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MagicTower *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->startGame(); break;
        case 1: _t->startGameWithLevel((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->show_monster_information(); break;
        case 3: _t->read_situation(); break;
        case 4: _t->enter_store(); break;
        default: ;
        }
    }
}

const QMetaObject *MagicTower::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MagicTower::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMagicTowerENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MagicTower::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
