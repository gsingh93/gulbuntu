/*  * Bits 56-63: Bits 24-32 of the base address
    * Bit 55: Granularity
          o 0: None
          o 1: Limit gets multiplied by 4K
    * Bit 54: Segment type
          o 0: 16 bit
          o 1: 32 bit
    * Bit 53: Reserved-Should be zero
    * Bits 52: Reserved for OS use
    * Bits 48-51: Bits 16-19 of the segment limit
    * Bit 47 Segment is in memory (Used with Virtual Memory)
    * Bits 45-46: Descriptor Privilege Level
          o 0: (Ring 0) Highest
          o 3: (Ring 3) Lowest
    * Bit 44: Descriptor Bit
          o 0: System Descriptor
          o 1: Code or Data Descriptor
    * Bits 41-43: Descriptor Type
          o Bit 43: Executable segment
                + 0: Data Segment
                + 1: Code Segment
          o Bit 42: Expansion direction (Data segments), conforming (Code Segments)
          o Bit 41: Readable and Writable
                + 0: Read only (Data Segments); Execute only (Code Segments)
                + 1: Read and write (Data Segments); Read and Execute (Code Segments)
    * Bit 40: Access bit (Used with Virtual Memory)
    * Bits 16-39: Bits 0-23 of the Base Address
    * Bits 0-15: Bits 0-15 of the Segment Limit */

/**** Access Fields ***/   
/*7   6    5 4  3     0
/**********************/
/* P * DPL * DT * Type*/
/**********************/

// P - Segment is present (1 = Yes)
// DPL - Privilege Ring (0 = System Use, 3 = Application Use)
// DT - Descriptor Type (0 = System Descriptor, 1 = Code or Data Descriptor)
// Type - Code segment, Data segment, etc...

/* Granularity Fields */
/*7   6    5 4  3     0
/**********************************/
/* G * D * O * A* Seg. Len. 19:16 */
/**********************************/

// G - Granularity (0 = 1byte, 1 = 4kbyte)
// D - Operand Size (0 = 16bit, 1 = 32-bit)
// 0 - Always 0
// A - Available for System (Always set to 0) 

struct gdt_entry // Entry in the GDT
{
    unsigned short limit_low; // GDT limit bits 0-15 is in the low two bytes of the GDT
    unsigned short base_low; // Bits 0-15 of the base address of the segment
    unsigned char base_middle; // Bits 16-23 of the base address of the segment
    unsigned char access; // Access privelages defined above
    unsigned char granularity; // Granularity defined above
    unsigned char base_high; // Bits 24-32 of the base address of the segment
} __attribute__((packed)); // Prevents compiler "optimization" by packing

struct gdt_ptr // Pointer to GDT
{
    unsigned short limit; // Size of GDT minus 1
    unsigned int base; // Starting address of GDT
} __attribute__((packed)); // Prevents compiler "optimization" by packing

struct gdt_entry gdt[3];
struct gdt_ptr gp;

extern void gdt_flush(); // Reloads segment registers; found in loader.s

void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran) // Sets a descriptor in the GDT
{
    gdt[num].base_low = (base & 0xFFFF); // Sets first 16 bits of base address
    gdt[num].base_middle = (base >> 16) & 0xFF; // Sets next 8 bits of base address
    gdt[num].base_high = (base >> 24) & 0xFF; // Sets next 8 bits of base address

    gdt[num].limit_low = (limit & 0xFFFF); // Sets first 16 bits of limit
    gdt[num].granularity = ((limit >> 16) & 0x0F); // Sets the first bits of the granularity to bits 16-19 of the limit

    gdt[num].granularity |= (gran & 0xF0); // Sets high four bits of the granularity
    gdt[num].access = access; // Sets access flags
}

void gdt_install()
{
    gp.limit = (sizeof(struct gdt_entry) * 3) - 1; // Limit of GDT
    gp.base = (int)&gdt; // Base address of GDT

    gdt_set_gate(0, 0, 0, 0, 0); // GDT must start with a NULL descriptor

    /* Base Address = 0, limit = 4GB, Granularity = 4KB, 32 bit opcodes, type = Code Segment */
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // 0x9A = 10011010, 0xCF = 11001111 
    /* Base Address = 0, limit = 4GB, Granularity = 4KB, 32 bit opcodes, type = Data Segment */
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // 0x92 = 10010010, 0xCF = 11001111

    gdt_flush(); // Gets rid of the old GDT and installs the changes
}

