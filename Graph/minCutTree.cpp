/**
 * @Author Ir1d(sirius.caffrey@gmail.com)
 * @Copyright SATA
 * @Example http://www.lydsy.com:808/JudgeOnline/problem.php?id=2229
 * @Notes Gomory-Hu tree
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
const int MAXN = 100033;

std::queue<int> Q;  // NOLINT
struct edge {
  int t, w, x;
} e[MAXN];
int k, l, m, n, S, T, q, ti, a, b, c, ans, cas, w;
int A[233][233], d[233], st[233], vis[233];
int first[233], p[233];
int head[233], cnt = 1;
inline void add(int s, int t, int w) {
  e[++cnt].t = t;
  e[cnt].w = w;
  e[cnt].x = head[s];
  head[s] = cnt;
  e[++cnt].t = s;
  e[cnt].w = w;
  e[cnt].x = head[t];
  head[t] = cnt;
}
inline void init() {
  cnt = 1;
  memset(A, 0x1f, sizeof A);
  memset(head, 0, sizeof head);
}
bool bfs() {
  vis[S] = ++ti;
  d[S] = 0;
  Q.push(S);
  int u;
  while (!Q.empty()) {
    u = Q.front();
    Q.pop();
    for (int i = head[u]; i; i = e[i].x) {
      if (e[i].w && vis[e[i].t] != ti) {
        vis[e[i].t] = ti;
        d[e[i].t] = d[u] + 1;
        Q.push(e[i].t);
      }
    }
  }
  return vis[T] == ti;
}
int dfs(int x, int fl) {
  if (x == T || !fl) return fl;
  int w, used = 0;
  for (int i = head[x]; i; i = e[i].x) {
    if (e[i].w && d[e[i].t] == d[x] + 1) {
      w = dfs(e[i].t, std::min(fl - used, e[i].w));  // NOLINT
      e[i].w -= w;
      e[i ^ 1].w += w;
      used += w;
      if (used == fl) return fl;
    }
  }
  if (!used) d[x] = -1;
  return used;
}
void dinic() {
  ans = 0;
  while (bfs()) ans += dfs(S, oo);
}
void solve(int ll, int rr) {
  if (ll == rr) return;
  S = st[ll];
  T = st[rr];
  for (int i = 2; i <= cnt; i += 2) {
    e[i].w = (e[i].w + e[i ^ 1].w) >> 1;
    e[i ^ 1].w = e[i].w;
  }
  dinic();
  int lt = ll - 1, rt = rr + 1;
  g(i, 1, n) g(j, i + 1, n) {
    if (vis[i] != vis[j] && ans < A[i][j]) A[i][j] = ans;
  }
  g(i, 1, n) {
    if (p[i] > rr || p[i] < ll) continue;
    if (vis[i] != ti) {
      st[++lt] = i;
      p[i] = lt;
    } else {
      st[--rt] = i;
      p[i] = rt;
    }
  }
  solve(ll, lt);
  solve(rt, rr);
}
int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  scanf("%d", &cas);
  while (cas--) {
    init();
    scanf("%d%d", &n, &m);
    g(i, 1, m) {
      scanf("%d%d%d", &a, &b, &c);
      add(a, b, c);
    }
    g(i, 1, n) {
      st[i] = i;
      p[i] = i;
    }
    solve(1, n);
    scanf("%d", &q);
    while (q--) {
      scanf("%d", &k);
      ans = 0;
      g(i, 1, n) g(j, i + 1, n) ans += A[i][j] <= k;
      printf("%d\n", ans);
    }
    if (T) puts("");
  }

#ifdef LOCAL
  fclose(stdin);
  fclose(stdout);
#endif
  return 0;
}
