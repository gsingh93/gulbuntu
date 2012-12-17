#include "functions.h"

int timer_ticks = 0; // Keeps track of how many ticks the system has been running for

/* Timer runs at 18.222 ticks per second. With this rate, the clock will overflow and wrap to zero every hour. */
void timer_handler(struct regs *r)
{
    timer_ticks++;

    /*if (timer_ticks % 18 == 0) // Every second; Every 18 ticks
    {
        putsa("One second has passed\n");
    }*/
}

void timer_install() // Installs timer to IRQ0
{
    irq_install_handler(0, timer_handler);
}

