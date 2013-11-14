#include "multilib.h"
#include "gf_table.h"
#include "w_x.h"

///prim指根据本原多项式，GF中若有一个4-bit的word *2 可以对应转换成（正常的移位运算XOR prim），这样不会用到lookup tables
static int prim = -1;
///mask1指fefe...，*2表示x向左移一位，移位后，将高位移出去的1设置为0，这样结果才不会出错
static int mask1 = -1;
///mask2为100010001000...，判断x的4th/8th等等是不是1，如果是1，则取prim与（x<<1）XOR，结果即为*2的result
static int mask2 = -1;

///和上面类似，唯一区别是，机器的int型大小是32，若将整个一次运算的word增大，速度也会提高；
static uint64_t prim_64 = -1UL;
static uint64_t mask1_64 = -1UL;
static uint64_t mask2_64 = -1UL;

/**@fn int single_logtable_multi_w4(int x, int y)
 * @brief call function of gf_logtable_multi(x, y, w) in gf_tables.c
 */
int single_logtable_multi_w4(int x, int y) {
	int w = 4;
//	if(gflog[w] == NULL) {
//		if(gf_create_tables(w) < 0) {
//			fprintf(stderr, "ERROR -- cannot make log tables for w = %d\n", w);
//			exit(1);
//		}
//	}
//	printf("  ...  %d\n", gflog[w]);
	return gf_logtable_multi(x, y, w);
}

/**@fn int single_multitable_w4(int x, int y)
 * @brief call function of gf_multitable_multi(x, y, w) in gf_tables.c
 */
int single_multitable_w4(int x, int y) {
	int w = 4;
//		printf("%d\n", gf_multi_tables[w]);
//	if(gf_multi_tables[w] == NULL) {
//		//printf("the create multi_table %d\n", gf_create_multi_tables(w));
//		if(gf_multi_tables[w] == NULL) {
//			printf("the table is null first\n");
//		}
//		if(gf_create_multi_tables(w) < 0) {
//			fprintf(stderr, "ERROR -- cannot make gf_multi_tables for w = %d\n", w);
//			exit(1);
//		}
//	}
	
//		printf("ttt %d\n", gf_multi_tables[w]);
//	if(gf_multi_tables[w] == NULL) {
//		printf("the table is null second!\n");
//	}
//	printf("1\n");
//	printf("gf = %d\n", gf_multi_tables[w][4]);
//	printf("1\n");
	return gf_multitable_multi(x, y, w);
}

/**@fn int single_shift_multi_w4(int x, int y)
 * @brief call function of gf_shift_multi(x, y, w) in gf_tables.c
 */
int single_shift_multi_w4(int x, int y) {
	int w = 4;
	return gf_shift_multi(x, y, w);
}

/**@fn void gf_region_multiby2_w4(unsigned char *region, int nbytes)
 * this by 2 functions are another form of the gf algrithm without refer to the gflog and gfilog tables, whereas it is still rooting in the prim_poly.
 * @param region the data region will join the multiplication
 * @param nbytes it will multiply the region
 */
void gf_region_multiby2_w4(unsigned char *region, int nbytes) {
	unsigned int *start, *end;
	unsigned char *length;
	unsigned int tmp1, tmp2;

	if(prim == -1) {
		tmp1 = gf_multitable_multi((1 << 3), 2, 4); //最高位是1时，*2得到的结果即正常移位以外还需要XOR的数值
		prim = 0;
		while(tmp1 != 0) { //将int分成多个4，每个4-bit进行分别操作
			prim |= tmp1;
			tmp1 = tmp1 << 4;
		}
		tmp1 = (1 << 4) - 2;//tmp1 = 1110
		mask1 = 0;
		while(tmp1 != 0) {
			mask1 |= tmp1;
			tmp1 = tmp1 << 4;
		}
		tmp1 = (1 << 3);//tmp1 = 1000
		mask2 = 0;
		while(tmp1 != 0) {
			mask2 |= tmp1;
			tmp1 = tmp1 << 4;
		}
	}

	length = region + nbytes;
	start = (unsigned int *) region;
	end = (unsigned int *) length;

	while(start < end) {
		tmp1 = ((*start) << 1) & mask1;
		tmp2 = (*start) & mask2;
		tmp2 = (tmp2 << 1) - (tmp2 >> 3);//如果高位是1，则将4bit均设置成1，即1111
		*start = (tmp1 ^ (tmp2 & prim));
		++start;
	}
}

/**@fn void gf_region_multiby2_w4_64(unsigned char *region, int nbytes)
 * This function merely seem to the gf_region_multiby2_w4(), but it has aligned the word size to 64-bit
 * /param region the data region will join the mulplication
 * /param nbytes it will multiply the region
 */
void gf_region_multiby2_w4_64(unsigned char *region, int nbytes) {
	uint64_t *start, *end;
	unsigned *length;
	uint64_t tmp1, tmp2;

	if(prim_64 == -1UL) {
		tmp1 = (uint64_t)gf_multitable_multi((1 << 3), 2, 4);
		prim_64 = 0UL;
		while(tmp1 != 0UL) {
			prim_64 |= tmp1;
			tmp1 = tmp1 << 4UL;
		}
		tmp1 = (1UL << 4UL) - 2UL;
		mask1_64 = 0UL;
		while(tmp1 != 0UL) {
			mask1_64 |= tmp1;
			tmp1 = (tmp1 << 4UL);
		}
		tmp1 = (1UL << 3UL);
		mask2_64 = 0UL;
		while(tmp1 != 0UL) {
			mask2_64 |= tmp1;
			tmp1 = tmp1 << 4UL;
		}
	}

	length = region + nbytes;
	start = (uint64_t *) region;
	end = (uint64_t *) length;

	while(start < end) {
		tmp1 = ((*start) << 1UL) & mask1_64;
		tmp2 = (*start) & mask2_64;
		tmp2 = (tmp2 << 1UL) - (tmp2 >> 3UL);
		*start = (tmp1) ^ (tmp2 & prim_64);
		++start;
	}
}
