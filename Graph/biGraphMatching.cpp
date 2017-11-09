/**
 * @Author SCaffrey(sirius.caffrey@gmail.com)
 * @Copyright SATA
 * http://uoj.ac/problem/78
 */
#include <cstdio>// NOLINT
#include <cstring>// NOLINT
#include <bits/stdc++.h>// NOLINT
#include <queue>// NOLINT
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
const int MAXN = 100033;

int n, m;
struct node {
  int t, w, x;
} e[MAXN * 50];
int head[MAXN], cnt = 1;
inline void add(int s, int t, int w) {
  // printf("```%d %d %d\n", s, t, w);
  e[++cnt].t = t; e[cnt].w = w; e[cnt].x = head[s]; head[s] = cnt;
  e[++cnt].t = s; e[cnt].w = 0; e[cnt].x = head[t]; head[t] = cnt;
}
std::queue<int> Q;
int dis[MAXN];
int S, T;
bool bfs() {
  memset(dis, -1, sizeof dis);
  dis[S] = 0; Q.push(S);
  int u;
  while (!Q.empty()) {
    u = Q.front(); Q.pop();
    for (int i = head[u]; i; i = e[i].x) {
      if (e[i].w && dis[e[i].t] == -1) {
        dis[e[i].t] = dis[u] + 1;
        Q.push(e[i].t);
      }
    }
  }
  return dis[T] != -1;
}
int dfs(int x, int fl) {
  if (x == T) return fl;
  int w, used = 0;
  for (int i = head[x]; i; i = e[i].x) {
    if (e[i].w && dis[e[i].t] == dis[x] + 1) {
      w = dfs(e[i].t, std::min(fl - used, e[i].w));
      e[i].w -= w; e[i ^ 1].w += w; used += w;
      if (used == fl) return fl;
    }
  }
  if (!used) dis[x] = -1;
  return used;
}
int dinic() {
  int res = 0;
  while (bfs()) res += dfs(S, oo);
  return res;
}
int x, y;
int q;
int res[MAXN];
int main() {
  scanf("%d%d%d", &n, &m, &q);
  S = n + m + 1; T = n + m + 2;
  f(i, 0, q) {
    scanf("%d%d", &x, &y);
    add(x, y + n, 1);
  }
  g(i, 1, n) add(S, i, 1);
  g(i, 1, m) add(i + n, T, 1);
  printf("%d\n", dinic());
  g(cur, 1, n) for (int i = head[cur]; i; i = e[i].x) {
    // printf("[%d %d\n", cur, e[i].t);
    if (e[i].t != S && e[i].w == 0) {
      res[cur] = e[i].t - n;
      // res[e[i].t] = i;
    }
  }
  g(i, 1, n) printf("%d ", res[i]); puts("");
  return 0;
}
