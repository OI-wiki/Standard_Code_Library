/**
 * @name ZJOI2008_count.cpp
 * @subject HLD
 * @author CJSoft (egwcyh@qq.com)
 * @Copyright DWTFABG
 * @comment HLD including editing single node and Sum/Max query between two single nodes
 * @tests http://codevs.cn/problem/2460/
 */

/**
 * Sorry, but there's no standard interface.
 * But it's easy to modify its function.
 * For future instruction about this piece of HLD code,
 * redirect to https://github.com/cjsoft/noip/blob/master/notes/hld.md
 */
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#define CLEAR(x) memset(x, 0, sizeof(x))
const int MXN = 30007;
typedef long long ll; //NOLINT
int n;
struct edge {
    int to;
    explicit edge(int a) {
        to = a;
    }
};
std::vector <int> v[MXN];
int nodeweight[MXN];
int c_sub_nodes[MXN];
int fa[MXN];
int h_son[MXN];
int head[MXN];
int dep[MXN];
int locator[MXN];
int revlocator[MXN];
int tot = 1;
void dfs_1(int root, int from, int depth) {
    if (!from) {
        fa[root] = 0;
    } else {
        fa[root] = from;
    }
    dep[root] = depth;
    c_sub_nodes[root] = 1;
    h_son[root] = 0;
    for (int i = 0; i < v[root].size(); ++i) {
        if (v[root][i] == from) continue;
        dfs_1(v[root][i], root, depth + 1);
        c_sub_nodes[root] += c_sub_nodes[v[root][i]];
        if (c_sub_nodes[v[root][i]] >= c_sub_nodes[h_son[root]]) {
            h_son[root] = v[root][i];
        }
    }
}
void dfs_2(int root, int hd) {
    locator[root] = tot;
    revlocator[tot++] = root;
    head[root] = hd;
    if (h_son[root]) {
        dfs_2(h_son[root], hd);
    }
    for (int i = 0; i < v[root].size(); ++i) {
        if (v[root][i] == h_son[root] || v[root][i] == fa[root]) continue;
        dfs_2(v[root][i], v[root][i]);
    }
}
struct RMQ_QJH_XDS {
    ll stree_rmq[MXN * 4 + 7];
    ll stree_qjh[MXN * 4 + 7];
    RMQ_QJH_XDS() {
        std::fill(stree_rmq, stree_rmq + MXN * 4 + 7, - 1e9);
        std::fill(stree_qjh, stree_qjh + MXN * 4 + 7, 0);
    }
    inline int lson(int root) {
        return root << 1;
    }
    inline int rson(int root) {
        return root << 1 | 1;
    }
    void build(int root, int l, int r) {
        if (l == r) {
            stree_rmq[root] = nodeweight[revlocator[l]];
            stree_qjh[root] = nodeweight[revlocator[l]];
            return;
        }
        int m = (l + r) >> 1;
        build(lson(root), l, m);
        build(rson(root), m + 1, r);
        stree_rmq[root] = std::max(
            stree_rmq[lson(root)],
            stree_rmq[rson(root)]);
        stree_qjh[root] = stree_qjh[lson(root)] + stree_qjh[rson(root)];
    }
    ll rmq_query(int root, int l, int r, int queryl, int queryr) {
        if (queryl > queryr) std::swap(queryl, queryr);
        if (queryl > r || queryr < l) return - 1e9;
        if (queryl <= l && queryr >= r) return stree_rmq[root];
        int m = (l + r) >> 1;
        return std::max(rmq_query(lson(root), l, m, queryl, queryr),
            rmq_query(rson(root), m + 1, r, queryl, queryr));
    }
    ll qjh_query(int root, int l, int r, int queryl, int queryr) {
        if (queryl > queryr) std::swap(queryl, queryr);
        if (queryl > r || queryr < l) return 0;
        if (queryl <= l && queryr >= r) return stree_qjh[root];
        int m = (l + r) >> 1;
        return qjh_query(lson(root), l, m, queryl, queryr) +
        qjh_query(rson(root), m + 1, r, queryl, queryr);
    }
    void edit(int root, int l, int r, int pos, ll new_data) {
        if (l == r) {
            stree_qjh[root] = new_data;
            stree_rmq[root] = new_data;
            return;
        }
        if (pos > ((l + r) >> 1)) {
            edit(rson(root), ((l + r) >> 1) + 1, r, pos, new_data);
        } else {
            edit(lson(root), l, (l + r) >> 1, pos, new_data);
        }
        stree_rmq[root] = std::max(stree_rmq[lson(root)],
            stree_rmq[rson(root)]);
        stree_qjh[root] = stree_qjh[lson(root)] +
        stree_qjh[rson(root)];
    }
} slpf;
ll tree_rmq_query(int l, int r) {
    ll resu = - 1e9;
    while (head[l] != head[r]) {
        if (dep[head[l]] < dep[head[r]]) std::swap(l, r);
        resu = std::max(resu,
            slpf.rmq_query(1, 1, tot - 1, locator[head[l]], locator[l]));
        l = fa[head[l]];
    }
    if (locator[l] > locator[r]) std::swap(l, r);
    resu = std::max(resu,
        slpf.rmq_query(1, 1, tot - 1, locator[l], locator[r]));
    return resu;
}
ll tree_qjh_query(int l, int r) {
    ll resu = 0;
    while (head[l] != head[r]) {
        if (dep[head[l]] < dep[head[r]]) std::swap(l, r);
        resu += slpf.qjh_query(1, 1, tot - 1, locator[head[l]], locator[l]);
        l = fa[head[l]];
    }
    if (locator[l] > locator[r]) std::swap(l, r);
    resu += slpf.qjh_query(1, 1, tot - 1, locator[l], locator[r]);
    return resu;
}
int main() {
    CLEAR(nodeweight);
    CLEAR(c_sub_nodes);
    CLEAR(fa);
    CLEAR(h_son);
    CLEAR(head);
    CLEAR(dep);
    CLEAR(locator);
    CLEAR(revlocator);
    scanf("%d", &n);
    int tempa, tempb;
    for (int i = 0; i < n - 1; ++i) {
        scanf("%d %d", &tempa, &tempb);
        v[tempa].push_back(tempb);
        v[tempb].push_back(tempa);
    }
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &nodeweight[i]);
    }
    head[1] = 1;
    dfs_1(1, 0, 1);
    dfs_2(1, 1);
    slpf.build(1, 1, tot - 1);
    int q;
    char tc[11];
    scanf("%d", &q);
    for (int i = 0; i < q; ++i) {
        CLEAR(tc);
        scanf("%s %d %d", tc, &tempa, &tempb);
        if (tc[1] == 'M') {
            ll asd = tree_rmq_query(tempa, tempb);
            printf("%lld\n", asd);
        } else if (tc[1] == 'S') {
            printf("%lld\n", tree_qjh_query(tempa, tempb));
        } else {
            slpf.edit(1, 1, tot - 1, locator[tempa], tempb);
            nodeweight[tempa] = tempb;
        }
    }
}
