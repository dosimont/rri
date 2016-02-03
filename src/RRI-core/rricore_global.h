#ifndef RRICORE_GLOBAL_H
#define RRICORE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CORE_LIBRARY)
#  define CORESHARED_EXPORT Q_DECL_EXPORT
#else
#  define CORESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // RRICORE_GLOBAL_H
