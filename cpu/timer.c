#include "timer.h"
#include "isr.h"
#include "../kernel/ports.h"
#include "../kernel/util.h"

u32 tick = 0;

static void timer_callback(registers_t regs) {
    tick++;
    UNUSED(regs);
}

void init_timer(u32 freq) {
    register_interrupt_handler(IRQ0, timer_callback);

    u32 divisor = 1193180 / freq;
    u8 low  = (u8)(divisor & 0xFF);
    u8 high = (u8)( (divisor >> 8) & 0xFF);
    outb(0x43, 0x36); 
    outb(0x40, low);
    outb(0x40, high);
}