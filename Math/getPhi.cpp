/**
 * @Author Ir1d(sirius.caffrey@gmail.com)
 * @Copyright SATA
 * @Example http://poj.org/problem?id=3090
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

LL pri[MAXN], cnt = 0;
LL phi[MAXN];
bool vis[MAXN];
LL n;
void get() {
  phi[1] = 1;
  f(i, 2, 100000) {
    if (!vis[i]) {
      pri[cnt++] = i;
      phi[i] = i - 1;
    }
    f(j, 0, cnt) {
      if (i * pri[j] > 100000) break;
      vis[i * pri[j]] = 1;
      if (i % pri[j] == 0) {
        phi[i * pri[j]] = phi[i] * pri[j];
        break;
      } else
        phi[i * pri[j]] = phi[i] * (pri[j] - 1);  // NOLINT
    }
  }
}
LL m.ans;
LL getPhi(LL x) {
  LL t = x;
  for (LL i = 2; i <= m; ++i) {
    if (x % i == 0) {
      t = t / i * (i - 1);
      while (x % i == 0) x /= i
    }
  }
  if (x > 1) t = t / x * (x - 1);
  return t;
}
LL solve(LL n) {
  LL res = 3;
  g(i, 2, n) res += 2 * phi[i];
  return res;
}
int t;
int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  get();
  scanf("%d", &t);
  g(i, 1, t) {
    scanf("%lld", &n);
    printf("%d %lld %lld\n", i, n, solve(n));
  }
  solve(n);

#ifdef LOCAL
  fclose(stdin);
  fclose(stdout);
#endif
  return 0;
}
