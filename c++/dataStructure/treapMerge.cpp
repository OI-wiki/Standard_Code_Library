/**
 * @Author SCaffrey(sirius.caffrey@gmail.com)
 * @Copyright SATA
 * http://www.lydsy.com/JudgeOnline/problem.php?id=2733
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
  node* ch[2];
  int r, v, s, c, idx;
  node(int v):v(v) {ch[0] = ch[1] = NULL; r = rand(); s = 1; c = 1; idx = 0;}// NOLINT
  inline bool operator < (const node& T) const {
    return r < T.r;
  }
  inline int cmp(int x) const {
    if (x == v) return -1;
    if (x < 0) return 0;
    return 1;
  }
  inline void maintain() {
    s = c;
    f(i, 0, 2) if (ch[i]) s += ch[i]->s;
  }
};
node* root[MAXN];
void rotate(node* &o, int d) {// NOLINT
  node* k = o->ch[d ^ 1]; o->ch[d ^ 1] = k->ch[d]; k->ch[d] = o;
  o->maintain(); k->maintain(); o = k;
}
void insert(node* &o, int x, int idx) {// NOLINT
  if (o == NULL) {
    o = new node(x);
    o->idx = idx;
    return;
  }
  ++o->s;
  if (o->v == x) {
    ++o->c;
  } else {
    int d = x > o->v;
    insert(o->ch[d], x, idx);
    if (o->ch[d]->r < o->r) rotate(o, d ^ 1);
  }
  o->maintain();
}
void remove(node* &o, int x) {// NOLINT
  int d = o->cmp(x);
  if (d == -1) {
    node* u = o;
    if (o->ch[0] && o->ch[1]) {
      int d2 = o->ch[0]->r > o->ch[1]->r;
      rotate(o, d2); remove(o->ch[d2], x);
    } else {
      if (o->ch[0]) {
        o = o->ch[1];
      } else {
        o = o->ch[0];
      }
      delete u;
    }
  } else {
    remove(o->ch[d], x);
  }
  if (o) o->maintain();
}
int getKth(node* o, int k) {// NOLINT
  if (o == NULL || k <= 0 || k > o->s) return -1;
  int s = 0;
  if (o->ch[0]) s += o->ch[0]->s;
  if (k <= s) return getKth(o->ch[0], k);
  if (k > s + o->c) return getKth(o->ch[1], k - s - o->c);
  return o->idx;
}
void merge(node* &a, node* &b) { // merge a into b NOLINT
  if (a->ch[0]) merge(a->ch[0], b);
  if (a->ch[1]) merge(a->ch[1], b);
  insert(b, a->v, a->idx);
  delete a;
  a = NULL;
}
int fa[MAXN];
int get(int x) {
  int tee = fa[x], q;
  while (tee != fa[tee]) tee = fa[tee];
  while (x != tee) {
    q = fa[x]; fa[x] = tee; x = q;
  }
  return tee;
}
void add(int s, int t) {
  int u = get(s), v = get(t);
  if (u != v) {
    if (root[u]->s < root[v]->s) {
      fa[u] = v; merge(root[u], root[v]);
    } else {
      fa[v] = u; merge(root[v], root[u]);
    }
  }
}
int w[MAXN];
int u, v;
int n, m;
char buf[12];
int main() {
  scanf("%d%d", &n, &m);
  g(i, 1, n) {
    fa[i] = i;
    scanf("%d", w + i);
    root[i] = new node(w[i]);
    root[i]->idx = i;
  }
  f(i, 0, m) {
    scanf("%d%d", &u, &v);
    add(u, v);
  }
  scanf("%d", &m);
  while (m--) {
    scanf("%s%d%d", buf, &u, &v);
    if (buf[0] == 'Q') {
      u = get(u);
      if (root[u]->s < v) {
        puts("-1");
      } else {
        printf("%d\n", getKth(root[u], v));
      }
    } else {
      add(u, v);
    }
  }
  return 0;
}
