/*****************************************************************************/
/*  pemagination: a (virtual) tour into portable bits and executable bytes   */
/*  Copyright (C) 2013,2014,2015  Z. Gilboa                                  */
/*  Released under GPLv2 and GPLv3; see COPYING.PEMAGINE.                    */
/*****************************************************************************/

#include <psxtypes/psxtypes.h>
#include <pemagine/pe_consts.h>
#include <pemagine/pe_structs.h>
#include <pemagine/pemagine.h>
#include "pe_impl.h"

static __inline__ int pe_addr_within_bounds(void * addr, void * bottom, void * top)
{
	return (((uintptr_t)addr >= (uintptr_t)bottom) && ((uintptr_t)addr < (uintptr_t)top));
}

pe_api
int pe_get_export_symbol_info(
	const void *		base,
	const char *		name,
	struct pe_export_sym *	sym)
{
	struct pe_export_hdr *	exp_hdr;

	ssize_t		len;
	uint32_t *	rva_offset;
	uintptr_t *	addr_offset;

	uint32_t	sec_size;
	void *		sec_addr_cap;

	uint32_t *	fn_addr;
	uint32_t *	fn_names;
	uint16_t *	fn_ordinals;
	uint32_t *	addr_entries;
	uint32_t *	name_entries;

	char *		exp_name;
	const char *	src;
	const char *	dst;
	ssize_t		match;

	uint32_t	lower;
	uint32_t	upper;
	uint32_t	idx;

	/* initialize pe_exp_item */
	sym->ordinal_base	= (uint32_t *)0;
	sym->ordinal		= (uint16_t *)0;
	sym->addr		= (void *)0;
	sym->forwarder_rva	= (void *)0;
	sym->name		= (char *)0;
	sym->status		= 0;

	if (!(exp_hdr = pe_get_image_export_hdr_addr(base,&sec_size)))
		return -1;

	sec_addr_cap = pe_va_from_rva(exp_hdr,sec_size);
	rva_offset   = (uint32_t *)(exp_hdr->export_addr_tbl_rva);
	fn_addr      = (uint32_t *)pe_va_from_rva(base,*rva_offset);

	rva_offset = (uint32_t *)(exp_hdr->name_ptr_rva);
	fn_names   = (uint32_t *)pe_va_from_rva(base,*rva_offset);

	rva_offset  = (uint32_t *)(exp_hdr->ordinal_tbl_rva);
	fn_ordinals = (uint16_t *)pe_va_from_rva(base,*rva_offset);

	addr_entries = (uint32_t *)exp_hdr->addr_tbl_entries;
	name_entries = (uint32_t *)exp_hdr->num_of_name_ptrs;

	/* by ordinal? */
	if ((intptr_t)name < 0x10000) {
		sym->ordinal_base = (uint32_t *)exp_hdr->ordinal_base;

		/* the array is zero-based, but ordinals are normally one-based... */
		if (((intptr_t)name - *sym->ordinal_base + 1) > *addr_entries)
			return -1;

		rva_offset  = (uint32_t *)pe_va_from_rva(fn_addr,((uintptr_t)name-*sym->ordinal_base)*sizeof(uint32_t));
		addr_offset = (uintptr_t *)pe_va_from_rva(base,*rva_offset);

		if (pe_addr_within_bounds(addr_offset,exp_hdr,sec_addr_cap)) {
			sym->forwarder_rva = 0;
			sym->addr = addr_offset;
		} else
			/* todo: resolve forwarder address */
			sym->addr = addr_offset;

		return 0;
	}

	if ((len = pe_impl_strlen_ansi(name)) < 0)
		return -1;

	len++;
	lower  = 0;
	upper  = *name_entries;

	while (lower < upper) {
		idx    = (lower + upper) / 2;
		rva_offset = (uint32_t *)pe_va_from_rva(fn_names,idx*sizeof(uint32_t));
		exp_name   = (char *)pe_va_from_rva(base,*rva_offset);

		src = name;
		dst = exp_name;

		for (match=0; (match<len) && (*src==*dst); match++) {
				src++;
				dst++;
		}

		if (match == len) {
			sym->ordinal_base = (uint32_t *)exp_hdr->ordinal_base;
			sym->ordinal      = (uint16_t *)pe_va_from_rva(fn_ordinals,idx*sizeof(uint16_t));

			rva_offset  = (uint32_t *)pe_va_from_rva(fn_addr,(*sym->ordinal)*sizeof(uint32_t));
			addr_offset = (uintptr_t *)pe_va_from_rva(base,*rva_offset);

			if (pe_addr_within_bounds(addr_offset,exp_hdr,sec_addr_cap)) {
				/* todo: resolve forwarder address */
				sym->forwarder_rva = 0;
				sym->addr = 0;
			} else {
				sym->forwarder_rva = 0;
				sym->addr = addr_offset;
			}

			return 0;
		}

		else {
			if (*src > *dst)
				lower = idx + 1;
			else
				upper = idx;
		}
	}

	/* export name not found */
	return -1;
}
