#include "../multilib.h"
#include "../common.h"
#include "../w_x.h"

//this is to verify the w = 32's single multiplication;
int main(int argc, char *argv[]) {
	int a, b;
	printf("please input two integers:\n");
	scanf("%d%d", &a, &b);
	//printf("the answer is:%d\n", gf_split_w8_multi(a, b));
	printf("the answer is:%d\n", single_shift_multi_w32(a, b));
	return 1;
}
