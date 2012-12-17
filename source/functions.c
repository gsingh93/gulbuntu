#include "functions.h"

#define SCRWIDTH 200 // Need to figure out these sizes...
#define SCRHEIGHT 1200

unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count) // Copy bytes from source string to destination string
{
	int i;
	for(i = 0; i < count; i++)
		*dest++ = *src++;
	return dest;
}

unsigned short *memcpyw(unsigned short *dest, unsigned short *src, int count) // Copy bytes from source string to destination string
{
	int i;
	for(i = 0; i < count; i++)
		*dest++ = *src++;
	return dest;
}


unsigned char *memseta(unsigned char *dest, unsigned char val, int count) // Set bytes of destination string to value
{
	int i;
	for(i = 0; i < count; i++)
		*dest++ = val;
	return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, int count) // Set bytes of destination string to value
{
	int i;
	for(i = 0; i < count; i++)
		*dest++ = val;
	return dest;
}

int strcmpa(unsigned char *str, unsigned char *txt, int count) // Compare two strings, return 1 if they are the same
{
	int i, same;
	for(i = 0; i < count; i++)
	{
		if (str[i] == txt[i])
			same = 1;
		else
		{
			same = 0;
			return same;
		}
	}
	
	return same;
	
}

int strlen(unsigned char *str) // Get string length
{
	int i;
	for(i = 0; *str != 0; str++)
		i++;
	return i;
}

int command_handler(unsigned char *command) // Handle commands
{
	int len = strlen(command);
	unsigned char help[] =	"cls - Clear the screen\n"
				"help - Displays possible commands\n";
	if (strcmpa(command, (unsigned char*)"help", len))
		putsa(help);
	else if (strcmpa(command, (unsigned char*)"cls", len))
		cls();
	else
		putsa((unsigned char*)"Command not found");
	return 0;
}

unsigned char inportb (unsigned short _port) // Read from port
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outportb (unsigned short _port, unsigned char _data) // Write to port
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

