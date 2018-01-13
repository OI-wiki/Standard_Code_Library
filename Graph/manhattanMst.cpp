/**
 * @Author Ir1d(sirius.caffrey@gmail.com)
 * @Copyright SATA
 * @Example http://poj.org/problem?id=3241
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

inline void read(int &x) { // NOLINT
  char c = getchar();
  int f = 1;
  while (c < '0' || c > '9') {
    if (c == '-') f = -1;
    c = getchar();
  }
  x = 0;
  while (c >= '0' && c <= '9') {
    x = (x << 1) + (x << 3) + c - 48;
    c = getchar();
  }
  x *= f;
}
int n, m, w[MAXN], c[MAXN], t[MAXN], fa[MAXN];
LL ans;
struct node {
  int x, y, p;
  inline node() {}
  inline node(int X, int Y, int P) {
    x = X; y = Y; p = P;
  }
} a[MAXN], b[MAXN], e[MAXN << 2];
inline bool cmp(const node& a, const node& b) {
  if (a.x == b.x) return a.y < b.y;
  return a.x < b.x;
}
inline bool cmpe(const node& a, const node& b) {
  return a.p < b.p;
}
inline int lower(int x) {
  int lb = 1, rb = n, res, md;
  while (lb <= rb) {
    md = lb + (rb - lb >> 1);
    if (c[md] <= x) {
      lb = (res = md) + 1;
    } else {
      rb = md - 1;
    }
  }
  return res;
}
inline int abs(int x) {
  if (x < 0) return -x;
  return x;
}
inline int dis(int x, int y) {
  return abs(a[x].x - a[y].x) + abs(a[x].y - a[y].y);
}
inline void ins(int x, int p) {
  for (; x <= n; x += x & -x) if (w[p] <= w[t[x]]) t[x] = p; // NOLINT
}
inline int ask(int x) {
  int res = 0;
  for (; x; x -= x & -x) if (w[t[x]] <= w[res]) res = t[x]; // NOLINT
  return res;
}
inline int get(int x) {
  int tee = fa[x], q;
  while (tee != fa[tee]) tee = fa[tee];
  while (x != tee) {
    q = fa[x]; fa[x] = tee; x = q;
  }
  return tee;
}
void solve() {
  std::sort(b + 1, b + n + 1, cmp);
  std::sort(c + 1, c + n + 1);
  int j;
  g(i, 1, n) {
    j = ask(lower(b[i].y));
    if (j) e[++m] = node(b[i].p, j, dis(b[i].p, j));
    ins(lower(b[i].y), b[i].p);
  }
}
int k;
LL getMST() {
  w[0] = ~0U >> 1;
  m = ans = 0;
  g(i, 1, n) fa[i] = i;
  g(i, 1, n) {
    b[i] = node(-a[i].x, a[i].x - a[i].y, i);
    c[i] = b[i].y;
    w[i] = a[i].x + a[i].y;
    t[i] = 0;
  }
  solve();
  g(i, 1, n) {
    b[i] = node(-a[i].y, a[i].y - a[i].x, i);
    c[i] = b[i].y;
    t[i] = 0;
  }
  solve();
  g(i, 1, n) {
    b[i] = node(a[i].y, -a[i].x - a[i].y, i);
    c[i] = b[i].y;
    w[i] = a[i].x - a[i].y;
    t[i] = 0;
  }
  solve();
  g(i, 1, n) {
    b[i] = node(-a[i].x, a[i].y + a[i].x, i);
    c[i] = b[i].y;
    t[i] = 0;
  }
  solve();
  std::sort(e + 1, e + m + 1, cmpe);
  ans = 0;
  int cnt = n;
  g(i, 1, m) if (get(e[i].x) != get(e[i].y)) {
    fa[fa[e[i].x]] = fa[e[i].y];
    --cnt;
//    printf("%d %d: %d %d\n", cnt, e[i].p, e[i].x, e[i].y);
    if (cnt == k) return e[i].p;
  }
}
int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  read(n); read(k);
  g(i, 1, n) read(a[i].x), read(a[i].y);
  printf("%lld\n", getMST());

#ifdef LOCAL
  fclose(stdin);
  fclose(stdout);
#endif
  return 0;
}
