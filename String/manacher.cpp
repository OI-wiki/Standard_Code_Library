/**
 * @Author SCaffrey(sirius.caffrey@gmail.com)
 * @Copyright SATA
 * http://hihocoder.com/problemset/problem/1032
 */
#include <cstdio>// NOLINT
#include <cstring>// NOLINT
#include <algorithm>// NOLINT
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
const int MAXN = 1000033;

char buf[MAXN];
char s[MAXN * 2];
int n;
int p[MAXN * 2];
int mx, id;
int T;
void get() {
  mx = 0;
  f(i, 1, n) {
    if (mx > i) {
      p[i] = std::min(p[2 * id - i], mx - i);
    } else {
      p[i] = 1;
    }
    while (s[i + p[i]] == s[i - p[i]]) ++p[i];
    if (i + p[i] > mx) {
      mx = i + p[i]; id = i;
    }
  }
}
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%s", buf);
    n = strlen(buf);
    s[0] = '$'; s[1] = '#';
    f(i, 0, n) {
      s[i * 2 + 2] = buf[i];
      s[i * 2 + 3] = '#';
    }
    n = n * 2 + 2;
    s[n] = '\0';
    get();
    mx = 0;
    f(i, 0, n) if (mx < p[i]) mx = p[i];
    printf("%d\n", mx - 1);
  }
  return 0;
}
