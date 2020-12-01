#include "bignum_test.h"

void bignumber_test()
{
	while(1) {
		int choose;
		printf("Choose your work\n");
		printf("Press 1 to check speed\n");
		printf("Press 2 to check accuracy\n");
		printf("Press 3 to calculate\n");
		printf("Press 4 to EXIT");
		printf("Press: ");
		scanf("%d", &choose);
		printf("\n\n");	

		if(choose == 1) {	// check time
			speed_check();
		}
		else if(choose == 2) {	// check accuracy
			check_accuracy();

		}
		else if(choose == 3) {
			calculate_bignumber();
		}
		else if(choose == 6)
			break;
		else 
			printf("You choose wrong number\n");
	
	}

}
