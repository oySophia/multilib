#include "multilib.h"
#include "gf_table.h"
#include "w_x.h"

static int prim = -1;
static int mask1 = -1;
static int mask2 = -1;

static uint64_t prim_64 = -1UL;
static uint64_t mask1_64 = -1UL;
static uint64_t mask2_64 = -1UL;

/**@fn int single_logtable_multi_w16(int x, int y)
 * @brief call function of gf_logtable_multi() in gf_tables.c
 *
 */
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

/**@fn int single_shift_multi_w16(int x, int y)
 * @brief call function of gf_shift_multi() in gf_tables.c
 */
int single_shift_multi_w16(int x, int y) {
	int w = 16;
	return gf_shift_multi(x, y, w);
}

/**@fn void gf_region_multiby2_w16(unsigned char *region, int nbytes)
 * @brief this function is same to the function of gf_region_multiby2_w4() in w4.c
 *
 */
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

/**@fn void gf_region_multiby2_w16_64(unsigned char *region, int nbytes)
 * @brief this function is same to the function of gf_region_multiby2_w4_64() in w4.c
 *
 */
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
                                                                                                      
/**@fn void gf_region_multi_w16(unsigned char *region,
 * 			int multiby,
 * 			int nbytes,
 * 			unsigned char *reslt,
 * 			int add)
 *@brief this function is same to the function gf_region_multi_w8() in w8.c
 */
void gf_region_multi_w16(unsigned char *region,
		int multiby,
		int nbytes,
		unsigned char *reslt,
		int add) {
	uint16_t *r1, *r2;
	//int lookup;
	int i;
	uint16_t *start, *end;

	r1 = (uint16_t *) region;
	r2 = (reslt == NULL) ? r1 : (uint16_t *) reslt;
	nbytes /= sizeof(uint16_t);

	if(multiby == 0) {
		if(!add) {
			start = (uint16_t *) r2;
			r2 += nbytes;
			end = (uint16_t *) r2;
			while(start < end) {
				*start = 0;
				++start;
			}
		}
		return;
	}

	if(reslt == NULL || !add) {
		for(i = 0; i < nbytes; ++i) {
			if(r1[i] == 0) {
				r2[i] = 0;
			} else {
				r2[i] = gf_logtable_multi(multiby, r1[i], 16);
			}
		}
	} else {
		for(i = 0; i < nbytes; ++i) {
			if(r1[i] == 0) {
				r2[i] = 0;
			} else {
				r2[i] = r2[i] ^ gf_logtable_multi(multiby, r1[i], 16);
			}
		}

	}
	return;
}

	

	
