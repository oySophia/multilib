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
 :* this function is same to the function of gf_region multiby2_w4() in w4.c.
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
		++start;
	}
}

void gf_invert_binary_matrix_64(uint64_t *mat, uint64_t *inv) {
	int i, j;
	uint64_t tmp;
	int rows, cols;
	rows = cols = 64;

	for(i = 0; i < cols; ++i) {
		inv[i] = (1UL << i);
	}

	for(i = 0; i < cols; ++i) {
		if((mat[i] & (1UL << i)) == 0) {
			for(j = i + 1; j < rows && (mat[j] & (1UL << i)) == 0; ++j);
			if(j == rows) {
				printf("i = %du, j = %u\n", i, j);
				fprintf(stderr, "gf_invert_matrix_64: matrix not invertible!!\n");
				exit(1);
			}
			tmp = mat[i];
			mat[i] = mat[j];
			mat[j] = tmp;
			tmp = inv[i];
			inv[i] = inv[j];
			inv[j] = tmp;
		}
		for(j = i + 1; j != rows; ++j) {
			if((mat[j] & (1UL << i)) != 0) {
				mat[j] ^= mat[i];
				inv[j] ^= inv[i];
			}
		}
	}
	for(i = rows - 1; i >= 0; --i) {
		for(j = 0; j < i; ++j) {
			if((mat[j] & (1UL << i))) {
				mat[j] ^= mat[i];
				inv[j] ^= inv[i];
			}
		}
	}

}


uint64_t gf_shift_inverse_64(uint64_t x) {
	uint64_t mat[64];
	uint64_t inv[64];
	int i;

	for(i = 0; i < 64; ++i) {
		mat[i] = x;
		if(x & 0x8000000000000000) {
			x = x << 1;
			x = x ^ prim64;
		} else {
			x = x << 1;
		}
	}
	gf_invert_binary_matrix_64(mat, inv);
	return inv[0];
}
