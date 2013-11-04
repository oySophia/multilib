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

//log and ilog tables just for w < 30
int gf_create_tables(int w);
int gf_logtable_multi(int x, int y, int w);

//multi_tables just for w <= 13
int gf_create_multi_tables(int w);
int gf_multitable_multi(int x, int y, int w);

//shift_multi can be for w <= 33, and when w = 64, it has been achieved in the file w64.c
int gf_shift_multi(int x, int y, int w);
