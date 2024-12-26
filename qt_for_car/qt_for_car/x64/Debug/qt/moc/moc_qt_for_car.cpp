/****************************************************************************
** Meta object code from reading C++ file 'qt_for_car.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../qt_for_car.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qt_for_car.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.3. It"
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
struct qt_meta_stringdata_CLASSqt_for_carENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSqt_for_carENDCLASS = QtMocHelpers::stringData(
    "qt_for_car",
    "car_forward",
    "",
    "car_backward",
    "car_left",
    "car_right",
    "car_stop",
    "quick_left",
    "quick_right"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSqt_for_carENDCLASS_t {
    uint offsetsAndSizes[18];
    char stringdata0[11];
    char stringdata1[12];
    char stringdata2[1];
    char stringdata3[13];
    char stringdata4[9];
    char stringdata5[10];
    char stringdata6[9];
    char stringdata7[11];
    char stringdata8[12];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSqt_for_carENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSqt_for_carENDCLASS_t qt_meta_stringdata_CLASSqt_for_carENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "qt_for_car"
        QT_MOC_LITERAL(11, 11),  // "car_forward"
        QT_MOC_LITERAL(23, 0),  // ""
        QT_MOC_LITERAL(24, 12),  // "car_backward"
        QT_MOC_LITERAL(37, 8),  // "car_left"
        QT_MOC_LITERAL(46, 9),  // "car_right"
        QT_MOC_LITERAL(56, 8),  // "car_stop"
        QT_MOC_LITERAL(65, 10),  // "quick_left"
        QT_MOC_LITERAL(76, 11)   // "quick_right"
    },
    "qt_for_car",
    "car_forward",
    "",
    "car_backward",
    "car_left",
    "car_right",
    "car_stop",
    "quick_left",
    "quick_right"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSqt_for_carENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   56,    2, 0x0a,    1 /* Public */,
       3,    0,   57,    2, 0x0a,    2 /* Public */,
       4,    0,   58,    2, 0x0a,    3 /* Public */,
       5,    0,   59,    2, 0x0a,    4 /* Public */,
       6,    0,   60,    2, 0x0a,    5 /* Public */,
       7,    0,   61,    2, 0x0a,    6 /* Public */,
       8,    0,   62,    2, 0x0a,    7 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject qt_for_car::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSqt_for_carENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSqt_for_carENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSqt_for_carENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<qt_for_car, std::true_type>,
        // method 'car_forward'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'car_backward'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'car_left'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'car_right'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'car_stop'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'quick_left'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'quick_right'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void qt_for_car::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<qt_for_car *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->car_forward(); break;
        case 1: _t->car_backward(); break;
        case 2: _t->car_left(); break;
        case 3: _t->car_right(); break;
        case 4: _t->car_stop(); break;
        case 5: _t->quick_left(); break;
        case 6: _t->quick_right(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *qt_for_car::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *qt_for_car::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSqt_for_carENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int qt_for_car::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
