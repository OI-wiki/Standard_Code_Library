/**
 * @Author SCaffrey(sirius.caffrey@gmail.com)
 * @Copyright SATA
 * http://www.icpc.moe/onlinejudge/showProblem.do?problemCode=2334
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

int nx[MAXN];
int v[MAXN], l[MAXN], r[MAXN], d[MAXN], root[MAXN];
int n, m;
void start() {
  f(i, 0, MAXN - 33) nx[i] = i + 1;
}
int merge(int x, int y) {
  if (!x) return y;
  if (!y) return x;
  if (v[x] < v[y]) std::swap(x, y);
  r[x] = merge(r[x], y);
  if (d[l[x]] < d[r[x]]) std::swap(l[x], r[x]);
  d[x] = d[r[x]] + 1;
  return x;
}
int init(int x) {
  int p = nx[0]; nx[0] = nx[p];
  v[p] = x; l[p] = r[p] = d[p] = 0;
  return p;
}
void del(int x) {
  nx[x] = nx[0]; nx[0] = x;
}
int insert(int x, int y) {
  return merge(x, init(y));
}
int top(int x) {
  return v[x];
}
int pop(int x) {
  int p = merge(l[x], r[x]);
  del(x);
  return p;
}
int fa[MAXN];
void init() {
  g(i, 0, n) fa[i] = i;
}
int get(int x) {
  int tee = fa[x], q;
  while (tee != fa[tee]) tee = fa[tee];
  while (x != tee) {
    q = fa[x]; fa[x] = tee; x = q;
  }
  return tee;
}
bool unite(int a, int b) {
  int x = get(a), y = get(b);
  if (x == y) return 0;
  fa[x] = y;
  return 1;
}
int tee, x, y, a, b;
int main() {
  while (~scanf("%d", &n)) {
    start();
    init();
    g(i, 1, n) {
      scanf("%d", &tee);
      root[i] = 0;
      root[i] = insert(root[i], tee);
    }
    scanf("%d", &m);
    f(i, 0, m) {
      scanf("%d%d", &a, &b);
      if (get(a) == get(b)) {
        puts("-1");
      } else {
        a = get(a); b = get(b);
        x = top(root[a]); root[a] = pop(root[a]);
        y = top(root[b]); root[b] = pop(root[b]);
        root[a] = insert(root[a], x / 2);
        root[b] = insert(root[b], y / 2);
        unite(a, b);
        root[b] = merge(root[a], root[b]);
        printf("%d\n", top(root[b]));
      }
    }
  }
  return 0;
}
