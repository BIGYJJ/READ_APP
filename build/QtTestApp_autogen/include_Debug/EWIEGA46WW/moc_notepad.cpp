/****************************************************************************
** Meta object code from reading C++ file 'notepad.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../notepad.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'notepad.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.3. It"
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
struct qt_meta_stringdata_CLASSNotePadENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSNotePadENDCLASS = QtMocHelpers::stringData(
    "NotePad",
    "newFile",
    "",
    "openFile",
    "saveFile",
    "saveAsFile",
    "undo",
    "redo",
    "cut",
    "copy",
    "paste",
    "selectAll",
    "setFont",
    "setColor",
    "about",
    "documentModified",
    "updateStatusBar",
    "fontFamilyChanged",
    "font",
    "fontSizeChanged",
    "size",
    "boldClicked",
    "checked",
    "italicClicked",
    "underlineClicked",
    "textColorClicked",
    "updateFormatButtons",
    "insertImage",
    "showFileToolBar",
    "showEditToolBar",
    "showFormatToolBar",
    "showInsertToolBar",
    "showHelpToolBar"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSNotePadENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      28,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  182,    2, 0x08,    1 /* Private */,
       3,    0,  183,    2, 0x08,    2 /* Private */,
       4,    0,  184,    2, 0x08,    3 /* Private */,
       5,    0,  185,    2, 0x08,    4 /* Private */,
       6,    0,  186,    2, 0x08,    5 /* Private */,
       7,    0,  187,    2, 0x08,    6 /* Private */,
       8,    0,  188,    2, 0x08,    7 /* Private */,
       9,    0,  189,    2, 0x08,    8 /* Private */,
      10,    0,  190,    2, 0x08,    9 /* Private */,
      11,    0,  191,    2, 0x08,   10 /* Private */,
      12,    0,  192,    2, 0x08,   11 /* Private */,
      13,    0,  193,    2, 0x08,   12 /* Private */,
      14,    0,  194,    2, 0x08,   13 /* Private */,
      15,    0,  195,    2, 0x08,   14 /* Private */,
      16,    0,  196,    2, 0x08,   15 /* Private */,
      17,    1,  197,    2, 0x08,   16 /* Private */,
      19,    1,  200,    2, 0x08,   18 /* Private */,
      21,    1,  203,    2, 0x08,   20 /* Private */,
      23,    1,  206,    2, 0x08,   22 /* Private */,
      24,    1,  209,    2, 0x08,   24 /* Private */,
      25,    0,  212,    2, 0x08,   26 /* Private */,
      26,    0,  213,    2, 0x08,   27 /* Private */,
      27,    0,  214,    2, 0x08,   28 /* Private */,
      28,    0,  215,    2, 0x08,   29 /* Private */,
      29,    0,  216,    2, 0x08,   30 /* Private */,
      30,    0,  217,    2, 0x08,   31 /* Private */,
      31,    0,  218,    2, 0x08,   32 /* Private */,
      32,    0,  219,    2, 0x08,   33 /* Private */,

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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QFont,   18,
    QMetaType::Void, QMetaType::QString,   20,
    QMetaType::Void, QMetaType::Bool,   22,
    QMetaType::Void, QMetaType::Bool,   22,
    QMetaType::Void, QMetaType::Bool,   22,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject NotePad::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSNotePadENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSNotePadENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSNotePadENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<NotePad, std::true_type>,
        // method 'newFile'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'openFile'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'saveFile'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'saveAsFile'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'undo'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'redo'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'cut'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'copy'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'paste'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'selectAll'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setFont'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setColor'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'about'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'documentModified'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateStatusBar'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'fontFamilyChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QFont &, std::false_type>,
        // method 'fontSizeChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'boldClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'italicClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'underlineClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'textColorClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateFormatButtons'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'insertImage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showFileToolBar'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showEditToolBar'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showFormatToolBar'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showInsertToolBar'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showHelpToolBar'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void NotePad::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NotePad *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->newFile(); break;
        case 1: _t->openFile(); break;
        case 2: _t->saveFile(); break;
        case 3: _t->saveAsFile(); break;
        case 4: _t->undo(); break;
        case 5: _t->redo(); break;
        case 6: _t->cut(); break;
        case 7: _t->copy(); break;
        case 8: _t->paste(); break;
        case 9: _t->selectAll(); break;
        case 10: _t->setFont(); break;
        case 11: _t->setColor(); break;
        case 12: _t->about(); break;
        case 13: _t->documentModified(); break;
        case 14: _t->updateStatusBar(); break;
        case 15: _t->fontFamilyChanged((*reinterpret_cast< std::add_pointer_t<QFont>>(_a[1]))); break;
        case 16: _t->fontSizeChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 17: _t->boldClicked((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 18: _t->italicClicked((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 19: _t->underlineClicked((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 20: _t->textColorClicked(); break;
        case 21: _t->updateFormatButtons(); break;
        case 22: _t->insertImage(); break;
        case 23: _t->showFileToolBar(); break;
        case 24: _t->showEditToolBar(); break;
        case 25: _t->showFormatToolBar(); break;
        case 26: _t->showInsertToolBar(); break;
        case 27: _t->showHelpToolBar(); break;
        default: ;
        }
    }
}

const QMetaObject *NotePad::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NotePad::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSNotePadENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int NotePad::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 28)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 28;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 28)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 28;
    }
    return _id;
}
QT_WARNING_POP
