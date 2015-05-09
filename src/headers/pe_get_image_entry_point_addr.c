/*****************************************************************************/
/*  pemagination: a (virtual) tour into portable bits and executable bytes   */
/*  Copyright (C) 2013,2014,2015  Z. Gilboa                                  */
/*  Released under GPLv2 and GPLv3; see COPYING.PEMAGINE.                    */
/*****************************************************************************/

#include <psxtypes/psxtypes.h>
#include <pemagine/pe_structs.h>
#include <pemagine/pe_consts.h>
#include <pemagine/pemagine.h>


pe_api
void * pe_get_image_entry_point_addr(const void * base)
{
	uint16_t *		magic;
	union pe_opt_hdr *	hdr;
	uint32_t *		rva;

	if (!(hdr = pe_get_image_opt_hdr_addr(base)))
		return 0;

	magic = (uint16_t *)hdr;

	switch (*magic) {
		case PE_MAGIC_PE32:
			rva = (uint32_t *)hdr->opt_hdr_32.entry_point;
			break;

		case PE_MAGIC_PE32_PLUS:
			rva = (uint32_t *)hdr->opt_hdr_64.entry_point;
			break;

		default:
			return 0;
	}

	return pe_va_from_rva(base,*rva);
}
