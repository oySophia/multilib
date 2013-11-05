//directly employing the gflog tables and gfilog tables
int single_logtable_multi_w4(int x, int y);
int single_logtable_multi_w8(int x, int y);
int single_logtable_multi_w16(int x, int y);
//int single_logtable_multi_w32(int x, int y);

//externing the gflog and gfilog tables to 2^w * 2^w size tables, namely multiply table
int single_multitable_w4(int x, int y);
int single_multitable_w8(int x, int y);

//such 2 funcitons are special for w = 32;
int gf_create_split_w8_tables();
//according to james's lib, it tends to use such function when have two numbers multiplicated;
int gf_split_w8_multi(int x, int y);//also a single_multi

//shifting multiply with detailed information given in the original fulfillment of the related functions
int single_shift_multi_w4(int x, int y);
int single_shift_multi_w8(int x, int y);
int single_shift_multi_w16(int x, int y);
int single_shift_multi_w32(int x, int y);

uint64_t gf_shift_multi_64(uint64_t x, uint64_t y);

//functions listed below are used in raid6----refer to the algorithm by paper
void gf_region_multiby2_w4(unsigned char *region, int nbytes);
void gf_region_multiby2_w4_64(unsigned char *region, int nbytes);

void gf_region_multiby2_w8(unsigned char *region, int nbytes);
void gf_region_multiby2_w8_64(unsigned char *region, int nbytes);

void gf_region_multiby2_w16(unsigned char *region, int nbytes);
void gf_region_multiby2_w16_64(unsigned char *region, int nbytes);

void gf_region_multiby2_w32(unsigned char *region, int nbytes);
void gf_region_multiby2_w32_64(unsigned char *region, int nbytes);

void gf_region_multiby2_w64(unsigned char *region, int nbytes);

//these funcitons are to make region multiplied by an integer, and such process uses the fastest single_multi function for each w
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
