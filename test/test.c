#include "../multilib.h"

int main(int argc, char *argv[]) {
	int x = 0xAB;
	int half = 4;

	printf("the higher bit is %x, the lower bits are %x\n", x >> half, x ^ ((x >> half) << half));
	return 0;
}

