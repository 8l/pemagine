/*****************************************************************************/
/*  pemagination: a (virtual) tour into portable bits and executable bytes   */
/*  Copyright (C) 2013,2014,2015  Z. Gilboa                                  */
/*  Released under GPLv2 and GPLv3; see COPYING.PEMAGINE.                    */
/*****************************************************************************/

#include <psxtypes/psxtypes.h>
#include <pemagine/pe_consts.h>
#include <pemagine/pe_structs.h>
#include <pemagine/pemagine.h>

pe_api
int pe_enum_image_exports(
	const void *				base,
	pe_enum_image_exports_callback *	callback,
	struct pe_export_sym  *			sym,
	void *					ctx)
{
	struct pe_export_hdr *	exp_hdr;
	uint32_t *		count;
	uint32_t *		fn_addr;
	uint32_t *		fn_names;
	uint16_t *		fn_ordinals;
	uint32_t *		offset;
	uint32_t		idx;
	int			ret;

	if (!(exp_hdr = pe_get_image_export_hdr_addr(base,0))) {
		callback(base,0,0,PE_CALLBACK_REASON_ERROR,ctx);
		return -1;
	}

	offset  = (uint32_t *)(exp_hdr->export_addr_tbl_rva);
	fn_addr = (uint32_t *)pe_va_from_rva(base,*offset);

	offset   = (uint32_t *)(exp_hdr->name_ptr_rva);
	fn_names = (uint32_t *)pe_va_from_rva(base,*offset);

	offset      = (uint32_t *)(exp_hdr->ordinal_tbl_rva);
	fn_ordinals = (uint16_t *)pe_va_from_rva(base,*offset);

	if ((ret = callback(base,exp_hdr,0,PE_CALLBACK_REASON_INIT,ctx)) <= 0)
		return ret;

	count = (uint32_t *)exp_hdr->num_of_name_ptrs;
	sym->ordinal_base = (uint32_t *)exp_hdr->ordinal_base;

	for (idx=0; idx<*count; idx++) {
		offset = (uint32_t *)pe_va_from_rva(fn_names,idx*sizeof(uint32_t));
		sym->name = (char *)pe_va_from_rva(base,*offset);
		sym->ordinal = (uint16_t *)pe_va_from_rva(fn_ordinals,idx*sizeof(uint16_t));

		offset  = (uint32_t *)pe_va_from_rva(fn_addr,(*sym->ordinal)*sizeof(uint32_t));
		sym->addr = pe_va_from_rva(base,*offset);

		if ((ret = callback(base,exp_hdr,sym,PE_CALLBACK_REASON_ITEM,ctx)) <= 0)
			return ret;
	}

	return callback(base,exp_hdr,sym,PE_CALLBACK_REASON_DONE,ctx);
}
