/**
 * @Author SCaffrey(sirius.caffrey@gmail.com)
 * @Copyright SATA
 * http://hihocoder.com/problemset/problem/1183
 */
#include <cstdio>// NOLINT
#include <cstring>// NOLINT
#include <bits/stdc++.h>// NOLINT
#include <utility>// NOLINT
#include <set>// NOLINT
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

struct edge {
  int s, t, x;
} e[MAXN << 1];
int head[MAXN], cnt = 1;
inline void add(int s, int t) {
  e[++cnt].t = t; e[cnt].x = head[s]; head[s] = cnt; e[cnt].s = s;
  e[++cnt].t = s; e[cnt].x = head[t]; head[t] = cnt; e[cnt].s = t;
}
int low[MAXN], dfn[MAXN], idx;
int cut[MAXN], bri[MAXN];
typedef std::pair<int, int> PII;
std::set<PII> S;
// void dfs(int u, int fa) {
//   // printf("dfs: %d\n", u);
//   low[u] = dfn[u] = ++idx;
//   int ch = 0, v;
//   for (int i = head[u]; i; i = e[i].x) {
//     v = e[i].t;
//     if (!dfn[v]) {
//       ++ch;
//       dfs(v, u);
//       if (low[v] < low[u]) low[u] = low[v];
//       if (low[v] >= dfn[u]) cut[u] = 1;
//       if (low[v] > dfn[u]) {
//         // printf("``%d %d:%d %d\n", v, u, low[v], dfn[u]);
//         if (u < v) S.insert(PII(u, v));
//         else S.insert(PII(v, u));
//       }
//     } else if (dfn[v] < dfn[u] && v != fa) {
//       if (dfn[v] < low[u]) low[u] = dfn[v];
//     }
//   }
//   if (fa < 0 && ch == 1) cut[u] = 0;
// }
int n, m;
int u, v;
bool c;
int vis[MAXN];
void get(int u, int fa, int dep, int n) {
  vis[u] = 1; dfn[u] = low[u] = dep;
  int ch = 0;
  for (int i = head[u]; i; i = e[i].x) {
    if (e[i].t != fa && vis[e[i].t] == 1) {
      if (dfn[e[i].t] < low[u]) low[u] = dfn[e[i].t];
    }
    if (vis[e[i].t] == 0) {
      get(e[i].t, u, dep + 1, n);
      ++ch;
      if (low[e[i].t] < low[u]) low[u] = low[e[i].t];
      if ((fa == -1 && ch > 1) || (fa != -1 && low[e[i].t] >= dfn[u])) {
        cut[u] = 1;
      }
      if (low[e[i].t] > dfn[u]) {
        if (u < e[i].t) {
          S.insert(PII(u, e[i].t));
        } else {
          S.insert(PII(e[i].t, u));
        }
      }
    }
  }
  vis[u] = 2;
}
int main() {
  scanf("%d%d", &n, &m);
  f(i, 0, m) {
    scanf("%d%d", &u, &v);
    add(u, v);
  }
  get(1, -1, 0, n);
  // dfs(1, -1);
  g(i, 1, n) if (cut[i]) {
    printf("%d ", i);
    c = 1;
  }
  if (c) {
    puts("");
  }  else {
    puts("Null");
  }
  for (std::set<PII>::iterator it = S.begin(); it != S.end(); ++it) {
    printf("%d %d\n", it->first, it->second);
  }
  return 0;
}
