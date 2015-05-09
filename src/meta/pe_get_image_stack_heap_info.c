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
int pe_get_image_stack_heap_info(const void * base, struct pe_stack_heap_info * stack_heap_info)
{
	uint16_t *		magic;
	union pe_opt_hdr *	hdr;

	if (!(hdr = pe_get_image_opt_hdr_addr(base)))
		return 0;

	magic = (uint16_t *)hdr;

	switch (*magic) {
		case PE_MAGIC_PE32:
			stack_heap_info->size_of_stack_reserve = *(uint32_t *)hdr->opt_hdr_32.size_of_stack_reserve;
			stack_heap_info->size_of_stack_commit  = *(uint32_t *)hdr->opt_hdr_32.size_of_stack_commit;
			stack_heap_info->size_of_heap_reserve  = *(uint32_t *)hdr->opt_hdr_32.size_of_heap_reserve;
			stack_heap_info->size_of_heap_commit   = *(uint32_t *)hdr->opt_hdr_32.size_of_heap_commit;
			break;

		case PE_MAGIC_PE32_PLUS:
			stack_heap_info->size_of_stack_reserve = *(size_t *)hdr->opt_hdr_64.size_of_stack_reserve;
			stack_heap_info->size_of_stack_commit  = *(size_t *)hdr->opt_hdr_64.size_of_stack_commit;
			stack_heap_info->size_of_heap_reserve  = *(size_t *)hdr->opt_hdr_64.size_of_heap_reserve;
			stack_heap_info->size_of_heap_commit   = *(size_t *)hdr->opt_hdr_64.size_of_heap_commit;
			break;

		default:
			return -1;
	}

	return 0;
}
