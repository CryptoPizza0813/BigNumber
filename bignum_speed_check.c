#include "bignum_speed_check.h"

// clock_t start = clock();
// clock_t end = clock();
// printf("Time : %lf\n", (double)(end - start) / CLOCKS_PER_SEC);

void speed_check()
{
	while(1) {
		int select;
		printf("Select a function to check speed\n");
		printf("1. ADD\n2. SUB\n3. schoolbook MUL\n");
        printf("4. karatsuba MUL\n5. schoolbook SQUARING\n6.karatsuba SQUARING\n");
        printf("7. binary-long-division\n8. multi-precision-division\n9. EXIT\n");
		printf("Select: ");
		scanf("%d", select);
		switch (select) {
			case 1:
				add_speed();
				break;
			case 2:
				sub_speed();
				break;	
			case 3:
				schoolbook_mul_speed();
				break;
			case 4:
				karatsuba_mul_speed();
				break;
			case 5:
				Schoolbook_Squaring_speed();
				break;
			case 6:
                Karatsuba_Squaring_speed();
				break;
            case 7:
                Binary_Long_Division_speed();
                break;
            case 8:
                Multiprecision_Division_speed();
                break;
            case 9: 
                break;
			default:
				printf("You choose wrong number\n");
				break;
	
			if(select == 9)
				break;
		}
	}

}



