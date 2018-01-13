/**
 * @Author Ir1d(sirius.caffrey@gmail.com)
 * @Copyright SATA
 * @Example https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&category=17&page=show_problem&problem=1486
 */
#include <cstdio>// NOLINT
#include <cstring>// NOLINT
#include <bits/stdc++.h>// NOLINT
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

double a;
inline double F(double x) {
  return sqrt(1 + 4 * a * a * x * x);
}
inline double simpson(double a, double b) {
  double c = a + (b - a) / 2;
  return (F(a) + F(b) + 4 * F(c)) * (b - a) / 6.0;
}
double asr(double a, double b, double eps, double A) {
  double c = a + (b - a) / 2;
  double L = simpson(a, c), R = simpson(c, b);
  if (fabs(L + R - A) <= 15 * eps) return L + R + (L + R - A) / 15.00;
  return asr(a, c, eps / 2, L) + asr(c, b, eps / 2, R);
}
double asr(double a, double b, double eps) {
  return asr(a, b, eps, simpson(a, b));
}
double getAns(double w, double h) {
  a = 4.0 * h / (w * w);
  return asr(0, w / 2, 1e-5) * 2;
}
int T;
int D, H, B, L;
int n;
double D1, L1;
double x, y, md;
// LA3485
int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  scanf("%d", &T);
  g(cas, 1, T) {
    scanf("%d%d%d%d", &D, &H, &B, &L);
    n = (B + D - 1) / D;
    D1 = B * 1. / n;
    L1 = L * 1. / n;
    x = 0, y = H;
    while (y - x > 1e-5) {
      md = x + (y - x) / 2.0;
      if (getAns(D1, md) < L1) x = md;
      else y = md; // NOLINT
    }
    if (cas > 1) puts("");
    printf("Case %d:\n%.2lf\n", cas, H - x);
  }

#ifdef LOCAL
  fclose(stdin);
  fclose(stdout);
#endif
  return 0;
}


