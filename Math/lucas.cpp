/**
 * @Author Ir1d (sirius.caffrey@gmail.com)
 * @Copyright SATA
 * @Example http://www.lydsy.com:808/JudgeOnline/problem.php?id=2111
 * @Notes Lucas's theorem
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
const int MAXN = 1000033;

LL n, p, fac[MAXN], caf[MAXN], sz[MAXN], f[MAXN];
void init() {
  fac[0] = 1;
  g(i, 1, n) {
    if (i >= p) break;
    fac[i] = fac[i - 1] * i % p;
  }
  caf[1] = 1;
  g(i, 2, n) {
    if (i >= p) break;
    caf[i] = p - p / i * caf[p % i] % p;
  }
  caf[0] = 1;
  g(i, 1, n) caf[i] = caf[i] * caf[i - 1] % p;
}
LL C(LL x, LL y) {
  if (x < y) return 0;
  if (x < p && y < p) return fac[x] * caf[y] % p * caf[x - y] % p;
  return C(x / p, y / p) * C(x % p, y % p) % p;
}
int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  scanf("%lld%lld", &n, &p);
  init();
  gd(i, n, 1) {
    sz[i] = sz[i << 1] + sz[i << 1|1] + 1;
    f[i] = C(sz[i] - 1, sz[i << 1]) * ((i << 1) > n ? 1 : f[i << 1]) % p * ((i << 1 | 1) > n ? 1 : f[i << 1|1]) % p; // NOLINT
  }
  printf("%lld\n", f[1]);

#ifdef LOCAL
  fclose(stdin);
  fclose(stdout);
#endif
  return 0;
}

