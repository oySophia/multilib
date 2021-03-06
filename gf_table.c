#include "multilib.h"
#include "gf_table.h"

///the prim_polys, transferred into binary, are listed to the w.
static int prim_poly[33] =                                                                                                                         
{ 0, 
  /*  1 */     1, 
  /*  2 */    07,
  /*  3 */    013,
  /*  4 */    023,
  /*  5 */    045,
  /*  6 */    0103,
  /*  7 */    0211,
  /*  8 */    0435,
  /*  9 */    01021,
  /* 10 */    02011,
  /* 11 */    04005,
  /* 12 */    010123,
  /* 13 */    020033,
  /* 14 */    042103,
  /* 15 */    0100003,
  /* 16 */    0210013,
  /* 17 */    0400011,
  /* 18 */    01000201,
  /* 19 */    02000047,
  /* 20 */    04000011,
  /* 21 */    010000005,
  /* 22 */    020000003,
  /* 23 */    040000041,
  /* 24 */    0100000207,
  /* 25 */    0200000011,
  /* 26 */    0400000107,
  /* 27 */    01000000047,
  /* 28 */    02000000011,
  /* 29 */    04000000005,
  /* 30 */    010040000007,
  /* 31 */    020000000011, 
  /* 32 */    00020000007 }; 

///the total number refers to the wordsize w
static int nw[33] = { 0, (1 << 1), (1 << 2), (1 << 3), (1 << 4), 
	(1 << 5), (1 << 6), (1 << 7), (1 << 8), (1 << 9), (1 << 10),
    (1 << 11), (1 << 12), (1 << 13), (1 << 14), (1 << 15), (1 << 16),
    (1 << 17), (1 << 18), (1 << 19), (1 << 20), (1 << 21), (1 << 22),
    (1 << 23), (1 << 24), (1 << 25), (1 << 26), (1 << 27), (1 << 28),
    (1 << 29), (1 << 30), (1 << 31), -1 };

///with w-wordsize, the total table size
static int table_nw[33] = { 0, (1 << 1)-1, (1 << 2)-1, (1 << 3)-1, (1 << 4)-1, 
    (1 << 5)-1, (1 << 6)-1, (1 << 7)-1, (1 << 8)-1, (1 << 9)-1, (1 << 10)-1,
    (1 << 11)-1, (1 << 12)-1, (1 << 13)-1, (1 << 14)-1, (1 << 15)-1, (1 << 16)-1,
    (1 << 17)-1, (1 << 18)-1, (1 << 19)-1, (1 << 20)-1, (1 << 21)-1, (1 << 22)-1,
    (1 << 23)-1, (1 << 24)-1, (1 << 25)-1, (1 << 26)-1, (1 << 27)-1, (1 << 28)-1,
    (1 << 29)-1, (1 << 30)-1, 0x7fffffff, 0xffffffff };

///the original gfilog tables
//static int *gflog_orig[33] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL,
 //  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  // NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };

///the original gfilog tables
//static int *gfilog_orig[33] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
//   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
//   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
//

///the gflog tables
static int *gflog[33] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL,
   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
  
///the gfilog tables
static int *gfilog[33] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };

///the HUang's gflog tables
static int *gflog_Huang[33] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL,
   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }; 

///the Huang's gfilog tables
static int *gfilog_Huang[33] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL,
   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };

///the optimized gflog tables
static int *gflog_optimized[33] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL,
   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
   
///the optimized gfilog tables
static int *gfilog_optimized[33] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL,
   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };


///the externed multiply tables
static int *gf_multi_tables[33] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL,
   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };

static int *gf_div_tables[33] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL,
   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };

///The optimizing of the full multiplication table
static int *gf_multi_left_tbl[33] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL,
   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

static int *gf_multi_right_tbl[33] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL,
   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};


//int gf_create_tables_orig(int w) {
//}

//int gf_logtable_multi_orig(int w, int x, int y) {
//}



/**@fn int gf_create_tables(int w) --------similiar to the aproach 2
 * @brief create gflog tables and gfilog tables with the vented w.
 */
