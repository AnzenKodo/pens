OUTPUT_DIR=build
MAIN_FILE=main
C_COMP=~/Apps/bin/tcc
# C_COMP=gcc

build_main:
	@mkdir -p $(@D)
	nasm -f elf64 -o $(OUTPUT_DIR)/$(MAIN_FILE).o $(MAIN_FILE).asm
	ld $(OUTPUT_DIR)/$(MAIN_FILE).o -o $(OUTPUT_DIR)/$(MAIN_FILE) -e main
	$(OUTPUT_DIR)/$(MAIN_FILE)

build_c:
	$(C_COMP) test.c -o $(OUTPUT_DIR)/test
	objdump -d $(OUTPUT_DIR)/test -M intel > test.asm
	cat test.asm
