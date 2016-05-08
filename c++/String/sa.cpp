/**
 * @Author SCaffrey(sirius.caffrey@gmail.com)
 * @Copyright SATA
 * http://uoj.ac/problem/35
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
const int MAXN = 100033;

char s[MAXN];
int sa[MAXN], rank[MAXN], height[MAXN];
int t1[MAXN], t2[MAXN], r[MAXN], c[MAXN];
void hz(int *r, int n, int m) {
  int *x = t1, *y = t2, *t, p = 0;
  f(i, 0, m) c[i] = 0;
  f(i, 0, n) c[ x[i] = r[i] ]++;
  f(i, 1, m) c[i] += c[i - 1];
  gd(i, n - 1, 0) sa[ --c[ x[i] ] ] = i;
  for (int j = 1; j <= n && p < n; j <<= 1, m = p) {
    f(i, n - j, n) y[p++] = i;
    f(i, 0, n) if (sa[i] >= j) y[p++] = sa[i] - j;
    f(i, 0, m) c[i] = 0;
    f(i, 0, n) c[ x[ y[i] ] ]++;
    f(i, 1, m) c[i] += c[i - 1];
    gd(i, n - 1, 0) sa[ --c[ x[ y[i] ] ] ] = y[i];
    t = x; x = y; y = t;
    p = 1; x[ sa[0] ] = 0;
    f(i, 1, n) {
      x[ sa[i] ] = y[ sa[i] ] == y[ sa[i - 1] ] && y[ sa[i] + j ] == y[ sa[i - 1] + j ] ? p - 1 : p++;// NOLINT
    }
  }
}
void getHeight(int n) {
  g(i, 1, n) rank[ sa[i] ] = i;
  int k = 0, j;
  f(i, 0, n) {
    j = rank[ sa[i] - 1 ];
    for (k?k--:0; s[i + k] == s[j + k]; ++k);// NOLINT
    height[ rank[i] ] = k;
  }
}
int mn;
void solve() {
  int n = strlen(s);
  f(i, 0, n) r[i] = s[i] - 'a' + 1;
  hz(r, n + 1, 27);
  getHeight(n);
  g(i, 1, n) printf("%d ", sa[i] + 1); puts("");
  g(i, 2, n) printf("%d ", height[i]); puts("");
}
int main() {
  while (~scanf("%s", s) && s[0] != '.') {
    solve();
  }
}
