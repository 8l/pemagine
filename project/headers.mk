API_HEADERS = \
	$(PROJECT_DIR)/include/$(PACKAGE)/pemagine.h \
	$(PROJECT_DIR)/include/$(PACKAGE)/pe_api.h \
	$(PROJECT_DIR)/include/$(PACKAGE)/pe_consts.h \
	$(PROJECT_DIR)/include/$(PACKAGE)/pe_inline_asm.h \
	$(PROJECT_DIR)/include/$(PACKAGE)/pe_structs.h \

API_HEADERS_NT32 = \
	$(PROJECT_DIR)/include/$(PACKAGE)/bits/nt32/pe_inline_asm__gcc.h \
	$(PROJECT_DIR)/include/$(PACKAGE)/bits/nt32/pe_inline_asm__msvc.h \

API_HEADERS_NT64 = \
	$(PROJECT_DIR)/include/$(PACKAGE)/bits/nt64/pe_inline_asm__gcc.h \
	$(PROJECT_DIR)/include/$(PACKAGE)/bits/nt64/pe_inline_asm__msvc.h \

INTERNAL_HEADERS = \
	$(PROJECT_DIR)/src/internal/pe_impl.h

ALL_HEADERS = $(API_HEADERS) $(INTERNAL_HEADERS) $(API_HEADERS_NT32) $(API_HEADERS_NT64)
