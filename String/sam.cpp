/**
 * @Author Ir1d (sirius.caffrey@gmail.com)
 * @Copyright SATA
 * @Example http://poj.org/problem?id=1509
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
const int MAXN = 1000033;

int n;
struct node {
  node *f;
  node *ch[26];
  int v, r;
} pool[MAXN * 2];
node *root, *tail, *last;
node* newnode(int v) {
  node *p = tail++;
  f(i, 0, 26) p->ch[i] = NULL;
  p->f = 0; p->r = 0;
  p->v = v;
  return p;
}
void init() {
  tail = pool;
  root = last = newnode(0);
}
void add(int c) {
  node *p = last, *np = newnode(p->v + 1);
  while (p && !p->ch[c]) {
    p->ch[c] = np; p = p->f;
  }
  if (!p) np->f = root;
  else {
    node *q = p->ch[c];
    if (p->v + 1 == q->v) np->f = q;
    else {
      node *nq = newnode(p->v + 1);
      f(i, 0, 26) nq->ch[i] = q->ch[i];
      nq->f = q->f; q->f = np->f = nq;
      while (p && p->ch[c] == q) {
        p->ch[c] = nq; p = p->f;
      }
    }
  }
  last = np; np->r = 1;
}
int T;
void solve() {
  node *p = root;
  f(i, 0, n) {
    f(j, 0, 26) if (p->ch[j]) {
      p = p->ch[j];
      break;
    }
  }
  printf("%d\n", p->v - n + 1);
}
char s[MAXN];
int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  scanf("%d", &T);
  while (T--) {
    scanf("%s", s);
    init();
    n = strlen(s);
    f(i, 0, n) add(s[i] - 'a');
    f(i, 0, n) add(s[i] - 'a');
    solve();
  }

#ifdef LOCAL
  fclose(stdin);
  fclose(stdout);
#endif
  return 0;
}