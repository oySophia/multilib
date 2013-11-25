#include "../multilib.h"
#include "../common.h"
#include "../w_x.h"

#define SIZE 2048
#define top (1 << 8)

//this is for the shifting and region_multiby2 multiplication for w = 64
int main(int argc, char *argv[]) {
	unsigned char *c1, *c2;
	uint64_t *uc1, *uc2;
	//uint64_t multiby;
	int i;

	c1 = (unsigned char *) malloc (sizeof(unsigned char *) * SIZE);
	c2 = (unsigned char *) malloc (sizeof(unsigned char *) * SIZE);
	
	srand((unsigned)time(0));
	for(i = 0; i < SIZE; ++i) {
		c1[i] = rand() % top;
		c2[i] = c1[i];
	}
	uc1 = (uint64_t *) c1;
	uc2 = (uint64_t *) c2;

	printf("uc1 = %lu, uc2 = %lu\n", uc1[0], uc2[0]);
	printf("%lu\n", gf_shift_multi_64(uc1[0], 2));
	//multiby = (uint64_t) rand() % top;

	gf_region_multiby2_w64((unsigned char *) uc1, SIZE);
	for(i = 0; i < SIZE / 8; ++i) {
		if(uc1[i] != gf_shift_multi_64(uc2[i], 2)) {
			printf("failed i = %d, uc1[i] = %lu, uc[2] * 2 = 2 * %lu = %lu\n", i, uc1[i], uc2[i], gf_shift_multi_64(uc2[i], 2));
			exit(1);
		}
	}
	printf("the shift multiplication and region multiby2 multiplication is BINGO!\n");
	free(c1);
	free(c2);
	return 1;
}
