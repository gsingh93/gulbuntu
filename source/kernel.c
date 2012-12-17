#include "functions.h"

void kmain( void* mbd, unsigned int magic )
{
	/* Installations */
	gdt_install();
	idt_install();
	isrs_install();
	irq_install();
	timer_install();
	keyboard_install();
	init_video();
	
	__asm__ __volatile__ ("sti"); // Disable interrupts

	settextcolor(0x0F, 0x00);

	unsigned char string[] = "Welcome to Gulinux 0.01. For a list of commands, type help.\n";

	putsa(string);
	for(;;);
}
