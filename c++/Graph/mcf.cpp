/**
 * @Author SCaffrey(sirius.caffrey@gmail.com)
 * @Copyright SATA
 * http://www.lydsy.com/JudgeOnline/problemset.php?search=1834
 */
#include <cstdio>// NOLINT
#include <cstring>// NOLINT
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

int n, m, k;
int dis[MAXN];
bool inq[MAXN];
struct node {
  int s, w, t, c, q, x;
} e[MAXN];
int head[MAXN], cnt = 1;
inline void add(int s, int t, int w, int c) {
  e[++cnt].s = s; e[cnt].t = t; e[cnt].w = w; e[cnt].q = c; e[cnt].x = head[s]; head[s] = cnt;// NOLINT
  e[++cnt].s = t; e[cnt].t = s; e[cnt].w = 0; e[cnt].q = -c; e[cnt].x = head[t]; head[t] = cnt;// NOLINT
}
inline void add2(int s, int t, int w, int c) {
  e[++cnt].s = s; e[cnt].t = t; e[cnt].w = w; e[cnt].c = c; e[cnt].x = head[s]; head[s] = cnt;// NOLINT
  e[++cnt].s = t; e[cnt].t = s; e[cnt].w = 0; e[cnt].c = -c; e[cnt].x = head[t]; head[t] = cnt;// NOLINT
}
void upd() {
  int t = cnt;
  for (int i = 2; i <= t; i += 2) add2(e[i].s, e[i].t, k, e[i].q);
}
std::queue<int> Q;
int S, T;
bool bfs() {
  memset(dis, -1, sizeof dis);
  while (!Q.empty()) Q.pop();
  int u;
  Q.push(S); dis[S] = 0;
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
  if (x == n) return fl;
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
int ans;
void dinic() {
  while (bfs()) ans += dfs(S, oo);
}
int a[MAXN], pre[MAXN];
bool spfa() {
  memset(dis, 0x1f, sizeof dis);
  memset(inq, 0, sizeof inq);
  int mx = dis[0]; a[0] = mx;
  dis[0] = 0;
  while (!Q.empty()) Q.pop();
  Q.push(0); inq[0] = 1;
  int u;
  while (!Q.empty()) {
    u = Q.front(); Q.pop();
    for (int i = head[u]; i; i = e[i].x) {
      if (e[i].w && dis[e[i].t] > dis[u] + e[i].c) {
        dis[e[i].t] = dis[u] + e[i].c;
        a[e[i].t] = std::min(a[u], e[i].w);
        pre[e[i].t] = i;
        if (!inq[e[i].t]) {
          Q.push(e[i].t);
          inq[e[i].t] = 1;
        }
      }
    }
    inq[u] = 0;
  }
  return dis[n] != mx;
}
void mcf() {
  ans += dis[n] * a[n];
  int u = n;
  while (u) {
    e[ pre[u] ].w -= a[n];
    e[ pre[u] ^ 1 ].w += a[n];
    u = e[ pre[u] ].s;
  }
}
int u, v, w, c;
int main() {
  scanf("%d%d%d", &n, &m, &k);
  g(i, 1, m) {
    scanf("%d%d%d%d", &u, &v, &w, &c);
    add(u, v, w, c);
  }
  S = 1; T = n;
  dinic();
  printf("%d ", ans);
  ans = 0;
  upd();
  add(0, 1, k, 0);
  while (spfa()) mcf();
  printf("%d\n", ans);
  return 0;
}
