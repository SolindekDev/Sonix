#include "./ports.h"
#include "./screen.h"
#include "./util.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"
#include "./colors.h"

void init_video() {
    outb(0x3d4, 14); 
    int position = inb(0x3d5);
    position = position << 8; 

    outb(0x3d4, 15); 
    position += inb(0x3d5);
}

void input(char input) {
    print(input);
}

void start_kernel() {
    init_video();
    clear_screen();
    irq_install();
    isr_install();

    print("\n\nSonix OS\n\n");
}