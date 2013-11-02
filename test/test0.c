#include "../multilib.h"
#include "../w_x.h"

int main() {
	int a, b;
	while(1) {
	printf("input 2 intergers:\n");
	scanf("%d%d", &a, &b);

	printf("log : %d\n", single_logtable_multi_w4(a, b));
	printf("multitable :%d\n", single_multitable_w4(a, b));
	printf("shift :%d\n", single_shift_multi_w4(a, b));
	}
	return 1;
}
