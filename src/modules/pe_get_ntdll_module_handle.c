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
void * pe_get_ntdll_module_handle(void)
{
	struct pe_peb_ldr_data * 	peb_ldr_data;
	struct pe_list_entry *   	peb_list_entry;
	intptr_t 			peb_tbl_addr;
	struct pe_ldr_tbl_entry *	peb_ldr_tbl_entry;

	peb_ldr_data = (struct pe_peb_ldr_data *)pe_get_peb_ldr_data_address();
	peb_list_entry = peb_ldr_data->in_init_order_module_list.flink;
	peb_tbl_addr = (intptr_t)peb_list_entry - IN_INITIALIZATION_ORDER_MODULE_LIST_OFFSET;
	peb_ldr_tbl_entry = (struct pe_ldr_tbl_entry *)peb_tbl_addr;

	return peb_ldr_tbl_entry->dll_base;
}
