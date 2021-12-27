#include "../drivers/ports.h"
#include "./types.h"
#include "./display.h"
#include "./colors.h"
#include "../drivers/screen.h"
#include "./string.h"

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
    set_cursor_offset(get_offset(MAX_ROWS, MAX_COLS));
    // while(1) {
    //     const char *sc_name[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6", 
    //         "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E", 
    //         "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl", 
    //         "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", 
    //         "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".", 
    //         "/", "RShift", "Keypad *", "LAlt", "Spacebar"};
    //     const char sc_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    //         '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 
    //         'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G', 
    //         'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V', 
    //         'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};
    //     u8 code = port_byte_in(0x60);

    //     if (code > 57) return;

    //     if (code == 1) {
    //         set_cursor_offset(get_offset(0, 0));
    //         print("Si", WHITE_ON_BEAUTY_BLUE);
    //     }
    // }
}
