/**
 * @Author SCaffrey(sirius.caffrey@gmail.com)
 * @Copyright SATA(The Star And Thank Author License)
 * http://poj.org/problem?id=3253
 */
#include <cstdio>// NOLINT
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

LL h[MAXN];
int hs;
void swim(int p) {
  int q = p >> 1;
  LL a = h[p];
  while (q && a < h[q]) {
    h[p] = h[q]; p = q; q = p >> 1;
  }
  h[p] = a;
}
void sink(int p) {
  int q = p << 1;
  LL a = h[p];
  while (q <= hs) {
    if (q < hs && h[q + 1] < h[q]) ++q;
    if (h[q] >= a) break;
    h[p] = h[q]; p = q; q = p << 1;
  }
  h[p] = a;
}
void insert(LL a) {
  h[++hs] = a; swim(hs);
}
LL getMin() {
  LL r = h[1]; h[1] = h[hs--];
  sink(1);
  return r;
}
void build() {
  fd(i, hs / 2, 0) sink(i);
}
void decreaseKey(int p, LL a) {
  h[p] = a; swim(p);
}
int n;
LL ans = 0, tee;
int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  scanf("%d", &n);
  g(i, 1, n) scanf("%lld", h + i);
  hs = n;
  build();
  f(i, 1, n) {
    tee = getMin();
    tee += getMin();
    insert(tee);
    ans += tee;
  }
  printf("%lld\n", ans);

#ifdef LOCAL
  fclose(stdin);
  fclose(stdout);
#endif
  return 0;
}

