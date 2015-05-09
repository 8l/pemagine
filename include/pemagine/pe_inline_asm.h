#if defined(__NT32)
#if (__COMPILER__ == __GCC__)
#include "bits/nt32/pe_inline_asm__gcc.h"
#elif (__COMPILER__ == __MSVC__)
#include "bits/nt32/pe_inline_asm__msvc.h"
#endif

#elif defined(__NT64)
#if (__COMPILER__ == __GCC__)
#include "bits/nt64/pe_inline_asm__gcc.h"
#elif (__COMPILER__ == __MSVC__)
#include "bits/nt64/pe_inline_asm__msvc.h"
#endif
#endif

/* trivial */
static __inline__ void * pe_va_from_rva(const void * base, intptr_t offset)
{
        return (void *)((intptr_t)base + offset);
}
