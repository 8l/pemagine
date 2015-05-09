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
struct pe_image_dos_hdr * pe_get_image_dos_hdr_addr(const void * base)
{
	struct pe_image_dos_hdr * dos;

	dos = (struct pe_image_dos_hdr *)base;

	if ((dos->dos_magic[0] == 'M') && (dos->dos_magic[1] == 'Z'))
		return dos;
	else
		return 0;
}
