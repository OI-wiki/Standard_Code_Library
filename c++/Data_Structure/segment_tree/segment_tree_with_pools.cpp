/**
 * @name segment_tree_seg_modify_seg_query.cpp
 * @subject Segment Tree
 * @author SCaffrey(sirius.caffrey@gmail.com)
 * @Copyright DWTFABG
 * @comment This is a segment tree implemented with pointers.
 * @tests http://acm.hdu.edu.cn/showproblem.php?pid=1754
 */

#include <cstdio>
#include <cmath>
#include <algorithm>

#define g(x, y, z) for (int x = (y), __ = (z); x <= __; ++x)

const int MAXNODE = 400033;

int n, m;
char buf[12];
int a, b;

/**
 * 'struct node'
 * Each node represents one in the seg_tree
 */
struct node {
  int l, r, md;
  int mx;
  node *ls, *rs;
  /**
   * seg query
   * @param  ll [int]
   * @param  rr [int]
   * @return  the max in seg [ll, rr]  [int]
   */
  inline int query(int ll, int rr) {
    if (ll == l && rr == r) {
      return mx;
    }
    if (ll > md)return rs->query(ll, rr);
    if (rr <= md)return ls->query(ll, rr);
    return std::max(ls->query(ll, md), rs->query(md + 1, rr));
  }
  /**
   * point modify
   * @param pos [int]
   * @param val [int]
   */
  inline void modify(int pos, int val) {
    if (l == r) {
      mx = val;
      return;
    }
    if (pos > md) {
      rs->modify(pos, val);
    } else {
      ls->modify(pos, val);
    }
    mx = std::max(ls->mx, rs->mx);
  }
  inline void remove() {
    if (ls)ls->remove();
    if (rs)rs->remove();
    delete this;
  }
} pool[MAXNODE], *tail;

/**
 * using pool to construct new node
 * @param  ll [int]
 * @param  rr [int]
 * @return  the new node as required  [node*]
 */
inline node* newnode(int ll, int rr) {
  node* ans = tail++;
  ans->l = ll; ans->r = rr; ans->md = ll + (rr - ll >> 1);
  if (ll == rr) {
    scanf("%d", &(ans->mx));
    ans->ls = ans->rs = NULL;
    return ans;
  }
  ans->ls = newnode(ll, ans->md);
  ans->rs = newnode(ans->md + 1, rr);
  ans->mx = std::max(ans->ls->mx, ans->rs->mx);
  return ans;
}

int main() {
  while (~scanf("%d%d", &n, &m)) {
    tail = pool;
    node* root = newnode(1, n);
    while (m--) {
      scanf("%s%d%d", buf, &a, &b);
      if (buf[0] == 'Q') {
        printf("%d\n", root->query(a, b));
      } else {
        root->modify(a, b);
      }
    }
  }
  return 0;
}
