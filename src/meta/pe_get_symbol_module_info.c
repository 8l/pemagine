/*****************************************************************************/
/*  pemagination: a (virtual) tour into portable bits and executable bytes   */
/*  Copyright (C) 2013,2014,2015  Z. Gilboa                                  */
/*  Released under GPLv2 and GPLv3; see COPYING.PEMAGINE.                    */
/*****************************************************************************/

#include <psxtypes/psxtypes.h>
#include <pemagine/pemagine.h>


struct pe_module_info_ctx {
	uintptr_t			sym_addr;
	struct pe_ldr_tbl_entry *	image_ldr_tbl_entry;
};



static int pe_get_symbol_module_info_callback(
	struct pe_ldr_tbl_entry *	ldr_tbl_entry,
	enum pe_callback_reason		reason,
	void *				context)
{
	uintptr_t			image_base;
	uintptr_t			image_size;
	struct pe_module_info_ctx *	ctx;

	if (reason != PE_CALLBACK_REASON_ITEM)
		return 1;

	ctx = (struct pe_module_info_ctx *)context;
	image_base = (uintptr_t)(ldr_tbl_entry->dll_base);
	image_size = (uintptr_t)(ldr_tbl_entry->size_of_image);

	if ((ctx->sym_addr > image_base) && (ctx->sym_addr < image_base + image_size)) {
		/* within bounds */
		ctx->image_ldr_tbl_entry = ldr_tbl_entry;
		return 0;
	} else
		return 1;
}


pe_api
struct pe_ldr_tbl_entry * pe_get_symbol_module_info(const void * sym_addr)
{
	struct pe_module_info_ctx ctx;

	ctx.sym_addr = (uintptr_t)sym_addr;
	ctx.image_ldr_tbl_entry = 0;

	pe_enum_modules_in_load_order(
		pe_get_symbol_module_info_callback,
		&ctx);

	return ctx.image_ldr_tbl_entry;
}
