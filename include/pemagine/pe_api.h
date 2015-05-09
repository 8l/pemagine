#ifndef PE_API_H
#define PE_API_H

/* portable integer types */
#if defined (MIDIPIX_FREESTANDING)
#include <psxtypes/psxtypes.h>
#else
#include <stdint.h>
#endif

/* pe_export */
#if	defined(__attr_export__)
#define pe_export __attr_export__
#else
#define pe_export
#endif

/* pe_import */
#if	defined(__attr_import__)
#define pe_import __attr_import__
#else
#define pe_import
#endif

/* pe_api */
#if     defined (PE_BUILD)
#define pe_api pe_export
#elif   defined (PE_SHARED)
#define pe_api pe_import
#elif   defined (PE_STATIC)
#define pe_api
#else
#define pe_api
#endif

#endif /* _PE_API_H_ */
