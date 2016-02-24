#ifndef RRIPRV_GLOBAL_H
#define RRIPRV_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(RRIPRV_LIBRARY)
#  define RRIPRVSHARED_EXPORT Q_DECL_EXPORT
#else
#  define RRIPRVSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // RRIPRV_GLOBAL_H
