#include "bignum_add_sub.c"

void bi_mulc(word x, word y, bigint** C)
{
   //이거 word로 한거 다 bigint로 생성해서 마지막에 delete를 해야하나? 
   word R_x = x >> (WORD_BITLEN / 2);      // x를 절반으로 나눈 앞 자리
   word L_x = x % (1 << (WORD_BITLEN / 2));// x를 절반으로 나눈 뒷 자리
   word R_y = y >> (WORD_BITLEN / 2);      // y를 절반으로 나눈 앞 자리
   word L_y = y % (1 << (WORD_BITLEN/2));  // y를 절반으로 나눈 뒷 자리
   word A0, A1, AA, AA0, AA1;  //계산한 것을 저장할 곳
   word c = 0;
   A1 = R_x * R_y; // 앞 자리끼리 곱
   A0 = L_x * L_y; // 뒷 자리끼리 곱
   AA = ((R_x * L_y) + (L_x * R_y)); // 대각선 곱의 합
   AA1 = AA >> (WORD_BITLEN / 2); // 대각선 곱의 앞자리
   AA0 = AA << (WORD_BITLEN / 2); // 대각선 곱의 뒷자리

   // 뒷자리에서 carry 발생
   if (A0 > A0 + AA0)
      c = 1;

   if (A1 + AA1 + c == 0)
   {
      bi_new(C, 1);
      (*C)->a[0] = A0 + AA0;
   }
   else
   {
      bi_new(C, 2);
      (*C)->a[1] = A1 + AA1 + c;
      (*C)->a[0] = A0 + AA0;
   }
}

void bi_mul(bigint* x, bigint* y, bigint** C)
{
   int max_len = x->wordlen + y->wordlen;  //C의 최대 길이

   bi_new(C, max_len);   // 곱셈 결과를 저장할 C를 max_len 길이로 초기화

   bigint* C_word = NULL;  // singhle pricision을 저장하는 bigint 구조체

   for (int i = 0; i < x->wordlen; i++)
   {
      for (int j = 0; j < y->wordlen; j++)
      {
         bi_new(&C_word, 2);     // 2개의 워드를 저장할 수 있는 공간 할당.
         bi_mulc(x->a[i], y->a[j], &C_word);          // 한 워드씩 곱
         Left_Shift(&C_word, WORD_BITLEN * (i + j));  // 제대로 된 위치로 설정
         (*C)->a[C_word->wordlen - 1] = (*C)->a[C_word->wordlen - 1] + C_word->a[C_word->wordlen - 1];  // 덧셈
         if(C_word->wordlen != 1)
            (*C)->a[C_word->wordlen - 2] = (*C)->a[C_word->wordlen - 2] + C_word->a[C_word->wordlen - 2];  //덧셈
      }
   }

   if(x->sign == y->sign)         //부호 맞추기
      (*C)->sign = NON_NEGATIVE;
   else
      (*C)->sign = NEGATIVE;
   bi_delete(&C_word);
}