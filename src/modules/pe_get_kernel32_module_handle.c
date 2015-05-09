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

static int pe_get_kernel32_handle_callback(
	struct pe_ldr_tbl_entry *	ldr_tbl_entry,
	enum pe_callback_reason		reason,
	void *				context)
{
	#define KERNEL32_UTF16_STRLEN	24

	int32_t		kernel32_base_name_le[4];
	char *		kernel32_base_name_ansi;

	intptr_t *	addr;
	char *		ch;
	size_t 		match;

	/* avoid scan-based false positives */
	kernel32_base_name_le[0] = 0x6E72656B; /* 'kern' */
	kernel32_base_name_le[1] = 0x32336C65; /* 'el32' */
	kernel32_base_name_le[2] = 0x6C6C642E; /* '.dll' */
	kernel32_base_name_le[3] = 0;

	kernel32_base_name_ansi = (char *)&kernel32_base_name_le;

	match = 0;
	addr = (intptr_t *)context;

	if (reason == PE_CALLBACK_REASON_ITEM)
		if (ldr_tbl_entry->base_dll_name.strlen == KERNEL32_UTF16_STRLEN) {
			ch	= (char *)ldr_tbl_entry->base_dll_name.buffer;
			match	= 0;

			while ((match < sizeof(kernel32_base_name_ansi))
				&& ((*ch == kernel32_base_name_ansi[match])
					|| (*ch == (kernel32_base_name_ansi[match] + 'A' - 'a')))
				&& (*(ch + 1) == 0)) {
					ch+=sizeof(uint16_t);
					match++;
				}
		}

	if (match == sizeof(kernel32_base_name_ansi)) {
		*addr = (intptr_t)ldr_tbl_entry->dll_base;
		return 0;
	}
	else
		return 1;
}


pe_api
void * pe_get_kernel32_module_handle(void)
{

	intptr_t kernel32_base_addr = 0;
	void * ptr_to_callback = &kernel32_base_addr;

	pe_enum_modules_in_init_order(
		&pe_get_kernel32_handle_callback,
		ptr_to_callback);

	return (void *)kernel32_base_addr;
}
