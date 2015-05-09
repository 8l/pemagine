/* optimize: use __readfsdword rather than explicit eax */

static __inline__ void * pe_get_teb_address(void)
{
	__asm {
		mov	eax, fs:0x18
	};
}


static __inline__ void * pe_get_peb_address(void)
{
	__asm {
		mov	eax, fs:0x18
		mov	eax, ds:[eax+0x30]
	};
}


static __inline__ void * pe_get_peb_address_alt(void)
{
	__asm {
		mov	eax, fs:0x30
	};
}


static __inline__ void * pe_get_peb_ldr_data_address(void)
{
	__asm {
		mov	eax, fs:0x18
		mov	eax, ds:[eax+0x30]
		mov	eax, ds:[eax+0x0C]
	};
}


static __inline__ void * pe_get_peb_ldr_data_address_alt(void)
{
	__asm {
		mov	eax, fs:0x30
		mov	eax, ds:[eax+0x0C]
	};
}

static __inline__ uint32_t pe_get_current_process_id(void)
{
	__asm {
		mov	eax, fs:0x20
	};
}

static __inline__ uint32_t pe_get_current_thread_id(void)
{
	__asm {
		mov	eax, fs:0x24
	};
}

static __inline__ uint32_t pe_get_current_session_id(void)
{
	__asm {
		mov	eax, fs:0x18
		mov	eax, ds:[eax+0x30]
		mov	eax, ds:[eax+0x1d4]
	};
}
