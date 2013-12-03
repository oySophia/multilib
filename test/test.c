#include "../multilib.h"
static int *tmp[4] = {NULL, NULL, NULL, NULL};

int main(int argc, char *argv[]) {
	int x = 0xAB;
	int half = 4, i;

	tmp[1] = (int *) malloc (sizeof(int) * 6);

	for(i = 0; i < 6; ++i) {
		tmp[1][i] = 1;
	}
	printf("the tmp[i] = %d\n", tmp[1]);
	tmp[1] += 1;
	printf("the tmp[i] = %d	\t %d\n", tmp[1], tmp[1][0]);
			

	printf("the higher bit is %x, the lower bits are %x\n", x >> half, x ^ ((x >> half) << half));
	return 0;
}