int gf_create_tables(int w) {
	int b, log;
	if(w > 30) {
		return -1;
	}
	if(gflog[w] != NULL) {
		return 0;
	}

	gflog[w] = (int *) malloc (sizeof(int) * nw[w]);
	gfilog[w] = (int *) malloc (sizeof(int) * nw[w] * 3);
	if((gflog[w] == NULL) || (gfilog[w] == NULL)) {
		fprintf(stderr, "ERROR -- malloc gflog or gfilog tables failed!\n");
		//free(gflog[w]);
		//free(gflog[w]);
		return -1;
	}

	for(log = 0; log < nw[w]; ++log) {
		gflog[w][log] = table_nw[w];
		gfilog[w][log] = 0;
	}

	b = 1;
	for(log = 0; log < table_nw[w]; ++log) {
		if(gflog[w][b] != table_nw[w]) {
			fprintf(stderr, "ERROR -- gf_create_tables() error: log = %d, b = %d, w = %d\n", log, b, w);
			exit(1);
		}
		gflog[w][b] = log;
		gfilog[w][log] = b;
		b = b << 1;
		if(b & nw[w]) {
			b = (b ^ prim_poly[w]) & table_nw[w];
		}
	}
	for(log = 0; log < table_nw[w]; ++log) {
		gfilog[w][log + table_nw[w]] = gfilog[w][log];
		gfilog[w][log + 2 * table_nw[w]] = gfilog[w][log];
	}
	gfilog[w] += table_nw[w]; //to move the addr of the table of size of table_nw[w]
	return 1;
}

//(approach 1)this technique is proposed by Huang and Xu(PRECOMPUTATION thoughts) to optimize the original log and ilog multiplications. it eliminates the mod operation which need much more time than merely look-up operations.
int gf_create_tables_Huang(int w) {
   	int b, log;
    if(w > 30) {
		return -1;
    }    
    if(gflog_Huang[w] != NULL) {
		return 0;
    }    
          
	gflog_Huang[w] = (int *) malloc (sizeof(int) * nw[w]);
	gfilog_Huang[w] = (int *) malloc (sizeof(int) * nw[w]);
    if((gflog_Huang[w] == NULL) || (gfilog_Huang[w] == NULL)) {
		fprintf(stderr, "ERROR -- malloc gflog_Huang or gfilog_Huang tables failed!\n");
		//free(gflog[w]);
		////free(gflog[w]);
		return -1;
	}    
	          
	for(log = 0; log < nw[w]; ++log) {
	    gflog_Huang[w][log] = table_nw[w];                                                                                                                
		gfilog_Huang[w][log] = 0;
   	}	
          
    b = 1;
    for(log = 0; log < table_nw[w]; ++log) {
    	if(gflog_Huang[w][b] != table_nw[w]) {
        	fprintf(stderr, "ERROR -- gf_create_tables_Huang() error: log = %d, b = %d, w = %d\n", log, b, w);
			exit(1);
		}  
		gflog_Huang[w][b] = log;
		gfilog_Huang[w][log] = b;
		b = b << 1;
		if(b & nw[w]) {
	 		b = (b ^ prim_poly[w]) & table_nw[w];
		}  
	}
	gfilog_Huang[w][table_nw[w]] = gfilog_Huang[w][0];//the augment of the expf table to eliminate mod operations
	gfilog_Huang[w] += table_nw[w];
	//for(log = 0; log < table_nw[w]; ++log) {
	//	gfilog[w][log + table_nw[w]] = gfilog[w][log];
	//	gfilog[w][log + 2 * table_nw[w]] = gfilog[w][log];
 	//}    
    //gfilog_Huang[w] += table_nw[w];
    return 1;
}        


/**@fn int gf_logtable_multi(int x, int y, int w)
 * @brief single multiply with directly using of gflog tables and gfilog tables
 */
int gf_logtable_multi(int x, int y, int w) {
	int sum;
	if(x == 0 || y == 0) {
		return 0;
	}
	
	if(gflog[w] == NULL) {
		if(gf_create_tables(w) < 0) {
			fprintf(stderr, "ERROR -- cannot make log tables for w = %d\n", w);
			exit(1);
		}
	}
	
	sum = gflog[w][x] + gflog[w][y];
	return gfilog[w][sum];
}

int gf_logtable_multi_Huang(int x, int y, int w) {
	if(x == 0 || y == 0) {
		return 0;
	}
	if(gflog_Huang[w] == NULL) {
		if(gf_create_tables_Huang(w) < 0) {
			fprintf(stderr, "ERROR -- cannot make Huang's log tables for w = %d\n", w);
			exit(1);
		}
	}
	return gfilog_Huang[w][((gflog_Huang[w][x] + gflog_Huang[w][y]) & table_nw[w]) + ((gflog_Huang[w][x] + gflog_Huang[w][y]) >> w)];
}

