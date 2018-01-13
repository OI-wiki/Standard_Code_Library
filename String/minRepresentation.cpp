/**
 * @Author Ir1d(sirius.caffrey@gmail.com)
 * @Copyright SATA
 * @example http://poj.org/problem?id=1509
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

int n, t;
char ss[MAXN], s[MAXN];
int minRep() {
  int i = 0, j = 1, k = 0, t;
  while (i < n && j < n && k < n) {
    t = s[(i + k) % n] - s[(j + k) % n];
    if (t == 0) {
      k++;
      continue;
    }
    if (t > 0) i += k + 1;
    else j += k + 1; //NOLINT
    if (i == j) ++j;
    k = 0;
  }
  if (i < j) return i;
  return j;
}
int T;
int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  scanf("%d", &T);
  f(i, 0, T) {
    scanf("%s", ss);
    n = strlen(ss);
    strcpy(s, ss); //NOLINT
    strcpy(s + n, ss); //NOLINT
    n <<= 1;
    printf("%d\n", minRep() + 1);
  }

#ifdef LOCAL
  fclose(stdin);
  fclose(stdout);
#endif
  return 0;
}


