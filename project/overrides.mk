ifneq ($(PE_SUBSYSTEM),)
	LDFLAGS_COMMON += -Wl,--subsystem=$(PE_SUBSYSTEM)
endif
