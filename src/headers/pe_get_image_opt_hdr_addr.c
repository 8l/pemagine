/*****************************************************************************/
/*  pemagination: a (virtual) tour into portable bits and executable bytes   */
/*  Copyright (C) 2013,2014,2015  Z. Gilboa                                  */
/*  Released under GPLv2 and GPLv3; see COPYING.PEMAGINE.                    */
/*****************************************************************************/

#include <psxtypes/psxtypes.h>
#include <pemagine/pe_structs.h>
#include <pemagine/pemagine.h>

pe_api
union pe_opt_hdr * pe_get_image_opt_hdr_addr(const void * base)
{
	struct pe_coff_file_hdr * coff;

	if (!(coff = pe_get_image_coff_hdr_addr(base)))
		return 0;
	else
		return (union pe_opt_hdr *)pe_va_from_rva(coff, sizeof(*coff));
}
