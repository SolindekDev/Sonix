#include "./ports.h"
#include "../cpu/isr.h"
#include "./screen.h"
#include "../cpu/idt.h"
#include "./keyboard.h"
#include "./util.h"
#include "./colors.h"

int shift_pressed = 0;
int capslock_pressed = 0;

#define BACKSPACE 0x0E
#define ENTER 0x1C
#define ESC 0x1
#define ONE 0x2
#define TWO 0x3
#define THREE 0x4
#define FOUR 0x5
#define FIVE 0x6
#define SIX 0x7
#define SEVEN 0x8
#define EIGHT 0x9
#define NINE 0x0A
#define ZERO 0x0B

#define SC_MAX 57

char* buffer_keys;
int letters;

void keyboard_callback(registers_t regs) {
    u8 scancode = inb(0x60);
    
    if (scancode > SC_MAX) return;
    if (scancode == BACKSPACE) {
        if (letters > 0) {
            int cursorPos = get_cursor_offset();
            int row = get_offset_row(cursorPos);
            int col = get_offset_col(cursorPos);

            print_char(' ', col-1, row, WHITE_ON_BLACK);
            int cursorPos1 = get_cursor_offset()-2;
            set_cursor_offset(cursorPos1);
            letters--;
        } else {
            return;
        }
    } else if (scancode == ENTER) {
        print("\n\n");
    } else {
        letters++;
        switch(scancode) {
            /*
                NUMBERS
            */
            case ONE:
                print_char('1', -1, -1, WHITE_ON_BLACK);
                break;
            case TWO:
                print_char('2', -1, -1, WHITE_ON_BLACK);
                break;
            case THREE:
                print_char('3', -1, -1, WHITE_ON_BLACK);
                break;
            case FOUR:
                print_char('4', -1, -1, WHITE_ON_BLACK);
                break;
            case FIVE:
                print_char('5', -1, -1, WHITE_ON_BLACK);
                break;
            case SIX:
                print_char('6', -1, -1, WHITE_ON_BLACK);
                break;
            case SEVEN:
                print_char('7', -1, -1, WHITE_ON_BLACK);
                break;
            case EIGHT:
                print_char('8', -1, -1, WHITE_ON_BLACK);
                break;
            case NINE:
                print_char('9', -1, -1, WHITE_ON_BLACK);
                break;
            case ZERO:
                print_char('0', -1, -1, WHITE_ON_BLACK);
                break;
        }
    }
    UNUSED(regs);
}

void init_keyboard() {
   register_interrupt_handler(IRQ1, keyboard_callback); 
}