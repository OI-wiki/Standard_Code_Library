/**
 * @Author SCaffrey(sirius.caffrey@gmail.com)
 * @Copyright SATA
 * http://poj.org/problem?id=1741
 */
#include <cstdio>// NOLINT
#include <cstring>// NOLINT
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

int n, k;
int sum, ans, root;
int dep[MAXN], d[MAXN], f[MAXN], sz[MAXN];
bool vis[MAXN];
struct node {
  int t, w, x;
} e[MAXN << 1];
int head[MAXN], cnt = 1;
inline void add(int s, int t, int w) {
  e[++cnt].t = t; e[cnt].w = w; e[cnt].x = head[s]; head[s] = cnt;
  e[++cnt].t = s; e[cnt].w = w; e[cnt].x = head[t]; head[t] = cnt;
}
void getRoot(int x, int fa) {
  sz[x] = 1; f[x] = 0;
  for (int i = head[x]; i; i = e[i].x) {
    if (e[i].t == fa || vis[e[i].t]) continue;
    getRoot(e[i].t, x);
    sz[x] += sz[e[i].t];
    f[x] = std::max(f[x], sz[e[i].t]);
  }
  f[x] = std::max(f[x], sum - sz[x]);
  if (f[x] < f[root]) root = x;
}
void getDep(int x, int fa) {
  dep[++dep[0]] = d[x];
  for (int i = head[x]; i; i = e[i].x) {
    if (e[i].t == fa || vis[e[i].t]) continue;
    d[e[i].t] = d[x] + e[i].w;
    getDep(e[i].t, x);
  }
}
int calc(int x, int now) {
  d[x] = now; dep[0] = 0;
  getDep(x, 0);
  std::sort(dep + 1, dep + dep[0] + 1);
  int t = 0, l, r;
  for (l = 1, r = dep[0]; l < r;) {
    if (dep[l] + dep[r] <= k) {
      t += r - l; ++l;
    } else {
      --r;
    }
  }
  return t;
}
void work(int x) {
  ans += calc(x, 0);
  vis[x] = 1;
  for (int i = head[x]; i; i = e[i].x) {
    if (vis[e[i].t]) continue;
    ans -= calc(e[i].t, e[i].w);
    sum = sz[e[i].t];
    root = 0;
    getRoot(e[i].t, 0);
    work(root);
  }
}
int s, t, w;
int main() {
  while (233) {
    ans = 0; root = 0; cnt = 0;
    scanf("%d%d", &n, &k);
    if (!n) break;
    memset(vis, 0, sizeof vis);
    memset(head, 0, sizeof head);
    f(i, 1, n) {
      scanf("%d%d%d", &s, &t, &w);
      add(s, t, w);
    }
    sum = n; f[0] = ~0u >> 2;
    getRoot(1, 0);
    work(root);
    printf("%d\n", ans);
  }
  return 0;
}
