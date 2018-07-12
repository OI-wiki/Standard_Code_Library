
/**
 * @author SCaffrey (sirius.caffrey@gmail.com)
 * @date    2016-04-15 08:46:39
 * @copyright MIT
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
const int MAXN = 500033;

int n, m;
struct edge {
  int s, t, x;
} e[MAXN << 1], E[MAXN << 1];
int head[MAXN], cnt = 1, Head[MAXN], c = 1;
inline void add(int s, int t) {
  e[++cnt].t = t;
  e[cnt].x = head[s];
  head[s] = cnt;
  e[cnt].s = s;
}
inline void Add(int s, int t) {
  E[++c].t = t;
  E[c].x = Head[s];
  Head[s] = c;
}
int dfn[MAXN], low[MAXN], scc, idx, sta[MAXN], top;
bool inSta[MAXN];
int belong[MAXN], bar[MAXN], cost[MAXN];
int has[MAXN], w[MAXN];
void tarjan(int u) {
  int v;
  dfn[u] = low[u] = ++idx;
  inSta[u] = 1;
  sta[top++] = u;
  for (int i = head[u]; i; i = e[i].x) {
    v = e[i].t;
    if (!dfn[v]) {
      tarjan(v);
      if (low[v] < low[u]) low[u] = low[v];
    } else if (inSta[v] && dfn[v] < low[u])
      low[u] = dfn[v];  // NOLINT
  }
  if (low[u] == dfn[u]) {
    ++scc;
    do {
      v = sta[--top];
      belong[v] = scc;
      bar[scc] |= has[v];
      cost[scc] += w[v];
      inSta[v] = 0;
    } while (u != v);
  }
}
void init() { g(i, 1, n) if (!dfn[i]) tarjan(i); }
int fa[MAXN];
int get(int x) {
  int tee = fa[x], q;
  while (tee != fa[tee]) tee = fa[tee];
  while (x != tee) {
    q = fa[x];
    fa[x] = tee;
    x = q;
  }
  return tee;
}
int s, t, p, u, v;
int d[MAXN];
int ans;
int dp[MAXN];
int vis[MAXN];
void bfs() {
  sta[top = 1] = s;
  while (top) {
    u = sta[top--];
    vis[u] = 1;
    for (int i = head[u]; i; i = e[i].x) {
      v = e[i].t;
      if (!vis[v]) sta[++top] = v;
    }
  }
}
int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  scanf("%d%d", &n, &m);
  f(i, 0, m) {
    scanf("%d%d", &s, &t);
    add(s, t);
  }
  g(i, 1, n) scanf("%d", w + i);
  scanf("%d%d", &s, &p);
  f(i, 0, p) {
    scanf("%d", &t);
    has[t] = 1;
  }
  init();
  bfs();
  // g(i, 1, n) fa[i] = i;
  g(i, 2, cnt) {
    if (!vis[e[i].s] || !vis[e[i].t]) continue;
    u = belong[e[i].s];
    v = belong[e[i].t];
    if (u != v) {
      Add(u, v);
      ++d[v];
    }
  }
  top = 1;
  sta[1] = belong[s];
  while (top) {
    u = sta[top--];
    if (bar[u]) ans = std::max(ans, dp[u] + cost[u]);
    for (int i = Head[u]; i; i = E[i].x) {
      v = E[i].t;
      dp[v] = std::max(dp[v], dp[u] + cost[u]);  // NOLINT
      --d[v];
      if (!d[v]) sta[++top] = v;
    }
  }
  // g(i, 1, scc) printf("%d ", cost[i]); puts("");
  // g(i, 1, scc) printf("%d ", dp[i]); puts("");
  printf("%d\n", ans);

#ifdef LOCAL
  fclose(stdin);
  fclose(stdout);
#endif
  return 0;
}
