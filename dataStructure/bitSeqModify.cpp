/**
 * @author Ir1d(sirius.caffrey@gmail.com)
 * @Copyright SATA(The Star And Thank Author License)
 * http://www.codevs.cn/problem/1082/
 */

#include <cstdio>// NOLINT
#include <cstring>// NOLINT
#include <bits/stdc++.h>// NOLINT
#include <cmath>// NOLINT
#define x1 x11
#define y1 y11

#define f(x, y, z) for (int x = (y), __ = (z); x < __; ++x)
#define g(x, y, z) for (int x = (y), __ = (z); x <= __; ++x)
#define fd(x, y, z) for (int x = (y), __ = (z); x > __; --x)
#define gd(x, y, z) for (int x = (y), __ = (z); x >= __; --x)

#ifdef WIN32
  #define LLD "%I64d"
  #define LLU "%I64u"
#else
  #define LLD "%lld"
  #define LLU "%llu"
#endif

typedef long long LL;// NOLINT
typedef long double real;

const double INF = 1e100;
const int oo = ~0u >> 2;
const double pi = acos(-1.0);
const double EPS = 1e-8;
const int MAXN = 300033;

int n, m;
int op, x, y, v;
LL d[MAXN], d1[MAXN], s[MAXN];
// d1 is d * i
LL query(LL *a, int x) {
  LL res = 0;
  for (int i = x; i; i -= i & -i) res += a[i];
  return res;
}
void update(LL *a, int x, int v) {
  for (int i = x; i <= n; i += i & -i) {
    a[i] += v;
  }
}
int main() {
  scanf("%d", &n);
  g(i, 1, n) scanf("%lld", s + i), s[i] += s[i - 1];
  scanf("%d", &m);
  while (m--) {
    scanf("%d%d%d", &op, &x, &y);
    if (op == 1) {
      scanf("%d", &v);
      update(d, x, v); update(d, y + 1, -v);
      update(d1, y, v * x); update(d1, y + 1, -v * (y + 1));
    } else {
      LL s1 = s[x - 1] + x * query(d, x - 1) - query(d1, x - 1);
      LL s2 = s[y] + (y + 1) * query(d, y) - query(d1, y);
      printf("%lld\n", s2 - s1);
    }
  }

  return 0;
}


/*

sum[i] = a[1]+...+a[i] + delta[1]*i + delta[2]*(i - 1) + delta[3]*(i - 2)+...+delta[i]*1   // a[i]为原始数组  
       = sigma( a[x] ) + sigma( delta[x]  *  (i + 1 - x) )  
       = sigma( a[x] ) + (i + 1) * sigma( delta[x] ) - sigma( delta[x] * x )
 */
