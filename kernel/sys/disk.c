#include "disk.h"
#include "../../cpu/types.h"
#include "../colors.h"
#include "../screen.h"

char* driveTypes[8] = {
    "None",
    "360kB 5.25\"",
    "1.2MB 5.25\"",
    "720kB 3.5\"",
    "1.44MB 3.5\"",
    "2.88MB 3.5\"",
    "unknown type",
    "unknown type"
};

void floppy_disk_detect() {
    port_byte_out(0x70, 0x10);
    unsigned char drivers = port_byte_in(0x71);

    better_print("Floppy drive 0:", WHITE_ON_BEAUTY_BLUE);
    better_print(driveTypes[drivers >> 4], WHITE_ON_BEAUTY_BLUE);
    better_print("\n\nFloppy drive 1:", WHITE_ON_BEAUTY_BLUE);
    better_print(driveTypes[drivers & 0xf], WHITE_ON_BEAUTY_BLUE);
}