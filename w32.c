#include "multilib.h"
#include "gf_table.h"
#include "w_x.h"

static int prim = -1;

static uint64_t prim_64 = -1UL;
static uint64_t mask1_64 = -1UL;
static uint64_t mask2_64 = -1UL;

//int single_logtable_multi_w32(int x, int y) {
//	int w = 32;
//	gf_create_tables(w);
//	return gf_logtable_multi(x, y, w);
//}

int single_shift_multi_w32(int x, int y) {
	int w = 32;
	return gf_shift_multi(x, y, w);
}	




void gf_region_multiby2_w32(unsigned char *region, int nbytes) {
	int *start, *end;
	unsigned char *length;

	if(prim == -1) {
		prim = gf_shift_multi((1 << 31), 2, 32);
	}
	
	length = region + nbytes;
	start = (int *)region;
	end = (int *)length;

	while(start < end) {
		*start = ((*start) << 1) ^ ((*start & 0x80000000) ? prim : 0);
		++start;
	}
}

void gf_region_multiby2_w32_64(unsigned char *region, int nbytes) {
	uint64_t *start, *end;
	unsigned char *length;
	uint64_t tmp1, tmp2;

	if(prim_64 = -1UL) {
		tmp1 = (uint64_t)gf_shift_multi((1 << 31), 2, 32);
		prim_64 = 0UL;
		while(tmp1 != 0UL) {
			prim_64 |= tmp1;
			tmp1 = tmp1 << 32UL;
		}
		tmp1 = (1UL << 32UL) - 2UL;
		mask1_64 = 0UL;
		while(tmp1 != 0UL) {
			mask1_64 |= tmp1;
			tmp1 = tmp1 << 32UL;
		}
		tmp1 = (1UL << 31UL);
		mask2_64 = 0UL;
		while(tmp1 != 0UL) {
			mask2_64 |= tmp1;
			tmp1 = tmp1 << 32UL;
		}
	}

	length = region + nbytes;
	start = (uint64_t) region;
	end = (uint64_t) length;

	while(start < end) {
		tmp1 = ((*start) << 1UL) & mask1_64;
		tmp2 = (*start) & mask2_64;
		tmp2 = (tmp2 << 1UL) - (tmp2 >> 31UL);
		*start = tmp1 ^ (tmp2 & prim_64);
		++start;
	}
}
