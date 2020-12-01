#include "bignum_all_header.h"

int main()
{
	
	srand((unsigned)time(NULL));
	
	bignumber_test();
	
	printf("Thanks for using!\n");
	

	return 0;
}


/*
	char a[] = "3456789876543456";

	bigint* Teemo = NULL;

	bi_set_by_string(&Teemo, NON_NEGATIVE, a, 10);


	
	bi_show(Teemo, 16);
	printf("\n");


	bi_show(Teemo, 16);
	printf("\n");

	bi_delete(&Teemo);
	*/