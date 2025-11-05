CC = gcc
ASM = nasm
CFLAGS = -m32 -ffreestanding -nostdlib -I src/ -fno-builtin
ASMFLAGS = -f elf32
LD = ld
LDFLAGS = -m elf_i386 -T src/linker.ld -nostdlib -n

# Добавляем shell.c
C_SOURCES = src/kernel.c src/kprint.c src/keyboard.c src/shell.c
ASM_SOURCES = src/multiboot_header.asm

C_OBJECTS = $(C_SOURCES:src/%.c=build/%.o)
ASM_OBJECTS = $(ASM_SOURCES:src/%.asm=build/%.o)
OBJECTS = $(C_OBJECTS) $(ASM_OBJECTS)

all: os.iso

os.iso: kernel.bin
	mkdir -p iso/boot/grub
	cp kernel.bin iso/boot/
	echo 'menuentry "Dasteldi OS - 1.2" { multiboot /boot/kernel.bin; boot }' > iso/boot/grub/grub.cfg
	grub-mkrescue -o dasteldi.iso iso

kernel.bin: $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^

build/%.o: src/%.c
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

build/%.o: src/%.asm
	@mkdir -p build
	$(ASM) $(ASMFLAGS) -o $@ $<

clean:
	rm -rf build kernel.bin os.iso isodir

run: os.iso
	qemu-system-x86_64 -cdrom os.iso

.PHONY: all clean run