#include "../multilib.h"
#include "../common.h"
#include "../w_x.h"

#define num 1024
#define top (1 << 31)

//this is to verify all the inversing functions for w = 4 8 16 32 and 64;
int main(int argc, char *argv[]) {
	unsigned int x, ans, i;
	unsigned char *c;
	int w = (1 << 8);
	uint64_t *y, yy;

	c = (unsigned char *) malloc (sizeof(unsigned char) * num);

	srand((unsigned) time(0));
	for(i = 0; i < num; ++i) {
		x = rand() % top;
		ans = gf_inverse_w32(x);
		if(i < 10) {
			printf("x = %d, ans = %d, gf_inv = %d\n", x, ans, gf_inverse_w32(ans));
		}
		if(x != gf_inverse_w32(ans)) {
			printf("failed testing gf_inverse_w8() with i = %d: %d != %d\n", i, x, gf_inverse_w32(ans));			
			exit(1);
		}
	}
	printf("testing w16 inverse BINGO!\n");
	
	for(i = 0; i < num; ++i) {
		c[i] = rand() % w;
	}
	y = (uint64_t *) c;
	for(i = 0; i < num / 8; ++i) {
		yy = gf_shift_inverse_64(y[i]);
		if(y[i] != gf_shift_inverse_64(yy)) {
			printf("failed testing w = 64 with i = %d: %lu != %lu\n", i, y[i], gf_shift_inverse_64(yy));
			exit(1);
		}
	}
	printf("testing w64 inverse BINGO!\n");
	return 0;
}
