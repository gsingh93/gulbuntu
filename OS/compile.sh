nasm -f elf -o "Object Files"/loader.o "Source Files"/loader.s
gcc -I "Source Files"/Includes -o "Object Files"/kernel.o -c "Source Files"/kernel.c -Wall -Wextra -nostdlib -nostartfiles -nodefaultlibs
gcc -I "Source Files"/Includes -o "Object Files"/functions.o -c "Source Files"/functions.c -Wall -Wextra -nostdlib -nostartfiles -nodefaultlibs
gcc -I "Source Files"/Includes -o "Object Files"/scrn.o -c "Source Files"/scrn.c -Wall -Wextra -nostdlib -nostartfiles -nodefaultlibs
gcc -I "Source Files"/Includes -o "Object Files"/gdt.o -c "Source Files"/gdt.c -Wall -Wextra -nostdlib -nostartfiles -nodefaultlibs
gcc -I "Source Files"/Includes -o "Object Files"/idt.o -c "Source Files"/idt.c -Wall -Wextra -nostdlib -nostartfiles -nodefaultlibs
gcc -I "Source Files"/Includes -o "Object Files"/isrs.o -c "Source Files"/isrs.c -Wall -Wextra -nostdlib -nostartfiles -nodefaultlibs
gcc -I "Source Files"/Includes -o "Object Files"/irqs.o -c "Source Files"/irqs.c -Wall -Wextra -nostdlib -nostartfiles -nodefaultlibs
ld -T "Source Files"/linker.ld -o "Final Files"/kernel.bin "Object Files"/loader.o "Object Files"/kernel.o "Object Files"/scrn.o "Object Files"/gdt.o "Object Files"/idt.o "Object Files"/functions.o "Object Files"/isrs.o "Object Files"/irqs.o
cd "Final Files"
cat stage1 stage2 pad kernel.bin > ../floppy.img
