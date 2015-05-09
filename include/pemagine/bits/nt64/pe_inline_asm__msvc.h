#include <psxtypes/psxtypes.h>

unsigned __int64 __readgsqword(unsigned long);

static __inline__ void * pe_get_teb_address(void)
{
	return (void *)__readgsqword(0x30);
}


static __inline__ void * pe_get_peb_address(void)
{
	return (void *)__readgsqword(0x60);
}


static __inline__ void * pe_get_peb_address_alt(void)
{
	return (void *)__readgsqword(0x60);
}


static __inline__ void * pe_get_peb_ldr_data_address(void)
{
	char * rsi;

	rsi  = (char *)__readgsqword(0x60);
	rsi += 0x18;

	return *(void **)rsi;
}


static __inline__ void * pe_get_peb_ldr_data_address_alt(void)
{
	return pe_get_peb_ldr_data_address();
}


static __inline__ uint32_t pe_get_current_process_id(void)
{
	return (uint32_t)__readgsqword(0x40);
}

static __inline__ uint32_t pe_get_current_thread_id(void)
{
	return (uint32_t)__readgsqword(0x48);
}

static __inline__ uint32_t pe_get_current_session_id(void)
{
	char * rsi;

	rsi = (char *)__readgsqword(0x60);
	rsi += 0x2c0;

	return *(uint32_t *)rsi;
}
