/**
 * @Author Ir1d(sirius.caffrey@gmail.com)
 * @Copyright SATA
 * @Example 
 */
#include <cstdio>// NOLINT
#include <cstring>// NOLINT
#include <map>// NOLINT
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

// std::map<LL, int> M;
const int MOD = 100007;
LL hs[MOD + 233], id[MOD + 233];
LL find(LL x) {
  LL t = x % MOD;
  while (hs[t] != x && hs[t] != -1) t = (t + 1) % MOD;
  return t;
}
void insert(LL x, LL s) {
  LL pos = find(x);
  if (hs[pos] == -1) {
    hs[pos] = x; id[pos] = s;
  }
}
LL getVal(LL x) {
  LL pos = find(x);
  return hs[pos] == x ? id[pos] : -1;
}
int a, b, c;
LL gcd(LL a, LL b) {
  if (b) return gcd(b, a % b);
  return a;
}
inline LL get(LL a, LL b, LL c) {
  LL res = 1, bas = a;
  while (b) {
    if (b & 1) res = res * bas % c;
    bas = bas * bas % c;
    b >>= 1;
  }
  return res;
}
void solve(LL a, LL b, LL c) {
  // L = i * M - j; i from [1 .. M], j from [1 .. M]
  if (b == 1) {
    puts("0");
    return;
  }
  memset(hs, -1, sizeof hs);
  memset(id, -1, sizeof id);
  LL s, d = 1, t, k = 0, z;
  while ((t = gcd(a, c)) != 1) {
    if (b % t) {
      puts("No Solution");
      // puts("");
      return;
    }
    ++k; b /= t; c /= t; d = d * (a / t) % c;
    if (b == d) {
      printf(LLD"\n", k);
      return;
    }
  }
  // M.clear();
  LL m  = ceil(sqrt(c + .5));  // s = a ** m
  s = get(a, m, c);
  // M[b] = 0;
  g(j, 1, m) {
    b = b * a % c;
    insert(b, j);
    // M[b] = j;
  }
  // printf(LLD"\n", m * (m - 1));
  g(i, 1, m) {
    d = d * s % c;
    // if (M[d]) {
    if ((z = getVal(d)) != -1) {
    // if (M.find(d) != M.end()) {
      // printf("%d %d %d\n", i, M[d], m);
      printf(LLD"\n", ((k + i * m - z + c) % c + c) % c);
      return;
    }
  }
  puts("No Solution");
}
int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  while (~scanf("%d%d%d", &a, &c, &b) && (a || b || c)) {
  // while (~scanf("%d%d%d", &c, &a, &b)) {
    solve(a % c, b % c, c);
  }

#ifdef LOCAL
  fclose(stdin);
  fclose(stdout);
#endif
  return 0;
}
