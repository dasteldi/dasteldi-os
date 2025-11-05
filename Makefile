CC = gcc
ASM = nasm
CFLAGS = -m32 -ffreestanding -nostdlib -nostartfiles -nodefaultlibs \
         -fno-pic -fno-pie -fno-stack-protector -fno-builtin \
         -fno-exceptions -fno-asynchronous-unwind-tables \
         -fno-unwind-tables -fno-ident -I src/ \
         -mgeneral-regs-only -mno-sse -mno-mmx -mno-red-zone
ASMFLAGS = -f elf32
LD = ld
LDFLAGS = -m elf_i386 -T src/linker.ld -nostdlib -n -s

# Добавьте kprint.c в список исходных файлов
C_SOURCES = src/kernel.c src/kprint.c
ASM_SOURCES = src/multiboot_header.asm

# Объектные файлы
C_OBJECTS = $(C_SOURCES:src/%.c=build/%.o)
ASM_OBJECTS = $(ASM_SOURCES:src/%.asm=build/%.o)
OBJECTS = $(C_OBJECTS) $(ASM_OBJECTS)

all: kernel.bin

kernel.bin: $(OBJECTS)
	@echo "Linking kernel..."
	$(LD) $(LDFLAGS) -o $@ $^
	@echo "Kernel built: kernel.bin"

build/%.o: src/%.c
	@mkdir -p build
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

build/multiboot_header.o: src/multiboot_header.asm
	@mkdir -p build
	@echo "Assembling $<..."
	$(ASM) $(ASMFLAGS) -o $@ $<

clean:
	rm -rf build kernel.bin

.PHONY: all clean