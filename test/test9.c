#include "../multilib.h"
#include "../common.h"
#include "../w_x.h"

#define top (1 << 8)
#define n 4096

//testing the optimizing full-multiplication tables with left + right tables
int main(int agrc, char *argv[]) {
	int x[n], y[n], ans1[n], ans2[n];
	int i;
	now_time start, end;
	
	srand((unsigned) time(0));
	for(i = 0; i < n; ++i) {
		x[i] = rand() % top;
		y[i] = rand() % top;
	}
	single_logtable_multi_w8(x[0], y[0]);
	gettimeofday(&start, NULL);
	for(i = 0; i < n; ++i) {
		//ans1[i] = single_multi_lrtbl_w8(x[i], y[i]);
		ans2[i] = single_shift_multi_w8(x[i], y[i]);
	}
	gettimeofday(&end, NULL);
	printf("the single_multi_lrtbl need time is %.6f/s\n", (end.tv_sec - start.tv_sec) + (float)(end.tv_usec - start.tv_usec)/1000000);

	gettimeofday(&start, NULL);
	for(i = 0; i < n; ++i) {
		//ans2[i] = single_logtable_multi_w8(x[i], y[i]);
		ans1[i] = single_multi_lrtbl_w8(x[i], y[i]);
	}
	gettimeofday(&end, NULL);
	printf("the single_logtable multi need time is %.6f/s\n", (end.tv_sec - start.tv_sec) + (float)(end.tv_usec - start.tv_usec)/1000000);

	for(i = 0; i < n; ++i) {
		if(ans1[i] != ans2[i]) {
			printf("ans1 != ans2: %d != %d\n", ans1[i], ans2[i]);
			exit(1);
		}
	}
	printf("the logtable and optimizing full-table are all right!\n");

//		printf("the x = %d, y = %d\n", x, y);
//		printf("the optimizing ans = %d, the former ans = %d\n", single_multi_lrtbl_w16(x, y), single_shift_multi_w16(x, y));
//		
//		--n;
//	}
	return 0;
}

