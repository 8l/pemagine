CFLAGS_SHARED_ATTR 	+= -DPE_BUILD
CFLAGS_STATIC_ATTR 	+= -DPE_STATIC

CFLAGS_CONFIG 		+= -DMIDIPIX_FREESTANDING -D__NT$(HOST_BITS)
CFLAGS_CONFIG 		+= -UWIN32 -U_WIN32 -U__WIN32 -U__WIN32__
CFLAGS_CONFIG 		+= -UWIN64 -U_WIN64 -U__WIN64 -U__WIN64__

LDFLAGS_SHARED 		+= -Wl,--exclude-all-symbols
LDFLAGS_SHARED 		+= -nostdlib

ifeq ($(HOST_BITS),32)
	LDFLAGS_SHARED 	+= -Wl,--entry -Wl,$(HOST_UNDERSCORE)pe_entry_point@12
else
	LDFLAGS_SHARED 	+= -Wl,--entry -Wl,$(HOST_UNDERSCORE)pe_entry_point
endif

install-headers-custom:	install-headers-default
			mkdir -p $(DESTDIR)$(INCLUDEDIR)/$(PACKAGE)/bits
			mkdir -p $(DESTDIR)$(INCLUDEDIR)/$(PACKAGE)/bits/nt32
			mkdir -p $(DESTDIR)$(INCLUDEDIR)/$(PACKAGE)/bits/nt64

			cp $(API_HEADERS_NT32) \
			   $(DESTDIR)$(INCLUDEDIR)/$(PACKAGE)/bits/nt32

			cp $(API_HEADERS_NT64) \
			   $(DESTDIR)$(INCLUDEDIR)/$(PACKAGE)/bits/nt64
