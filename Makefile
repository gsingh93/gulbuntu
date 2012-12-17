
CXX=gcc -m32

all:
	nasm -f elf -o obj/loader.o source/loader.s
	$(CXX) -I source/Includes -o obj/kernel.o -c source/kernel.c -Wextra -nostdlib -nostartfiles -nodefaultlibs -fno-builtin
	$(CXX) -I source/Includes -o obj/functions.o -c source/functions.c -Wextra -nostdlib -nostartfiles -nodefaultlibs -fno-builtin
	$(CXX) -I source/Includes -o obj/scrn.o -c source/scrn.c  -Wextra -nostdlib -nostartfiles -nodefaultlibs -fno-builtin
	$(CXX) -I source/Includes -o obj/gdt.o -c source/gdt.c  -Wextra -nostdlib -nostartfiles -nodefaultlibs -Wno-pointer-to-int-cast -fno-builtin
	$(CXX) -I source/Includes -o obj/idt.o -c source/idt.c  -Wextra -nostdlib -nostartfiles -nodefaultlibs -Wno-pointer-to-int-cast -fno-builtin
	$(CXX) -I source/Includes -o obj/isrs.o -c source/isrs.c -nostdlib -nostartfiles -nodefaultlibs -Wno-pointer-to-int-cast -fno-builtin
	$(CXX) -I source/Includes -o obj/irqs.o -c source/irqs.c  -Wextra -nostdlib -nostartfiles -nodefaultlibs -Wno-pointer-to-int-cast -fno-builtin
	$(CXX) -I source/Includes -o obj/timer.o -c source/timer.c  -Wextra -nostdlib -nostartfiles -nodefaultlibs -fno-builtin
	$(CXX) -I source/Includes -o obj/kb.o -c source/kb.c  -Wextra -nostdlib -nostartfiles -nodefaultlibs -fno-builtin
	ld -melf_i386 -T source/linker.ld -o "Final Files"/kernel.bin obj/loader.o obj/kernel.o obj/scrn.o obj/gdt.o obj/idt.o obj/functions.o obj/isrs.o obj/irqs.o obj/timer.o obj/kb.o


	#python pad.py
	#cd "Final Files"
	#cat stage1 stage2 pad kernel.bin pad2 > ../floppy.img
	#cp ../floppy.img ../cdcontents/floppy.img
