#include <psxtypes/psxtypes.h>
#include <pemagine/pemagine.h>

#define PE_STR_MAX_SYMBOL_LEN_ALLOWED			(uint32_t)0x10000

#define IN_LOAD_ORDER_MODULE_LIST_OFFSET		(intptr_t)0x00
#define IN_MEMORY_ORDER_MODULE_LIST_OFFSET		(intptr_t)0x01 * sizeof(struct pe_list_entry)
#define IN_INITIALIZATION_ORDER_MODULE_LIST_OFFSET	(intptr_t)0x02 * sizeof(struct pe_list_entry)

struct pe_block {
	uint32_t	rva;
	uint32_t	size;
};

size_t		pe_impl_strlen_ansi(const char * str);
size_t		pe_impl_strlen_utf16(const wchar16_t * str);
wchar16_t	pe_impl_utf16_char_to_lower(const wchar16_t c);
