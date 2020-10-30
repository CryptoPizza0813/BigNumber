#include <stdio.h>
#include <stdlib.h>

#define WORD_BITLEN 32

#if WORD_BITLEN == 8
typedef unsigned char word;
#elif WORD_BITLEN == 32
typedef unsigned int word;
#else WORD_BITLEN == 64
typedef unsigned long long word;
#endif 

#define NON_NEGATIVE 0
#define NEGATIVE 1

/*
MX_WORD_LEN
array_init?
set bigint?

*/





/* Dynamic Memory Allocation */
typedef struct{

    int sign;       // NEGATIVE or NON-NEGATIVE
    int wordlen;    // wordlen >= 0
    word* a;        // address for big integer
} bigint;

/* Static Memory Allocation */
typedef struct{

    int sign;       // NEGATIVE or NON-NEGATIVE
    int wordlen;    // wordlen >= 0
    word a[MAX_WORD_LEN];        // address for big integer
} bigint;


/* 2.1 Create BigInt, Delete BigInt, Zeroize BigInt */
void bi_delete(bigint** x)
{
    if(*x == NULL)
        return;
    
#ifdef ZERORIZE
    array_init((*x)->a, (*x)->wordlen);
#endif

    free((*x)->a);
    free(*x);
    *x = NULL;
}

void bi_new(bigint** x, int wordlen)
{
    if(*x != NULL)
        bi_delete(x);

    *x = (bigint*)malloc(sizeof(bigint));
    (*x)->sign = NON_NEGATIVE;
    (*x)->wordlen = wordlen;
    (*x)->a = (word*)calloc(wordlen, sizeof(word));
}

// zeroize??


/* 2.2 Set BigInt, Show BigInt */
void bi_set_by_array(bigint** x, int sign, word* a, int wordlen)   // bigint x <- sign and array a
{
    (*x)->sign = sign;

    for(int i = 0;  i < wordlen; i++)
    {
        (*x)->a[i] = a[i];
    }
}

// developed by CJH
void bi_set_by_string(bigint** x, int sign, char* a, word base)   // bigint x <- base string
{
    (*x)->sign;

    int len = strlen(a);    

    if(base == 2){
        int k = 0;
        for(int i = (*x)->wordlen - 1; i >= 0; i--){    // x.a[3], x.a[2], x.a[1], x.a[0] 순서대로 바이트를 집어넣는다.
            while(1) {
                (*x)->a[i] = ((*x)->a[i] << 1) | atoi(a[k]);   // 해당 x.a[i] 를 한비트 왼쪽 이동하고, 0번 인덱스 자리에 문자열의 0 또는 1을 OR연산한다.
                k += 1;
                if((len - k) % WORD_BITLEN == 0)    // len - k가 WORD_BITLEN의 배수이면 다음 x.a[i] 에 숫자를 저장해야 한다.
                    break;                          // 즉, 한개의 x.a[i]에는 WORD_BITLEN 만큼 0과 1이 들어가게 된다.
            }

        }

    }
    else if(base == 10){
        // NEED TO IMPLEMENT!!
    }
    else if(base == 16){
        int k = 0;
        for(int i = (*x)->wordlen - 1; i >= 0; i--){
            while(1) {
                (*x)->a[i] = ((*x)->a[i] << 4) | atoi(a[k]);
            }
            k += 1;
            if((len - k) % WORD_BITLEN == 0)
                break;
        }

    }


}


/*
void bi_show_hex(bigint* x);    // show x in hexa representation.
void bi_show_dec(bigint* x);    // show x in decimal representation.
void bi_show_bin(bigint* x);    // show x in binary representation.
*/
// bi_show(bigint* x, base) 형태로 구현하는 것을 추천.
// developed by CJH
void bi_show(bigint*x , word base)
{
    if(x->sign == NEGATIVE) printf("-");    
    
    if(base == 2)
    {
        for(int i = x->wordlen - 1; i >=0; i--)
        {
            for(int j = WORD_BITLEN - 1; j >=0; j--)
            {
                int temp = ( ( x->a[i]) >> j ) && 0x01;
                printf("%d", temp);
            }

        } printf("\n");

    }
    else if(base == 10)
    {
        // NEED TO IMPLEMENT!!
    }
    else if(base == 16)
    {
        for(int i = x->wordlen-1; i >= 0; i--)   
            printf("%04x", x->a[i]);
        printf("\n");

    }

}




/* 2.3 Refine BigInt (Remove Last Zero Words) */        //????????????????????
void bi_refine(bigint* x)
{
    if(x == NULL)
        return;

    int new_wordlen = x->wordlen;
    while(new_wordlen > 1)  //  at least one word needed
    {
        if(x-> a[new_wordlen - 1] != 0)
            break;
        new_wordlen--;
    }
    if (x-> wordlen != new_wordlen)
    {
        x->wordlen = new_wordlen;
        x->a =  (word*)realloc(x->a, sizeof(word)*new_wordlen);
    }

    if((x->wordlen == 1) && (x->a[0] == 0x0))
        x->sign = NON_NEGATIVE;
}


/* 2.4 Assign BigInt */
void bi_assign(bigint** y, bigint* x)
{
    if(*y != NULL)
        bi_delete(y);

    bi_new(y, x->wordlen);
    (*y)->sign = x->sign;
    array_copy((*y)->a, x->a, x->wordlen);      // array_copy는 내가 구현해야 함?
}


