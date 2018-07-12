/**
 * @Author Ir1d(sirius.caffrey@gmail.com)
 * @Copyright SATA
 * @Example http://uoj.ac/problem/34
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

int bitrev[MAXN], n, m, l, N, bitl;
struct complex {
  double r, i;
  inline complex(double r = 0, double i = 0) : r(r), i(i) {}  // NOLINT
  inline friend complex operator+(const complex& a, const complex& b) {
    return complex(a.r + b.r, a.i + b.i);
  }
  inline friend complex operator-(const complex& a, const complex& b) {
    return complex(a.r - b.r, a.i - b.i);
  }
  inline friend complex operator*(const complex& a, const complex& b) {
    return complex(a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r);
  }
} a[MAXN], b[MAXN];
void fft(complex* a, int n, int ctf) {
  f(i, 0, n) if (i < bitrev[i]) std::swap(a[i], a[bitrev[i]]);  // NOLINT
  for (int i = 1; i < n; i <<= 1) {
    complex wn(cos(pi / i), ctf * sin(pi / i));
    for (int j = 0; j < n; j += i << 1) {
      complex w(1, 0);
      for (int k = 0; k < i; ++k, w = w * wn) {
        complex x = a[j + k], y = w * a[j + k + i];
        a[j + k] = x + y;
        a[j + k + i] = x - y;
      }
    }
  }
  if (ctf == -1) f(i, 0, n) a[i].r /= n;
}
int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  scanf("%d%d", &n, &m);
  ++n;
  ++m;
  l = n + m - 1;
  for (N = 1, bitl = 0; N < l; N <<= 1, ++bitl)
    ;
  f(i, 1, N) bitrev[i] = (bitrev[i >> 1] >> 1) | (i & 1) << (bitl - 1);
  f(i, 0, n) scanf("%lf", &a[i].r);
  f(i, 0, m) scanf("%lf", &b[i].r);
  fft(a, N, 1);
  fft(b, N, 1);
  f(i, 0, N) a[i] = a[i] * b[i];
  fft(a, N, -1);
  f(i, 0, l) printf("%d ", int(a[i].r + 0.5));  // NOLINT
  puts("");

#ifdef LOCAL
  fclose(stdin);
  fclose(stdout);
#endif
  return 0;
}
