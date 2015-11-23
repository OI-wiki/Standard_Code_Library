/**
 * @name Size_Balanced_Tree.cpp
 * @subject Size Balanced Tree
 * @author KingsNeverDie(lm19990323@outlook.com)
 * @Copyright DWTFABG
 * @tests http://www.lydsy.com/JudgeOnline/problem.php?id=1503/
 */

#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

struct node {
    int left, right, size, key;
    void init(int k) {
        key = k;
        size = 1;
        left = right = 0;
    }
}tree[1000011];

int n, min;
int delta;
int root = 0, top = 0;
const int nil = 0;
int leave = 0;

void right_rotate(int &x) {// NOLINT
    int y = tree[x].left;
    tree[x].left = tree[y].right;
    tree[y].right = x;
    tree[y].size = tree[x].size;
    tree[x].size = tree[tree[x].right].size + tree[tree[x].left].size + 1;
    x = y;
}

void left_rotate(int &y) {// NOLINT
    int x = tree[y].right;
    tree[y].right = tree[x].left;
    tree[x].left = y;
    tree[x].size = tree[y].size;
    tree[y].size = tree[tree[y].left].size + tree[tree[y].right].size + 1;
    y = x;
}

void Maintain(int &x, bool flag) {// NOLINT
    if (flag) {
        if (tree[tree[x].left].size < tree[tree[tree[x].right].left].size) {
            right_rotate(tree[x].right);
            left_rotate(x);
        } else if (tree[tree[x].left].size
            < tree[tree[tree[x].right].right].size) {
            left_rotate(x);
        } else {
            return;
        }
    } else {
        if (tree[tree[x].right].size < tree[tree[tree[x].left].right].size) {
            left_rotate(tree[x].left);
            right_rotate(x);
        } else if (tree[tree[x].right].size
            < tree[tree[tree[x].left].left].size) {
            right_rotate(x);
        } else {
            return;
        }
    }
    Maintain(tree[x].left, false);
    Maintain(tree[x].right, true);
    Maintain(x, true);
    Maintain(x, false);
}

/**
 * Insert a new point to Size Balanced Tree
 * @param x   [int]
 * @param key [int]
 */
void insert(int &x, int key) {// NOLINT
    if (x == nil) {
        x = ++top;
        tree[x].init(key);
        return;
    }
    if (key < tree[x].key) {
        insert(tree[x].left, key);
    } else {
        insert(tree[x].right, key);
    }
    tree[x].size = tree[tree[x].left].size + tree[tree[x].right].size + 1;
    Maintain(x, key >= tree[x].key);
}

/**
 * Remove a point from Size Balanced Tree
 * @param x   [int]
 * @param key [int]
 */
void remove(int &x, int key) {// NOLINT
    if (x == nil) {
        return;
    } else if (tree[x].key < key) {
        leave += tree[tree[x].left].size + 1;
        x = tree[x].right;
        remove(x, key);
    } else if (key <= tree[x].key) {
        remove(tree[x].left, key);
    }
    if (x != nil) tree[x].size =
        tree[tree[x].left].size + tree[tree[x].right].size + 1;
}

/**
 * Rank
 * @param  x   [int]
 * @param  key [int]
 * @return     [the key_th rank]
 */
int rank(int x, int key) {
    if (key == tree[tree[x].right].size + 1) return tree[x].key;
    if (key < tree[tree[x].right].size + 1) return rank(tree[x].right, key);
    return rank(tree[x].left, key - tree[tree[x].right].size - 1);
}

int main() {
    scanf("%d%d", &n, &min);
    char rd[5];
    int k;
    while (n--) {
        scanf("%s%d", rd, &k);
        if  (rd[0] == 'I' && k >= min) insert(root, k - delta);
        if (rd[0] == 'A') delta += k;
        if (rd[0] == 'S') {
            delta -= k;
            remove(root, min - delta);
        }
        if (rd[0] == 'F') {
            if (k <= top - leave) {
                printf("%d\n", rank(root,  k) + delta);
            } else {
                puts("-1");
            }
        }
    }
    printf("%d\n", leave);
    return 0;
}
