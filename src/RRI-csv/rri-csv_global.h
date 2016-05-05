#ifndef RRICSV_GLOBAL_H
#define RRICSV_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(RRICSV_LIBRARY)
#  define RRICSVSHARED_EXPORT Q_DECL_EXPORT
#else
#  define RRICSVSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // RRICSV_GLOBAL_H
