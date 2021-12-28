// #include "../kernel/types.h"
// #include "../kernel/kernel.h"

// #define BACKSPACE 0x0E
// #define ENTER 0x1C

// void keyboard_handler(int type){
//     u8 scancode;

//     scancode = port_byte_in(0x60);

//     if (scancode > 57) return;
//     if (scancode == BACKSPACE) {
//         keyboard("Backspace", "Backspace");
//     } else if (scancode == ENTER) {
//         keyboard("Enter", "Enter");
//     } else {
//         keyboard("Test", "Test");
//     }
// }