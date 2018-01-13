/**
 * @author SCaffrey (srius.caffrey@gmail.com)
 * @Copyright SATA(The Star And Thank Author License)
 * @Example http://hihocoder.com/problemset/problem/1014
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

int n, m;
char buf[100033];
struct node {
  int cnt;
  node* ch[27];
  inline node() {
    cnt = 0; memset(ch, 0, sizeof ch);
  }
} *root;
int get() {
  node* tee = root;
  f(j, 0, strlen(buf)) {
    if (tee->ch[ buf[j] - 'a' ] == NULL) {
      return 0;
      // tee->ch[ buf[j] - 'a' ] = new node();
    }
    tee = tee->ch[ buf[j] - 'a' ];
  }
  return tee->cnt;
}
int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  scanf("%d", &n);
  root = new node();
  f(i, 0, n) {
    scanf("%s", buf);
    node* tee = root;
    f(j, 0, strlen(buf)) {
      if (tee->ch[ buf[j] - 'a' ] == NULL) {
        tee->ch[ buf[j] - 'a' ] = new node();
      }
      tee = tee->ch[ buf[j] - 'a' ]; ++tee->cnt;
    }
  }
  scanf("%d", &m);
  f(i, 0, m) {
    scanf("%s", buf);
    printf("%d\n", get());
  }

#ifdef LOCAL
  fclose(stdin);
  fclose(stdout);
#endif
  return 0;
}

