#ifndef IDT_H
    #define IDT_H

    #include "types.h"

    #define KERNEL_CS 0x08

    typedef struct {
        u16 low_offset; 
        u16 sel; 
        u8 always0;
        u8 flags; 
        u16 high_offset; 
    } __attribute__((packed)) idt_gate_t ;

    typedef struct {
        u16 limit;
        u32 base;
    } __attribute__((packed)) idt_register_t;

    #define IDT_ENTRIES 256
    idt_gate_t idt[IDT_ENTRIES];
    idt_register_t idt_reg;

    void set_idt_gate(int n, u32 handler);
    void set_idt();

#endif