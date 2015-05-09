/*****************************************************************************/
/*  pemagination: a (virtual) tour into portable bits and executable bytes   */
/*  Copyright (C) 2013,2014,2015  Z. Gilboa                                  */
/*  Released under GPLv2 and GPLv3; see COPYING.PEMAGINE.                    */
/*****************************************************************************/

#include <psxtypes/psxtypes.h>
#include <pemagine/pe_structs.h>
#include <pemagine/pemagine.h>

pe_api
int pe_enum_image_import_hdrs(
	const void *				base,
	pe_enum_image_import_hdrs_callback *	callback,
	void *					ctx)
{
	struct pe_import_hdr *	imp_hdr;
	int			ret;

	if (!(imp_hdr = pe_get_image_import_dir_addr(base,0))) {
		callback(base,0,PE_CALLBACK_REASON_ERROR,ctx);
		return -1;
	}

	if ((ret = callback(base,0,PE_CALLBACK_REASON_INIT,ctx)) <= 0)
		return ret;

	while (imp_hdr->name_rva[0]) {
		if ((ret = callback(base,imp_hdr,PE_CALLBACK_REASON_ITEM,ctx)) <= 0)
			return ret;
		imp_hdr++;
	};

	return callback(base,imp_hdr,PE_CALLBACK_REASON_DONE,ctx);
}
