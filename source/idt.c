#include "functions.h"

/*  * Bits 0...15:
          o Interrupt / Trap Gate: Offset address Bits 0-15 of IR
          o Task Gate: Not used. 
    * Bits 16...31:
          o Interrupt / Trap Gate: Segment Selector (Usually 0x10)
          o Task Gate: TSS Selector
    * Bits 31...35: Not used
    * Bits 36...38:
          o Interrupt / Trap Gate: Reserved. Must be 0.
          o Task Gate: Not used.
    * Bits 39...41:
          o Interrupt Gate: Of the format 0D110, where D determins size
                + 01110 - 32 bit descriptor
                + 00110 - 16 bit descriptor
          o Task Gate: Must be 00101
          o Trap Gate: Of the format 0D111, where D determines size
                + 01111 - 32 bit descriptor
                + 00111 - 16 bit descriptor
    * Bits 42...44: Descriptor Privedlge Level (DPL)
          o 00: Ring 0
          o 01: Ring 1
          o 10: Ring 2
          o 11: Ring 3
    * Bit 45: Segment is present (1: Present, 0:Not present)
    * Bits 46...62:
          o Interrupt / Trap Gate: Bits 16...31 of IR address
          o Task Gate: Not used */

/********* Flag Fields ********/   
/*7   6   5  4               0
/******************************/
/* P * DPL * Always 01110 (14)*/
/******************************/


struct idt_entry // An IDT entry
{
    unsigned short base_lo; // The low 16 bits of the entry base address
    unsigned short sel; // Kernel segment selector
    unsigned char always0; // Always 0
    unsigned char flags; // Flags defined above
    unsigned short base_hi; // Upper 16 bits of base address
} __attribute__((packed));

struct idt_ptr // Pointer to the IDT
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

struct idt_entry idt[256];
struct idt_ptr idtp;

extern void idt_load(); // Located in loader.s

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags) // Sets an IDT entry
{
    idt[num].base_lo = (base & 0xFFFF); // Sets first 16 bits of base address
    idt[num].base_hi = (base >> 16) & 0xFFFF; // Sets last 16 bits of base address

    idt[num].sel = sel; // Sets selector
    idt[num].always0 = 0; // This value is always 0
    idt[num].flags = flags; // Sets flags
}

void idt_install() // Installs IDT
{
    idtp.limit = (sizeof (struct idt_entry) * 256) - 1; // Sets IDT limit
    idtp.base = (int)&idt; // Sets IDT base address

    memseta((unsigned char*)&idt, 0, sizeof(struct idt_entry) * 256); // Clears the entire IDT by filling it with zeros

    /* Add any new ISRs to the IDT here using idt_set_gate */

    idt_load(); // Points the processor toward the new IDT
}

