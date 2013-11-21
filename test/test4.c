#include "../multilib.h"
#include "../w_x.h"
#include "../common.h"

//testing the functions of gf_region_multiby2_*() and gf_region_multiby2_*_64()
int main(int argc, char *argv[]) {
	now_time start, end;
	
	unsigned char *in_buff;
	unsigned char *out_buff;
	unsigned char *in_start, *length;
	unsigned long size_buff = 2048;

	in_buff = (unsigned char *) malloc (sizeof(char) * size_buff);
	out_buff = (unsigned char *) malloc (sizeof(char) * size_buff);

	in_start = in_buff;
	length = in_buff + size_buff;
	srand((unsigned) time(0));
	while(in_start < length) {
		*in_start = rand() % 16384;
		++in_start;
	}

	memcpy(out_buff, in_buff, size_buff);
	printf("--------------original ones----------------------------:\n");
	printf("in_buff:\n");
	mem_print(in_buff, 128, 8);
	printf("out_buff:\n");
	mem_print(out_buff, 128, 8);

	gettimeofday(&start, NULL);
	gf_region_multiby2_w32(in_buff, size_buff);
	gettimeofday(&end, NULL);
	printf("gf_region_multiby2_w4() need time is %.6f/s\n", (end.tv_sec - start.tv_sec) + (float)(end.tv_usec - start.tv_usec)/1000000);
	gettimeofday(&start, NULL);
	gf_region_multiby2_w32_64(out_buff, size_buff);
	gettimeofday(&end, NULL);
	printf("gf_region_multiby2_w4_64() need time is %.6f/s\n", (end.tv_sec - start.tv_sec) + (float)(end.tv_usec - start.tv_usec)/1000000);


	if(memcmp(in_buff, out_buff, size_buff) == 0) {
		printf("the answer is same\n");
	} else {
		printf("sth. wrong\n");
		printf("----------------now buff contents-----------------------:\n");
		printf("in_buff\n");
		mem_print(in_buff, 128, 8);
		printf("out_Buff\n");
		mem_print(out_buff, 128, 8);
	}

	free(in_buff);
	free(out_buff);
	return 1;
}



