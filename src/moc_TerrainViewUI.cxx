/****************************************************************************
** Meta object code from reading C++ file 'TerrainViewUI.h'
**
** Created: Sun Apr 24 14:54:33 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "TerrainViewUI.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TerrainViewUI.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TerrainView[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x09,
      24,   12,   12,   12, 0x09,
      38,   12,   12,   12, 0x09,
      52,   12,   12,   12, 0x09,
      64,   12,   12,   12, 0x09,
      79,   12,   12,   12, 0x09,
      97,   12,   12,   12, 0x09,
     110,   12,   12,   12, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_TerrainView[] = {
    "TerrainView\0\0slotExit()\0slotConnect()\0"
    "slotTerrain()\0slotFrame()\0slotAttitude()\0"
    "slotGroundPlane()\0slotOrigin()\0"
    "slotScreenshot()\0"
};

const QMetaObject TerrainView::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_TerrainView,
      qt_meta_data_TerrainView, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TerrainView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TerrainView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TerrainView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TerrainView))
        return static_cast<void*>(const_cast< TerrainView*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int TerrainView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: slotExit(); break;
        case 1: slotConnect(); break;
        case 2: slotTerrain(); break;
        case 3: slotFrame(); break;
        case 4: slotAttitude(); break;
        case 5: slotGroundPlane(); break;
        case 6: slotOrigin(); break;
        case 7: slotScreenshot(); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
