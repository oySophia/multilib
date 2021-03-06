/**@file gf_table.h
 * This head file is a supplemental file to the w_x.h, which takes w into consideration in details.
 * Whereas this file is all about the log tables establishment .etc, namely,
 * it is used to complete the same part codes which is required by all forms of w values.
 *
 **/
//the gflog tables
//static int *gflog[33] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// 	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
//    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
     
//the gfilog tables
//static int *gfilog[33] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL,
// 	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
//	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
	   
//the externed multiply tables
//static int *gf_multi_tables[33] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL,
//    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
//	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };   


//this two function is the original ones of log and ilog tables
//int gf_create_tables_orig(int w); //we just can use the Huang's tables with the same range of 2^w + 2^w
int gf_logtable_multi_orig(int x, int y, int w);

/////this two functions is the aproach 2, which augment the expf table to 3 * nw[w], and eliminate the % operation
/**@fn int gf_create_tables(int w)
 * @brief log and ilog tables just for w < 30
 */
int gf_create_tables(int w);

/**@fn int gf_logtable_multi(int x, int y, int w)
 * @brief related functions with gf_create_tables, further fulfullment of gf_logtables multiplication
 */
int gf_logtable_multi(int x, int y, int w);

//this funciton is the approach 1, which use an &, shift etc. to eliminate the mod operation without augment the tables
int gf_create_tables_Huang(int w);
int gf_logtable_multi_Huang(int x, int y, int w);

//(approach 3)this two function is the optimized log and ilog algorithm to eliminate the mod operation and the branch operation.
int gf_create_tables_optimized(int w);
int gf_logtable_multi_optimized(int x, int y, int w);


/**@fn int gf_create_multi_tables(int w)
 * Multi_tables just for w <= 13. This function just applies log and ilog tables to complete the full-multiplication tables, which need much more space but less compute.
 */
int gf_create_multi_tables(int w);

/**@fn int gf_multitable_multi(int x, int y, int w)
 * @brief This function merely further completes the look step of full-multiplication table.
 */
int gf_multitable_multi(int x, int y, int w);

int gf_create_lr_multi_tbl(int w);
int gf_multi_lr_multi(int x, int y, int w);

/**@fn int gf_shift_multi(int x, int y, int w)
 * shift_multi can be for w <= 33, and when w = 64, it has been achieved in the file w64.c.
 * consideration the memory limitation, the space needing can be so tremendous that it can not be fulfillment when w > 33,
 * so this function doesn't use any table or look-up, it calculates the variable y's shifting values according to the every x-bit.
 */
int gf_shift_multi(int x, int y, int w);


int gf_single_div(int a, int b, int w);

void gf_invert_binary_matrix(int *mat, int *inv, int rows);

int gf_shift_inverse(int y, int w);
