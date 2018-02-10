/**
 * @Author Ir1d(sirius.caffrey@gmail.com)
 * @Copyright SATA
 * @Example http://www.lydsy.com:808/JudgeOnline/problem.php?id=1013
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


int n;
double f[23], a[23][23];
double sqr(double x) {
  return x * x;
}
double tee;
void init() {
  scanf("%d", &n);
  f(i, 0, n) scanf("%lf", f + i);
  f(i, 0, n) f(j, 0, n) {
    scanf("%lf", &tee);
    a[i][j] = 2 * (tee - f[j]);
    a[i][n] += sqr(tee) - sqr(f[j]);
  }
}
void gauss(int n) {
  f(i, 0, n) {
    f(j, i, n) {
      if (fabs(a[j][i]) > EPS) {
        g(k, i, n) std::swap(a[i][k], a[j][k]);
        break;
      }
    }
    if (fabs(a[i][i]) < EPS) continue;
    f(j, 0, n)
      if (i != j && fabs(a[j][i]) > EPS) {
        double det = a[j][i] / a[i][i];
        g(k, i, n) a[j][k] -= a[i][k] * det;
      }
  }
  f(i, 0, n) {
    if (fabs(a[i][i]) < EPS) {
      if (fabs(a[i][n]) > EPS) {
        puts("No Solution");
      } else {
        puts("Infinite");
      }
    } else {
      a[i][n] /= a[i][i];
      if (fabs(a[i][n]) < EPS) a[i][n] = 0;
    }
  }
}
int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  init();
  gauss(n);
  f(i, 0, n) printf("%.3lf%c", a[i][n], i == n - 1 ? '\n' : ' ');

#ifdef LOCAL
  fclose(stdin);
  fclose(stdout);
#endif
  return 0;
}
