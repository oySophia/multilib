#include "../multilib.h"
#include "../common.h"
#include "../w_x.h"

#define top (1 << 31)

//this is to verify the w = 32's single multiplication;
int main(int argc, char *argv[]) {
	unsigned int a, b;

	int n = 128;
	srand((unsigned)time(0));
	while(n) {
	//printf("please input two integers:\n");
	//scanf("%d%d", &a, &b);
	a = rand() % top;
	b = rand() % top;
	printf("a = %d, b = %d\n", a, b);
	printf("the split answer is:%d\n", single_split8_multi_w32(a, b));
	printf("the shift answer is:%d\n", single_shift_multi_w32(a, b));
	n--;
	}
	return 1;
}