void add_speed()
{
    int check;  // 테스트 데이터 쌍 개수
    int first_number_wordlen;   // 첫번째 bigint의 워드길이
    int second_number_wordlen;  // 두번째 bigint의 워드길이

    printf("Enter number for checks: ");
    scanf("%d", &check);
    printf("Enter number for first number's wordlen: ");
    scanf("%d", &first_number_wordlen);
    printf("Enter number for second number's wordlen: ");
    scanf("%d", &second_number_wordlen);

    bigint* A = NULL;
    bigint* B = NULL;
    bigint* C = NULL;
    bi_gen_rand(&A, 0, first_number_wordlen);
    bi_gen_rand(&B, 0, second_number_wordlen);

    clock_t start, end; // 시간 측정용 변수

    start = clock();    // 측정 시작
    for(int i = 0; i < check / 3; i++){
        bi_add(A, B, &C);   
        bi_add(C, A, &B);
        bi_add(B, C, &A);
    }
    end = clock();      // 측정 종료

    printf("Add function Time: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);

    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}

void sub_speed()
{
    int check;  // 테스트 데이터 쌍 개수
    int first_number_wordlen;   // 첫번째 bigint의 워드길이
    int second_number_wordlen;  // 두번째 bigint의 워드길이

    printf("Enter number for checks: ");
    scanf("%d", &check);
    printf("Enter number for first number's wordlen: ");
    scanf("%d", &first_number_wordlen);
    printf("Enter number for second number's wordlen: ");
    scanf("%d", &second_number_wordlen);

    bigint* A = NULL;
    bigint* B = NULL;
    bigint* C = NULL;
    bi_gen_rand(&A, 0, first_number_wordlen);
    bi_gen_rand(&B, 0, second_number_wordlen);

    clock_t start, end; // 시간 측정용 변수

    start = clock();    // 측정 시작
    for(int i = 0; i < check / 3; i++) {
        bi_sub(A, B, &C);   
        bi_sub(C, A, &B);
        bi_sub(B, C, &A);
    }
    end = clock();

    printf("Sub function Time: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);

    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
    
}


void schoolbook_mul_speed()
{
    int check;  // 테스트 데이터 쌍 개수
    int first_number_wordlen;   // 첫번째 bigint의 워드길이
    int second_number_wordlen;  // 두번째 bigint의 워드길이

    printf("Enter number for checks: ");
    scanf("%d", &check);
    printf("Enter number for first number's wordlen: ");
    scanf("%d", &first_number_wordlen);
    printf("Enter number for second number's wordlen: ");
    scanf("%d", &second_number_wordlen);

    bigint* A = NULL;
    bigint* B = NULL;
    bigint* C = NULL;
    bi_gen_rand(&A, 0, first_number_wordlen);
    bi_gen_rand(&B, 0, second_number_wordlen);

    clock_t start, end; // 시간 측정용 변수

    start = clock();    // 측정 시작
    for(int i = 0; i < check; i++) {
        bi_mul(A, B, &C);
    }
    end = clock();

    printf("Schoolbook multiplication Time: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);

    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}

void karatsuba_mul_speed()
{
    int check;  // 테스트 데이터 쌍 개수
    int first_number_wordlen;   // 첫번째 bigint의 워드길이
    int second_number_wordlen;  // 두번째 bigint의 워드길이

    printf("Enter number for checks: ");
    scanf("%d", &check);
    printf("Enter number for first number's wordlen: ");
    scanf("%d", &first_number_wordlen);
    printf("Enter number for second number's wordlen: ");
    scanf("%d", &second_number_wordlen);

    bigint* A = NULL;
    bigint* B = NULL;
    bigint* C = NULL;
    bi_gen_rand(&A, 0, first_number_wordlen);
    bi_gen_rand(&B, 0, second_number_wordlen);

    clock_t start, end; // 시간 측정용 변수

    start = clock();    // 측정 시작
    for(int i = 0; i < check; i++) {
        bi_kmulc(A, B, &C);
    }
    end = clock();

    printf("Karatsuba multiplication Time: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);

    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&C);
}

void Schoolbook_Squaring_speed()
{
    int check;  // 테스트 데이터 쌍 개수
    int first_number_wordlen;   // 첫번째 bigint의 워드길이

    printf("Enter number for checks: ");
    scanf("%d", &check);
    printf("Enter number for first number's wordlen: ");
    scanf("%d", &first_number_wordlen);

    bigint* A = NULL;
    bigint* B = NULL;
    bi_gen_rand(&A, 0, first_number_wordlen);

    clock_t start, end; // 시간 측정용 변수

    start = clock();
    for(int i = 0; i < check; i++){
        bi_squaring(A, &B);
    }
    end = clock();

    printf("Schoolbook Squaring Time: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);

    bi_delete(&A);
    bi_delete(&B);    

}

void Karatsuba_Squaring_speed()
{
    int check;  // 테스트 데이터 쌍 개수
    int first_number_wordlen;   // 첫번째 bigint의 워드길이

    printf("Enter number for checks: ");
    scanf("%d", &check);
    printf("Enter number for first number's wordlen: ");
    scanf("%d", &first_number_wordlen);

    bigint* A = NULL;
    bigint* B = NULL;
    bi_gen_rand(&A, 0, first_number_wordlen);

    clock_t start, end; // 시간 측정용 변수

    start = clock();
    for(int i = 0; i < check; i++){
        bi_ksquaringC(A, &B);
    }
    end = clock();

    printf("Karatsuba Squaring Time: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);

    bi_delete(&A);
    bi_delete(&B);
}

void Binary_Long_Division_speed()
{
    int check;  // 테스트 데이터 쌍 개수
    int first_number_wordlen;   // 첫번째 bigint의 워드길이
    int second_number_wordlen;  // 두번째 bigint의 워드길이

    printf("Enter number for checks: ");
    scanf("%d", &check);
    printf("Enter number for first number's wordlen: ");
    scanf("%d", &first_number_wordlen);
    printf("Enter number for second number's wordlen: ");
    scanf("%d", &second_number_wordlen);

    bigint* A = NULL;
    bigint* B = NULL;
    bigint* Q = NULL;
    bigint* R = NULL;
    bi_gen_rand(&A, 0, first_number_wordlen);
    bi_gen_rand(&B, 0, second_number_wordlen);

    clock_t start, end; // 시간 측정용 변수

    start = clock();    // 측정 시작
    for(int i = 0; i < check; i++) {
        Binary_Long_Division(A, B, &Q, &R);
    }
    end = clock();

    printf("Binary Lond Division Time: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);

    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&Q);
    bi_delete(&R);

}


void Multiprecision_Division_speed()
{
    int check;  // 테스트 데이터 쌍 개수
    int first_number_wordlen;   // 첫번째 bigint의 워드길이
    int second_number_wordlen;  // 두번째 bigint의 워드길이

    printf("Enter number for checks: ");
    scanf("%d", &check);
    printf("Enter number for first number's wordlen: ");
    scanf("%d", &first_number_wordlen);
    printf("Enter number for second number's wordlen: ");
    scanf("%d", &second_number_wordlen);

    bigint* A = NULL;
    bigint* B = NULL;
    bigint* Q = NULL;
    bigint* R = NULL;
    bi_gen_rand(&A, 0, first_number_wordlen);
    bi_gen_rand(&B, 0, second_number_wordlen);

    clock_t start, end; // 시간 측정용 변수

    start = clock();    // 측정 시작
    for(int i = 0; i < check; i++) {
        DIV(A, B, &Q, &R);
    }
    end = clock();

    printf("Multi-precision Division Time: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);

    bi_delete(&A);
    bi_delete(&B);
    bi_delete(&Q);
    bi_delete(&R);

}

