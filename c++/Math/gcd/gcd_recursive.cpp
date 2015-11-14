/**
 * @name gcd_recursive.cpp
 * @subject GCD algorithm
 * @author SCaffrey(sirius.caffrey@gmail.com)
 * @Copyright DWTFABG
 * @comment This is a recursive GCD algorithm.
 * @tests http://codevs.cn/problem/1212/
 */
#include <cstdio>

int a, b;

int gcd(int a, int b) {
  if (b)return gcd(b, a % b);
  return a;
}

int main() {
  scanf("%d%d", &a, &b);
  printf("%d\n", gcd(a, b));
  return 0;
}
