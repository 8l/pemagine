# direct linker invocation
LDFLAGS_SYSROOT = $(CFLAGS_SYSROOT)

ifneq ($(PE_SUBSYSTEM)x,x)
	LDFLAGS_COMMON += --subsystem=$(PE_SUBSYSTEM)
endif
