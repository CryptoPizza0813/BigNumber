#include "bignum_add_sub.c"

void SP_mul(word x, word y, bigint** C)
{
   word R_x = x >> (WORD_BITLEN / 2);      // x를 절반으로 나눈 앞 자리
   word L_x = x <<(WORD_BITLEN / 2);  // x를 절반으로 나눈 뒷 자리  *****이거 좀 깔끔한거 생각점여*****
   L_x = L_x >> (WORD_BITLEN / 2);
   word R_y = y >> (WORD_BITLEN / 2);      // y를 절반으로 나눈 앞 자리
   word L_y = y << (WORD_BITLEN / 2); // y를 절반으로 나눈 뒷 자리  *****이거 좀 깔끔한거 생각점여*****
   L_y = L_y >> (WORD_BITLEN / 2);
   word A1, A0, AA1, AA0;  //계산한 것을 저장할 곳
   word c = 0;
   A1 = R_x * R_y; // 앞 자리끼리 곱
   A0 = L_x * L_y; // 뒷 자리끼리 곱
   AA1 = ((R_x * L_y) + (L_x * R_y)) >> (WORD_BITLEN / 2); // 대각선 곱의 앞자리
   AA0 = ((R_x * L_y) + (L_x * R_y)) << (WORD_BITLEN / 2); // 대각선 곱의 뒷자리

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