/**
 * @Author Ir1d(sirius.caffrey@gmail.com)
 * @Copyright SATA
 * @Example 
 */
#pragma GCC optimize("O2")
#include <cstdio>// NOLINT
#include <cstring>// NOLINT
#include <map>// NOLINT
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

std::map<LL, int> M;
const int MOD = 9986213;
int a, b, c;
inline LL get(LL a, LL b, LL c) {
  LL res = 1, bas = a;
  while (b) {
    if (b & 1) res = res * bas % c;
    bas = bas * bas % c;
    b >>= 1;
  }
  return res;
}
void solve(LL a, LL b, LL c) {
  // L = i * M - j; i from [1 .. M], j from [1 .. M]
  LL m  = ceil(sqrt(double(c))), s, x; // s = a ** m
  b %= c;
  if (b == 0) {
    puts("no solution");
    return;
  }
  M.clear();
  M[b] = 0;
  s = get(a, m, c);
  g(j, 1, m) {
    b = b * a % c;
    M[b] = j;
  }
  // printf(LLD"\n", m * (m - 1));
  x = 1;
  g(i, 1, m) {
    x = x * s % c;
    if (M[x]) {
    // if (M.find(x) != M.end()) {
      // printf("%d %d %d\n", i, M[x], m);
      printf(LLD"\n", (i * m - M[x] + c) % c);
      return;
    }
  }
  puts("no solution");
}
int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  while (~scanf("%d%d%d", &c, &a, &b)) {
    solve(a, b, c);
  }

#ifdef LOCAL
  fclose(stdin);
  fclose(stdout);
#endif
  return 0;
}

