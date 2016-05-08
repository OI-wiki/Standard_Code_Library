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

int n, m;
struct node {
  int v, s, r, c;
  node* ch[2];
  inline node(int v = 0):v(v) {// NOLINT
    ch[0] = ch[1] = NULL;
    r = rand(); s = c = 1;// NOLINT
  }
  inline int cmp(int x) const {
    if (x == v) return -1;
    if (x < v) return 0;
    return 1;
  }
  inline void maintain() {
    s = c;
    f(i, 0, 2) if (ch[i]) s += ch[i]->s;
  }
  inline void print() {
    if (ch[0]) ch[0]->print();
    printf("(%d,%d)", v, s);
    if (ch[1]) ch[1]->print();
  }
};
void rotate(node* &o, int d) {// NOLINT
  node* k = o->ch[d ^ 1];
  o->ch[d ^ 1] = k->ch[d];
  k->ch[d] = o;
  o->maintain(); k->maintain(); o = k;
}
void insert(node* &o, int x) {// NOLINT
  if (o == NULL) {
    o = new node(x);
    return;
  }
  ++o->s;
  if (o->v == x) {
    ++o->c;
  } else {
    int d = x > o->v;
    insert(o->ch[d], x);
    if (o->ch[d]->r < o->r) rotate(o, d ^ 1);
  }
  o->maintain();
}
void remove(node* o, int x) {
  if (o->v == x) {
    if (o->c > 1) {
      --o->c; --o->s; return;
    }
    node* u = o;
    if (o->ch[0] && o->ch[1]) {
      int d = (o->ch[0]->r < o->ch[1]->r);
      rotate(o, d); remove(o->ch[d], x);
    } else {
      if (o->ch[0] == NULL && o->ch[1] == NULL) o = NULL;
      else if (o->ch[0]) o = o->ch[0];
      else if (o->ch[1]) o = o->ch[1];
      delete u;
    }
  } else {
    remove(o->ch[x > o->v], x);
  }
  if (o) o->maintain();
}
int getRank(node* o, int x) {
  if (o == NULL) return 0;
  int sz = 0;
  if (o->ch[0]) sz = o->ch[0]->s;
  if (o->v == x) return sz + 1;
  if (x > o->v) return sz + o->c + getRank(o->ch[1], x);
  return getRank(o->ch[0], x);
}
int getKth(node* o, int x) {
  if (o == NULL || x <= 0 || x > o->s) return 0;
  int sz = 0;
  if (o->ch[0]) sz = o->ch[0]->s;
  if (x <= sz) return getKth(o->ch[0], x);
  if (x > sz + o->c) return getKth(o->ch[1], x - sz - o->c);
  return o->v;
}
int sz;
node* ans;
void getPre(node* o, int x) {
  if (o == NULL) return;
  while (o) {
    if (o->v < x) {
      ans = o; o = o->ch[1];
    } else {
      o = o->ch[0];
    }
  }
}
void getSuc(node* o, int x) {
  ans = o;
  while (o) {
    if (x < o->v) {
      ans = o; o = o->ch[0];
    } else {
      o = o->ch[1];
    }
  }
}
int opt, x;
int main() {
  scanf("%d", &n);
  node* root = NULL;
  srand(233);
  g(i, 1, n) {
    scanf("%d%d", &opt, &x);
    switch (opt) {
      case 1: insert(root, x); break;
      case 2: remove(root, x); break;
      case 3: printf("%d\n", getRank(root, x)); break;
      case 4: printf("%d\n", getKth(root, x)); break;
      case 5: getPre(root, x); /*if (ans)*/ printf("%d\n", ans->v); break;
      case 6: getSuc(root, x); /*if (ans)*/ printf("%d\n", ans->v); break;
    }
  }
}
