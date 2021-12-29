#include "./ports.h"
#include "./screen.h"
#include "./util.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"
#include "./colors.h"
#include "./sys/memory_info.h"
#include "./sys/cpuid.h"
#include "./sys/power.h"
// #include "./sys/disk.h"

int input_menu_active = 1;
char* username = "user";

void init_video() {
    outb(0x3d4, 14); 
    int position = inb(0x3d5);
    position = position << 8; 

    outb(0x3d4, 15); 
    position += inb(0x3d5);
}

void start_kernel() {
    init_video();
    clear_screen();
    isr_install();

    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            print_char(' ', j, i, WHITE_ON_BEAUTY_BLUE);
        }
    }

    struct vec2 vec;
    vec.x = 40;
    vec.y = 7;
    vec.mTop = 7;
    vec.mLeft = 20;
    vec.saveOnStart = 1;
    draw_rec(vec, WHITE_ON_GRAY, WHITE_ON_BEAUTY_BLUE);

    set_cursor_offset(get_offset(vec.mLeft + 16, vec.mTop + 1));
    print_color(" Sonix OS", WHITE_ON_GRAY);
    set_cursor_offset(get_offset(vec.mLeft + 2, vec.mTop + 4));
    print_color(" Press space to open shell", WHITE_ON_GRAY);
    set_cursor_offset(get_offset(vec.mLeft + 2, vec.mTop + 5));
    print_color(" Press enter to shutdown", WHITE_ON_GRAY);
    set_cursor_offset(get_offset(MAX_COLS, MAX_ROWS));

    irq_install();
    keyboard_mode(MENU_MODE);
}

void write_prompt(char *username) {
    better_print_color(username, 0xf03);
    better_print_color("@", WHITE_ON_BLACK);
    better_print_color("root", 0xf04);
    better_print_color(":~$ ", WHITE_ON_BLACK);
}

void shell() {
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            print_char(' ', j, i, WHITE_ON_BLACK);
        }
    }
    set_cursor_offset(get_offset(0, 0));
    print_color("\n\n   Sonix OS v0.0.2", 0xf09);
    print(" - Copyright (C) 2021-2022\n\n");
    set_cursor_offset(get_offset(0, 3));
    write_prompt(username);
    keyboard_mode(SHELL_MODE);
}

void input_menu(int code) {
    if (input_menu_active == 1) {
        if (code == 0) {
            // ehhhh
            clear_screen();
            better_print("Halt the CPU...");
            asm volatile("hlt");
        } else {
            input_menu_active = 0;
            shell();
        }
    }
}

void input(char* input) {
    better_print(input);
    better_print("\n");
    write_prompt(username);
}