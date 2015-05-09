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

pe_api
void * pe_get_first_module_handle(void)
{
	struct pe_peb_ldr_data *	peb_ldr_data;
	struct pe_list_entry *   	peb_list_entry;
	intptr_t 			peb_tbl_addr;
	struct pe_ldr_tbl_entry *	peb_ldr_tbl_entry;

	peb_ldr_data		= (struct pe_peb_ldr_data *)pe_get_peb_ldr_data_address();
	peb_list_entry		= (struct pe_list_entry *)peb_ldr_data->in_load_order_module_list.flink;
	peb_tbl_addr		= (intptr_t)peb_list_entry - IN_LOAD_ORDER_MODULE_LIST_OFFSET;
	peb_ldr_tbl_entry	= (struct pe_ldr_tbl_entry *)peb_tbl_addr;

	return peb_ldr_tbl_entry->dll_base;
}

pe_api
void * pe_get_module_handle(const wchar16_t * name)
{
	wchar16_t * src;
	wchar16_t * dst;

	size_t match;
	size_t len;

	struct pe_peb_ldr_data *	peb_ldr_data;
	struct pe_list_entry *		plist_head;

	struct pe_list_entry *		plist_current;
	struct pe_ldr_tbl_entry *	ldr_tbl_entry = 0;

	peb_ldr_data  = (struct pe_peb_ldr_data *)pe_get_peb_ldr_data_address();
	plist_head    = (struct pe_list_entry *)peb_ldr_data->in_load_order_module_list.flink;
	plist_current = plist_head;

	len = pe_impl_strlen_utf16(name);

	do {
		ldr_tbl_entry = (struct pe_ldr_tbl_entry *)plist_current - IN_LOAD_ORDER_MODULE_LIST_OFFSET;

		if (ldr_tbl_entry->base_dll_name.strlen == len)
			dst = (wchar16_t *)ldr_tbl_entry->base_dll_name.buffer;
		else if (ldr_tbl_entry->full_dll_name.strlen == len)
			dst = (wchar16_t *)ldr_tbl_entry->full_dll_name.buffer;
                else
                        dst = (wchar16_t *)0;

		if ((intptr_t)(dst)) {
		        src   = (wchar16_t *)name;
			match = 0;

			while ((match < len)
				&& ((pe_impl_utf16_char_to_lower(*src)) == (pe_impl_utf16_char_to_lower(*dst)))) {
					src = (wchar16_t *)pe_va_from_rva(src,sizeof(wchar16_t));
					dst = (wchar16_t *)pe_va_from_rva(dst,sizeof(wchar16_t));
					match+=sizeof(wchar16_t);
				}

			if (match == len)
				return ldr_tbl_entry->dll_base;
		}

		plist_current = plist_current->flink;
	} while (plist_current != plist_head);

	/* address not found */
	return 0;
}
