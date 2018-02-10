/**
 * @Author Ir1d(sirius.caffrey@gmail.com)
 * @Copyright SATA
 * @Example http://acm.hdu.edu.cn/showproblem.php?pid=3542
 * @Notes 分解素数$p$为$x^2+y^2$的费马降阶法，失败返回$-1$，主程序调用calcu(p,x,y)
 */
#include <cstdio>// NOLINT
#include <algorithm>// NOLINT
#include <cstdlib>// NOLINT
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

int p, expp, A, B, aa, ans, tt;
LL m;
LL exp(int a, int b, LL mod) {
  LL ans = 1, bas = a;
  while (b) {
    if (b & 1) ans = ans * bas % mod;
    bas = bas * bas % mod;
    b >>= 1;
  }
  return ans;
}
int calcu(int p, int &x, int &y) { // NOLINT
  if (p % 4 != 1) return -1;
  expp = (p - 1) / 4;
  int A, B, aa;
  while (1) {
    aa = rand() % p; // NOLINT
    if (aa == 0) continue;
    A = exp(aa, expp, p);
    ans = (((LL)A % p) * ((LL)A % p)) % p;
    if (ans == p - 1) break;
  }
  B = 1;
  LL M = ((LL)A * (LL)A + (LL)B * (LL)B) / p;
  if (M != 1) B = p;
  while (M != 1) {
    if (B > A) std::swap(A, B);
    tt = A; A = B; B = tt % B;
    M = ((LL)A * (LL)A + (LL)B * (LL)B) / p;
  }
  if (B <= A) {
    x = B; y = A;
  } else {
    x = A; y = B;
  }
}
int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  int n;
  int x, y;
  while (scanf("%d", &n) == 1) {
    if (calcu(n, x, y) != -1) {
      printf("Legal %d %d\n", x, y);
    } else {
      puts("Illegal");
    }
  }

#ifdef LOCAL
  fclose(stdin);
  fclose(stdout);
#endif
  return 0;
}
