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

///the gflog tables
static int *gflog[33] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL,
   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
  
///the gfilog tables
static int *gfilog[33] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL,
   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };

///the externed multiply tables
static int *gf_multi_tables[33] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL,
   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };

/**@fn int gf_create_tables(int w)
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
		gflog[w][b] = log;
		gfilog[w][log] = gfilog[w][log + nw[w]]= b;
		b = b << 1;
		if(b & nw[w]) {
			b = (b ^ prim_poly[w]) & table_nw[w];
		}
	}
	for(log = 0; log < table_nw[w]; ++log) {
		gfilog[w][log + table_nw[w]] = gfilog[w][log];
		gfilog[w][log + 2 * table_nw[w]] = gfilog[w][log];
	}
	gfilog[w] += table_nw[w];
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
//	printf("the pointer addr: %d, log addr%d\n", gf_multi_tables[w], gflog[w]);
	if(gf_multi_tables[w] == NULL) {
		fprintf(stderr, "ERROR -- malloc gf_multi_tables[w] failed!\n");
		//free(gf_multi_tables[w]);
		return -1;
	}
	if(gflog[w] == NULL) {
		if(gf_create_tables(w) < 0) {
			free(gf_multi_tables[w]);
			gf_multi_tables[w] = NULL;
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
//	printf("4\n");
	++global_i;
//	printf("5\n");
	//for y != 0
	for(index_y = 1; index_y < nw[w]; ++index_y) {
		gf_multi_tables[w][global_i] = 0;
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
//		printf("%d\t", gf_multi_tables[w][global_i]);
		++global_i;
		logx = gflog[w][index_x];
		for(index_y = 1; index_y < nw[w]; ++index_y) {
			gf_multi_tables[w][global_i] = gfilog[w][logx + gflog[w][index_y]];
		
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























