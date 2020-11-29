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
        // Reduction(&t_temp, N);  // t_temp mod N (t^2 mod N)
        
        if(bit[i] == 1) {   // if n_i == 1
            bi_mul(t_temp, x_temp, &t);  // t = t_temp * x 
            // Reduction(&t, N);       // t mod N ( t^2 * x mod N)
            
        }
        else
            bi_assign(&t, t_temp);

    }

    bi_assign(x, t);
    bi_delete(&t);
    bi_delete(&x_temp);

}


void R_t_L(bigint** x, int n, int N)
{
    bigint* t0 = NULL;
    bigint* t1 = NULL;
    bi_set_one(&t0);        // t0 <- 1
    bi_assign(&t1, *x);     // t1 <- x

    while(n != 0) {
        int n_i = n & 0x01; // n의 lsb
 
        if(n_i == 1) {
            bigint* t0_temp = NULL;
            bi_assign(&t0_temp, t0);
            bi_mul(t0_temp, t1, &t0);
            // Reduction(&t0, N);
            bi_delete(&t0_temp);
                        
        }

        bigint* t1_temp = NULL;
        bi_squaring(t1, &t1_temp);
        bi_assign(&t1, t1_temp);
        // Reduction(&t1, N);
        bi_delete(&t1_temp);
    

        n = n >> 1;
    }

    bi_assign(x, t0);

    bi_delete(&t0);
    bi_delete(&t1);

}

void M_n_S(bigint** x, int n, int N)
{
    bigint* t0 = NULL;
    bigint* t1 = NULL;
    bi_set_one(&t0);    // t0 <- 1
    bi_assign(&t1, *x); // t1 <- x

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

    for(int i = j - 1; i >= 0; i--) {
        bigint* t1_temp = NULL;
        bigint* t0_temp = NULL;

        if(bit[i] == 0) {
            // t1 <- t0 * t1
            bi_assign(&t1_temp, t1);
            bi_mul(t0, t1_temp, &t1);
            Reduction(&t1, N);

            // t0 <- t0^2
            bi_assign(&t0_temp, t0);
            bi_squaring(t0_temp, &t0); 
            // Reduction(&t0, N);
        }
        else {
            // t0 <- t0 * t1
            bi_assign(&t0_temp, t0);
            bi_mul(t1, t0_temp, &t0);
            // Reduction(&t0, N);

            // t1 <- t1^2
            bi_assign(&t1_temp, t1);
            bi_squaring(t1_temp, &t1); 
            // Reduction(&t1, N);
        }

        bi_delete(&t1_temp);
        bi_delete(&t0_temp);
    }

    bi_assign(x, t0);

    bi_delete(&t0);
    bi_delete(&t1);
}


