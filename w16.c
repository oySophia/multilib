#include "multilib.h"
#include "gf_table.h"
#include "w_x.h"

static int prim = -1;
static int mask1 = -1;
static int mask2 = -1;

static uint64_t prim_64 = -1UL;
static uint64_t mask1_64 = -1UL;
static uint64_t mask2_64 = -1UL;

int single_logtable_multi_w16(int x, int y) {
	int w = 16;
//	if(gflog[w] == NULL) {
//		if(gf_create_tables(w) < 0) {
//			fprintf(stderr, "ERROR -- cannot make log tables for w = %d\n", w);
//			exit(1);
//		}
//	}
	return gf_logtable_multi(x, y, w);
}

int single_shift_multi_w16(int x, int y) {
	int w = 16;
	return gf_shift_multi(x, y, w);
}





void gf_region_multiby2_w16(unsigned char *region, int nbytes) {
	unsigned int *start, *end;                                                                                
	unsigned char *length;
	unsigned int tmp1, tmp2;

	if(prim == -1) {
		tmp1 = gf_logtable_multi((1 << 15), 2, 16); //最高位是1时，*2得到的结果即正常移位以外还需要XOR的数值
		prim = 0;
		while(tmp1 != 0) { //将int分成多个4，每个4-bit进行分别操作
			prim |= tmp1;
			tmp1 = tmp1 << 16;
		}
		tmp1 = (1 << 16) - 2;//tmp1 = 1110
		mask1 = 0;
		while(tmp1 != 0) {
			mask1 |= tmp1;
			tmp1 = tmp1 << 16;
		}
		tmp1 = (1 << 15);//tmp1 = 1000
		mask2 = 0;
		while(tmp1 != 0) {
			mask2 |= tmp1;
			tmp1 = tmp1 << 16;
		}
	}

	length = region + nbytes;
	start = (unsigned int *) region;
	end = (unsigned int *) length;

	while(start < end) {
		tmp1 = ((*start) << 1) & mask1;
		tmp2 = (*start) & mask2;
		tmp2 = (tmp2 << 1) - (tmp2 >> 15);//如果高位是1，则将4bit均设置成1，即1111
		*start = (tmp1 ^ (tmp2 & prim));
		++start;
	}
}

void gf_region_multiby2_w16_64(unsigned char *region, int nbytes) {
	uint64_t *start, *end;
	unsigned *length;
	uint64_t tmp1, tmp2;

	if(prim_64 == -1UL) {
		tmp1 = (uint64_t)gf_logtable_multi((1 << 15), 2, 16);
		prim_64 = 0UL;
		while(tmp1 != 0UL) {
			prim_64 |= tmp1;
			tmp1 = tmp1 << 16UL;
		}
		tmp1 = (1UL << 16UL) - 2UL;
		mask1_64 = 0UL;
		while(tmp1 != 0UL) {
			mask1_64 |= tmp1;
			tmp1 = (tmp1 << 16UL);
		}
		tmp1 = (1UL << 15UL);
		mask2_64 = 0UL;
		while(tmp1 != 0UL) {
			mask2_64 |= tmp1;
			tmp1 = tmp1 << 16UL;
		}
	}					   

	length = region + nbytes;
	start = (uint64_t *) region;
	end = (uint64_t *) length;

	while(start < end) {
		tmp1 = ((*start) << 1UL) & mask1_64;
		tmp2 = (*start) & mask2_64;
		tmp2 = (tmp2 << 1UL) - (tmp2 >> 16UL);
		*start = (tmp1) ^ (tmp2 & prim_64);
		++start;
	}
}                                                                                                     
                                                                                                      


