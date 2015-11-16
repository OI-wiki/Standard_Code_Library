/**
 * @name segment_tree_point_modify_seg_query.cpp
 * @subject Segment Tree
 * @author SCaffrey(sirius.caffrey@gmail.com)
 * @Copyright DWTFABG
 * @comment This is a segment tree implemented with pointers.
 * @tests http://acm.hdu.edu.cn/showproblem.php?pid=1166
 */

#include <cstdio>
#include <cmath>

#define g(x, y, z) for (int x = (y), __ = (z); x <= __; ++x)

int T;
int n;
char buf[12];
int x, y;

/**
 * 'struct node'
 * Each node represents one in the seg_tree
 */
struct node{
  int l, r, md;
  int sum;
  node *ls, *rs;
  /**
   * constructor
   * @param  ll [int]
   * @param  rr [int]
   */
  inline node(int ll = 0, int rr = 0):l(ll), r(rr),// NOLINT
      md(ll + (rr - ll >> 1)) {
    if (ll == rr) {
      scanf("%d", &sum);
      ls = rs = NULL;
      return;
    }
    ls = new node(ll, md);
    rs = new node(md + 1, rr);
    sum = ls->sum + rs->sum;
  }
  /**
   * point modify
   * @param pos   [int]
   * @param delta [int]
   */
  inline void add(int pos, int delta) {
    if (l == r) {
      sum += delta;
      return;
    }
    if (pos <= md) {
      ls->add(pos, delta);
    } else {
      rs->add(pos, delta);
    }
    sum = ls->sum + rs->sum;
  }
  /**
   * seg query
   * @param  ll [int]
   * @param  rr [int]
   * @return  the sum of seg [ll, rr]  [int]
   */
  inline int query(int ll, int rr) {
    if (ll == l && rr == r) {
      return sum;
    }
    if (ll > md)return rs->query(ll, rr);
    if (rr <= md)return ls->query(ll, rr);
    return ls->query(ll, md) + rs->query(md + 1, rr);
  }
};

int main() {
  scanf("%d", &T);
  g(i, 1, T) {
    scanf("%d", &n);
    node* root = new node(1, n);
    printf("Case %d:\n", i);
    while (~scanf("%s", buf)) {
      if (buf[0] == 'E')break;
      scanf("%d%d", &x, &y);
      if (buf[0] == 'A') {
        root->add(x, y);
      } else if (buf[0] == 'S') {
        root->add(x, -y);
      } else {
        printf("%d\n", root->query(x, y));
      }
    }
  }
  return 0;
}
