#include "../multilib.h"
#include "../common.h"
#include "../w_x.h"

#define top (1 << 8)
#define SIZE 9999

//this is for the region multiplication for w = 16
int main(int argc, char *argv[]) {
	unsigned char *c1, *c2, *c3;
	unsigned short *uc1, *uc2, *uc3;
	int multiby, i;
	
	c1 = (unsigned char *) malloc (sizeof(unsigned char) * SIZE);
	c2 = (unsigned char *) malloc (sizeof(unsigned char) * SIZE);
	c3 = (unsigned char *) malloc (sizeof(unsigned char) * SIZE);
	srand((unsigned)time(0)); 
	for(i = 0; i < SIZE; ++i) {
		c1[i] = rand() % top;
		c2[i] = rand() % top;
	}
	uc1 = (unsigned short *) c1;
	uc2 = (unsigned short *) c2;
	uc3 = (unsigned short *) c3;

	printf("Now testing the r2 specified, and add = 0\n");
	multiby = rand() % top;
	gf_region_multi_w16((unsigned char *)uc1, multiby, SIZE, (unsigned char *) uc2, 0);
	for(i = 0; i < SIZE/2; ++i) {
		if(single_shift_multi_w16(uc1[i], multiby) != uc2[i]) {
			printf("failed test (r2 != NULL and add = 0) %d * %d != %d, in c2 it is %d and the i = %d\n", c1[i], multiby, single_shift_multi_w16((int) c1[i], multiby), c2[i], i);
			printf("the logtable ans = %d\n", single_logtable_multi_w16(uc1[i], multiby));
			exit(1);
		}
	}
	printf("r2 specified and add = 0 testing Bingo!\n");

	//testing with r2 = NULL
	printf("Now testing the r2 = NULL\n");
	multiby = rand() % top;
	gf_region_multi_w16((unsigned char *) uc1, multiby, SIZE, (unsigned char *) uc2, 0);
	gf_region_multi_w16((unsigned char *) uc1, multiby, SIZE, NULL, 0);
	for(i = 0; i < SIZE/2; ++i) {
		if(uc1[i] != uc2[i]) {
			printf("failed testing with r2 = NULL: %d != %d\n", c1[i], c2[i]);
			exit(1);
		}
	}
	printf("r2 = NULL testing BINGO!\n");

	
	//testing with r2 specified and add = 1
	printf("Now testing the r2 != NULL and add = 1\n");
	multiby = rand() % top;
	for(i = 0; i < SIZE/2; ++i) {
		uc3[i] = uc1[i];
	}
	gf_region_multi_w16((unsigned char *) uc2, multiby, SIZE, (unsigned char *) uc1, 1);
	for(i = 0; i < SIZE/2; ++i) {
		if(uc1[i] != (uc3[i] ^ single_shift_multi_w16(uc2[i], multiby))) {
			printf("failed testing with r2 != NULL and add = 1: (%d * %d) ^ %d = %d, but in c1 it is %d\n", uc2[i], multiby, uc3[i], single_shift_multi_w16(uc2[i], multiby), uc1[i]);
			exit(1);
		}
	}
	printf("r2 != NULL and add = 1 testing BINGO!\n");

	free(c1);
	free(c2);
	free(c3);
	//free(uc1);
	//free(uc2);
	//free(uc3);

	return 1;
}
