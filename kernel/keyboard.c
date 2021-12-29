#include "./ports.h"
#include "../cpu/isr.h"
#include "./screen.h"
#include "../cpu/idt.h"
#include "./keyboard.h"
#include "./util.h"
#include "./colors.h"
#include "./string.h"

int shift_pressed = 0;
int capslock_pressed = 0;

// Numbers
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
#define SPACE 0x39

// Letters
#define Q 0x10
#define W 0x11
#define E 0x12
#define R 0x13
#define T 0x14
#define Y 0x15
#define U 0x16
#define I 0x17
#define O 0x18
#define P 0x19
#define A 0x1E
#define S 0x1F
#define D 0x20
#define F 0x21
#define G 0x22
#define H 0x23
#define J 0x24
#define K 0x25
#define L 0x26
#define Z 0x2C
#define X 0x2D
#define C 0x2E
#define V 0x2F
#define B 0x30
#define N 0x31
#define M 0x32

// Other keys
#define SPACE 0x39
#define CAPSLOCK 0x03A
#define BACKSPACE 0x0E
#define ENTER 0x1C
#define ESC 0x1

#define SC_MAX 58

char buffer_keys[256];
int letters;
int modeGlobal;

void keyboard_callback(registers_t regs) {
    u8 scancode = inb(0x60);
    
    if (modeGlobal == MENU_MODE) {
        if (scancode == ENTER) {
            input_menu(0);
        } else if (scancode == SPACE) {
            input_menu(1);
        }
    } else if (modeGlobal == SHELL_MODE) {
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

                backspace(buffer_keys);
            } else {
                return;
            }
        } else if (scancode == ENTER) {
            better_print("\n");
            input(buffer_keys);
            buffer_keys[0] = '\0';
        } else {
            letters++;
            switch(scancode) {
                /*
                    OTHER KEYS
                */
                case SPACE:
                    append(buffer_keys, ' ');
                    print_char(' ', -1, -1, WHITE_ON_BLACK);
                    break;
                case CAPSLOCK:
                    if (capslock_pressed == 1) {
                        capslock_pressed = 0;
                    } else {
                        capslock_pressed = 1;
                    }
                    break;
                /*
                    NUMBERS
                */
                case ONE:
                    append(buffer_keys, '1');
                    print_char('1', -1, -1, WHITE_ON_BLACK);
                    break;
                case TWO:
                    append(buffer_keys, '2');
                    print_char('2', -1, -1, WHITE_ON_BLACK);
                    break;
                case THREE:
                    append(buffer_keys, '3');
                    print_char('3', -1, -1, WHITE_ON_BLACK);
                    break;
                case FOUR:
                    append(buffer_keys, '4');
                    print_char('4', -1, -1, WHITE_ON_BLACK);
                    break;
                case FIVE:
                    append(buffer_keys, '5');
                    print_char('5', -1, -1, WHITE_ON_BLACK);
                    break;
                case SIX:
                    append(buffer_keys, '6');
                    print_char('6', -1, -1, WHITE_ON_BLACK);
                    break;
                case SEVEN:
                    append(buffer_keys, '7');
                    print_char('7', -1, -1, WHITE_ON_BLACK);
                    break;
                case EIGHT:
                    append(buffer_keys, '8');
                    print_char('8', -1, -1, WHITE_ON_BLACK);
                    break;
                case NINE:
                    append(buffer_keys, '9');
                    print_char('9', -1, -1, WHITE_ON_BLACK);
                    break;
                case ZERO:
                    append(buffer_keys, '0');
                    print_char('0', -1, -1, WHITE_ON_BLACK);
                    break;
                /*
                    LETTERS
                */
               case Q:
                    if (capslock_pressed == 1) {
                        append(buffer_keys, 'Q');
                        print_char('Q', -1, -1, WHITE_ON_BLACK);
                        break;
                    } else {
                        append(buffer_keys, 'q');
                        print_char('q', -1, -1, WHITE_ON_BLACK);
                        break;
                    }
               case W:
                    if (capslock_pressed == 1) {
                        append(buffer_keys, 'W');
                        print_char('W', -1, -1, WHITE_ON_BLACK);
                        break;
                    } else {
                        append(buffer_keys, 'w');
                        print_char('w', -1, -1, WHITE_ON_BLACK);
                        break;
                    }
                case E:
                    if (capslock_pressed == 1) {
                        append(buffer_keys, 'E');
                        print_char('E', -1, -1, WHITE_ON_BLACK);
                        break;
                    } else {
                        append(buffer_keys, 'e');
                        print_char('e', -1, -1, WHITE_ON_BLACK);
                        break;
                    }
                case R:
                    if (capslock_pressed == 1) {
                        append(buffer_keys, 'R');
                        print_char('R', -1, -1, WHITE_ON_BLACK);
                        break;
                    } else {
                        append(buffer_keys, 'r');
                        print_char('r', -1, -1, WHITE_ON_BLACK);
                        break;
                    }
                case T:
                    if (capslock_pressed == 1) {
                        append(buffer_keys, 'T');
                        print_char('T', -1, -1, WHITE_ON_BLACK);
                        break;
                    } else {
                        append(buffer_keys, 't');
                        print_char('t', -1, -1, WHITE_ON_BLACK);
                        break;
                    }
                case Y:
                    if (capslock_pressed == 1) {
                        append(buffer_keys, 'Y');
                        print_char('Y', -1, -1, WHITE_ON_BLACK);
                        break;
                    } else {
                        append(buffer_keys, 'y');
                        print_char('y', -1, -1, WHITE_ON_BLACK);
                        break;
                    }
                case U:
                    if (capslock_pressed == 1) {
                        append(buffer_keys, 'U');
                        print_char('U', -1, -1, WHITE_ON_BLACK);
                        break;
                    } else {
                        append(buffer_keys, 'u');
                        print_char('u', -1, -1, WHITE_ON_BLACK);
                        break;
                    }
                case I:
                    if (capslock_pressed == 1) {
                        append(buffer_keys, 'I');
                        print_char('I', -1, -1, WHITE_ON_BLACK);
                        break;
                    } else {
                        append(buffer_keys, 'i');
                        print_char('i', -1, -1, WHITE_ON_BLACK);
                        break;
                    }
               case O:
                    if (capslock_pressed == 1) {
                        append(buffer_keys, 'O');
                        print_char('O', -1, -1, WHITE_ON_BLACK);
                        break;
                    } else {
                        append(buffer_keys, 'o');
                        print_char('o', -1, -1, WHITE_ON_BLACK);
                        break;
                    }
                case P:
                    if (capslock_pressed == 1) {
                        append(buffer_keys, 'P');
                        print_char('P', -1, -1, WHITE_ON_BLACK);
                        break;
                    } else {
                        append(buffer_keys, 'p');
                        print_char('p', -1, -1, WHITE_ON_BLACK);
                        break;
                    }
                case A:
                    if (capslock_pressed == 1) {
                        append(buffer_keys, 'A');
                        print_char('A', -1, -1, WHITE_ON_BLACK);
                        break;
                    } else {
                        append(buffer_keys, 'a');
                        print_char('a', -1, -1, WHITE_ON_BLACK);
                        break;
                    }
                case S:
                    if (capslock_pressed == 1) {
                        append(buffer_keys, 'S');
                        print_char('S', -1, -1, WHITE_ON_BLACK);
                        break;
                    } else {
                        append(buffer_keys, 's');
                        print_char('s', -1, -1, WHITE_ON_BLACK);
                        break;
                    }
                case D:
                    if (capslock_pressed == 1) {
                        append(buffer_keys, 'D');
                        print_char('D', -1, -1, WHITE_ON_BLACK);
                        break;
                    } else {
                        append(buffer_keys, 'd');
                        print_char('d', -1, -1, WHITE_ON_BLACK);
                        break;
                    }
                case F:
                    if (capslock_pressed == 1) {
                        append(buffer_keys, 'F');
                        print_char('F', -1, -1, WHITE_ON_BLACK);
                        break;
                    } else {
                        append(buffer_keys, 'f');
                        print_char('f', -1, -1, WHITE_ON_BLACK);
                        break;
                    }
                case G:
                    if (capslock_pressed == 1) {
                        append(buffer_keys, 'G');
                        print_char('G', -1, -1, WHITE_ON_BLACK);
                        break;
                    } else {
                        append(buffer_keys, 'g');
                        print_char('g', -1, -1, WHITE_ON_BLACK);
                        break;
                    }
                case H:
                    if (capslock_pressed == 1) {
                        append(buffer_keys, 'H');
                        print_char('H', -1, -1, WHITE_ON_BLACK);
                        break;
                    } else {
                        append(buffer_keys, 'h');
                        print_char('h', -1, -1, WHITE_ON_BLACK);
                        break;
                    }
                case J:
                    if (capslock_pressed == 1) {
                        append(buffer_keys, 'J');
                        print_char('J', -1, -1, WHITE_ON_BLACK);
                        break;
                    } else {
                        append(buffer_keys, 'j');
                        print_char('j', -1, -1, WHITE_ON_BLACK);
                        break;
                    }
                case K:
                    if (capslock_pressed == 1) {
                        append(buffer_keys, 'K');
                        print_char('K', -1, -1, WHITE_ON_BLACK);
                        break;
                    } else {
                        append(buffer_keys, 'k');
                        print_char('k', -1, -1, WHITE_ON_BLACK);
                        break;
                    }
                case L:
                    if (capslock_pressed == 1) {
                        append(buffer_keys, 'L');
                        print_char('L', -1, -1, WHITE_ON_BLACK);
                        break;
                    } else {
                        append(buffer_keys, 'l');
                        print_char('l', -1, -1, WHITE_ON_BLACK);
                        break;
                    }
                case Z:
                    if (capslock_pressed == 1) {
                        append(buffer_keys, 'Z');
                        print_char('Z', -1, -1, WHITE_ON_BLACK);
                        break;
                    } else {
                        append(buffer_keys, 'z');
                        print_char('z', -1, -1, WHITE_ON_BLACK);
                        break;
                    }
                case X:
                    if (capslock_pressed == 1) {
                        append(buffer_keys, 'X');
                        print_char('X', -1, -1, WHITE_ON_BLACK);
                        break;
                    } else {
                        append(buffer_keys, 'x');
                        print_char('x', -1, -1, WHITE_ON_BLACK);
                        break;
                    }
                case C:
                    if (capslock_pressed == 1) {
                        append(buffer_keys, 'C');
                        print_char('C', -1, -1, WHITE_ON_BLACK);
                        break;
                    } else {
                        append(buffer_keys, 'c');
                        print_char('c', -1, -1, WHITE_ON_BLACK);
                        break;
                    }
                case B:
                    if (capslock_pressed == 1) {
                        append(buffer_keys, 'B');
                        print_char('B', -1, -1, WHITE_ON_BLACK);
                        break;
                    } else {
                        append(buffer_keys, 'b');
                        print_char('b', -1, -1, WHITE_ON_BLACK);
                        break;
                    }
                case N:
                    if (capslock_pressed == 1) {
                        append(buffer_keys, 'N');
                        print_char('N', -1, -1, WHITE_ON_BLACK);
                        break;
                    } else {
                        append(buffer_keys, 'n');
                        print_char('n', -1, -1, WHITE_ON_BLACK);
                        break;
                    }
                case M:
                    if (capslock_pressed == 1) {
                        append(buffer_keys, 'M');
                        print_char('M', -1, -1, WHITE_ON_BLACK);
                        break;
                    } else {
                        append(buffer_keys, 'm');
                        print_char('m', -1, -1, WHITE_ON_BLACK);
                        break;
                    }
            }
        }
        UNUSED(regs);
    }
    
}

void keyboard_mode(int mode) {
    modeGlobal = mode;
}

void init_keyboard() {
    register_interrupt_handler(IRQ1, keyboard_callback); 
}