//the log and ilog tables created are the same, with 2^w + 2^w, whereas it lies on the mod operation;
int gf_logtable_multi_orig(int x, int y, int w) {
	if(x == 0 || y == 0) {
		return 0;
	}
	if(gflog_Huang[w] == NULL) {
		if(gf_create_tables_Huang(w) < 0) {
			fprintf(stderr, "ERROR -- cannot make Huang's log tables for the original used with w = %d\n", w);
			exit(1);
		}
	}
	return gfilog_Huang[w][(gflog_Huang[w][x] + gflog_Huang[w][y]) % table_nw[w]];
}


int gf_create_tables_optimized(int w) {
	int b, log;
	if(w > 30) {
		return -1;
	}
	if(gflog_optimized[w] != NULL) {
		return 0;
	}

	gflog_optimized[w] = (int *) malloc (sizeof(int) * nw[w]);
	gfilog_optimized[w] = (int *) malloc (sizeof(int) * nw[w] * 4);

	if((gflog_optimized[w] == NULL) || (gfilog_optimized[w] == NULL)) {
		fprintf(stderr, "ERROR -- malloc gflog_optimized of glilog _optimized failed with w = %d\n", w);
		return -1;
	}

	for(log = 0; log < nw[w]; ++log) {
		gflog_optimized[w][log] = 2 * table_nw[w];
		gfilog_optimized[w][log] = 0;
	}

	b = 1;
	for(log = 0; log < table_nw[w]; ++log) {
		if(gflog_optimized[w][b] != 2 * table_nw[w]) {
			fprintf(stderr, "ERROR -- gf_create_tables_optimized() error\n");
			exit(1);
		}
		gflog_optimized[w][b] = log;
		gfilog_optimized[w][log] = b;
		b = b << 1;
		if(b & nw[w]) {
			b = (b ^ prim_poly[w]) & table_nw[w];
		}
	}
	
	for(log = 0; log < table_nw[w]; ++log) {
		gfilog_optimized[w][log + table_nw[w]] = gfilog_optimized[w][log];
	}
	
	b = 4 * nw[w];
	for(log = 2 * table_nw[w]; log < b; ++log) { //taking the 0 into consideration, and eliminate the branch of if(x == 0 || y == 0) .....
		gfilog_optimized[w][log] = 0;
	}
	gfilog_optimized[w] += table_nw[w];
	return 1;
}

int gf_logtable_multi_optimized(int x, int y, int w) {
	if(gflog_optimized[w] == NULL) {
		if(gf_create_tables_optimized(w) < 0) {
			fprintf(stderr, "ERROR -- cannot make the gf_create_tables of optimized\n");
			exit(1);
		}
	}

	return gfilog_optimized[w][gflog_optimized[w][x] + gflog_optimized[w][y]];
}



/**@fn gf_create_multi_tables(int w)
 * @brief this part's function is try to extern the multiply-tables to 2^w * 2^w, and sacrifice the space for little caculating. With such function, we can just look up the tables with values of x and y
 */
