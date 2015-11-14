/**
 * @name gcd_non_recursive.cpp
 * @subject GCD algorithm
 * @author SCaffrey(sirius.caffrey@gmail.com)
 * @Copyright DWTFABG
 * @comment This is a non_recursive GCD algorithm.
 * @tests http://codevs.cn/problem/1212/
 */
#include <cstdio>

int a, b, c;

int gcd(int a, int b) {
  while (b) {
    c = a % b;
    a = b; b = c;
  }
  return a;
}

int main() {
  scanf("%d%d", &a, &b);
  printf("%d\n", gcd(a, b));
  return 0;
}
