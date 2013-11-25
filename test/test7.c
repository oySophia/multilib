#include "../multilib.h"
#include "../common.h"
#include "../w_x.h"

#define top (1 << 31)
#define num 2048

//this is to verify the w = 32's region multiplication;
int main(int argc, char *argv[]) {
	unsigned char *c1, *c2;
	int *cc1, *cc2;
	int multiby, i, tmp;

	c1 = (unsigned char *) malloc (sizeof(unsigned char) * num);
	c2 = (unsigned char *) malloc (sizeof(unsigned char) * num);
	srand((unsigned)time(0));
	for(i = 0; i < num; ++i) {
	//printf("please input two integers:\n");
	//scanf("%d%d", &a, &b);
		c1[i] = rand() % top;
		c2[i] = c1[i];
	}
	multiby = rand() % top;

	cc1 = (int *) c1;
	cc2 = (int *) c2;
	//r2 specified and add = 0 testing
	gf_region_multi_w32((unsigned char *) cc1, multiby, num, (unsigned char *) cc2, 0);
	for(i = 0; i < num / 4; ++i) {
		if(single_split8_multi_w32(cc1[i], multiby) != cc2[i]) {
			printf("failed test (r2 != NULL and add = 0) %d * %d != %d and i = %d\n", cc1[i], multiby, single_split8_multi_w32(cc1[i], multiby),i);
			exit(1);
		}
	}
	printf("r2 specified and add = 0 testing Bingo!\n");

	//r2 = null testing
	multiby = rand() % top;
	gf_region_multi_w32((unsigned char *) cc1, multiby, num, (unsigned char *) cc2, 0);
	gf_region_multi_w32((unsigned char *) cc1, multiby, num, NULL, 0);
	for(i = 0; i < num / 4; ++i) {
		if(cc1[i] != cc2[i]) {
			printf("failed test with r2 = NULL: %d != %d \n", cc1[i], cc2[i]);
			exit(1);
		}
	}
	printf("r2 = NULL testing BINGO!\n");

	//r2 specified and add = 1
	multiby = rand() % top;
	gf_region_multi_w32((unsigned char *) cc2, multiby, num, (unsigned char *)cc1, 1);
	for(i = 0; i < num / 4; ++i) {
		tmp = cc2[i];
		if(cc1[i] != (tmp ^ single_split8_multi_w32(cc2[i], multiby))) {
			printf("failed test with r2 != NULL and add = 1: (%d * %d) ^ %d = %d, but in cc1 it is %d\n", cc2[i], multiby, tmp, single_split8_multi_w32(tmp, cc2[i]), cc1[i]);
			exit(1);
		}
	}
	printf("r2 specified and add = 1 testing BINGO!\n");

	free(c1);
	free(c2);

	return 1;
}
