#include "../multilib.h"
#include "../common.h"
#include "../w_x.h"

#define top (1 << 16)
#define SIZE 9999

//this is for the region multiplication for w = 8 and 16
int main(int argc, char *argv[]) {
	unsigned char *c1, *c2, *c3;
	int multiby, i;
	
	c1 = (unsigned char *) malloc (sizeof(unsigned char) * SIZE);
	c2 = (unsigned char *) malloc (sizeof(unsigned char) * SIZE);
	c3 = (unsigned char *) malloc (sizeof(unsigned char) * SIZE);
	srand((unsigned)time(0)); 
	for(i = 0; i < SIZE; ++i) {
		c1[i] = rand() % top;
		c2[i] = rand() % top;
	}

	printf("Now testing the r2 specified, and add = 0\n");
	multiby = rand() % top;
	printf("c2[0] = %d\n", c2[0]);
	gf_region_multi_w16(c1, multiby, SIZE, c2, 0);
	for(i = 0; i < SIZE; ++i) {
		if(single_shift_multi_w16((int) c1[i], multiby) != (int) c2[i]) {
			printf("failed test (r2 != NULL and add = 0) %d * %d != %d, in c2 it is %d and the i = %d\n", c1[i], multiby, single_shift_multi_w16((int) c1[i], multiby), c2[i], i);
			printf("the logtable ans = %d\n", single_logtable_multi_w16(c1[i], multiby));
			exit(1);
		}
	}
	printf("r2 specified and add = 0 testing Bingo!\n");

	//testing with r2 = NULL
	printf("Now testing the r2 = NULL\n");
	multiby = rand() % top;
	gf_region_multi_w16(c1, multiby, SIZE, c2, 0);
	gf_region_multi_w16(c1, multiby, SIZE, NULL, 0);
	for(i = 0; i < SIZE; ++i) {
		if(c1[i] != c2[i]) {
			printf("failed testing with r2 = NULL: %d != %d\n", c1[i], c2[i]);
			exit(1);
		}
	}
	printf("r2 = NULL testing BINGO!\n");

	
	//testing with r2 specified and add = 1
	printf("Now testing the r2 != NULL and add = 1\n");
	multiby = rand() % top;
	for(i = 0; i < SIZE; ++i) {
		c3[i] = c1[i];
	}
	gf_region_multi_w16(c2, multiby, SIZE, c1, 1);
	for(i = 0; i < SIZE; ++i) {
		if(c1[i] != (c3[i] ^ single_shift_multi_w16(c2[i], multiby))) {
			printf("failed testing with r2 != NULL and add = 1: (%d * %d) ^ %d = %d, but in c1 it is %d\n", c2[i], multiby, c3[i], single_shift_multi_w16(c2[i], multiby), c1[i]);
			exit(1);
		}
	}
	printf("r2 != NULL and add = 1 testing BINGO!\n");

	free(c1);
	free(c2);
	free(c3);

	return 1;
}
