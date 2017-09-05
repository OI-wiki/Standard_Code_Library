/**
 * @author SCaffrey (sirius.caffrey@gmail.com)
 * @copyright SATA(The Star And Thank Author License)
 * http://www.lydsy.com:808/JudgeOnline/problem.php?id=3531
 */

#include <cstdio>// NOLINT
#include <cstring>// NOLINT
#include <algorithm>// NOLINT
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
int n, m, idx;
int w[MAXN], c[MAXN];
int fa[MAXN][18], dep[MAXN], belong[MAXN], pos[MAXN], sz[MAXN];
bool vis[MAXN];
struct edge {
  int t, x;
} e[MAXN << 3];
int head[MAXN], cnt = 1;
inline void add(int s, int t) {
  e[++cnt].t = t; e[cnt].x = head[s]; head[s] = cnt;
}
void dfs1(int x) {
  vis[x] = 1; sz[x] = 1;
  g(i, 1, 16) {
    if (dep[x] < (1 << i)) break;
    fa[x][i] = fa[ fa[x][i - 1] ][i - 1];
  }
  for (int i = head[x]; i; i = e[i].x) {
    if (vis[e[i].t]) continue;
    dep[e[i].t] = dep[x] + 1;
    fa[e[i].t][0] = x;
    dfs1(e[i].t);
    sz[x] += sz[e[i].t];
  }
}
void dfs2(int x, int chain) {
  pos[x] = ++idx; belong[x] = chain;
  int k = 0;
  for (int i = head[x]; i; i = e[i].x) {
    if (dep[e[i].t] > dep[x] && sz[e[i].t] > sz[k]) k = e[i].t;
  }
  if (!k) return;
  dfs2(k, chain);
  for (int i = head[x]; i; i = e[i].x) {
    if (e[i].t != k && dep[e[i].t] > dep[x]) dfs2(e[i].t, e[i].t);
  }
}
int lca(int x, int y) {
  if (dep[x] < dep[y]) std::swap(x, y);
  int t = dep[x] - dep[y];
  g(i, 0, 16) if (t & (1 << i)) x = fa[x][i];
  gd(i, 16, 0) if (fa[x][i] != fa[y][i]) {
    x = fa[x][i]; y = fa[y][i];
  }
  if (x == y) return x;
  return fa[x][0];
}
struct node {
  int mx, sum;
  node *ls, *rs;
  inline node() {
    mx = sum = 0;
    ls = rs = NULL;
  }
  inline void maintain() {
    if (ls == NULL) ls = new node();
    if (rs == NULL) rs = new node();
    mx = std::max(ls->mx, rs->mx);
    sum = ls->sum + rs->sum;
  }
  void update(int l, int r, int pos, int num) {
    if (l == r) {
      mx = sum = num;
      return;
    }
    if (ls == NULL) ls = new node();
    if (rs == NULL) rs = new node();
    int md = l + (r - l >> 1);
    if (pos <= md) {
      ls->update(l, md, pos, num);
    } else {
      rs->update(md + 1, r, pos, num);
    }
    maintain();
  }
  int getMax(int l, int r, int ll, int rr) {
    if (l == ll && r == rr) return mx;
    if (ls == NULL) ls = new node();
    if (rs == NULL) rs = new node();
    int md = l + (r - l >> 1);
    if (rr <= md) return ls->getMax(l, md, ll, rr);
    if (ll > md) return rs->getMax(md + 1, r, ll, rr);
    return std::max(ls->getMax(l, md, ll, md),
     rs->getMax(md + 1, r, md + 1, rr));
  }
  int getSum(int l, int r, int ll, int rr) {
    if (ll == l && rr == r) return sum;
    if (ls == NULL) ls = new node();
    if (rs == NULL) rs = new node();
    int md = l + (r - l >> 1);
    if (rr <= md) return ls->getSum(l, md, ll, rr);
    if (ll > md) return rs->getSum(md + 1, r, ll, rr);
    return ls->getSum(l, md, ll, md) + rs->getSum(md + 1, r, md + 1, rr);
  }
};
node *root[MAXN];
int solveMax(int c, int x, int f) {
  int mx = 0;
  while (belong[x] != belong[f]) {
    mx = std::max(mx, root[c]->getMax(1, n, pos[ belong[x] ], pos[x]));
    x = fa[ belong[x] ][0];
  }
  mx = std::max(mx, root[c]->getMax(1, n, pos[f], pos[x]));
  return mx;
}
int solveSum(int c, int x, int f) {
  int sum = 0;
  while (belong[x] != belong[f]) {
    sum += root[c]->getSum(1, n, pos[ belong[x] ], pos[x]);
    x = fa[ belong[x] ][0];
  }
  sum += root[c]->getSum(1, n, pos[f], pos[x]);
  return sum;
}
int u, v;
char s[12];
int x, y, lc, tee;
int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  read(n); read(m);
  g(i, 1, n) {
    read(w[i]); read(c[i]);
  }
  g(i, 1, 100000) root[i] = new node();
  f(i, 1, n) {
    read(u); read(v);
    add(u, v); add(v, u);
  }
  dfs1(1); dfs2(1, 1);
  g(i, 1, n) root[ c[i] ]->update(1, n, pos[i], w[i]);
  g(i, 1, m) {
    scanf("%s", s);
    read(x); read(y);
    if (s[0] == 'C') {
      if (s[1] == 'C') {
        root[ c[x] ]->update(1, n, pos[x], 0);
        c[x] = y;
        root[y]->update(1, n, pos[x], w[x]);
      } else {
        root[ c[x] ]->update(1, n, pos[x], y);
        w[x] = y;
      }
    } else {
      lc = lca(x, y);
      if (s[1] == 'S') {
        tee = solveSum(c[x], x, lc) + solveSum(c[x], y, lc);
        if (c[x] == c[lc]) tee -= w[lc];
        printf("%d\n", tee);
      } else {
        printf("%d\n", std::max(solveMax(c[x], x, lc), solveMax(c[x], y, lc)));
      }
    }
  }

#ifdef LOCAL
  fclose(stdin);
  fclose(stdout);
#endif
  return 0;
}

