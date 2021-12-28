#include "ports.h"
#include "../kernel/colors.h"
#include "screen.h"

int get_cursor_offset();
void set_cursor_offset(int offset);
int print_char(char c, int col, int row, char attr);
int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);

void print(char* message, int type) {
    int col = -1;
    int row = -1;

    int offset;
    if (col >= 0 && row >= 0)
        offset = get_offset(col, row);
    else {
        offset = get_cursor_offset();
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }

    int i = 0;
    while (message[i] != 0) {
        i++;
        offset = print_char(message[i], col, row, type);
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }
}

void print_backspace(int type) {
    int offset = get_cursor_offset()-2;
    int row = get_offset_row(offset);
    int col = get_offset_col(offset);
    print_char(0x08, col, row, type);
}

int print_char(char c, int col, int row, char attr) {
    unsigned char *vidmem = (unsigned char*) VIDEO_ADDRESS;
    if (!attr) attr = WHITE_ON_BLACK;

    if (col >= MAX_COLS || row >= MAX_ROWS) {
        vidmem[2*(MAX_COLS)*(MAX_ROWS)-2] = 'E';
        vidmem[2*(MAX_COLS)*(MAX_ROWS)-1] = RED_ON_WHITE;
        return get_offset(col, row);
    }

    int offset;
    if (col >= 0 && row >= 0) offset = get_offset(col, row);
    else offset = get_cursor_offset();

    if (c == '\n') {
        row = get_offset_row(offset);
        offset = get_offset(0, row+1);
    } else {
        vidmem[offset] = c;
        vidmem[offset+1] = attr;
        offset += 2;
    }
    set_cursor_offset(offset);
    return offset;
}

int get_cursor_offset() {
    port_byte_out(REG_SCREEN_CTRL, 14);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8;
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);
    return offset * 2; 
}

void set_cursor_offset(int offset) {
    offset /= 2;
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

void clear_screen(int type) {
    char* screen = VIDEO_ADDRESS;

    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            print_char(' ', j, i, type);
        }
    }
    set_cursor_offset(get_offset(0, 0));
}

int get_offset(int col, int row) { 
    return 2 * (row * MAX_COLS + col); 
}

int get_offset_row(int offset) {
    return offset / (2 * MAX_COLS); 
}

int get_offset_col(int offset) { 
    return (offset - (get_offset_row(offset)*2*MAX_COLS))/2; 
}

int draw_rec(struct vec2 vec, int colorRect, int colorBack) {
    if (vec.x > MAX_COLS || vec.y > MAX_ROWS) return 0;

    for (int i = 0; i < vec.y; i++) {
        for (int j = 0; j < vec.x; j++) {
            print_char(' ', j + vec.mLeft, i + vec.mTop, colorRect);
        }
    }

    if (vec.saveOnStart == 1) {
        set_cursor_offset(get_offset(vec.mLeft, vec.mTop));
    } else {
        set_cursor_offset(get_offset(0, 0));
    }
}