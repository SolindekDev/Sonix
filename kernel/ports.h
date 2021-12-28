#ifndef PORTS_H
    #define PORTS_H 0x1
    unsigned char inb(unsigned short port);
    void outb(unsigned short port, unsigned char data);
    unsigned char inw(unsigned short port);
    void outw(unsigned short port, unsigned char data);
#endif