#include "multilib.h"
#include "w_x.h"

static uint64_t prim64 = 0x1b;

/**@fn uint64_t gf_shift_multi_64(uint64_t x, uint64_t y)
 * @brief this shift funcitons algorithm is same with the 4, 8, 16-word size shifting funcitons
 */
 uint64_t gf_shift_multi_64(uint64_t x, uint64_t y) {
	uint64_t result = 0;
	uint64_t shift_y[64], x_binary;
	int i;

	shift_y[0] = y;
	for(i = 1; i < 64; ++i) {
		shift_y[i] = shift_y[i - 1];
		if(shift_y[i] & 0x8000000000000000) {
			shift_y[i] = shift_y[i] << 1;
			shift_y[i] = shift_y[i] ^ prim64;
		} else {
			shift_y[i] = shift_y[i] << 1;
		}
	}

	for(i = 0; i < 64; ++i) {
		x_binary = 1UL << i;
		if(x_binary & x) {
			result = result ^ shift_y[i];
		}
	}
	return result;
}

/**@fn void gf_region_multiby2_w64(unsigned char *region, int nbytes)
 * this function is same to the function of gf_region multiby2_w4() in w4.c.
 * And because it is 64-bit word size, so it need not to align to 64-bits
 */
void gf_region_multiby2_w64(unsigned char *region, int nbytes) {
	uint64_t *start, *end;
	unsigned char *length;

	length = region + nbytes;
	start = (uint64_t *) region;
	end = (uint64_t *) length;

	while(start < end) {
		*start = (*start << 1) ^ ((*start & 0x8000000000000000) ? prim64 :0);
		++*start;
	}
}
