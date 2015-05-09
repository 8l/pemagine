static __inline__ void * pe_get_teb_address(void)
{
	void * ptrRet;
	__asm__ __volatile__ (
		"mov %%gs:0x30, %0\n\t"
		: "=r" (ptrRet) : :
		);
	return ptrRet;
}


static __inline__ void * pe_get_peb_address(void)
{
	void * ptrRet;
	__asm__ __volatile__ (
		"mov %%gs:0x60, %0\n\t"
		: "=r" (ptrRet) : :
		);
	return ptrRet;
}


static __inline__ void * pe_get_peb_address_alt(void)
{
	void * ptrRet;
	__asm__ __volatile__ (
		"mov %%gs:0x60, %0\n\t"
		: "=r" (ptrRet) : :
		);
	return ptrRet;
}


static __inline__ void * pe_get_peb_ldr_data_address(void)
{
	void * ptrRet;
	__asm__ __volatile__ (
		"mov %%gs:0x60, %0\n\t"
		"mov %%ds:0x18(%0), %0\n\t"
		: "=r" (ptrRet) : :
		);
	return ptrRet;
}


static __inline__ void * pe_get_peb_ldr_data_address_alt(void)
{
	void * ptrRet;
	__asm__ __volatile__ (
		"mov %%gs:0x60, %0\n\t"
		"mov %%ds:0x18(%0), %0\n\t"
		: "=r" (ptrRet) : :
		);
	return ptrRet;
}


static __inline__ uint32_t pe_get_current_process_id(void)
{
	uint32_t ptrRet;
	__asm__ __volatile__ (
		"mov %%gs:0x40, %0\n\t"
		: "=r" (ptrRet) : :
		);
	return ptrRet;
}

static __inline__ uint32_t pe_get_current_thread_id(void)
{
	uint32_t ptrRet;
	__asm__ __volatile__ (
		"mov %%gs:0x48, %0\n\t"
		: "=r" (ptrRet) : :
		);
	return ptrRet;
}

static __inline__ uint32_t pe_get_current_session_id(void)
{
	uint32_t ptrRet;
	__asm__ __volatile__ (
		"mov %%gs:0x60, %0\n\t"
		"mov %%ds:0x2c0(%0), %0\n\t"
		: "=r" (ptrRet) : :
		);
	return ptrRet;
}
