CC 		= $(CROSS_COMPILE)gcc
CPP 		= $(CROSS_COMPILE)cpp
CXX 		= $(CROSS_COMPILE)c++


AS 		= $(CROSS_COMPILE)as
AR 		= $(CROSS_COMPILE)ar
LD 		= $(CROSS_COMPILE)ld
NM 		= $(CROSS_COMPILE)nm
OBJDUMP 	= $(CROSS_COMPILE)objdump
RANLIB 		= $(CROSS_COMPILE)ranlib
SIZE 		= $(CROSS_COMPILE)size
STRIP 		= $(CROSS_COMPILE)strip
STRINGS 	= $(CROSS_COMPILE)strings


ADDR2LINE 	= $(CROSS_COMPILE)addr2line
COV 		= $(CROSS_COMPILE)gcov
CXXFILT 	= $(CROSS_COMPILE)c++filt
ELFEDIT 	= $(CROSS_COMPILE)elfedit
OBJCOPY 	= $(CROSS_COMPILE)objcopy
READELF 	= $(CROSS_COMPILE)readelf


CFLAGS_PIC 	= -fPIC
