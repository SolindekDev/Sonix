#include "memory.h"

int freeMem = 0;

void init_mem() {
    freeMem = FREE_MEM;
}

void copy_mem(unsigned char* s, unsigned char* d, int count) {
    for (int i = 0; i < count; i++)
        *(d + i) = *(s + i);
}

void* set_mem(void* d, unsigned char v, int count){ 
	unsigned char* dC = (unsigned char*)d;
	int i;
	for (i = 0; i < count; i++)
		dC[i] = v;
	return d;
}

// More soon