/**
 * @Author Ir1d(sirius.caffrey@gmail.com)
 * @Copyright SATA
 * @Example https://www.51nod.com/onlineJudge/questionCode.html#!problemId=1135
 */
#include <bits/stdc++.h>  // NOLINT
#include <cmath>          // NOLINT
#include <cstdio>         // NOLINT
#include <cstring>        // NOLINT
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

typedef long long LL;  // NOLINT
typedef long double real;

const double INF = 1e100;
const int oo = ~0u >> 2;
const double pi = acos(-1.0);
const double EPS = 1e-8;
const int MAXN = 100033;

int p;
std::vector<LL> a;
LL get(LL x, LL y, LL z) {
  LL bas = x, res = 1;
  while (y) {
    if (y & 1) res = res * bas % z;
    bas = bas * bas % z;
    y >>= 1;
  }
  return res;
}
bool test(LL g, LL p) {
  for (LL i = 0; i < a.size(); ++i) {
    if (get(g, (p - 1) / a[i], p) == 1) return 0;
  }
  return 1;
}
LL getRoot(LL p) {
  LL tee = p - 1;
  for (LL i = 2; i <= tee / i; ++i) {
    if (tee % i == 0) {
      a.push_back(i);
      while (tee % i == 0) tee /= i;
    }
  }
  if (tee != 1) a.push_back(tee);
  LL g = 1;
  while (233)
    if (test(g, p))
      return g;
    else
      ++g;  // NOLINT
}
int main() {
  scanf("%d", &p);
  printf("%lld\n", getRoot(p));
  return 0;
}
