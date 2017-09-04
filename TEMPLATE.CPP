/**
 * @name TEMPLATE.CPP
 * @subject Segment Tree
 * @author Ir1d(sirius.caffrey@gmail.com)
 * @copyright SATA(The Star And Thank Author License)
 * @comment This is a segment tree implemented with pointers.(kidding)
 */

// I used DocBlockr to make this comment!
// Simply type '/**' in the first line

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

int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

#ifdef LOCAL
  fclose(stdin);
  fclose(stdout);
#endif
  return 0;
}

