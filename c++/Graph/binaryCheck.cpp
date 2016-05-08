/**
 * @Author SCaffrey(sirius.caffrey@gmail.com)
 * @Copyright SATA
 * http://hihocoder.com/problemset/problem/1121
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

int T;
int n, m;
int u, v;
struct node {
  int t, x;
} e[MAXN];
int head[MAXN], cnt = 1;
inline void add(int s, int t) {
  e[++cnt].t = t; e[cnt].x = head[s]; head[s] = cnt;
  e[++cnt].t = s; e[cnt].x = head[t]; head[t] = cnt;
}
int col[MAXN];
bool bipartite(int u) {
  for (int i = head[u]; i; i = e[i].x) {
    int v = e[i].t;
    if (col[v] == col[u]) return 0;
    if (!col[v]) {
      col[v] = 3 - col[u];
      if (!bipartite(v)) return 0;
    }
  }
  return 1;
}
bool solve() {
  g(i, 1, n) if (!col[i]) {
    col[i] = 1;
    if (!bipartite(i)) return 0;
  }
  return 1;
}
int main() {
  scanf("%d", &T);
  while (T--) {
    memset(head, 0, sizeof head);
    cnt = 1;
    memset(col, 0, sizeof col);
    scanf("%d%d", &n, &m);
    f(i, 0, m) {
      scanf("%d%d", &u, &v);
      add(u, v);
    }
    if (solve()) {
      puts("Correct");
    } else {
      puts("Wrong");
    }
  }
  return 0;
}
