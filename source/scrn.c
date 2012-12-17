#include "Includes/functions.h"

unsigned short *textmemptr; // Text pointer, pointer to video memory
int attrib = 0x0F; // Background/Foreground Attributes
int csr_x = 0, csr_y = 0; // Cursor Coordinates

void scroll(void) // Scrolls the screen
{
    unsigned blank, temp;

    blank = 0x20 | (attrib << 8); // Space(last 8 bits - 20) with black background color(first 8 bits - 0F)

    if(csr_y >= 25) // If the cursor goes below the last row, scroll up
    {
        temp = csr_y - 25 + 1; 
        memcpyw (textmemptr, textmemptr + temp * 80, (25 - temp) * 80 * 2); // Copies lines 1-24 and shifts them to lines 0-23 (copies both characters and attributes)

        memsetw (textmemptr + (25 - temp) * 80, blank, 80); // Makes last line blank
        csr_y = 25 - 1; // Sets cursor to second to last line
    }
}

void move_csr(void) // Updates the hardware cursor
{
    unsigned temp;

    temp = csr_y * 80 + csr_x; // Index = [(y * width) + x]

    outportb(0x3D4, 14); // Sets Index Register of cursor to register 14 (bits 8-15)
    outportb(0x3D5, temp >> 8); // Sets Data Register to last 8 bits of the index
    outportb(0x3D4, 15); // Sets Index Register of cursor to register 15 (bits 0-7)
    outportb(0x3D5, temp); // Sets Data Register to first 8 bits of the index
}

void cls() // Clears the screen
{
    unsigned blank;
    int i;

    blank = 0x20 | (attrib << 8); // Space

    for(i = 0; i < 25; i++) // Sets each byte to a space - Clears the screen
        memsetw (textmemptr + i * 80, blank, 80);

    csr_x = 0; // Set the virtual cursor back to the beginning
    csr_y = 0;
    move_csr(); // Update the hardware cursor
}

void putch(unsigned char c) // Puts a single character on the screen
{
    unsigned short *where;
    unsigned att = attrib << 8;
    unsigned blank = 0x20 | att;

    if(c == 0x08) // Moves cursor back one space for a backspace
    {
        if(csr_x != 0) csr_x--;
	memsetw (textmemptr + (csr_y * 80 + csr_x), blank, 1);
    }
    
    else if(c == 0x09) // Handles a tab
    {
        csr_x = (csr_x + 8) & ~(8 - 1); // Why do you need the '& ~(8 - 1)'?
    }

    else if(c == '\r') // Handles a carriage return, bringing the cursor to the beginning of the line
    {
        csr_x = 0;
    }

    else if(c == '\n') // Handles a new line
    {
        csr_x = 0;
        csr_y++;
    }

    else if(c >= ' ') // Handles all printable characters (characters greater than a space)
    {
        where = textmemptr + (csr_y * 80 + csr_x); // Pointer to video memory at current index
        *where = c | att; // Prints character and attribute
        csr_x++;
    }

    if(csr_x >= 80) // Go to a new line
    {
        csr_x = 0;
        csr_y++;
    }

    scroll(); // Scroll screen if needed
    move_csr(); // Update hardware cursor
}

void putsa(unsigned char *text) // Print a string
{
    int i;

    for (i = 0; i < strlen(text); i++)
    {
        putch(text[i]);
    }
}

/*
0  	BLACK   	8  	 DARK GREY
1 	BLUE 		9 	LIGHT BLUE
2 	GREEN 		10 	LIGHT GREEN
3 	CYAN 		11 	LIGHT CYAN
4 	RED 		12 	LIGHT RED
5 	MAGENTA 	13 	LIGHT MAGENTA
6 	BROWN 		14 	LIGHT BROWN
7 	LIGHT GREY 	15 	WHITE
*/

void settextcolor(unsigned char forecolor, unsigned char backcolor) // Sets background and foreground color
{
    attrib = (backcolor << 4) | (forecolor & 0x0F);
}

void init_video() // Sets the video memory pointer and clears the screen
{
    textmemptr = (unsigned short *)0xB8000; // This is the address of the text buffer in memory
    cls();
}
