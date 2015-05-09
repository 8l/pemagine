/*****************************************************************************/
/*  pemagination: a (virtual) tour into portable bits and executable bytes   */
/*  Copyright (C) 2013,2014,2015  Z. Gilboa                                  */
/*  Released under GPLv2 and GPLv3; see COPYING.PEMAGINE.                    */
/*****************************************************************************/

#include <psxtypes/psxtypes.h>
#include <pemagine/pemagine.h>

/* private args structure */
struct pe_symbol_name_ctx {
	const void *	addr;
	char *		name;
};

/* private forward declarations */
static int pe_enum_exports_callback(
	const void *			base,
	struct pe_export_hdr *		exp_hdr,
	struct pe_export_sym *		sym,
	enum pe_callback_reason		reason,
	void *				context);

#if defined (__NT32)
static char * pe_get_imported_symbol_info_32(
	const void *			sym_addr,
	void **				sym_image_addr,
	char **				sym_name,
	struct pe_ldr_tbl_entry **	ldr_tbl_entry);
#endif

#if defined (__NT64)
static char * pe_get_imported_symbol_info_64(
	const void *			sym_addr,
	void **				sym_image_addr,
	char **				sym_name,
	struct pe_ldr_tbl_entry **	ldr_tbl_entry);
;
#endif

pe_api
char * pe_get_symbol_name(const void * base, const void * sym_addr)
{
	struct pe_export_sym		exp_item;
	struct pe_symbol_name_ctx	ctx;

	ctx.name = 0;
	ctx.addr = sym_addr;

	pe_enum_image_exports(
		base,
		pe_enum_exports_callback,
		&exp_item,
		&ctx);

	return ctx.name;
}


pe_api
char * pe_get_import_symbol_info(
	const void *			sym_addr,
	void **				sym_image_addr,
	char **				sym_name,
	struct pe_ldr_tbl_entry **	ldr_tbl_entry)
{
	#if defined(__NT32)
		return pe_get_imported_symbol_info_32(
			sym_addr,
			sym_image_addr,
			sym_name,
			ldr_tbl_entry);
	#elif defined (__NT64)
		return pe_get_imported_symbol_info_64(
			sym_addr,
			sym_image_addr,
			sym_name,
			ldr_tbl_entry);
	#endif
}

static int pe_enum_exports_callback(
	const void *			base,
	struct pe_export_hdr *		exp_hdr,
	struct pe_export_sym  *		sym,
	enum pe_callback_reason		reason,
	void *				context)
{
	struct pe_symbol_name_ctx * ctx;

	if (reason != PE_CALLBACK_REASON_ITEM)
		return 1;

	ctx = (struct pe_symbol_name_ctx *)context;

	if (sym->addr == ctx->addr) {
		ctx->name = sym->name;
		return 0;
	} else
		return 1;
}


#ifdef __NT32
static char * pe_get_imported_symbol_info_32(
	const void *			sym_addr,
	void **				sym_image_addr,
	char **				sym_name,
	struct pe_ldr_tbl_entry **	ldr_tbl_entry)
{
	struct symbol {
		unsigned char	call;
		unsigned char	ds;
		unsigned char	sym_addr[4];
		unsigned char	padding[2];
	};

	char *				fn_name;
	struct pe_ldr_tbl_entry *	mod_info;
	void *				mod_base;
	uint32_t ***			sym_redirected_addr;
	struct symbol *			sym;

	fn_name  = 0;
	mod_info = 0;
	sym = (struct symbol *)sym_addr;

	if ((sym->call == 0xff) && (sym->ds == 0x25)) {
		sym_redirected_addr = (uint32_t ***)sym->sym_addr;

		if (sym_redirected_addr)
			mod_info = pe_get_symbol_module_info(**sym_redirected_addr);

		if (mod_info)
			mod_base = mod_info->dll_base;
		else
			mod_base = (void *)0;

		if (mod_base)
			fn_name = pe_get_symbol_name(
				mod_base,
				**sym_redirected_addr);
	}

	if (fn_name && ldr_tbl_entry)
		*ldr_tbl_entry = mod_info;

	return fn_name;
}
#endif


#ifdef __NT64
static char * pe_get_imported_symbol_info_64(
	const void *			sym_addr,
	void **				sym_image_addr,
	char **				sym_name,
	struct pe_ldr_tbl_entry **	ldr_tbl_entry)
{
	struct symbol {
		unsigned char	call;
		unsigned char	ds;
		unsigned char	sym_addr[4];
		unsigned char	padding[2];
	};

	char *				fn_name;
	struct pe_ldr_tbl_entry *	mod_info;
	void *				mod_base;
	uint32_t *			sym_offset;
	uint32_t			offset;
	struct symbol *			sym;

	fn_name  = 0;
	mod_info = 0;
	sym = (struct symbol *)sym_addr;

	if ((sym->call == 0xff) && (sym->ds == 0x25)) {
		sym_offset = (uint32_t *)sym->sym_addr;

		if (sym_offset) {
			offset		= *sym_offset;
			sym_addr	= *(void **)(offset + (uintptr_t)(++sym_offset));
			mod_info	= pe_get_symbol_module_info(sym_addr);
		}

		if (mod_info)
			mod_base = mod_info->dll_base;
		else
			mod_base = (void *)0;

		if (mod_base)
			fn_name = pe_get_symbol_name(mod_base,sym_addr);
	}

	if (fn_name) {
		if (ldr_tbl_entry)
			*ldr_tbl_entry = mod_info;

		if (sym_image_addr)
			*sym_image_addr = (void *)sym_addr;

		if (sym_name)
			*sym_name = fn_name;
	}

	return fn_name;
}
#endif
