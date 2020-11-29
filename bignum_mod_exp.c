#include "bignum_mod_exp.h"

void L_t_R(bigint** x, int n, int N)    // x^n mod N
{
    bigint* t = NULL;
    bi_set_one(&t); // t <- 1

    int bit[2049] = {0, };  // n의 비트열을 담을 행렬 선언
    int n_temp = n;
    int j = 0;

    // 비트열 저장 단계
    while(n_temp >= 1) {
        bit[j] = n_temp & 0x01;

        j += 1;
        n_temp = n_temp >> 1;

    }
    // j 는 n의 비트열 길이를 의미한다. j - 1 은 bit[]에서 MSB가 위치한 곳의 인덱스가 된다.  

    // x를 저장하는 임시변수
    bigint* x_temp = NULL;
    bi_assign(&x_temp, *x);

    for(int i = j - 1; i >= 0; i--) {
        bigint* t_temp = NULL;
        bi_set_zero(&t_temp); 
        bi_squaring(t, &t_temp);  // t_temp = t^2
        Reduction(&t_temp, N);  // t_temp mod N (t^2 mod N)
        
        if(bit[i] == 1) {   // if n_i == 1
            bi_mul(t_temp, x_temp, &t);  // t = t_temp * x 
            Reduction(&t, N);       // t mod N ( t^2 * x mod N)
            
        }
        else
            bi_assign(&t, t_temp);

    }

    bi_assign(x, t);
    bi_delete(&t);
    bi_delete(&x_temp);

}