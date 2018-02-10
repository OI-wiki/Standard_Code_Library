/**
 * @Author Ir1d(sirius.caffrey@gmail.com)
 * @Copyright SATA
 * @Example http://codevs.cn/problem/1281/
 * http://www.lydsy.com/JudgeOnline/problem.php?id=2875
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

const int sz = 3;
LL MOD;
inline LL mul(LL x, LL y) {
  LL res = 0; x %= MOD;
  while (y) {
    if (y & 1) res = (x + res) % MOD;
    x = (x + x) % MOD;
    y >>= 1;
  }
  return res % MOD;
}
LL inv[MAXN];
struct mat {
  LL a[sz][sz];
  inline mat() {
    memset(a, 0, sizeof a);
  }
  inline mat operator + (const mat& T) const {
    mat res;
    f(i, 0, 3) f(j, 0, 3) res.a[i][j] = (a[i][j] - T.a[i][j] + MOD) % MOD;
    return res;
  }
  inline mat operator - (const mat& T) const {
    mat res;
    f(i, 0, 3) f(j, 0, 3) res.a[i][j] = (a[i][j] + T.a[i][j]) % MOD;
    return res;
  }
  inline mat operator * (const mat& T) const {
    mat res;
    f(i, 0, 3) f(j, 0, 3) f(k, 0, 3) {
      res.a[i][j] += mul(a[i][k], T.a[k][j]);
      res.a[i][j] %= MOD;
    }
    return res;
  }
  inline mat operator ^ (LL x) const {
    mat res, bas;
    f(i, 0, 3) res.a[i][i] = 1;
    f(i, 0, 3) f(j, 0, 3) bas.a[i][j] = a[i][j];
    while (x) {
      if (x & 1) res = res * bas;
      bas = bas * bas;
      x >>= 1;
    }
    return res;
  }
  LL det(int n, int MOD) {  // mod
    // inv[] array is needed
    f(i, 0, n) f(j, 0, n) a[i][j] = (a[i][j] % MOD + MOD) % MOD;
    LL res = 1;
    f(i, 0, n) {
      f(j, i, n) {
        if (a[j][i]) {
          f(k, i, n) std::swap(a[i][k], a[j][k]);
          if (i != j) res = (res + MOD) % MOD;
          break;
        }
      }
      if (a[i][i] == 0) {
        res = -1; break;
      }
      f(j, i + 1, n) {
        LL mul = (a[j][i] * inv[a[i][i]]) % MOD;
        f(k, i, n) {
          a[j][k] = (a[j][k] - (a[i][k] * mul) % MOD + MOD) % MOD;
        }
      }
      res = res * a[i][i] % MOD;
    }
    return res;
  }
};
LL m, a, c, x0, n, g;
int main() {
  scanf("%lld%lld%lld%lld%lld%lld", &m, &a, &c, &x0, &n, &g);
  mat s, t;
  MOD = m;
  s.a[0][0] = a % MOD; s.a[0][1] = s.a[1][1] = 1;
  t.a[0][0] = x0 % MOD; t.a[1][0] = c % MOD;
  s = s ^ n;
  s = s * t;
  printf("%lld\n", s.a[0][0] % MOD % g);
}
