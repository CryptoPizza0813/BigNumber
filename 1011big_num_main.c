/**
 * Big Number Library
 * Developed by JangHyuck Choi & JaeHui In 
 * 2020-10-11
 * */
#include "1011big_num_header.h"

/**
 * NEED TO IMPLEMENT
 * 2진수 bi_show 오류 수정 필요
 * WORD_BITLEN 선택 구현 필요
 * 10진수 bi_show 구현 필요     --> ADD, MUL 구현 이후 작성할 예정.
 * bi_gen_rand 함수 오류 수정 필요
 * j-th bit 와 bit len 출력값 검증 필요
 * bi_delete의 free((*x)->a); 부분에서 코드가 죽어버림. bi_delete를 쓰는 함수들은 주석처리함.
 * bi_rand, bi_show(10진수), LeftShift, RightShift, Reduction 은 주석처리됨.

*/


int main()
{
    word arr[3] = {0x1234, 0x5678, 0x9abc};
    bigint teemo;
    bigint *teemo_p = &teemo;
    teemo.sign = NON_NEGATIVE;
    teemo.wordlen = 3;

    /*
    더블 포인터 구조체 참고
    mystruct actualThing;
    mystruct *pointer = &actualThing;
    mystruct **data = &pointer;
    myfunc(data);
    */

    printf("create big int\n");
    bi_new(&teemo_p, 3);
    printf("created\n\n");

    printf("set by array\n");
    bi_set_by_array(&teemo_p, teemo.sign, arr, teemo.wordlen);
    printf("set completed\n\n");

    printf("show big int\n");
    printf("show by base 2: ");
    bi_show(teemo_p, 2);    
    // printf("show by base 10: \n");   // ADD, MUL 구현 이후 제작할 예정
    // bi_show(teemo_p, 10);
    printf("show by base 16: ");
    bi_show(teemo_p, 16);
    printf("\n");

    // printf("bi_refine: \n");

    printf("Assign big int A <-- B \n");
    printf("show big int B: ");
    bi_show(teemo_p, 16);
    bigint teemo2;
    bigint* teemo2_p = &teemo2;
    bi_assign(&teemo2_p, teemo_p);
    printf("show assigned big int A: ");
    bi_show(teemo2_p, 16);
    printf("\n");

    printf("generate random bigint: ");
    bigint teemo3;
    bigint* teemo3_p = &teemo3;
    // bi_gen_rand(&teemo3_p, NON_NEGATIVE, 3); // wordlen 3인 양수의 랜덤 big int 생성
    // bi_show(teemo3_p, 16);

    printf("get word length: ");
    int wordlen = get_wordlen(teemo_p);    
    printf("%d", wordlen);
    printf("\n");

    printf("get bit length: ");
    int bitlen = get_bitlen(teemo_p);
    printf("%d", bitlen);
    printf("\n");

    printf("get j-th bit \n");
    // printf("enter j: ");
    int j = 3;
    // scanf("%d\n", j);
    j = get_jth_bit(teemo_p, j);
    // j가 비트 길이를 넘어서면 에러 메세지를 출력해야 함 --> 구현 필요
    printf("j-th bit: %d\n\n", j);

    printf("get sign and flip sign of big int\n");
    printf("sign of big int: %d\n", bi_get_sign(teemo_p));
    bi_flip_sign(&teemo_p);
    printf("flipped sign: %d\n\n", bi_get_sign(teemo_p));

    printf("big int set one, is one\n");
    bigint teemo4;
    bigint* teemo4_p;
    bi_assign(&teemo4_p, teemo_p);
    printf("before set one: ");
    bi_show(teemo4_p, 16);
    printf("is big int one: %d\n", is_one(teemo4_p));
    printf("after set one: ");
    bi_set_one(&teemo4_p);
    bi_show(teemo4_p, 16);
    printf("is big int one: %d\n\n", is_one(teemo4_p));

    printf("big int set zero, is zero\n");
    bigint teemo5;
    bigint* teemo5_p;
    bi_assign(&teemo5_p, teemo4_p);
    printf("before set zero: ");
    bi_show(teemo5_p, 16);
    printf("is big int zero: %d\n", is_zero(teemo5_p));
    printf("after set zero: ");
    bi_set_zero(&teemo5_p);
    bi_show(teemo5_p, 16);
    printf("is big int zero: %d\n\n", is_zero(teemo5_p));

    printf("compare big int\n");
    printf("big int A = ");
    bi_show(teemo4_p, 16);
    printf("big int B = ");
    bi_show(teemo5_p, 16);
    printf("print 1 if A > B: %d\n\n",Compare_AB(&teemo4_p, &teemo5_p));

    
    printf("left shift\nbefore left shift: ");
    bi_show(teemo4_p, 16);
    printf("after shift 4 bit: ");
    Left_Shift(&teemo4_p, 4);
    bi_show(teemo4_p, 16);

    printf("right shift\nbefore right shift: ");
    bi_show(teemo4_p, 16);
    printf("after shift 4 bit: ");
    Right_Shift(&teemo4_p, 4);
    bi_show(teemo4_p, 16);
    

    printf("big int reduction\nbefore reduction: ");
    Left_Shift(&teemo4_p, 4);
    bi_show(teemo4_p, 16);
    printf("after reduction by 2^4: ");
    Reduction(&teemo4_p, 4);
    bi_show(teemo4_p, 16);

    return 0;
}