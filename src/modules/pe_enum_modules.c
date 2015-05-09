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

static int pe_enum_modules(
	pe_enum_modules_callback *	callback,
	const uintptr_t			in_order_member_offset,
	void *				context)
{
	int				ret;
	uintptr_t 			peb_tbl_addr;
	struct pe_peb_ldr_data *	peb_ldr_data;
	struct pe_ldr_tbl_entry *	ldr_tbl_entry;
	struct pe_list_entry *		plist_head;
	struct pe_list_entry * 		plist_current;

	peb_ldr_data = (struct pe_peb_ldr_data *)pe_get_peb_ldr_data_address();
	plist_head   = (struct pe_list_entry *)0;

	if ((intptr_t)peb_ldr_data == 0) {
		callback(
			0,
			PE_CALLBACK_REASON_ERROR,
			context);
		return -1;
	}

	ret = callback(
		0,
		PE_CALLBACK_REASON_INIT,
		context);

	if (ret <= 0)
		return ret;

	switch (in_order_member_offset) {
		case IN_LOAD_ORDER_MODULE_LIST_OFFSET:
			plist_head = peb_ldr_data->in_load_order_module_list.flink;
			break;

		case IN_MEMORY_ORDER_MODULE_LIST_OFFSET:
			plist_head = peb_ldr_data->in_memory_order_module_list.flink;
			break;

		case IN_INITIALIZATION_ORDER_MODULE_LIST_OFFSET:
			plist_head = peb_ldr_data->in_init_order_module_list.flink;
			break;
	}

	plist_current = plist_head;

	do
	{
		peb_tbl_addr	= (uintptr_t)plist_current - in_order_member_offset;
		ldr_tbl_entry	= (struct pe_ldr_tbl_entry *)peb_tbl_addr;

		ret = callback(
			ldr_tbl_entry,
			PE_CALLBACK_REASON_ITEM,
			context);

		if (ret <= 0)
			return ret;
		else
			plist_current = plist_current->flink;

	} while (plist_current != plist_head);

	ret = callback(
			ldr_tbl_entry,
			PE_CALLBACK_REASON_DONE,
			context);

	return ret;
}


pe_api
int pe_enum_modules_in_load_order(pe_enum_modules_callback * fn, void * ctx)
{
	return pe_enum_modules(fn,IN_LOAD_ORDER_MODULE_LIST_OFFSET,ctx);
}

pe_api
int pe_enum_modules_in_memory_order(pe_enum_modules_callback * fn, void * ctx)
{
	return pe_enum_modules(fn,IN_MEMORY_ORDER_MODULE_LIST_OFFSET,ctx);
}

pe_api
int pe_enum_modules_in_init_order(pe_enum_modules_callback * fn, void * ctx)
{
	return pe_enum_modules(fn,IN_INITIALIZATION_ORDER_MODULE_LIST_OFFSET,ctx);
}
