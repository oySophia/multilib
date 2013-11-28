#include "../multilib.h"
#include "../common.h"
#include "../w_x.h"

#define top (1 << 8)

//testing the optimizing full-multiplication tables with left + right tables
int main(int agrc, char *argv[]) {
	int x, y;
	int n = 8;
	
	srand((unsigned) time(0));
	while(n) {
		x = rand() % top;
		y = rand() % top;
		printf("the x = %d, y = %d\n", x, y);
		printf("the optimizing ans = %d, the former ans = %d\n", single_multi_lrtbl_w8(x, y), single_multitable_w8(x, y));
		
		--n;
	}
	return 0;
}

