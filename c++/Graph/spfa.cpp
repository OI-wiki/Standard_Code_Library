/**
 * @Author SCaffrey(sirius.caffrey@gmail.com)
 * @Copyright SATA
 * http://hihocoder.com/problemset/problem/1093
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

struct edeg {
  int t, w, x;
} e[MAXN * 20];
int head[MAXN], cnt = 1;
inline void add(int s, int t, int w) {
  e[++cnt].t = t; e[cnt].w = w; e[cnt].x = head[s]; head[s] = cnt;
  e[++cnt].t = s; e[cnt].w = w; e[cnt].x = head[t]; head[t] = cnt;
}
int n, m;
LL ans;
int dp[MAXN], ti[MAXN];
bool vis[MAXN];
std::queue<int> Q;
int u, v, s, t, w;
void spfa() {
  memset(dp, 0x1f, sizeof dp);
  Q.push(s); dp[s] = 0;
  int x;
  while (!Q.empty()) {
    x = Q.front(); Q.pop();
    for (int i = head[x]; i; i = e[i].x) {
      if (dp[e[i].t] > dp[x] + e[i].w) {
        dp[e[i].t] = dp[x] + e[i].w;
        if (++ti[e[i].t] > n) {
          exit(0);
        }
        if (!vis[e[i].t]) {
          vis[e[i].t] = 1;
          Q.push(e[i].t);
        }
      }
    }
    vis[x] = 0;
  }
  printf("%d\n", dp[t]);
}
int main() {
  scanf("%d%d%d%d", &n, &m, &s, &t);
  f(i, 0, m) {
    scanf("%d%d%d", &u, &v, &w);
    add(u, v, w);
  }
  spfa();
  return 0;
}
