nasm -f elf -o "Object Files"/loader.o "Source Files"/loader.s
i586-elf-gcc -I "Source Files"/Includes -o "Object Files"/kernel.o -c "Source Files"/kernel.c -Wextra -nostdlib -nostartfiles -nodefaultlibs -fno-builtin
i586-elf-gcc -I "Source Files"/Includes -o "Object Files"/functions.o -c "Source Files"/functions.c -Wextra -nostdlib -nostartfiles -nodefaultlibs -fno-builtin
i586-elf-gcc -I "Source Files"/Includes -o "Object Files"/scrn.o -c "Source Files"/scrn.c  -Wextra -nostdlib -nostartfiles -nodefaultlibs -fno-builtin
i586-elf-gcc -I "Source Files"/Includes -o "Object Files"/gdt.o -c "Source Files"/gdt.c  -Wextra -nostdlib -nostartfiles -nodefaultlibs -Wno-pointer-to-int-cast -fno-builtin
i586-elf-gcc -I "Source Files"/Includes -o "Object Files"/idt.o -c "Source Files"/idt.c  -Wextra -nostdlib -nostartfiles -nodefaultlibs -Wno-pointer-to-int-cast -fno-builtin
i586-elf-gcc -I "Source Files"/Includes -o "Object Files"/isrs.o -c "Source Files"/isrs.c -nostdlib -nostartfiles -nodefaultlibs -Wno-pointer-to-int-cast -fno-builtin
i586-elf-gcc -I "Source Files"/Includes -o "Object Files"/irqs.o -c "Source Files"/irqs.c  -Wextra -nostdlib -nostartfiles -nodefaultlibs -Wno-pointer-to-int-cast -fno-builtin
i586-elf-gcc -I "Source Files"/Includes -o "Object Files"/timer.o -c "Source Files"/timer.c  -Wextra -nostdlib -nostartfiles -nodefaultlibs -fno-builtin
i586-elf-gcc -I "Source Files"/Includes -o "Object Files"/kb.o -c "Source Files"/kb.c  -Wextra -nostdlib -nostartfiles -nodefaultlibs -fno-builtin
i586-elf-ld -T "Source Files"/linker.ld -o "Final Files"/kernel.bin "Object Files"/loader.o "Object Files"/kernel.o "Object Files"/scrn.o "Object Files"/gdt.o "Object Files"/idt.o "Object Files"/functions.o "Object Files"/isrs.o "Object Files"/irqs.o "Object Files"/timer.o "Object Files"/kb.o
python pad.py
cd "Final Files"
cat stage1 stage2 pad kernel.bin pad2 > ../floppy.img
cp ../floppy.img ../cdcontents/floppy.img
