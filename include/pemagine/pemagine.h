#ifndef PEMAGINE_H
#define PEMAGINE_H

#include "pe_api.h"
#include "pe_consts.h"
#include "pe_structs.h"

#ifdef __cplusplus
extern "C" {
#endif

enum pe_callback_reason {
	PE_CALLBACK_REASON_INIT		= 0x00,
	PE_CALLBACK_REASON_ITEM		= 0x01,
	PE_CALLBACK_REASON_INFO		= 0x02,
	PE_CALLBACK_REASON_QUERY	= 0x04,
	PE_CALLBACK_REASON_DONE		= 0x1000,
	PE_CALLBACK_REASON_ERROR	= (-1)
};


/* library specific structures */
struct pe_export_sym {
	uint32_t *	ordinal_base;
	uint16_t *	ordinal;
	void *		addr;
	void *		forwarder_rva;
	char *		name;
	long		status;
};


struct pe_unicode_str {
	uint16_t	strlen;
	uint16_t	maxlen;
	uint16_t *	buffer;
};


struct pe_list_entry {
	struct pe_list_entry *	flink;
	struct pe_list_entry *	blink;
};


struct pe_client_id {
	uint32_t	process_id;
	uint32_t	thread_id;
};


struct pe_stack_heap_info {
	size_t size_of_stack_reserve;
	size_t size_of_stack_commit;
	size_t size_of_heap_reserve;
	size_t size_of_heap_commit;
};


struct pe_peb_ldr_data {
	uint32_t		length;
	uint32_t		initialized;
	void *			ss_handle;
	struct pe_list_entry	in_load_order_module_list;
	struct pe_list_entry	in_memory_order_module_list;
	struct pe_list_entry	in_init_order_module_list;
};


struct pe_ldr_tbl_entry {
	struct pe_list_entry	in_load_order_links;
	struct pe_list_entry	in_memory_order_links;
	struct pe_list_entry	in_init_order_links;
	void *			dll_base;
	void *			entry_point;

	union {
		uint32_t	size_of_image;
		unsigned char	size_of_image_padding[sizeof(uintptr_t)];
	};

	struct pe_unicode_str	full_dll_name;
	struct pe_unicode_str	base_dll_name;
	uint32_t		flags;
	uint16_t		load_count;
	uint16_t		tls_index;

	union {
		struct pe_list_entry	hash_links;
		struct {
			void *		section_pointer;
			uint32_t	check_sum;
		};
	};

	union {
		void *		loaded_imports;
		uint32_t	time_date_stamp;
	};

	void *			entry_point_activation_context;
	void *			patch_information;
	struct pe_list_entry	forwarder_links;
	struct pe_list_entry	service_tag_links;
	struct pe_list_entry	static_links;
	void *			context_information;
	uintptr_t		original_base;
	int64_t			load_time;
};



/*  static inlined functions */
static __inline__ void *	pe_get_teb_address(void);
static __inline__ void *	pe_get_peb_address(void);
static __inline__ void *	pe_get_peb_address_alt(void);
static __inline__ void *	pe_get_peb_ldr_data_address(void);
static __inline__ void *	pe_get_peb_ldr_data_address_alt(void);
static __inline__ uint32_t	pe_get_current_process_id(void);
static __inline__ uint32_t	pe_get_current_thread_id(void);
static __inline__ uint32_t	pe_get_current_session_id(void);
static __inline__ void *	pe_va_from_rva(const void * base, intptr_t offset);

#include "pe_inline_asm.h"


/**
 * user callback function responses
 *
 * positive: continue enumeration.
 * zero:     exit enumeration (ok).
 * negative: exit enumeration (error).
**/

/* callback signatures */
typedef int pe_enum_modules_callback(
	struct pe_ldr_tbl_entry *	image_ldr_tbl_entry,
	enum pe_callback_reason		reason,
	void *				context);

typedef int pe_enum_image_exports_callback(
	const void *			base,
	struct pe_export_hdr *		exp_hdr,
	struct pe_export_sym  *		sym,
	enum pe_callback_reason		reason,
	void *				context);

typedef int pe_enum_image_import_hdrs_callback(
	const void *			base,
	struct pe_import_hdr *		imp_hdr,
	enum pe_callback_reason		reason,
	void *				context);

/* library functions */
pe_api struct pe_image_dos_hdr *pe_get_image_dos_hdr_addr	(const void * base);
pe_api struct pe_coff_file_hdr *pe_get_image_coff_hdr_addr	(const void * base);
pe_api union  pe_opt_hdr *	pe_get_image_opt_hdr_addr	(const void * base);
pe_api struct pe_data_dirs *	pe_get_image_data_dirs_addr	(const void * base);
pe_api struct pe_export_hdr *	pe_get_image_export_hdr_addr	(const void * base, uint32_t * sec_size);
pe_api struct pe_import_hdr *	pe_get_image_import_dir_addr	(const void * base, uint32_t * sec_size);
pe_api void *			pe_get_image_special_hdr_addr	(const void * base, uint32_t ordinal, uint32_t * sec_size);
pe_api void *			pe_get_image_entry_point_addr	(const void * base);
pe_api int			pe_get_image_stack_heap_info	(const void * base, struct pe_stack_heap_info *);

pe_api void *			pe_get_procedure_address	(const void * base, const char * name);
pe_api int			pe_get_export_symbol_info	(const void * base, const char * name, struct pe_export_sym *);
pe_api int			pe_enum_image_exports		(const void * base,
								 pe_enum_image_exports_callback *,
								 struct pe_export_sym *,
								 void * ctx);

pe_api int			pe_enum_image_import_hdrs	(const void * base,
								 pe_enum_image_import_hdrs_callback *,
								 void * ctx);

pe_api char *			pe_get_symbol_name		(const void * base, const void * sym_addr);
pe_api struct pe_ldr_tbl_entry *pe_get_symbol_module_info	(const void * sym_addr);
pe_api char *			pe_get_import_symbol_info	(const void * sym_addr,
								 void ** sym_image_addr,
								 char ** sym_name,
								 struct pe_ldr_tbl_entry ** ldr_tbl_entry);

pe_api int			pe_enum_modules_in_load_order	(pe_enum_modules_callback *, void * ctx);
pe_api int			pe_enum_modules_in_memory_order	(pe_enum_modules_callback *, void * ctx);
pe_api int			pe_enum_modules_in_init_order	(pe_enum_modules_callback *, void * ctx);
pe_api void *			pe_get_module_handle		(const wchar16_t * name);
pe_api void *			pe_get_first_module_handle	(void);
pe_api void *			pe_get_ntdll_module_handle	(void);
pe_api void *			pe_get_kernel32_module_handle	(void);


#ifdef __cplusplus
}
#endif

#endif
