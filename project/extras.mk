CFLAGS_SHARED_ATTR 	+= -DPE_BUILD
CFLAGS_STATIC_ATTR 	+= -DPE_STATIC

CFLAGS_CONFIG 		+= -DMIDIPIX_FREESTANDING -ffreestanding -D__NT$(HOST_BITS)
CFLAGS_CONFIG 		+= -UWIN32 -U_WIN32 -U__WIN32 -U__WIN32__
CFLAGS_CONFIG 		+= -UWIN64 -U_WIN64 -U__WIN64 -U__WIN64__

LDFLAGS_SHARED 		+= --out-implib $(SHARED_IMPLIB)
LDFLAGS_SHARED 		+= --exclude-all-symbols

ifeq ($(HOST_BITS),32)
	LDFLAGS_SHARED 	+= --entry $(HOST_UNDERSCORE)pe_entry_point@12
else
	LDFLAGS_SHARED 	+= --entry $(HOST_UNDERSCORE)pe_entry_point
endif
