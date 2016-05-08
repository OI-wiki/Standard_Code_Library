/**
 * @name segment_tree_seg_modify_seg_query.cpp
 * @subject Segment Tree
 * @author SCaffrey(sirius.caffrey@gmail.com)
 * @Copyright DWTFABG
 * @comment This is a segment tree implemented with pointers.
 * @tests http://acm.hdu.edu.cn/showproblem.php?pid=1698
 */

#include <cstdio>
#include <cmath>

#define g(x, y, z) for (int x = (y), __ = (z); x <= __; ++x)

typedef long long LL;// NOLINT

int n, q;
char buf[12];
int a, b, c;

/**
 * 'struct node'
 * Each node represents one in the seg_tree
 */
struct node{
  int l, r, md;
  node *ls, *rs;
  LL cover;
  LL sum;
  /**
   * constructor
   * @param  ll [int]
   * @param  rr [int]
   */
  inline node(int ll = 0,int rr = 0):l(ll), r(rr),// NOLINT
      md(ll + (rr - ll >> 1)) {
    cover = 0;
    if (l == r) {
      ls = rs = NULL;
      scanf("%lld", &sum);
      return;
    }
    ls = new node(ll, md);
    rs = new node(md + 1, rr);
    sum = ls->sum + rs->sum;
  }
  /**
   * [pushdown]
   * pass the cover down.
   */
  inline void pushdown() {
    if (cover) {
      ls->cover += cover;
      rs->cover += cover;
      ls->sum += (ls->r - ls->l + 1) * cover;
      rs->sum += (rs->r - rs->l + 1) * cover;
      cover = 0;
    }
  }
  /**
   * seg modify
   * @param ll  [int]
   * @param rr  [int]
   * @param val [int]
   */
  inline void add(int ll, int rr, int val) {
    if (ll == l && rr == r) {
      sum += val * (r - l + 1);
      cover += val;
      return;
    }
    pushdown();
    if (rr <= md) {
      ls->add(ll, rr, val);
    } else if (ll > md) {
      rs->add(ll, rr, val);
    } else {
      ls->add(ll, md, val); rs->add(md + 1, rr, val);
    }
    sum = ls->sum + rs->sum;
  }
  /**
   * seg query
   * @param  ll [int]
   * @param  rr [int]
   * @return  the sum of seg [ll, rr]  [long long]
   */
  inline LL query(int ll, int rr) {
    if (ll == l && rr == r) {
      return sum;
    }
    pushdown();
    if (ll > md)return rs->query(ll, rr);
    if (rr <= md)return ls->query(ll, rr);
    return ls->query(ll, md) + rs->query(md + 1, rr);
  }
};

int main() {
  scanf("%d%d", &n, &q);
  node* root = new node(1, n);
  while (q--) {
    scanf("%s", buf);
    if (buf[0] == 'C') {
      scanf("%d%d%d", &a, &b, &c);
      root->add(a, b, c);
    } else {
      scanf("%d%d", &a, &b);
      printf("%lld\n", root->query(a, b));
    }
  }
  return 0;
}
