#include "../colors.h"
#include "../ports.h"

char* diskTypes[8] = {
    "None",
    "360kB 5.25\"",
    "1.2MB 5.25\"",
    "720kB 3.5\"",
    "1.44MB 3.5\"",
    "2.88MB 3.5\"",
    "Unknown type of disk",
    "Unknown type of disk"
};

void floppy_disk_detect() {
    outb(0x70, 0x10);
    unsigned char disk = inb(0x71);

    better_print("Floppy drive 0: ", WHITE_ON_BEAUTY_BLUE);
    better_print(diskTypes[disk >> 4], WHITE_ON_BEAUTY_BLUE);
    better_print("\nFloppy drive 1: ", WHITE_ON_BEAUTY_BLUE);
    better_print(diskTypes[disk & 0xf], WHITE_ON_BEAUTY_BLUE);
}