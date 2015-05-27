/*****************************************************************************/
/*  pemagination: a (virtual) tour into portable bits and executable bytes   */
/*  Copyright (C) 2013,2014,2015  Z. Gilboa                                  */
/*  Released under GPLv2 and GPLv3; see COPYING.PEMAGINE.                    */
/*****************************************************************************/

#include <psxtypes/psxtypes.h>
#include <pemagine/pemagine.h>
#include "pe_impl.h"

uint32_t pe_impl_strlen_ansi(const char * str)
{
	char * ch;
	char * upper_bound;

	/* sanity check */
	upper_bound = (char *)str + PE_STR_MAX_SYMBOL_LEN_ALLOWED;

	for (ch = (char *)str; (ch < upper_bound) && (*ch); ch++);

	if (ch < upper_bound)
		return (uint32_t)(ch - str);
	else
		return -1;
}


uint32_t pe_impl_strlen_utf16(const wchar16_t * str)
{
	wchar16_t *	wch;
	wchar16_t *	upper_bound;

	/* sanity check */
	upper_bound = (wchar16_t *)str + PE_STR_MAX_SYMBOL_LEN_ALLOWED;

	for (wch = (wchar16_t *)str; (wch < upper_bound) && (*wch); wch++);

	if (wch < upper_bound)
		return (uint32_t)(wch - str);
	else
		return -1;
}


wchar16_t pe_impl_utf16_char_to_lower(const wchar16_t c)
{
	if ((c >= 'A') && (c <= 'Z'))
		return c + 'a' - 'A';
	else
		return c;
}
