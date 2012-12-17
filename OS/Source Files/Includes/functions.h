#ifndef FUNCTIONS_H
#define FUNCTIONS_H

/* Main */

unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count);
unsigned short *memcpyw(unsigned short *dest, unsigned short *src, int count);
unsigned char *memseta(unsigned char *dest, unsigned char val, int count);
unsigned short *memsetw(unsigned short *dest, unsigned short val, int count);
int strlen(unsigned char *str);
int command_handler(unsigned char *command);
unsigned char inportb (unsigned short _port);
void outportb (unsigned short _port, unsigned char _data);

/* Screen */

void cls();
void putch(unsigned char c);
void putsa(unsigned char *str);
void settextcolor(unsigned char forecolor, unsigned char backcolor);
void init_video();

/* GDT */

void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);
void gdt_install();

/* IDT */

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
void idt_install();

/* ISRs */

void isrs_install();

/* This defines what the stack looks like after an ISR was running */
struct regs
{
    unsigned int gs, fs, es, ds;      /* pushed the segs last */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    unsigned int int_no, err_code;    /* our 'push byte #' and ecodes do this */
    unsigned int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */ 
};

/* IRQs */

void irq_install();
void irq_install_handler();
void irq_uninstall_handler();

/* Timer */

void timer_install();

/* Keyboard */

void keyboard_install();

#endif
