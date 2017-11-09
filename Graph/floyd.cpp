/**
 * @Author SCaffrey(sirius.caffrey@gmail.com)
 * @Copyright SATA
 * http://hihocoder.com/problemset/problem/1089
 */
#include <cstdio>// NOLINT
#include <cstring>// NOLINT
#include <algorithm>// NOLINT
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
const int MAXN = 100033;

int d[133][133];
int n, m, u, v, w;
int main() {
  scanf("%d%d", &n, &m);
  memset(d, 0x1f, sizeof d);
  f(i, 0, m) {
    scanf("%d%d%d", &u, &v, &w);
    d[u][v] = std::min(d[u][v], w);
    d[v][u] = std::min(d[v][u], w);
  }
  g(i, 1, n) d[i][i] = 0;
  g(k, 1, n) g(i, 1, n) g(j, 1, n) {
    d[i][j] = std::min(d[i][j], d[i][k] + d[k][j]);
  }
  g(i, 1, n) {
    g(j, 1, n) printf("%d ", d[i][j]); puts("");
  }
  return 0;
}
