#include "multilib.h"

void mem_print(unsigned char *mem, int len, int breaklen) {
	int i;
	for(i = 0; i < len; ++i) {
		printf("%d ", *(mem + i));
		if((i + 1) % breaklen == 0) {
			printf("\n");
		}
	}
	printf("\n");
}
