/**
 * @Author SCaffrey(sirius.caffrey@gmail.com)
 * @Copyright SATA
 * http://tyvj.cn/p/3006
 */
#include <cstdio>// NOLINT
#include <cstring>// NOLINT
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

int priv[333];
double val[333];
double calc(double a, double b, double op) {
  if (op == '+') return a + b;
  if (op == '-') return a - b;
  if (op == '*') return a * b;
  if (op == '/') return a / b;
  if (op == '^') return exp(log(a) * b);
}
char buf[MAXN];
double num[MAXN];
char oper[MAXN];
int top, cur;
double solve() {
  priv['+'] = priv['-'] = 3;
  priv['*'] = priv['/'] = 2;
  priv['^'] = 1; priv['('] = 10;
  double x, y, t = 0;
  char last = 0;
  int len = strlen(buf);
  f(i, 0, len) {
    if (buf[i] >= 'a' &&  buf[i] <= 'z') {
      num[top++] = (val[buf[i]]);
    } else if (buf[i] >= '0' && buf[i] <= '9') {
      num[top++] = (atof(buf + i));
      for (; i + 1 < len && buf[i + 1] >= '0' && buf[i + 1] <= '9'; ++i);// NOLINT
      if (i + 1 < len && buf[i + 1] == '.') {
        for (i++; i + 1 < len && buf[i + 1] >= 0 && buf[i + 1] <= '9'; ++i);// NOLINT
      }
    } else if (buf[i] == '(') {
      oper[cur++] = (buf[i]);
    } else if (buf[i] == ')') {
      while (oper[cur - 1] != '(') {
        y = num[--top];
        x = num[--top];
        char op = oper[--cur];
        x = calc(x, y, op);
        x = fmod(x, 10000.0);
        // if (x > 10000) x = int(x) % 10000;
        num[top++] = (x);
      }
      --cur;
    } else if (buf[i] == '-' && (last == 0 || last == '(')) {
      num[top++] = (0.0);
      oper[cur++] = ('-');
    } else if (priv[buf[i]] > 0) {
      while (cur > 0 && priv[buf[i]] >= priv[oper[cur - 1]]) {
        y = num[--top];
        x = num[--top];
        char op = oper[--cur];
        x = calc(x, y, op);
        x = fmod(x, 10000.0);
        // if (x > 10000) x = int(x) % 10000;
        num[top++] = (x);
      }
      oper[cur++] = (buf[i]);
    } else {
      continue;
    }
    last = buf[i];
  }
  while (cur > 0) {
    y = num[--top];
    x = num[--top];
    char op = oper[--cur];
    x = calc(x, y, op);
    x = fmod(x, 10000.0);
    // if (x > 10000) x = int(x) % 10000;
    num[top++] = (x);
  }
  return num[top - 1];
}
int main() {
  scanf("%s", buf);
  printf("%d\n", int(solve()) % 10000);// NOLINT
}
