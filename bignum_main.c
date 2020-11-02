/**
 * Big Number Library
 * Developed by JangHyuck Choi & JaeHui In 
 * 2020-11-02
 * */

#include "bignum_add_sub.c"

int main()
{
	word arr[3] = { 0x1234, 0x5678, 0x9abc };
	bigint* teemo = NULL;

	printf("create big int\n");
	bi_new(&teemo, 3);
	printf("created\n\n");

	printf("set by array\n");
	bi_set_by_array(&teemo, teemo->sign, arr, teemo->wordlen);
	printf("set completed\n\n");

	printf("show big int\n");
	printf("show by base 2: ");
	bi_show(teemo, 2);
	// printf("show by base 10: \n");   // ADD, MUL 구현 이후 제작할 예정
	// bi_show(teemo, 10);
	printf("show by base 16: ");
	bi_show(teemo, 16);
	printf("\n");

	// printf("bi_refine: \n");

	printf("Assign big int A <-- B \n");
	printf("show big int B: ");
	bi_show(teemo, 16);
	bigint* teemo2 = NULL;
	bi_assign(&teemo2, teemo);
	printf("show assigned big int A: ");
	bi_show(teemo2, 16);
	printf("\n");

	printf("get word length: ");
	int wordlen = get_wordlen(teemo);
	printf("%d", wordlen);
	printf("\n");

	printf("get bit length: ");
	int bitlen = get_bitlen(teemo);
	printf("%d\n", bitlen);
	printf("\n");

	printf("generate random bigint: ");
	bigint* teemo3 = NULL;
	bi_gen_rand(&teemo3, NON_NEGATIVE, 3); // wordlen 3인 양수의 랜덤 big int 생성
	bi_show(teemo3, 2);
	printf("\n");
	bi_show(teemo3, 16);

	printf("get j-th bit \n");
	// printf("enter j: ");
	int j_th = 4;
	// scanf("%d\n", j);
	int j = get_jth_bit(teemo, j_th);
	// j가 비트 길이를 넘어서면 에러 메세지를 출력해야 함 --> 구현 필요
	printf("%d-th bit: %d\n\n", j_th, j);

	printf("get sign and flip sign of big int\n");
	printf("sign of big int: %d\n", bi_get_sign(teemo));
	bi_flip_sign(&teemo);
	printf("flipped sign: %d\n\n", bi_get_sign(teemo));

	printf("big int set one, is one\n");
	bigint* teemo4 = NULL;
	bi_assign(&teemo4, teemo);
	printf("before set one: ");
	bi_show(teemo4, 16);
	printf("is big int one: %d\n", is_one(teemo4));
	printf("after set one: ");
	bi_set_one(&teemo4);
	bi_show(teemo4, 16);
	printf("is big int one: %d\n\n", is_one(teemo4));

	printf("big int set zero, is zero\n");
	bigint* teemo5 = NULL;
	bi_assign(&teemo5, teemo4);
	printf("before set zero: ");
	bi_show(teemo5, 16);
	printf("is big int zero: %d\n", is_zero(teemo5));
	printf("after set zero: ");
	bi_set_zero(&teemo5);
	bi_show(teemo5, 16);
	printf("is big int zero: %d\n\n", is_zero(teemo5));

	printf("compare big int\n");
	printf("big int A = ");
	bi_show(teemo4, 16);
	printf("big int B = ");
	bi_show(teemo5, 16);
	printf("print 1 if A > B: %d\n\n", Compare_AB(&teemo4, &teemo5));


	printf("left shift\nbefore left shift: ");
	bi_show(teemo4, 16);
	printf("after shift 4 bit: ");
	Left_Shift(&teemo4, 4);
	bi_show(teemo4, 16);
	printf("\n");

	printf("right shift\nbefore right shift: ");
	bi_show(teemo4, 16);
	printf("after shift 4 bit: ");
	Right_Shift(&teemo4, 4);
	bi_show(teemo4, 16);
	printf("\n");


	printf("big int reduction\nbefore reduction: ");
	Left_Shift(&teemo3, 4);
	bi_show(teemo3, 16);
	printf("after reduction by 2^4: ");
	Reduction(&teemo3, 15);
	bi_show(teemo3, 16);
	printf("\n");
	
	/*
	printf("big int add\nA: ");
	bi_show(teemo2, 16);
	printf("big int add\nB: ");
	bi_show(teemo3, 16);
	bi_add(teemo2, teemo3, &teemo4);	
	printf("A + B = ");
	bi_set_one(&teemo3);
	bi_show(teemo3, 16);
	bi_sub(&teemo3, &teemo3, &teemo4);
	bi_show(teemo4, 16);
	*/



	return 0;
}