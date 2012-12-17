#include "functions.h"

/* Custom ISRs */
extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

void *irq_routines[16] = // Array of function pointers
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

void irq_install_handler(int irq, void (*handler)(struct regs *r)) // Installs custom IRQ handler for given IRQ
{
    irq_routines[irq] = handler;
}

void irq_uninstall_handler(int irq) // Clears the IRQ handler for the given IRQ
{
    irq_routines[irq] = 0;
}

/* IRQs 0 to 7 are usually mapped to entries 8 to 15 in the PICs. In protected mode, these entries are already used in the IDT. We send commands to the PICs in
*  order to make IRQ0 to 15 be remapped to IDT entries 32 to 47 */
void irq_remap(void) // ICWs described at http://heim.ifi.uio.no/~stanisls/helppc/8259.html
{
    outportb(0x20, 0x11); // Writes ICW1 (Initialization Command Word) to PIC
    outportb(0xA0, 0x11); // Writes ICW1 to PIC; ICW1 tells if ICW4 is coming and if the two PICs commmunicate with each other
    outportb(0x21, 0x20); // Remap PIC1 to 0x20 (32); ICW2 is the remapping location
    outportb(0xA1, 0x28); // Remap PIC2 to 0x28 (40)
    outportb(0x21, 0x04); // ICW3 tells which IRQ to use for communication between the PICs; IRQ 2 is used
    outportb(0xA1, 0x02); // IRQ 2 is used
    outportb(0x21, 0x01); // Write ICW4 to PIC1; 80x86 architecture
    outportb(0xA1, 0x01); // Write ICW4 to PIC2
    outportb(0x21, 0x0); // Enable all IRQs on PIC1
    outportb(0xA1, 0x0); // Enable all IRQs on PIC2
}

void irq_install() // Installs IRQ entries in the IDT
{
    irq_remap(); // Remaps IRQ entries before installing them

    idt_set_gate(32, (unsigned)irq0, 0x08, 0x8E);
    idt_set_gate(33, (unsigned)irq1, 0x08, 0x8E);
    idt_set_gate(34, (unsigned)irq2, 0x08, 0x8E);
    idt_set_gate(35, (unsigned)irq3, 0x08, 0x8E);
    idt_set_gate(36, (unsigned)irq4, 0x08, 0x8E);
    idt_set_gate(37, (unsigned)irq5, 0x08, 0x8E);
    idt_set_gate(38, (unsigned)irq6, 0x08, 0x8E);
    idt_set_gate(39, (unsigned)irq7, 0x08, 0x8E);

    idt_set_gate(40, (unsigned)irq8, 0x08, 0x8E);
    idt_set_gate(41, (unsigned)irq9, 0x08, 0x8E);
    idt_set_gate(42, (unsigned)irq10, 0x08, 0x8E);
    idt_set_gate(43, (unsigned)irq11, 0x08, 0x8E);
    idt_set_gate(44, (unsigned)irq12, 0x08, 0x8E);
    idt_set_gate(45, (unsigned)irq13, 0x08, 0x8E);
    idt_set_gate(46, (unsigned)irq14, 0x08, 0x8E);
    idt_set_gate(47, (unsigned)irq15, 0x08, 0x8E);
}

/* The IRQ Controllers need to be told when you are done using them, so you need to send them an "End of Interrupt" command (0x20) to both 8259 chips
   The first exists at 0x20, the second exists at 0xA0. If an EOI is not sent, another IRQ can not run. */
void irq_handler(struct regs *r)
{
    void (*handler)(struct regs *r); // A blank function pointer

    handler = irq_routines[r->int_no - 32]; // Find out if the IRQ has a custom handler
    if (handler) // Handle interrupt
    {
        handler(r);
    }

    if (r->int_no >= 40) // If an IDT entry greater than 40 (IRQs 8-15) was called, send an EOI (End Of Interrupt) command to the second (slave) PIC
    {
        outportb(0xA0, 0x20);
    }

    outportb(0x20, 0x20); // Always send EOI to first (master) PIC (Programmable Interrupt Controller)
}
