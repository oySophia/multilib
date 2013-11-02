//directly employing the gflog tables and gfilog tables
int single_logtable_multi_w4(int x, int y);
int single_logtable_multi_w8(int x, int y);
int single_logtable_multi_w16(int x, int y);
//int single_logtable_multi_w32(int x, int y);

//externing the gflog and gfilog tables to 2^w * 2^w size tables, namely multiply table
int single_multitable_w4(int x, int y);
int single_multitable_w8(int x, int y);

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
