/**
 * @name ext_gcd.cpp
 * @subject extended_GCD algorithm
 * @author SCaffrey(sirius.caffrey@gmail.com)
 * @Copyright DWTFABG
 * @comment This is a extended_GCD algorithm.
 * @tests http://poj.org/problem?id=1061
 * @warning Added NOLINT on line 12 and 28 in order to ignore
 *     strange tastes on (int64 && long long) and (reference and pointer).
 */
#include <cstdio>

typedef long long LL;// NOLINT 

LL x, y, m, n, L;
// Using variables the same as the problem statement.
LL a, b, c, d, xx, yy;

/**
 * ext_gcd
 * @param  a  [LL]
 * @param  b  [LL]
 * @param  xx [LL &]
 * @param  yy [LL &]
 * @return  gcd of a and b [LL]
 * @comment this function solves things like 'a * xx + b * yy = gcd(a,b)'
 *              and returns gcd(a,b);
 */
LL ext_gcd(LL a, LL b, LL &xx, LL &yy) {// NOLINT 
  if (b) {
    c = ext_gcd(b, a % b, yy, xx);
    yy -= xx * (a / b);
    // You know what, the '()' here is essential.
    // Or you may want to use 'yy -= a / b * xx;' instead.
    // The reason here is that a might not be divisable by b
    //     and from our math work we know what we want here
    //     is 'a div b'.
    return c;
  }
  xx = 1; yy = 0;
  return a;
}

int main() {
  scanf("%lld%lld%lld%lld%lld", &x, &y, &m, &n, &L);
  d = ext_gcd(n - m, L, xx, yy);
  if ((x - y) % d) {
    puts("Impossible");
  } else {
    xx = xx * ((x - y) / d);
    yy = L / d;
    xx = (xx % yy + yy) % yy;
    printf("%lld\n", xx);
  }
  return 0;
}
