/**
 * Big Number Library
 * Developed by JangHyuck Choi & JaeHui In
 * 2020-11-13
 * */
#include "bignum_test.c"

int main()
{
	srand((unsigned)time(NULL));

	// basic_test();

	// add_test();

	// sub_test();

	// mul_test();

	while(1) {			
		int cases = 0;
		printf("press 1 for basic test\n");
		printf("press 2 for big number addition test\n");
		printf("press 3 for big number subtraction test\n");
		printf("press 4 for big number multiplication\n");
		printf("press 5 for exit\n");
		scanf("%d", &cases);
		switch (cases)
		{
		case 1:
			basic_test();
			break;
		case 2:
			add_test();
			break;
		case 3:
			sub_test();
			break;
		case 4:
			mul_test();
			break;
		case 5:
			break;
		default:
			printf("you choose wrong number.\n");
			break;
		}

		if(cases == 5) 
			break;
		
	}
	printf("Thanks for using!\n");




	return 0;
}