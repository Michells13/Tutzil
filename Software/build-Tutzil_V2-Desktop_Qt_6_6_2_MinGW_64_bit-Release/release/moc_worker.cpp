/****************************************************************************
** Meta object code from reading C++ file 'worker.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Tutzil_V2/worker.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'worker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.2. It"
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
struct qt_meta_stringdata_CLASSWorkerENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSWorkerENDCLASS = QtMocHelpers::stringData(
    "Worker",
    "updateTextBrowser",
    "",
    "text",
    "updateFrame",
    "frame",
    "allDataArray",
    "updateData",
    "finished",
    "doWork",
    "stopComms",
    "checkPacketSize",
    "QTcpSocket*",
    "socket",
    "expectedSize",
    "timeout",
    "handleProcessOutput",
    "handleProcessFinished",
    "exitCode",
    "QProcess::ExitStatus",
    "exitStatus"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSWorkerENDCLASS_t {
    uint offsetsAndSizes[42];
    char stringdata0[7];
    char stringdata1[18];
    char stringdata2[1];
    char stringdata3[5];
    char stringdata4[12];
    char stringdata5[6];
    char stringdata6[13];
    char stringdata7[11];
    char stringdata8[9];
    char stringdata9[7];
    char stringdata10[10];
    char stringdata11[16];
    char stringdata12[12];
    char stringdata13[7];
    char stringdata14[13];
    char stringdata15[8];
    char stringdata16[20];
    char stringdata17[22];
    char stringdata18[9];
    char stringdata19[21];
    char stringdata20[11];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSWorkerENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSWorkerENDCLASS_t qt_meta_stringdata_CLASSWorkerENDCLASS = {
    {
        QT_MOC_LITERAL(0, 6),  // "Worker"
        QT_MOC_LITERAL(7, 17),  // "updateTextBrowser"
        QT_MOC_LITERAL(25, 0),  // ""
        QT_MOC_LITERAL(26, 4),  // "text"
        QT_MOC_LITERAL(31, 11),  // "updateFrame"
        QT_MOC_LITERAL(43, 5),  // "frame"
        QT_MOC_LITERAL(49, 12),  // "allDataArray"
        QT_MOC_LITERAL(62, 10),  // "updateData"
        QT_MOC_LITERAL(73, 8),  // "finished"
        QT_MOC_LITERAL(82, 6),  // "doWork"
        QT_MOC_LITERAL(89, 9),  // "stopComms"
        QT_MOC_LITERAL(99, 15),  // "checkPacketSize"
        QT_MOC_LITERAL(115, 11),  // "QTcpSocket*"
        QT_MOC_LITERAL(127, 6),  // "socket"
        QT_MOC_LITERAL(134, 12),  // "expectedSize"
        QT_MOC_LITERAL(147, 7),  // "timeout"
        QT_MOC_LITERAL(155, 19),  // "handleProcessOutput"
        QT_MOC_LITERAL(175, 21),  // "handleProcessFinished"
        QT_MOC_LITERAL(197, 8),  // "exitCode"
        QT_MOC_LITERAL(206, 20),  // "QProcess::ExitStatus"
        QT_MOC_LITERAL(227, 10)   // "exitStatus"
    },
    "Worker",
    "updateTextBrowser",
    "",
    "text",
    "updateFrame",
    "frame",
    "allDataArray",
    "updateData",
    "finished",
    "doWork",
    "stopComms",
    "checkPacketSize",
    "QTcpSocket*",
    "socket",
    "expectedSize",
    "timeout",
    "handleProcessOutput",
    "handleProcessFinished",
    "exitCode",
    "QProcess::ExitStatus",
    "exitStatus"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSWorkerENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   68,    2, 0x06,    1 /* Public */,
       4,    2,   71,    2, 0x06,    3 /* Public */,
       7,    1,   76,    2, 0x06,    6 /* Public */,
       8,    0,   79,    2, 0x06,    8 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       9,    0,   80,    2, 0x0a,    9 /* Public */,
      10,    0,   81,    2, 0x0a,   10 /* Public */,
      11,    3,   82,    2, 0x0a,   11 /* Public */,
      16,    0,   89,    2, 0x08,   15 /* Private */,
      17,    2,   90,    2, 0x08,   16 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QImage, QMetaType::QJsonArray,    5,    6,
    QMetaType::Void, QMetaType::QJsonArray,    6,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool, 0x80000000 | 12, QMetaType::Int, QMetaType::Int,   13,   14,   15,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 19,   18,   20,

       0        // eod
};

Q_CONSTINIT const QMetaObject Worker::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSWorkerENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSWorkerENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSWorkerENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Worker, std::true_type>,
        // method 'updateTextBrowser'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'updateFrame'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QImage &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QJsonArray &, std::false_type>,
        // method 'updateData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QJsonArray &, std::false_type>,
        // method 'finished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'doWork'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'stopComms'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'checkPacketSize'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<QTcpSocket *, std::false_type>,
        QtPrivate::TypeAndForceComplete<qint32, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'handleProcessOutput'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleProcessFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<QProcess::ExitStatus, std::false_type>
    >,
    nullptr
} };

void Worker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Worker *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updateTextBrowser((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->updateFrame((*reinterpret_cast< std::add_pointer_t<QImage>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QJsonArray>>(_a[2]))); break;
        case 2: _t->updateData((*reinterpret_cast< std::add_pointer_t<QJsonArray>>(_a[1]))); break;
        case 3: _t->finished(); break;
        case 4: _t->doWork(); break;
        case 5: _t->stopComms(); break;
        case 6: { bool _r = _t->checkPacketSize((*reinterpret_cast< std::add_pointer_t<QTcpSocket*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<qint32>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 7: _t->handleProcessOutput(); break;
        case 8: _t->handleProcessFinished((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QProcess::ExitStatus>>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QTcpSocket* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Worker::*)(const QString & );
            if (_t _q_method = &Worker::updateTextBrowser; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Worker::*)(const QImage & , const QJsonArray & );
            if (_t _q_method = &Worker::updateFrame; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Worker::*)(const QJsonArray & );
            if (_t _q_method = &Worker::updateData; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Worker::*)();
            if (_t _q_method = &Worker::finished; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject *Worker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Worker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSWorkerENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Worker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void Worker::updateTextBrowser(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Worker::updateFrame(const QImage & _t1, const QJsonArray & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Worker::updateData(const QJsonArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Worker::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
