#include "./ports.h"
#include "./screen.h"
#include "./util.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"
#include "./colors.h"
#include "./sys/memory_info.h"
#include "./sys/cpuid.h"
#include "./sys/power.h"
#include "./sys/disk.h"

#define OS_NAME "SonixOS"
#define OS_VERSION "1.0.0"
#define OS_VIDEO_RESOLUTION "640x200"
#define OS_DEFUALT_USER "user"

int input_menu_active = 1;

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

    /*
        OLD MENU CODE
    */
    // for (int i = 0; i < 25; i++) {
    //     for (int j = 0; j < MAX_COLS; j++) {
    //         print_char(' ', j, i, WHITE_ON_BEAUTY_BLUE);
    //     }
    // }

    // struct vec2 vec;
    // vec.x = 40;
    // vec.y = 7;
    // vec.mTop = 7;
    // vec.mLeft = 20;
    // vec.saveOnStart = 1;
    // draw_rec(vec, WHITE_ON_GRAY, WHITE_ON_BEAUTY_BLUE);

    // set_cursor_offset(get_offset(vec.mLeft + 16, vec.mTop + 1));
    // print_color(" Sonix OS", WHITE_ON_GRAY);
    // set_cursor_offset(get_offset(vec.mLeft + 2, vec.mTop + 4));
    // print_color(" Press space to open shell", WHITE_ON_GRAY);
    // set_cursor_offset(get_offset(vec.mLeft + 2, vec.mTop + 5));
    // print_color(" Press enter to shutdown", WHITE_ON_GRAY);
    // set_cursor_offset(get_offset(MAX_COLS, MAX_ROWS));

    // irq_install();
    // keyboard_mode(MENU_MODE);

    irq_install();
    keyboard_mode(SHELL_MODE);
    shell();
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
    write_prompt("user");
    keyboard_mode(SHELL_MODE);
}

void input_menu(int code) {
    // if (input_menu_active == 1) {
    //     if (code == 0) {
    //         input_menu_active = 0;
    //         shutdown();
    //     } else {
    //         input_menu_active = 0;
    //         shell();
    //     }
    // }
}

void input(char* input) {
    if (strcmp(input, "shutdown")==1) {
        shutdown();
    } else if (strcmp(input, "clear")==1){
        clear_screen();
        better_print("\n");
    } else if (strcmp(input, "")==1 || strcmp(input, " ")==1){
    } else if (strcmp(input, "disks")) {
        floppy_disk_detect();
        better_print("\n");
    } else if (strcmp(input, "reboot")) {
        reboot();
        better_print("\n");
    } else if (strcmp(input, "help")) {
        better_print("help      - Show list of commands\n");
        better_print("disks     - Show list of disks\n");
        better_print("neofetch  - Show information about everything \n");
        better_print("reboot    - Reboot the computer\n");
        better_print("shutdown  - Shutdown the computer\n");
    } else if (strcmp(input, "neofetch")) {
//         better_print_color("\n:'######:::'#######::'##::: ##:'####:'##::::'##:\n\
// '##... ##:'##.... ##: ###:: ##:. ##::. ##::'##::\n\
//  ##:::..:: ##:::: ##: ####: ##:: ##:::. ##'##:::\n\
// . ######:: ##:::: ##: ## ## ##:: ##::::. ###::::\n\
// :..... ##: ##:::: ##: ##. ####:: ##:::: ## ##:::\n\
// '##::: ##: ##:::: ##: ##:. ###:: ##::: ##:. ##::\n\
// . ######::. #######:: ##::. ##:'####: ##:::. ##:\n\
// :......::::.......:::..::::..::....::..:::::..::\n", 0xf03);
        better_print_color("\n  /$$$$$$                      /$$\n\          
 /$$__  $$                    |__/\n\          
| $$  \\__/  /$$$$$$  /$$$$$$$  /$$ /$$   /$$\n\
|  $$$$$$  /$$__  $$| $$__  $$| $$|  $$ /$$/\n\
 \\____  $$| $$  \\ $$| $$  \\ $$| $$ \\  $$$$/\n\ 
 /$$  \\ $$| $$  | $$| $$  | $$| $$  >$$  $$\n\ 
|  $$$$$$/|  $$$$$$/| $$  | $$| $$ /$$/\\  $$\n\
 \\______/  \\______/ |__/  |__/|__/|__/  \\__/\n", 0xf03);
        better_print("\n-------\n");
        better_print_color("\nOS: ", 0xf03);
        better_print("SonixOS\n");
        better_print_color("Kernel: ", 0xf03);
        better_print("1.0.0\n");
        better_print_color("Shell: ", 0xf03);
        better_print("Sash\n");
        better_print_color("Username: ", 0xf03);
        better_print("user");
        better_print("\n");
        better_print_color("Total memory: ", 0xf03);
        better_print((char)total_memory());
        better_print("\n");
        better_print_color("Resoultion: ", 0xf03);
        better_print("640x200\n\n");
        for (int i = 0; i < 6; i++) {
            switch (i) {
                case 0:
                    better_print_color("   ", BLACK);
                    break;
                case 1:
                    better_print_color("   ", WHITE);
                    break;
                case 2:
                    better_print_color("   ", PINK);
                    break;
                case 3:
                    better_print_color("   ", GREEN);
                    break;
                case 4:
                    better_print_color("   ", RED);
                    break;
                case 5:
                    better_print_color("   ", AQUA);
                    break;
            }
        }
        better_print("\n\n");
    } else {
        better_print("sash: ");
        better_print(input);
        better_print(": command not found");
        better_print("\n");
    } 
    write_prompt("user");
}