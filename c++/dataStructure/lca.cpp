/**
 * @Author SCaffrey(sirius.caffrey@gmail.com)
 * @Copyright SATA
 * http://codevs.cn/problem/2370/
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

int n, m;
int s, t, w, u, v;
struct node {
  int t, w, x;
} e[MAXN << 1];
int head[MAXN], cnt = 1;
inline void add(int s, int t, int w) {
  e[++cnt].t = t; e[cnt].w = w; e[cnt].x = head[s]; head[s] = cnt;
  e[++cnt].t = s; e[cnt].w = w; e[cnt].x = head[t]; head[t] = cnt;
}
int dep[MAXN], vis[MAXN];
int fa[MAXN][18];
int cost[MAXN][18];
void dfs(int x) {
  vis[x] = 1;
  g(i, 1, 17) {
    if (dep[x] < (1 << i)) break;
    fa[x][i] = fa[ fa[x][i - 1] ][i - 1];
    cost[x][i] = cost[x][i - 1] + cost[ fa[x][i - 1] ][i - 1];
  }
  for (int i = head[x]; i; i = e[i].x) {
    if (vis[e[i].t]) continue;
    dep[e[i].t] = dep[x] + 1;
    fa[e[i].t][0] = x;
    cost[e[i].t][0] = e[i].w;
    dfs(e[i].t);
  }
}
int solve(int x, int y) {
  int res = 0;
  if (dep[x] < dep[y]) std::swap(x, y);// NOLINT
  int t = dep[x] - dep[y];
  g(i, 0, 17) if (t & (1 << i)) {
    res += cost[x][i];
    x = fa[x][i];
  }
  // printf("%d %d\n", x, y);
  gd(i, 17, 0) if (fa[x][i] != fa[y][i]) {
    res += cost[x][i] + cost[y][i];
    x = fa[x][i]; y = fa[y][i];
  }
  // printf("%d %d %d %d\n", x, y, fa[x][0], fa[y][0]);
  if (x != y) {
    res += cost[x][0] + cost[y][0];
  }
  return res;
}
int main() {
  scanf("%d", &n);
  f(i, 1, n) {
    scanf("%d%d%d", &u, &v, &w);
    add(u, v, w);
  }
  dfs(0);
  scanf("%d", &m);
  f(i, 0, m) {
    scanf("%d%d", &u, &v);
    printf("%d\n", solve(u, v));
  }
  return 0;
}
