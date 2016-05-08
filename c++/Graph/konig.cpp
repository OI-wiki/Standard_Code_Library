/**
 * @Author SCaffrey(sirius.caffrey@gmail.com)
 * @Copyright SATA
 * http://hihocoder.com/problemset/problem/1127
 */
#include <cstdio>// NOLINT
#include <cstring>// NOLINT
#include <queue>// NOLINT
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

int n, m;
int u, v;
struct node {
  int w, t, x;
} e[MAXN << 1];
int head[MAXN], cnt = 1;
inline void add(int s, int t, int w) {
  // printf("``%d %d\n", s, t);
  e[++cnt].t = t; e[cnt].x = head[s]; head[s] = cnt; e[cnt].w = w;
  e[++cnt].t = s; e[cnt].x = head[t]; head[t] = cnt; e[cnt].w = 0;
}
std::queue<int> Q;
int dis[MAXN];
int S, T;
bool bfs() {
  memset(dis, -1, sizeof dis);
  Q.push(S); dis[S] = 0;
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
      w = dfs(e[i].t, std::min(e[i].w, fl - used));
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
int is[MAXN];
void init(int s) {
  // printf("??%d\n", s);
  while (!Q.empty()) Q.pop();
  // memset(is, -1, sizeof is);
  Q.push(s); is[s] = 0;
  int u;
  while (!Q.empty()) {
    u = Q.front(); Q.pop();
    for (int i = head[u]; i; i = e[i].x) {
      if (e[i].w && is[e[i].t] == -1) {
        is[e[i].t] = is[u] ^ 1;
        Q.push(e[i].t);
      }
    }
  }
}
int main() {
  scanf("%d%d", &n, &m);
  S = n + n + 2; T = S + 1;
  f(i, 0, m) {
    scanf("%d%d", &u, &v);
    add(u, v, 1);
    add(v, u, 1);
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!11
    // undirected
  }
  memset(is, -1, sizeof is);
  g(i, 1, n) if (is[i] == -1) init(i);
  g(i, 1, n) {
    if (is[i]) {
      add(S, i, 1);
      add(i, S, 1);
    } else {
      add(i, T, 1);
      add(T, i, 1);
    }
  }
  int res = dinic();
  printf("%d\n%d\n", res, n - res);
  return 0;
}
/*
3 7
1 8
5 9
1 10
S 1
S 2
S 3
S 4
S 5
6 T
7 T
8 T
9 T
10 T
 */