int gf_create_multi_tables(int w) {
	int global_i, index_x, index_y, logx;

	if(w >= 14) {
		return -1;
	}

	if(gf_multi_tables[w] != NULL) {
		return 0;
	}

	gf_multi_tables[w] = (int *) malloc (sizeof(int) * nw[w] * nw[w]);
	gf_div_tables[w] = (int *) malloc (sizeof(int) * nw[w] * nw[w]);
//	printf("the pointer addr: %d, log addr%d\n", gf_multi_tables[w], gflog[w]);
	if(gf_multi_tables[w] == NULL || gf_div_tables[w] == NULL) {
		fprintf(stderr, "ERROR -- malloc gf_multi_tables[w] failed!\n");
		//free(gf_multi_tables[w]);
		return -1;
	}
	if(gflog[w] == NULL) {
		if(gf_create_tables(w) < 0) {
			free(gf_multi_tables[w]);
			free(gf_div_tables[w]);
			gf_multi_tables[w] = NULL;
			gf_div_tables[w] = NULL;
			return -1;
		}
	}
	//printf("1\n");
	//printf("2\n");

	//set the multi tables for x = 0;
	global_i = 0;
	//printf("3\n");
	//printf("the pointer addr: %d, log addr %d\n", gf_multi_tables[w], gflog[w]);
	gf_multi_tables[w][global_i] = 0; //y = 0
	gf_div_tables[w][global_i] = -1;
//	printf("4\n");
	++global_i;
//	printf("5\n");
	//for y != 0
	for(index_y = 1; index_y < nw[w]; ++index_y) {
		gf_multi_tables[w][global_i] = 0;
		gf_div_tables[w][global_i] = -1;
//		printf("%d\n", gf_multi_tables[w]);
	//
//		printf("%d\t", gf_multi_tables[w][gf_multi_tables[w][global_i]]);
		++global_i;
	}
	//printf("\n");

	//printf("1\n");

	//set the multi tables for x > 0;
	for(index_x = 1; index_x < nw[w]; ++index_x) {
		gf_multi_tables[w][global_i] = 0;
		gf_div_tables[w][global_i] = -1;
//		printf("%d\t", gf_multi_tables[w][global_i]);
		++global_i;
		logx = gflog[w][index_x];
		for(index_y = 1; index_y < nw[w]; ++index_y) {
			gf_multi_tables[w][global_i] = gfilog[w][logx + gflog[w][index_y]];
			gf_div_tables[w][global_i] = gfilog[w][logx - gflog[w][index_y]];
//			printf("%d\t", gf_multi_tables[w][global_i]);
			++global_i;
		}
//		printf("\n");
	}

	//printf("1\n");
	return 0;
}	

/**@fn int gf_multitable_multi(int x, int y, int w)
 * @brief this function just complete the single ones multiplication using gf_multi_tables.
 */
int gf_multitable_multi(int x, int y, int w) {
	if(gf_multi_tables[w] == NULL) {
		if(gf_create_multi_tables(w) < 0) {
			fprintf(stderr, "ERROR -- cannot make gf_multi_tables for w = %d\n", w);
		    exit(1);
		 }
	  }

	return gf_multi_tables[w][(x << w) | y];
} 

int gf_create_lr_multi_tbl(int w) {
	int i, index_x, index_y, logx_left, logx_right;
	int half;

	if(w >= 18) { //if w is too big, the mem. cannot hold all the tables
		return -1;
	}

	if(gf_multi_left_tbl[w] != NULL) { //if the multi lr tables already exists, then there is no need to go on
		return 0;
	}

	half = (1 << (w / 2));
	gf_multi_left_tbl[w] = (int *) malloc (sizeof(int) * nw[w] * half);
	gf_multi_right_tbl[w] = (int *) malloc (sizeof(int) * nw[w] * half);

	if(gf_multi_left_tbl[w] == NULL || gf_multi_right_tbl[w] == NULL) {
		fprintf(stderr, "ERROR -- malloc of gf double tables failed in file gf_tables!\n");
		return -1;
	}
	if(gflog[w] == NULL) {
		if(gf_create_tables(w) < 0) {
			free(gf_multi_left_tbl[w]);
			free(gf_multi_right_tbl[w]);
			gf_multi_left_tbl[w] = NULL;
			gf_multi_right_tbl[w] = NULL;
			return -1;
		}
	}

	//when x = 0;
	i = 0;
	gf_multi_left_tbl[w][i] = 0;
	gf_multi_right_tbl[w][i] = 0;
	
	++i;

	for(index_y = 1; index_y < nw[w]; ++index_y) {
		gf_multi_left_tbl[w][i] = 0;
		gf_multi_right_tbl[w][i] = 0;
		++i;
	}
	//printf("1\n");

	for(index_x = 1; index_x < half; ++index_x) {

		gf_multi_left_tbl[w][i] = 0; //when y = 0
		gf_multi_right_tbl[w][i] = 0;
		++i;
		logx_right = gflog[w][index_x]; //the least significant bits
		logx_left = gflog[w][index_x << (w / 2)]; //the most significant bits
		for(index_y = 1; index_y < nw[w]; ++index_y) {
			gf_multi_right_tbl[w][i] = gfilog[w][logx_right + gflog[w][index_y]];
			gf_multi_left_tbl[w][i] = gfilog[w][logx_left + gflog[w][index_y]];
			++i;
		}
	}
	//printf("2\n");
	return 0;
}

