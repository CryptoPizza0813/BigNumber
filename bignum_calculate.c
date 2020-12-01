#include "bignum_calculate.h"

void calculate_bignumber()
{
	while(1) {
		int select;
		printf("Select a function to execute\n");
		printf("1. ADD\n2. SUB\n3. MUL\n4. DIV\n5. MOD_EXP\n6. EXIT\n");
		printf("Select: ");
		scanf("%d", select);
		switch (select) {
			case 1:
				calculate_add();
				break;
			case 2:
				calculate_sub();
				break;	
			case 3:
				calculate_mul();
				break;
			case 4:
				calculate_div();
				break;
			case 5:
				calculate_mod_exp();
				break;
			case 6:
				break;
			default:
				printf("You choose wrong number\n");
				break;
	
			if(select == 6)
				break;
		}
	}

}

void calculate_add()
{
	printf("Choose string base size\n");
	printf("1. Base 2\n2. Base 10\n3. Base 16\n");
	printf("Enter frist big number by string: ");
	/*
	첫번째 빅넘버 문자열 입력 구현 필요
	*/
	printf("Enter second big number by string: ");
	/*
	두번째 빅넘버 문자열 입력 구현 필요
	*/








}


void calculate_sub()
{




}


void calculate_mul()
{




}


void calculate_div()
{




}


void calculate_mod_exp()
{




}