static __inline__ void * pe_get_teb_address(void)
{
	void * ptrRet;
	__asm__ __volatile__ (
		"mov %%fs:0x18, %0\n\t"
		: "=r" (ptrRet) : :
		);
	return ptrRet;
}


static __inline__ void * pe_get_peb_address(void)
{
	void * ptrRet;
	__asm__ __volatile__ (
		"mov %%fs:0x18, %0\n\t"
		"mov %%ds:0x30(%0), %0\n\t"
		: "=r" (ptrRet) : :
		);
	return ptrRet;
}


static __inline__ void * pe_get_peb_address_alt(void)
{
	void * ptrRet;
	__asm__ __volatile__ (
		"mov %%fs:0x30, %0\n\t"
		: "=r" (ptrRet) : :
		);
	return ptrRet;
}


static __inline__ void * pe_get_peb_ldr_data_address(void)
{
	void * ptrRet;
	__asm__ __volatile__ (
		"mov %%fs:0x18, %0\n\t"
		"mov %%ds:0x30(%0), %0\n\t"
		"mov %%ds:0x0C(%0), %0\n\t"
		: "=r" (ptrRet) : :
		);
	return ptrRet;
}


static __inline__ void * pe_get_peb_ldr_data_address_alt(void)
{
	void * ptrRet;
	__asm__ __volatile__ (
		"mov %%fs:0x30, %0\n\t"
		"mov %%ds:0x0C(%0), %0\n\t"
		: "=r" (ptrRet) : :
		);
	return ptrRet;
}

static __inline__ uint32_t pe_get_current_process_id(void)
{
	uint32_t ptrRet;
	__asm__ __volatile__ (
		"mov %%fs:0x20, %0\n\t"
		: "=r" (ptrRet) : :
		);
	return ptrRet;
}

static __inline__ uint32_t pe_get_current_thread_id(void)
{
	uint32_t ptrRet;
	__asm__ __volatile__ (
		"mov %%fs:0x24, %0\n\t"
		: "=r" (ptrRet) : :
		);
	return ptrRet;
}

static __inline__ uint32_t pe_get_current_session_id(void)
{
	uint32_t ptrRet;
	__asm__ __volatile__ (
		"mov %%fs:0x18, %0\n\t"
		"mov %%ds:0x30(%0), %0\n\t"
		"mov %%ds:0x1d4(%0), %0\n\t"
		: "=r" (ptrRet) : :
		);
	return ptrRet;
}
