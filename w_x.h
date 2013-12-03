/**@file w_x.h
 * This is a .h file contains all the functions completed considering the different values of w.
 * And it's the head included by the files of w4.c w8.c w16.c w32.c w64.c w128.c.
 * What's more, it is distinct to the other head files of gf_table.h and multilib.h.
 **/

/**@name single_ogtable_multiplication
 * directly employing the gflog tables and gfilog tables. such functions are fastest when 13 < w <= 29.
 */
///@{
int single_logtable_multi_w4(int x, int y);
int single_logtable_multi_w8(int x, int y);
int single_logtable_multi_w16(int x, int y);
///@}
//int single_logtable_multi_w32(int x, int y);

/**@name single_multitable mutiplication
 * externing the gflog and gfilog tables to 2^w * 2^w size tables, namely multiply table. such functions are fastest when w <= 13.
 */
///@{
int single_multitable_w4(int x, int y);
int single_multitable_w8(int x, int y);
///@}

int single_multi_lrtbl_w4(int x, int y);
int single_multi_lrtbl_w8(int x, int y);
int single_multi_lrtbl_w16(int x, int y);

/**@name galois split_w8 multiplication
 * such 2 funcitons are special for w = 32; it's much simple merely dividing the 32-bit to 4 8-bit trips, and the split_tables just have the eventual answers of trip by trip considering the high bits.
 * according to james's lib, it tends to use such function when have two numbers multiplicated;
 * such function is fastest when w = 32.
*/
///{@
int gf_create_split_w8_tables();
int gf_split_w8_multi(int x, int y);
int single_split8_multi_w32(int x, int y);
///@}

/**@name single_shift multiplication
 * shifting multiply with detailed information given in the original fulfillment of the related functions. such functions are w >= 30 except w = 30.
 */
///@{
int single_shift_multi_w4(int x, int y);
int single_shift_multi_w8(int x, int y);
int single_shift_multi_w16(int x, int y);
int single_shift_multi_w32(int x, int y);

uint64_t gf_shift_multi_64(uint64_t x, uint64_t y);
///@}


/**@name galois region muliplication by 2 functions and externed word-size to 64 using by 2 multiplication functions
 * functions listed below are used in raid6----refer to the algorithm by paper
 */
///@{
void gf_region_multiby2_w4(unsigned char *region, int nbytes);
void gf_region_multiby2_w4_64(unsigned char *region, int nbytes);

void gf_region_multiby2_w8(unsigned char *region, int nbytes);
void gf_region_multiby2_w8_64(unsigned char *region, int nbytes);

void gf_region_multiby2_w16(unsigned char *region, int nbytes);
void gf_region_multiby2_w16_64(unsigned char *region, int nbytes);

void gf_region_multiby2_w32(unsigned char *region, int nbytes);
void gf_region_multiby2_w32_64(unsigned char *region, int nbytes);

void gf_region_multiby2_w64(unsigned char *region, int nbytes);
///@}

/**@name galois_region multiplication
 * these funcitons are to make region multiplied by an integer, and such process uses the fastest single_multi function for each w
 */
///@{
void gf_region_multi_w8(unsigned char *region,
		int multiby,
		int nbytes,
		unsigned char *reslt,
		int add);

void gf_region_multi_w16(unsigned char *region,
		int multiby,
		int nbytes,
		unsigned char *reslt,
		int add);

void gf_region_multi_w32(unsigned char *region,
		int multiby,
		int nbytes,
		unsigned char *reslt,
		int add);
///@}


int gf_inverse_w4(int y);
int gf_inverse_w8(int y);
int gf_inverse_w16(int y);
int gf_inverse_w32(int y);

void gf_invert_binary_matrix_64(uint64_t *mat, uint64_t *inv);
uint64_t gf_shift_inverse_64(uint64_t x);
