#include <assert.h>
#include <math.h>
#include "float-stuffs.c"

typedef unsigned float_bits;

/* Problem 2-92 */
float_bits float_negate(float_bits f)
{
  unsigned exp = f >> 23 & 0xFF;
  unsigned frac = f & 0x7FFFFF;
  if ((exp == 0xFF) && (!!frac)) return f ;
  return f + 0x80000000;
}

/* Problem 2-93 */
float_bits float_absval(float_bits f)
{
  unsigned exp = f >> 23 & 0xFF;
  unsigned frac = f & 0x7FFFFF;
  if ((exp == 0xFF) && (!!frac)) return f;
  return f & 0x7FFFFFFF;
}

/* Problem 2-94 */
float_bits float_twice(float_bits f)
{
  unsigned exp = f >> 23 & 0xFF;
  unsigned frac = f & 0x7FFFFF;
  switch (exp)
  {
    case 0:
      if (!frac) return f;
      if ((frac & 0x400000) == 0)
        return f & 0xFF800000 | (frac << 1);
      return (f + 0x00800000) & 0xFF800000 |
        (frac << 1);
    case 0xFF:
      return f;
    case 0xFE:
      return (f | 0x7F800000) & 0xFF800000;
    default:
      return f & 0x807FFFFF | ((exp + 1) << 23);
  }
}

/* Problem 2-95 */
float_bits float_half(float_bits f)
{
  unsigned exp = f >> 23 & 0xFF;
  unsigned frac = f & 0x7FFFFF;
  switch (exp)
  {
    case 0xFF:
      return f;
    case 1:
      if (frac == 0x7FFFFF) return f & 0xFF800000;
      if ((frac & 1) == 0 || (frac & 2) == 0)
        return (f & 0xFF000000) +
        (frac >> 1) + 0x400000;
      return (f & 0xFF000000) + (frac >> 1) +
        0x400001;
    case 0:
      if ((frac & 1) == 0 || (frac & 2) == 0)
        return (f & 0xFF000000) + (frac >> 1);
      return (f & 0xFF000000) + (frac >> 1) + 1;
    default:
      return (f & 0x807FFFFF) | ((exp - 1) << 23);
  }
}

/* Problem 2-96 
 * On my environment the int(NaN) isn't well
 * defined and int(Big Positive Float) gives 
 * INT_MAX instead of 0x80000000. */
int float_f2i(float_bits f)
{
  if (f == 0xCF000000) return 1 << 31;
  unsigned sign = f >> 31;
  unsigned exp = f >> 23 & 0xFF;
  unsigned frac = f & 0x7FFFFF;
  if (exp <= 126) return 0;
  if (exp >= 158) return 0x7FFFFFFF + sign;
  int pos_ans = 1 << (exp - 127);
  if (exp <= 150) pos_ans += frac >> (150 - exp);
  else pos_ans += frac << (exp - 150);
  return ((-sign) & (-pos_ans)) + 
    ((-!sign) & pos_ans);
}

/* Problem 2-97 */
float_bits float_i2f(int i)
{
  if (!i) return 0;
  if (i == 0x80000000) return 0xCF000000;
  unsigned sign = (i < 0);
  if (i < 0) i = -i;
  int j = i;
  j |= j >> 1;
  j |= j >> 2;
  j |= j >> 4;
  j |= j >> 8;
  j |= j >> 16;
  int exp_2 = (j >> 1) + 1;
  int exp = 0;
  j = 16;
  while (exp_2 != 1)
  {
    if (exp_2 >= (1 << j))
    {
      exp_2 >>= j;
      exp += j;
    }
    j >>= 1;
  }
  exp += 127;
  float_bits ans = (sign << 31) + (exp << 23);
  if (exp <= 150) return ans +
    ((i << 150 - exp) & 0x7FFFFF);
  unsigned frac = (i >> exp - 150) & 0x7FFFFF;
  unsigned res = i & ((1 << exp - 150) - 1);
  if (res == (1 << exp - 151) && (frac & 1))
    frac += 1;
  if (res > (1 << exp - 151)) frac += 1;
  if (frac >> 23) {frac = 0; ans += 1 << 23;}
  return ans + frac;
}

/* Test Start */
int main()
{
  int t = 1;
  while (t != 0)
  {
    float f = b2f(t);
    float f2 = b2f(float_negate(t));
    assert(!((isnan(f)&&f2b(f)!=f2b(f2)) 
          || ((!isnan(f))&&f!=-f2)));
    t+=1;
  }
  printf("2-92 Passed \n");

  t = 1;
  while (t != 0)
  {
    float f = b2f(t);
    float f2 = b2f(float_absval(t));
    assert(!((isnan(f)&&f2b(f)!=f2b(f2))
          || ((!isnan(f))&&f2!=fabs(f))));
    t+=1;
  }
  printf("2-93 Passed \n");

  t = 1;
  while (t != 0)
  {
    float f = b2f(t);
    float f2 = b2f(float_twice(t));
    assert(!((isnan(f)&&f2b(f)!=f2b(f2))
          || ((!isnan(f))&&f2!=2*f)));
    t+=1;
  }
  printf("2-94 Passed \n");

  t = 1;
  while (t != 0)
  {
    float f = b2f(t);
    float f2 = b2f(float_half(t));
    assert(!((isnan(f)&&f2b(f)!=f2b(f2))
          || ((!isnan(f))&&f2!=0.5f*f)));
    t+=1;
  }
  printf("2-95 Passed \n");

  t = 1;
  while (t != 0)
  {
    float f = b2f(t);
    int f2 = float_f2i(t);
    assert(!(!isnan(f)&&f2!=(int)f));
    t+=1;
  }
  printf("2-96 Passed \n");
  
  t = 1;
  while (t != 0)
  {
    float f = t;
    assert(float_i2f(t) == f2b(f));
    t+=1;
  }
  printf("2-97 Passed \n");

  return 0;
}
