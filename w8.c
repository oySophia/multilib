#include "multilib.h"
#include "gf_table.h"
#include "w_x.h"

static int prim = -1;
static int mask1 = -1;
static int mask2 = -1;

static uint64_t prim_64 = -1UL;
static uint64_t mask1_64 = -1UL;
static uint64_t mask2_64 = -1UL;

/**@fn int single_logtable_multi_w8(int x, int y)
 * @brief call function of gf_logtable_multi(x, y, w) in gf_tables.c
 */
int single_logtable_multi_w8(int x, int y) {
	int w = 8;
//	if(gflog[w] == NULL) {
//		if(gf_create_tables(w) < 0) {
//			fprintf(stderr, "ERROR -- cannot make log tables for w = %d\n", w);
///			exit(1);
//		}
//	}
	return gf_logtable_multi(x, y, w);
}

/**@fn int single_multitable_w8(int x, int y)
 * @brief call function of gf_multitable_multi(x, y, w) in gf_tables.c
 *
 */
int single_multitable_w8(int x, int y) {
	int w = 8;
//	if(gf_multi_tables[w] == NULL) {
//		if(gf_create_multi_tables(w) < 0) {
//			fprintf(stderr, "ERROR -- cannot make gf_multi_tables for w = %d\n", w);
//			exit(1);
//		}
//	}
	return gf_multitable_multi(x, y, w);
}

/**@fn int single_shift_multi_w8(int x, int y)
 * @brief call function of gf_shift_multi(x, y, w) in gf_tables.c
 *
 */
int single_shift_multi_w8(int x, int y) {
	int w = 8;
	return gf_shift_multi(x, y, w);
}

/**@fn void gf_region_multiby2_w8(unsigned char *region, int nbytes)
 * @brief this function is same to the function of gf_region_multiby2_w4() in w4.c
 */

void gf_region_multiby2_w8(unsigned char *region, int nbytes) {
	unsigned int *start, *end;
	unsigned char *length;
	unsigned int tmp1, tmp2;
	
	if(prim == -1) {
		tmp1 = gf_multitable_multi((1 << 7), 2, 8); //最高位是1时，*2得到的结果即正常移位以外还需要XOR的数值
		prim = 0;
		while(tmp1 != 0) { //将int分成多个4，每个4-bit进行分别操作
			prim |= tmp1;
			tmp1 = tmp1 << 8;
		}
		tmp1 = (1 << 8) - 2;//tmp1 = 1110
		mask1 = 0;
		while(tmp1 != 0) {
			mask1 |= tmp1;
			tmp1 = tmp1 << 8;
		}
		tmp1 = (1 << 7);//tmp1 = 1000
		mask2 = 0;
		while(tmp1 != 0) {
			mask2 |= tmp1;
			tmp1 = tmp1 << 8;
		}
	}
	    
	length = region + nbytes;
	start = (unsigned int *) region;
	end = (unsigned int *) length;
	    
	while(start < end) {
	    tmp1 = ((*start) << 1) & mask1;
		tmp2 = (*start) & mask2;
		tmp2 = (tmp2 << 1) - (tmp2 >> 7);//如果高位是1，则将4bit均设置成1，即1111
		*start = (tmp1 ^ (tmp2 & prim));
		++start;
	}
}

/**@fn void gf_region_multiby2_w8_64(unsigned char *region, int nbytes)
 * @brief this function is just like function gf_region_multiby2_w4_64() in w4.c
 */
void gf_region_multiby2_w8_64(unsigned char *region, int nbytes) {
	uint64_t *start, *end;
	unsigned *length;
	uint64_t tmp1, tmp2;
			   
	if(prim_64 == -1UL) {
		tmp1 = (uint64_t)gf_multitable_multi((1 << 7), 2, 8);
		prim_64 = 0UL;
		while(tmp1 != 0UL) {
			prim_64 |= tmp1;
			tmp1 = tmp1 << 8UL;
		}
		tmp1 = (1UL << 8UL) - 2UL;
		mask1_64 = 0UL;
		while(tmp1 != 0UL) {
			mask1_64 |= tmp1;
			tmp1 = (tmp1 << 8UL);
		}
		tmp1 = (1UL << 7UL);
		mask2_64 = 0UL;
		while(tmp1 != 0UL) {
		    mask2_64 |= tmp1;
			tmp1 = tmp1 << 8UL;
		}
	}
	
	length = region + nbytes;
	start = (uint64_t *) region;
	end = (uint64_t *) length;

	while(start < end) {
		tmp1 = ((*start) << 1UL) & mask1_64;
		tmp2 = (*start) & mask2_64;
		tmp2 = (tmp2 << 1UL) - (tmp2 >> 7UL);
		*start = (tmp1) ^ (tmp2 & prim_64);
		++start;
	}
}                                                                       

/**@fn void gf_region_multi_w8(unsigned char *region, 
 * 		int multiby, 
 * 		int nbytes,
 * 		unsigned char *reslt,
 * 		int add)
 * @param region the region will be in the multiplication
 * @param multiby the number will multiply the region stated above
 * @param nbytes the length of region
 * @param reslt if it's not null, then the result of such multiplication will be stored here, or it will be stored in the region above 
 * @oaram add if it's not zero, and reslt above not NULL, then the result would first XOR reslt and then stored in reslt
 */
//this funciton make a region multiply an integer.
void gf_region_multi_w8(unsigned char *region, //the region will be in the multiplication
		int multiby, //the number will multiply the region stated above
		int nbytes,  //the length of region
		unsigned char *reslt, //if it's not null, then the result of such multiplication will be stored here, or it will be stored in the region above
		int add) //if it's not zero, and reslt above not NULL, then the result would first XOR reslt and then stored in reslt. 
{
	unsigned char *r1, *r2;
	int i, lookup;

	r1 = (unsigned char *) region;
	r2 = (reslt == NULL) ? r1 : (unsigned char *) reslt;

	if(reslt == NULL || !add) {
		for(i = 0; i < nbytes; ++i) {
			lookup = gf_multitable_multi(multiby, r1[i], 8);
			r2[i] = lookup;
		}
	} else {
		for(i = 0; i < nbytes; ++i) {
			lookup = gf_multitable_multi(multiby, r1[i], 8);
			r2[i] ^= lookup;
		}
	}
}



int gf_inverse_w8(int y) {
	if(y == 0) return -1;
	return gf_single_div(1, y, 8);
}
