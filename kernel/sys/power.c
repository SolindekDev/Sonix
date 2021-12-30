#include "../ports.h"
#include "../screen.h"

void shutdown() {
    clear_screen();
    better_print("Shutting down the computer...");
    outw((unsigned short)0xB004, (unsigned char)0x00002000);
}

void reboot(){
    int good = 0x02;
    while (good & 0x02)
        good = inb(0x64);
    outb(0x64, 0xFE);
    asm volatile("hlt");
}