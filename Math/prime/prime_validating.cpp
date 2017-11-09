/**
 * @name prime_validating.cpp
 * @subject prime_validating algorithm
 * @author SCaffrey(sirius.caffrey@gmail.com)
 * @Copyright DWTFABG
 * @comment These are prime_validating algorithms, including brutal and Miler_Rabin.
 * @tests http://www.51nod.com/onlineJudge/questionCode.html#!problemId=1106
 */

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>

#define g(x, y, z) for (int x = (y), __ = (z); x <= __; ++x)

int n, m, t;
bool flag;
bool check_brutal(int t) {
  m = sqrt(t);
  flag = 1;
  g(i, 2, m) {
    if (t % i == 0) {
      return 0;
    }
  }
  return 1;
}

typedef long long LL;// NOLINT

int pow(int a, int b, int c) {
  int res = 1, bas = a;
  while (b) {
    if (b & 1)res = (LL)res * bas % c;
    // Transform to long long in case of overflow.
    bas = bas * bas % c;
    b >>= 1;
  }
  return res;
}

/*bool check_miller_rabin(int t) {
  if (t == 1)return 0;
  if (t == 2)return 1;
  if (t == 3)return 1;
  int s = 12;
  srand(time(0));
  // s is a chosen number according to this algorithm,
  // it might change as your dataset changes.
  int tee = 0;
  g(i, 1, s) {
    tee = rand() % (t - 2) + 2;
    if (pow(tee, t - 1, t) != 1)return 0;
  }
  return 1;
}*/

int main() {
  scanf("%d", &n);
  while (n--) {
    scanf("%d", &t);
    if (check_brutal(t)) {
      puts("Yes");
    } else {
      puts("No");
    }
  }
}
