#include "multilib.h"
#include "gf_table.h"
#include "w_x.h"

static int prim = -1;

static uint64_t prim_64 = -1UL;
static uint64_t mask1_64 = -1UL;
static uint64_t mask2_64 = -1UL;

//this is special for w = 32;
static int *gf_split_w8[7] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL};


//int single_logtable_multi_w32(int x, int y) {
//	int w = 32;
//	gf_create_tables(w);
//	return gf_logtable_multi(x, y, w);
//}

/**@fn int single_shift_multi_w32(int x, int y)
 * @brief call function of gf_shift_multi() in gf_tables.c
 */
int single_shift_multi_w32(int x, int y) {
	int w = 32;
	return gf_shift_multi(x, y, w);
}	

/**@fn int gf_create_split_w8_tables();
 * such function is a split-multiplication that uses 7 full multipllcation tables, since it's impossible to complete with log/ilog when w = 32; memory limiting
 * 这个函数只是简单的将32bit分成4个8份，然后一次相乘，分别保存相乘的结果在表格中，依次查找，并没有使用到更好的策略，如先查表再 and 运算等。
 * 思路比较简单，所需内存大小8 * 2^16 = 512K
 * ?比单纯只用shift要快？？因为在james的代码里实现single_multi的时候，此函数优先级高于shift的
 *
 */
int gf_create_split_w8_tables() {
	int x_orig, y_orig, i, j, x_ele, y_ele, index, ishift, jshift, *table;

	if(gf_split_w8[0] != NULL) return 0;

	for(i = 0; i < 7; ++i) {
		gf_split_w8[i] = (int *) malloc (sizeof(int) * (1 << 16));
		if(gf_split_w8[i] == NULL) {
			fprintf(stderr, "ERROR----gf_split_w8 malloc failed!\n");
			exit(1);
		}
	}

	for(i = 0; i < 4; i += 3) {
		ishift = i * 8;
		for(j = (i == 0? 0 : 1); j < 4; ++j) {
			jshift = j * 8;
			table = gf_split_w8[i + j];
			index = 0;
			for(x_orig = 0; x_orig < 256; ++x_orig) {
				x_ele = (x_orig << ishift);
				for(y_orig = 0; y_orig < 256; ++y_orig) {
					y_ele = (y_orig << jshift);
					table[index] = gf_shift_multi(x_ele, y_ele, 32);
					++index;
				}
			}
		}
	}
	return 0;
}

/**@fn int gf_split_w8_multi(int x, int y)
 * @brief 根据以上构造的tables，下面利用此进行运算；
 */
int gf_split_w8_multi(int x, int y) {
	int i, j, xx, yy, sum, x_8bits, y_8bits;

	sum = 0;
	x_8bits = 0;
	for(i = 0; i < 4; ++i) {
		xx = (((x >> x_8bits) & 255) << 8);//取出x的每8bits
		y_8bits = 0;
		for(j = 0; j < 4; ++j) {
			yy = ((y >> y_8bits) & 255); //取出y的每8bits
			sum ^= gf_split_w8[i + j][xx | yy];
			y_8bits += 8;
		}
		x_8bits += 8;
	}
	return sum;
}


/**@fn void gf_region_multiby2_w32(unsigned char *region, int nbytes)
 * @brief this function is same to the function of gf_region_multiby2_w4() in w4.c
 *
 */
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

/**@fn void gf_region_multiby2_w32_64(unsigned char *region, int nbytes)
 * @brief this function is same to the function of gf_region_multiby2_w4_64() in w4.c
 */
void gf_region_multiby2_w32_64(unsigned char *region, int nbytes) {
	uint64_t *start, *end;
	unsigned char *length;
	uint64_t tmp1, tmp2;

	if(prim_64 == -1UL) {
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
	start = (uint64_t *) region;
	end = (uint64_t *) length;

	while(start < end) {
		tmp1 = ((*start) << 1UL) & mask1_64;
		tmp2 = (*start) & mask2_64;
		tmp2 = (tmp2 << 1UL) - (tmp2 >> 31UL);
		*start = tmp1 ^ (tmp2 & prim_64);
		++start;
	}
}


/**@fn void gf_region_multi_w32(unsigned char *region,
 * 			int multiby,
 * 			int nbytes,
 * 			unsigned char *reslt.
 * 			int add)
 * @brief this function is same to the function of gf_region_multi_w8() in w8.c
 */
void gf_region_multi_w32(unsigned char *region,
		int multiby,
		int nbytes,
		unsigned char *reslt,
		int add) {
	uint32_t *r1, *r2;
	int i, j, k, xx, yy, x_8, y_8, tmp;
	int acache[4];
	
	r1 = (uint32_t *) region;
	r2 = (reslt == NULL) ? r1 : (uint32_t *) reslt;
	nbytes /= sizeof(uint32_t);

	//this use split_w8_works
	if(gf_split_w8[0] == NULL) {
		if(gf_create_split_w8_tables() < 0) {
			fprintf(stderr, "ERROR--gf_region_multi_w32---couldn't make split multi-tables!\n");
			exit(1);
		}
	}

	x_8 = 0;
	for(i = 0; i < 4; ++i) {
		acache[i] = ((multiby >> x_8) & 255) << 8;
		x_8 += 8;
	}

	if(!add) {
		for(k = 0; k < nbytes; ++k) {
			tmp = 0;
			for(i = 0; i < 4; ++i) {
				xx = acache[i];
				y_8 = 0;
				for(j = 0; j < 4; ++j) {
					yy = (r1[k] >> y_8) & 255;
					tmp ^= gf_split_w8[i + j][xx | yy];
					y_8 += 8;
				}
			}
			r2[k] = tmp;
		}
	} else {
		for(k = 0; k < nbytes; ++k) {
			tmp = 0;
			for(i = 0; i < 4; ++i) {
				xx = acache[i];
				y_8 = 0;
				for(j = 0; j < 4; ++j) {
					yy = (r1[k] >> y_8) & 255;
					tmp ^= gf_split_w8[i + j][xx | yy];
					y_8 += 8;
				}
			}
			r2[k] = r2[k] ^ tmp;
		}
	}
	return;
}

int gf_inverse_w32(int y) {
	if(y == 0) return -1;
	return gf_shift_inverse(y, 32);
}
