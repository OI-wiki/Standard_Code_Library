/**
 * @Author SCaffrey(sirius.caffrey@gmail.com)
 * @Copyright SATA
 * http://hihocoder.com/problemset/problem/1068
 */
#include <cstdio>// NOLINT
#include <cstring>// NOLINT
#include <bits/stdc++.h>// NOLINT
#include <algorithm>// NOLINT
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

int n, m;
int x, a, b;
int s[MAXN];
int p[MAXN];
int mn[MAXN][20];
void init() {
  p[1] = 0;
  g(i, 2, n) {
    p[i] = p[i - 1];
    if ((1 << (p[i] + 1)) == i) ++p[i];
  }
  gd(i, n, 1) {
    mn[i][0] = s[i];
    for (int j = 1; (i + (1 << j) - 1) <= n; ++j) {
      mn[i][j] = std::min(mn[i][j - 1], mn[i + (1 << (j - 1))][j - 1]);
    }
  }
}
int solve(int ll, int rr) {
  int len = rr - ll + 1;
  int k = p[len];
  return std::min(mn[ll][k], mn[rr - (1 << k) + 1][k]);
}
int main() {
  scanf("%d", &n);
  g(i, 1, n) scanf("%d", s + i);
  init();
  scanf("%d", &m);
  f(i, 0, m) {
    scanf("%d%d", &a, &b);
    if (a > b) std::swap(a, b);
    printf("%d\n", solve(a, b));
  }
}
