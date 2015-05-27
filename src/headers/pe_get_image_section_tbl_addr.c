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
struct pe_sec_hdr * pe_get_image_section_tbl_addr (const void * base)
{
	struct pe_coff_file_hdr *	coff;
	union  pe_opt_hdr *		opt;

	if (!(coff = pe_get_image_coff_hdr_addr(base)))
		return 0;

	if (!(opt = pe_get_image_opt_hdr_addr(base)))
		return 0;

	return (struct pe_sec_hdr *)((char *)opt  + *(uint16_t *)coff->size_of_opt_hdr);
}

pe_api
struct pe_sec_hdr * pe_get_image_named_section_addr (const void * base, const char * name)
{
	uint16_t		count;
	struct pe_sec_hdr *	hdr;
	struct pe_coff_file_hdr*coff;
	char *			ch;
	uint32_t		len;
	uint32_t		pos;
	uint64_t		sname = 0;

	if (!(hdr = pe_get_image_section_tbl_addr(base)))
		return 0;

	coff  = pe_get_image_coff_hdr_addr(base);
	count = *(uint16_t *)coff->num_of_sections;

	if ((len = pe_impl_strlen_ansi(name)) > 8) {
		/* todo: long name support */
		return 0;
	} else {
		for (pos=0, ch=(char *)&sname; pos<len; pos++)
			ch[pos] = name[pos];

		for (; count; hdr++,count--)
			if (*(uint64_t *)hdr->name == sname)
				return hdr;
	}

	return 0;
}
