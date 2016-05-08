/**
 * @Author SCaffrey(sirius.caffrey@gmail.com)
 * @Copyright SATA
 * http://hihocoder.com/problemset/problem/1174
 */
#include <cstdio>// NOLINT
#include <cstring>// NOLINT
#include <queue>// NOLINT
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

int T;
int n, m;
struct node {
  int t, x;
} e[MAXN * 10];
int head[MAXN], cnt = 1;
int u, v;
inline void add(int s, int t) {
  e[++cnt].t = t; e[cnt].x = head[s]; head[s] = cnt;
  // e[++cnt].t = s; e[cnt].x = head[t]; head[t] = cnt;
}
int in[MAXN], done;
std::queue<int> Q;
int main() {
  scanf("%d", &T);
  while (T--) {
    memset(head, 0, sizeof head); cnt = 1; done = 0;
    memset(in, 0, sizeof in);
    scanf("%d%d", &n, &m);
    f(i, 0, m) {
      scanf("%d%d", &u, &v);
      add(u, v);
      ++in[v];
    }
    g(i, 1, n) if (!in[i]) {
      Q.push(i);
    }
    while (!Q.empty()) {
      u = Q.front(); Q.pop();
      ++done;
      for (int i = head[u]; i; i = e[i].x) {
        if (--in[ e[i].t ] == 0) Q.push(e[i].t);
      }
    }
    // printf("%d\n", done);
    if (done == n) {
      puts("Correct");
    } else {
      puts("Wrong");
    }
  }
  return 0;
}
