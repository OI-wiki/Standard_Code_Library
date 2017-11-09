/**
 * @Author SCaffrey(sirius.caffrey@gmail.com)
 * @Copyright SATA
 * http://acm.hdu.edu.cn/showproblem.php?pid=2222
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
const int MAXN = 1000033;

int T;
int n;
char buf[MAXN];
struct node {
  node *fail, *ch[26];
  int cnt;
} pool[MAXN], *tail;
inline void init() {
  tail = pool;
}
inline node* newnode() {
  node* ans = tail++;
  ans->fail = NULL; ans->cnt = 0;
  memset(ans->ch, 0, sizeof ans->ch);
  return ans;
}
void insert(node* root, const char* str) {
  node* p = root;
  int idx;
  f(i, 0, strlen(str)) {
    idx = str[i] - 'a';
    if (p->ch[idx] == NULL) p->ch[idx] = newnode();
    p = p->ch[idx];
  }
  ++p->cnt;
}
std::queue<node*> Q;
void getFail(node* root) {
  node* p = root;
  while (!Q.empty()) Q.pop();
  root->fail = NULL;
  Q.push(root);
  while (!Q.empty()) {
    node* tee = Q.front(); Q.pop();
    node* p = NULL;
    f(i, 0, 26) {
      if (tee->ch[i]) {
        p = tee->fail;
        while (p) {
          if (p->ch[i]) {
            tee->ch[i]->fail = p->ch[i];
            break;
          }
          p = p->fail;
        }
        if (p == NULL) tee->ch[i]->fail = root;
        Q.push(tee->ch[i]);
      }
    }
  }
}
int query(node* root, const char* str) {
  node* p = root;
  int idx, ans = 0;
  f(i, 0, strlen(str)) {
    idx = str[i] - 'a';
    while (p->ch[idx] == NULL && p != root) p = p->fail;
    p = p->ch[idx];
    if (p == NULL) p = root;
    node* tee = p;
    while (tee != root && tee->cnt != -1) {
      ans += tee->cnt; tee->cnt = -1;
      tee = tee->fail;
    }
  }
  return ans;
}
void solve() {
  scanf("%d", &n);
  node* root = newnode();
  f(i, 0, n) {
    scanf("%s", buf);
    insert(root, buf);
  }
  getFail(root);
  scanf("%s", buf);
  printf("%d\n", query(root, buf));
}
int main() {
  scanf("%d", &T);
  while (T--) {
    init();
    solve();
  }
  return 0;
}
