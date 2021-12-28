#include "../drivers/ports.h"
#include "./types.h"
#include "./display.h"
#include "./colors.h"
#include "../drivers/screen.h"
#include "./string.h"
#include "./disk.h"
#include "../drivers/keyboard.h"

void keyboard(char* name, char* letter);

void start_kernel() {
    int offset = init_video();
    clear_screen(WHITE_ON_BEAUTY_BLUE);
    
    struct vec2 vec;
    vec.x = 40;
    vec.y = 7;
    vec.mTop = 8;
    vec.mLeft = 20;
    vec.saveOnStart = 1;

    draw_rec(vec, WHITE_ON_GRAY, WHITE_ON_BEAUTY_BLUE);

    set_cursor_offset(get_offset(vec.mLeft + 16, vec.mTop + 1));
    print(" Sonix OS", WHITE_ON_GRAY);
    set_cursor_offset(get_offset(vec.mLeft + 2, vec.mTop + 4));
    print(" Press Space to open shell", WHITE_ON_GRAY);
    set_cursor_offset(get_offset(vec.mLeft + 2, vec.mTop + 5));
    print(" Press Enter to shutdown computer", WHITE_ON_GRAY);
    set_cursor_offset(get_offset(MAX_COLS - lenstr(" by SolindekDev"), 24));
    print(" by SolindekDev", WHITE_ON_BEAUTY_BLUE);
    set_cursor_offset(get_offset(MAX_COLS - lenstr(" Sonix OS 1.0v"), 23));
    print(" Sonix OS 1.0v", WHITE_ON_BEAUTY_BLUE);
    set_cursor_offset(get_offset(0, 0));

    // set_cursor_offset(get_offset(MAX_COLS, MAX_ROWS));

    while(1) {
        u8 scancode;
        scancode = port_word_in(0x60);

        if (scancode > 57) return;
        if (scancode == 0x0E) {
            keyboard("Backspace", "Backspace");
            print("SSS", WHITE_ON_BLUE);
        } else if (scancode == 0x1C) {
            print("SS", WHITE_ON_BLUE);
            keyboard("Enter", "Enter");
        } else {
            keyboard("Test", "Test");
            print("S", WHITE_ON_BLUE);
        }
    }
}

void keyboard(char* name, char* letter) {
    print(name, WHITE_ON_BEAUTY_BLUE);
}
