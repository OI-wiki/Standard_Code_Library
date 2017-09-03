/**
 * @author SCaffrey(sirius.caffrey@gmail.com)
 * @Copyright SATA(The Star And Thank Author License)
 * http://poj.org/problem?id=2155
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

inline void read(int &x) {// NOLINT
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
int n;
int t[1033][1033];
void upd(int x, int y) {
  for (int i = x; i; i -= i & -i) {
    for (int j = y; j; j -= j & -j) {
      t[i][j] ^= 1;
    }
  }
}
int get(int x, int y) {
  int res = 0;
  for (int i = x; i <= n; i += i & -i) {
    for (int j = y; j <= n; j += j & -j) {
      res += t[i][j];
    }
  }
  return res & 1;
}
int T;
int x1, y1, x2, y2;
int m;
char buf[12];
int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    memset(t, 0, sizeof t);
    while (m--) {
      scanf("%s%d%d", buf, &x1, &y1);
      if (buf[0] == 'C') {
        scanf("%d%d", &x2, &y2);
        upd(x1 - 1, y1 - 1);
        upd(x2, y2);
        upd(x2, y1 - 1);
        upd(x1 - 1, y2);
      } else {
        printf("%d\n", get(x1, y1));
      }
    }
    puts("");
  }

#ifdef LOCAL
  fclose(stdin);
  fclose(stdout);
#endif
  return 0;
}