/* 2.5 Generate Random BigInt */
void bi_gen_rand(bigint** x, int sign, int wordlen)
{
    bi_new(x, wordlen);
    (*x)->sign = sign;
    array_rand((*x)->a, wordlen);

    bi_refine(*x);
}

void array_rand(word* dst, int wordlen)
{
    byte* p = (byte*)dst;       // byte 선언 필요???
    int cnt = wordlen * sizeof(word);
    while(cnt > 0)
    {
        *p = rand() & 0xff;
        p++;
        cnt--;
    }

}


/* 2.6 Get Word Lengh / Bit Length / j-th Bit of BigInt */
// developed by IJH
int get_wordlen(bigint* x)
{
    return x->wordlen;
}

int get_bitlen(bigint* x)
{
    int bitlen = (x->wordlen - 1) * WORD_BITLEN;
    int b;
    for(int i = WORD_BITLEN - 1; i >= 0; i--)
    {
        b = (x->a[x->wordlen - 1] >> i) & 0x01;
        if(b != 0)
        {
            return bitlen + i + 1;
        }
    }
    return bitlen;
}

int get_jth_bit(bigint* x, int j)
{
    int Q = j / WORD_BITLEN;
    int R = j % WORD_BITLEN;

    if(R == 0)
    {
        return ((x->a[Q-1]) >> WORD_BITLEN-1) % 0x01;
    }
    else
    {
        return ((x->a[Q]) >> R-1) % 0x01;
    }
}



/* 2.7 Get Sign and Flip Sign of BigInt */
// developed by CJH
int bi_get_sign(bigint* x)
{
    return x->sign;
}

void bi_flip_sign(bigint** x)
{
    if((*x)->sign == NEGATIVE)
        (*x)->sign = NON_NEGATIVE;
    else
        (*x)->sign = NEGATIVE;
}


/* 2.8 Set One, Set Zero, Is Zero, Is One */
// developed by CJH
void bi_set_one(bigint** x)
{
    bi_new(x, 1);
    (*x)->sign = NON_NEGATIVE;
    (*x)->a[0] = 0x1;
}

void bi_set_zero(bigint** x)
{
    bi_new(x, 1);
    (*x)->sign = NON_NEGATIVE;
    (*x)->a[0] = 0x0;
}

int is_zero(bigint* x)  // 0이면 0을, 0이 아니면 1을 반환한다.
{
    for(int i  = 0; i < x->wordlen; i++)    // 모든 x.a[i] 이 0인지 확인한다. 만약 0이 아니면 1 반환.
    {
        if(x->a[i] != 0)
            return 1;
    }

    return 0;
}

int is_one(bigint* x)  // 1이면 1, 1이 아니면 0을 반환한다.
{
    for(int i  = 0; i < x->wordlen; i++)    // a[0]을 제외한 모든 x.a[i] 이 0인지 확인한다. 만약 0이 아니면 flag = 0로 초기화.
    {
        if(i == 0)
        {
            if(x->a[0] != 1)
                return 0;
        }
        else
        {
            if(x->a[i] != 0)
                return 0;
        }
    }
    
    return 1;
}


/* 2.9 Compare ABS, Compare AB*/
// developed by CJH
int Compare_ABS(bigint* A, bigint* B) // 음이 아닌 정수 A, B의 대수 비교. A > B : 1 리턴, A = B : 0 리턴, A < B : -1 리턴 
{
    int n = A->wordlen;
    int m = B->wordlen;

    if(n > m)
        return 1;
    else if(n < m)
        return -1;
    
    for(int j = n - 1; j >= 0; j--)
    {
        if(*A->a[j] > *B->a[j])
            return 1;
        else if(*A->a[j] < *B->a[j])
            return -1;
    }

    return 0;
}

int Compare_AB(bigint** A, bigint** B)
{
    int sign_a = (*A)->sign;
    int sign_b = (*B)->sign;
    if(sign_a == 0 && sign_b == 1)
        return 1;
    
    if(sign_a == 1 && sign_b == 0)
        return -1;

    int ret = Compare_ABS(A, B);        // 그냥 A와 B?
    if(sign_a == 0)
        return ret;
    else
        return ret ^ 1;
}


/* 2.10 Left / Right Shift */
void bi_left_shift(bigint** x, int r)
{
    // NEED TO IMPLEMENT
}

void bi_right_shift(bigint** x, int r)
{
    if(r < WORD_BITLEN)
    {


    }
    else
    {
        // NEED TO IMPLEMENT
    }
    
}



/* 2.11 Reduction */





/* main */
int main()
{
    int arr[3] = {0x1234, 0x5678, 0x9abc};
    bigint teemo;
    teemo.sign = NON_NEGATIVE;
    teemo.wordlen = 3;

    /*
    더블 포인터 구조체 참고
    mystruct actualThing;
    mystruct *pointer = &actualThing;
    mystruct **data = &pointer;
    myfunc(data);
    */
    bigint *teemo_p = &teemo;


    bi_new(&teemo, 3);
    bi_set_by_array(&teemo, teemo.sign, arr, teemo.wordlen);

    return 0;

}