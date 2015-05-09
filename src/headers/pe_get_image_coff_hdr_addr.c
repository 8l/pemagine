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
struct pe_coff_file_hdr * pe_get_image_coff_hdr_addr(const void * base)
{
	struct pe_image_dos_hdr *	dos;
	struct pe_coff_file_hdr *	coff;
	uint32_t *			offset;

	if (!(dos = pe_get_image_dos_hdr_addr(base)))
		return 0;

	offset   = (uint32_t *)(dos->dos_lfanew);
	coff = (struct pe_coff_file_hdr *)pe_va_from_rva(base,*offset);

	if ((coff->signature[0] == 'P') && (coff->signature[1] == 'E')
			&& (coff->signature[2] == '\0') && (coff->signature[3] == '\0'))
		return coff;
	else
		return 0;
}
