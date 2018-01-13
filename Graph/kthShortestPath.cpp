/**
 * @Author Ir1d (sirius.caffrey@gmail.com)
 * @Copyright SATA
 * @Example http://poj.org/problem?id=2449
 */

#include <cstdio>// NOLINT
#include <queue>// NOLINT
#include <cstring>// NOLINT
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
  int t, w, x;
} e[MAXN << 1], E[MAXN << 1];
int head[MAXN], cnt = 1;
int Head[MAXN], Cnt = 1;
inline void add(int s, int t, int w) {
  e[++cnt].t = t; e[cnt].x = head[s]; head[s] = cnt; e[cnt].w = w;
}
inline void Add(int s, int t, int w) {
  E[++Cnt].t = t; E[Cnt].x = Head[s]; Head[s] = Cnt; E[Cnt].w = w;
}
struct node {
  int fx, gx, v;
  inline node() {}
  inline node(int a, int b, int c):fx(a), gx(b), v(c) {}
  inline bool operator < (const node& T) const {
    return fx > T.fx;
  }
};
int inq[MAXN];
int dis[MAXN];
int k, mx;
void init() {
  memset(head, 0, sizeof head);
  memset(Head, 0, sizeof Head);
  cnt = Cnt = 0;
  memset(dis, 0x1f, sizeof dis);
  mx = dis[0];
}
std::queue<int> Q;
void spfa(int ed) {
  while (!Q.empty()) Q.pop();
  Q.push(ed);
  int u, v;
  inq[ed] = 1; dis[ed] = 0;
  while (!Q.empty()) {
    u = Q.front(); Q.pop();
    for (int i = Head[u]; i; i = E[i].x) {
      v = E[i].t;
      if (dis[v] > dis[u] + E[i].w) {
        dis[v] = dis[u] + E[i].w;
        if (!inq[v]) {
          inq[v] = 1;
          Q.push(v);
        }
      }
      inq[u] = 0;
    }
  }
}
std::priority_queue<node> PQ;
int aStar(int st, int ed) {
  while (!PQ.empty()) PQ.pop();
  if (dis[st] == mx) return -1;
  memset(inq, 0, sizeof inq);
  PQ.push(node(dis[st], 0, st));
  node tee;
  while (!PQ.empty()) {
    tee = PQ.top(); PQ.pop();
    ++inq[tee.v];
    if (inq[ed] == k) return tee.fx;
    if (inq[tee.v] > k) continue;
    for (int i = head[tee.v]; i; i = e[i].x) {
      node cur(dis[e[i].t] + tee.gx + e[i].w, tee.gx + e[i].w, e[i].t);
      PQ.push(cur);
    }
  }
  return -1;
}
int n, m, st, ed, u, v, w;
int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  init();
  scanf("%d%d", &n, &m);
  f(i, 0, m) {
    scanf("%d%d%d", &u, &v, &w);
    add(u, v, w);
    Add(v, u, w);
  }
  scanf("%d%d%d", &st, &ed, &k);
  spfa(ed);
  if (st == ed) ++k;
  printf("%d\n", aStar(st, ed));

#ifdef LOCAL
  fclose(stdin);
  fclose(stdout);
#endif
  return 0;
}
