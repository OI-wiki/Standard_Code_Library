/**
 * @name quick_pow.cpp
 * @subject quick_pow algorithm
 * @author SCaffrey(sirius.caffrey@gmail.com)
 * @Copyright DWTFABG
 * @comment This is an algorithm for powing quickly.
 * @tests https://vijos.org/p/1841 (NOIP2013 TG D1T1)
 * @warning Added NOLINT on line 23 to ignore long long stuff in cpplint.
 */

#include <cstdio>

int n, m, k, x;

/**
 * pow
 * @param  a [int]
 * @param  b [int]
 * @param  c [int]
 * @return  a ^ b % c [int]
 */

typedef long long LL;// NOLINT

int pow(int a, int b, int c) {
  int res = 1, bas = a;
  while (b) {
    if (b & 1)res = (LL)res * bas % c;
    // Transform to long long in case of overflow.
    bas = bas * bas % c;
    b >>= 1;
  }
  return res;
}

int main() {
  scanf("%d%d%d%d", &n, &m, &k, &x);
  printf("%d", (x + (LL)m * pow(10, k, n) % n) % n);
}
