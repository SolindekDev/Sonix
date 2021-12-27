#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80

#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

struct vec2 {
    int x;
    int y;
    int mTop;
    int mLeft;
    int saveOnStart;
};

void clear_screen(int type);
void print(char *message, int type);