#ifndef SCREEN_H
    #define SCREEN_H 0x1

    #define MAX_ROWS 25
    #define MAX_COLS 80

    struct vec2 {
        int x;
        int y;
        int mTop;
        int mLeft;
        int saveOnStart;
    };

    void print(char* message);
    void print_backspace();
    int print_char(char c, int col, int row, char attr);
    int get_cursor_offset();
    void set_cursor_offset(int offset);
    void set_cursor_offset_pos(int row, int col);
    void clear_screen();
    int get_offset(int col, int row);
    int get_offset_row(int offset);
    int get_offset_col(int offset);
    int draw_rec(struct vec2 vec, int colorRect, int colorBack);
#endif