int gf_multi_lr_multi(int x, int y, int w) {
	int x_left, x_right;
	int half;
	if(gf_multi_left_tbl[w] == NULL) {
		if(gf_create_lr_multi_tbl(w) < 0) {
			fprintf(stderr, "ERROR -- cannot make gf_create_lr_multi_tbl functions!\n");
			exit(1);
		}
	}

	half = (w / 2);
	x_left = x >> (half);
	x_right = (x_left << (half)) ^ x;
	return gf_multi_left_tbl[w][(x_left << w) | y] ^ gf_multi_right_tbl[w][(x_right << w) | y];
}




/**@fn
 * @brief this shift function is a bit different with the table-looking-up ones, following the traditional multiply way: binary x and * y bit by bit with transfer such proccess to a y-shifting with MOD the prim_poly.
 */
int gf_shift_multi(int x, int y, int w) {
	int result = 0;
	int i, x_binary, shift_y[33];

	//firstly get y * 2^i in gf(2^w) by shifting y and moding the prim_poly
	for(i = 0; i < w; ++i) {
		shift_y[i] = y;
		if(y & (1 << (w - 1))) {
			y = y << 1;
			y = (y ^ prim_poly[w]) & table_nw[w];
		} else {
			y = y << 1;
		}
	}

	//then we can binary x, and check if i-th is 1 or 0, if it is 1, it means y must multiply the 2^w
	for(i = 0; i < w; ++i) {
		x_binary = (1 << i);
		if(x_binary & x) {
			result = result ^ shift_y[i];
		}
	}
	return result;
}

//just for 1 <= w <= 22
int gf_single_div(int a, int b, int w) {
	int sum;
	if(w <= 9 && w >= 1) {
		if(gf_div_tables[w] == NULL) {
			if(gf_create_multi_tables(w) < 0) {
				fprintf(stderr, "ERROR -- cannot make multiplication tables for w=%d\n", w);
				exit(1);
			}
		}
		return gf_div_tables[w][(a << w) | b];
	} else if(w <= 22 && w > 9) {
		if(b == 0) return -1;
		if(a == 0) return 0;
		if(gflog[w] == NULL) {
			if(gf_create_tables(w) < 0) {
				fprintf(stderr, "ERROR -- cannot make log tables for w=%d\n", w);
				exit(1);
			}
		}
		sum = gflog[w][a] - gflog[w][b];
		return gfilog[w][sum];
	} else {
		//if(b == 0) return -1;
		//if(a == 0) return 0;
		//sum = gf_inverse(b, w);
		//return gf_shift_multi(a, sum, w);
	//}
		fprintf(stderr, "gf_single_divide - no implementation for w = %d\n", w);
		exit(1);
	}
}
		

void gf_invert_binary_matrix(int *mat, int *inv, int rows) {
	int cols, i, j;
	int tmp;

	cols = rows;

	for(i = 0; i < rows; ++i) {
		inv[i] = (1 << i);
	}
	//operations on columns
	for(i = 0; i < cols; ++i) {
		if((mat[i] & (1 << i)) == 0) { //the 最高位是否是0，也就是对应的数值的二进制中是否有0值，如果有，交换，否则是不可能invertible的
			for(j = i + 1; j < rows && (mat[j] & (1 << i)) == 0; ++j);
			if(j == rows) {
				fprintf(stderr, "gf_invert_matrix: matrix not invertible!!\n");
				exit(1);
			}
			tmp = mat[i];
		   	mat[i] = mat[j];
			mat[j] = tmp;
			tmp = inv[i];
			inv[i] = inv[j];
			inv[j] = tmp;
		}
		//for each j > i, add a_ji * ai to aj
		for(j = i + 1; j != rows; ++j) {
			if((mat[j] & (1 << i)) != 0) {
				mat[j] ^= mat[i];
				inv[j] ^= inv[i];
			}
		}
	}
	//upper triangular, start at the top and multiply down
	for(i = rows - 1; i >= 0; --i) {
		for(j = 0; j < i; ++j) {
			if(mat[j] & (1 << i)) {
				inv[j] ^= inv[i];
			}
		}
	}

	return ;
}

int gf_shift_inverse(int y, int w) {
	int mat[32];// 23 <= w <= 32
	int inv[32];
	int i;

	for(i = 0; i < w; ++i) {
		mat[i] = y;
		if(y & nw[w - 1]) {
			y = y << 1;
			y = (y ^ prim_poly[w]) & table_nw[w];
		} else {
			y = y << 1;
		}
	}
	gf_invert_binary_matrix(mat, inv, w);
	return inv[0];
}
