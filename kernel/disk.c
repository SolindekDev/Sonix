#include "disk.h"
#include "types.h"
#include "colors.h"

char* driveTypes[8] = {
    " None",
    " 360kB 5.25\"",
    " 1.2MB 5.25\"",
    " 720kB 3.5\"",
    " 1.44MB 3.5\"",
    " 2.88MB 3.5\"",
    " unknown type",
    " unknown type"
};

void disk_floppy_detect() {
    port_byte_out(0x70, 0x10);
    u8 drivers = port_byte_in(0x71);

    print(" Floppy drive 0:", WHITE_ON_BEAUTY_BLUE);
    print(driveTypes[drivers >> 4], WHITE_ON_BEAUTY_BLUE);
    print("\n\nFloppy drive 1:", WHITE_ON_BEAUTY_BLUE);
    print(driveTypes[drivers & 0xf], WHITE_ON_BEAUTY_BLUE);
}