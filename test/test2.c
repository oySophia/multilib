#include "../multilib.h"
#include "../w_x.h"
#include "../common.h"

#define SIZE 128
#define limit (1 << 8)

//this is to ensure single multiplication for w = 4, 8, 16(logtable, multi-full table, shift)
int main(int argc, char *argv[]) {
	//now_time start, end;
	
	unsigned int x[SIZE], y[SIZE];
	//unsigned int ans1[SIZE], ans2[SIZE];
	unsigned int ans1, ans2;

	int i = SIZE;
	srand((unsigned)time(0));
	while(i) {
		x[i - 1] = rand() % (limit);
		y[i - 1] = rand() % (limit);
		--i;
	}
	for(i = 0; i < SIZE; ++i) {
		ans1 = single_logtable_multi_w8(x[i], y[i]);
		ans2 = single_multitable_w8(x[i], y[i]);
		if(ans1 - ans2 != 0) {
			printf("such two methods has sth. wrong!\n");
			printf("x = %u, y = %u, log_ans = %u, multi_ans = %u\n", x[i], y[i], ans1, ans2);
			break;
		}
	}
	if(i - SIZE == 0) {
		printf("BINGO!\n");
	}
	return 1;
}
	

	
	
