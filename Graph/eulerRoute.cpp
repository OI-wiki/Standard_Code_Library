/**
 * @Author SCaffrey(sirius.caffrey@gmail.com)
 * @Copyright SATA
 * http://uoj.ac/problem/117
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

struct node {
  int t, w, x;
} e[MAXN << 2];
int head[MAXN], cnt = 1;
int out[MAXN], in[MAXN];
inline void add(int s, int t, int w) {
  e[++cnt].t = t; e[cnt].x = head[s]; head[s] = cnt; e[cnt].w = w;
  ++out[s]; ++in[t];
}
bool vis[MAXN << 2];
int sta[MAXN << 2], top;
void dfs(int x) {
  for (int i = head[x]; i; i = head[x]) {
    while (i && vis[abs(e[i].w)]) i = e[i].x;
    if (!i) return;
    vis[abs(e[i].w)] = 1;
    head[x] = e[i].x;
    dfs(e[i].t);
    sta[top++] = e[i].w;
  }
}
int n, m, tp;
int x, y;
int main() {
  scanf("%d%d%d", &tp, &n, &m);
  g(i, 1, m) {
    scanf("%d%d", &x, &y);
    add(x, y, i);
    if (tp == 1) add(y, x, -i);
  }
  g(i, 1, n) {
    if (in[i] != out[i] || (tp == 1 && in[i] % 2)) {
      puts("NO");
      return 0;
    }
  }
  dfs(e[cnt].t);
  g(i, 1, m) if (!vis[i]) {
    puts("NO");
    return 0;
  }
  dfs(e[cnt].t);
  puts("YES");
  gd(i, top - 1, 0) printf("%d ", sta[i]);
  return 0;
}
