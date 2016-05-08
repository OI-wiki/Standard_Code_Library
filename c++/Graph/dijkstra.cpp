/**
 * @name dijkstra.cpp
 * @subject Dijkstra algorithm
 * @author SCaffrey(sirius.caffrey@gmail.com)
 * @Copyright SATA
 * @comment This is a sssp algorithm.
 * @tests http://hihocoder.com/problemset/problem/1081
 * @warning using 0x1f to memset for inf
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

struct node {
  int t, w, x;
} e[MAXN];
int head[MAXN], cnt = 1;
inline void add(int s, int t, int w) {
  e[++cnt].t = t; e[cnt].x = head[s]; head[s] = cnt; e[cnt].w = w;
  e[++cnt].t = s; e[cnt].x = head[t]; head[t] = cnt; e[cnt].w = w;
}
int n, m, s, t;
typedef std::pair<int, int> PII;// NOLINT
std::priority_queue<PII, std::vector<PII>, std::greater<PII> > Q;// NOLINT
int dis[MAXN], vis[MAXN];
void dij() {
  while (!Q.empty()) Q.pop();
  memset(dis, 0x1f, sizeof dis);
  memset(vis, 0, sizeof vis);
  dis[s] = 0;
  Q.push(PII(0, s));
  PII tee;
  int u;
  while (!Q.empty()) {
    tee = Q.top(); Q.pop();
    u = tee.second;
    if (vis[u]) continue;
    vis[u] = 1;
    for (int i = head[u]; i; i = e[i].x) {
      if (dis[e[i].t] > dis[u] + e[i].w) {
        dis[e[i].t] = dis[u] + e[i].w;
        Q.push(PII(dis[e[i].t], e[i].t));
      }
    }
  }
  printf("%d\n", dis[t]);
}
int u, v, w;
int main() {
  scanf("%d%d%d%d", &n, &m, &s, &t);
  f(i, 0, m) {
    scanf("%d%d%d", &u, &v, &w);
    add(u, v, w);
  }
  dij();
  return 0;
}
