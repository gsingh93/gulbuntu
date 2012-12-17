
CC := gcc
CFLAGS := -Iinclude -m32 -Wextra -nostdlib -nostartfiles -nodefaultlibs -fno-builtin -Wno-pointer-to-int-cast
LDFLAGS := -melf_i386

all:
	nasm -f elf -o obj/loader.o source/loader.s
	$(CC) -o obj/kernel.o -c source/kernel.c $(CFLAGS)
	$(CC) -o obj/functions.o -c source/functions.c $(CFLAGS)
	$(CC) -o obj/scrn.o -c source/scrn.c $(CFLAGS)
	$(CC) -o obj/gdt.o -c source/gdt.c $(CFLAGS)
	$(CC) -o obj/idt.o -c source/idt.c $(CFLAGS)
	$(CC) -o obj/isrs.o -c source/isrs.c $(CFLAGS)
	$(CC) -o obj/irqs.o -c source/irqs.c  $(CFLAGS)
	$(CC) -o obj/timer.o -c source/timer.c $(CFLAGS)
	$(CC) -o obj/kb.o -c source/kb.c $(CFLAGS)
	$(LD) $(LDFLAGS) -T source/linker.ld -o intermediate/kernel.bin obj/loader.o obj/kernel.o obj/scrn.o obj/gdt.o obj/idt.o obj/functions.o obj/isrs.o obj/irqs.o obj/timer.o obj/kb.o

clean:
	rm -rf obj/*.o