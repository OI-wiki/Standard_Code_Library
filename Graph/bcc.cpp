/**
 * @Author SCaffrey(sirius.caffrey@gmail.com)
 * @Copyright SATA
 * http://hihocoder.com/problemset/problem/1184
 */
#include <cstdio>// NOLINT
#include <cstring>// NOLINT
#include <bits/stdc++.h>// NOLINT
#include <algorithm>// NOLINT
#include <vector>// NOLINT
#include <utility>// NOLINT
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

int n, m, u, v;
struct node {
  int s, t, x;
} e[MAXN << 1];
int head[MAXN], cnt = 1;
inline void add(int s, int t) {
  e[++cnt].t = t; e[cnt].s = s; e[cnt].x = head[s]; head[s] = cnt;
  e[++cnt].t = s; e[cnt].s = t; e[cnt].x = head[t]; head[t] = cnt;
}
int dfn[MAXN], cut[MAXN], belong[MAXN << 1], idx, bcc, low[MAXN];
std::vector<int> res[MAXN];
typedef std::pair<int, int> PII;
typedef std::pair<PII, int> P;
P sta[MAXN], tee;
int top;
void dfs(int u, int fa) {
  low[u] = dfn[u] = ++idx;
  int ch = 0, v;
  for (int i = head[u]; i; i = e[i].x) {
    v = e[i].t;
    if (!dfn[v]) {
      ++ch;
      sta[top++] = P(PII(e[i].s, e[i].t), i);
      dfs(v, u);
      if (low[v] < low[u]) low[u] = low[v];
      if (low[v] >= dfn[u]) {
        cut[u] = 1;
        ++bcc; res[bcc].clear();
        for (;;) {
          tee = sta[--top];
          belong[tee.second] = bcc;
          // if (belong[tee.first.first] != bcc) {
            // res[bcc].push_back(tee.first.first);
            // belong[tee.first] = bcc;
          // }
          // if (belong[tee.first.second] != bcc) {
            // res[bcc].push_back(tee.first.second);
            // belong[tee.second] = bcc;
          // }
          if (tee.first.first == u && tee.first.second == v) break;
        }
      }
    } else if (dfn[v] < dfn[u] && v != fa) {
      sta[top++] = P(PII(e[i].s, e[i].t), i);
      if (dfn[v] < low[u]) low[u] = dfn[v];
    }
  }
  if (fa < 0 && ch == 1) cut[u] = 0;
}
int mn[MAXN];
void solve() {
  memset(dfn, 0, sizeof dfn);
  memset(cut, 0, sizeof cut);
  memset(belong, 0, sizeof belong);
  idx = top = 0;
  g(i, 1, n) if (!dfn[i]) dfs(i, -1);
}
int main() {
  scanf("%d%d", &n, &m);
  f(i, 0, m) {
    scanf("%d%d", &u, &v);
    add(u, v);
  }
  solve();
  printf("%d\n", bcc);
  memset(mn, 0x1f, sizeof mn);
  g(i, 2, cnt) printf("%d ", belong[i]); puts("");
  for (int i = 2; i <= cnt; i += 2) {
    mn[belong[i]] = std::min(mn[belong[i]], i / 2);
  }
  // printf("%d\n", cnt);
  for (int i = 2; i <= cnt; i += 2) printf("%d ", mn[belong[i]]); puts("");
  // g(i, 1, n) printf("%d ", belong[i]); puts("");
  return 0;
}
