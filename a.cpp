#include <iostream>
#include <cstdio>
#include <stack>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

int n;
struct dot {
    ll x, y;
    double angle;
} dts[100007];

stack < dot > tubao;
stack  < double >  ang;
inline double atan3(double a, double b ) {
    double t = atan2(a, b);
    if (t < 0) {
        t += 2*M_PI;
    }
    return t;
}
bool poscmp(const dot &a, const dot &b) {
    if (a.y  == b.y)
        return a.x < b.x;
    return a.y > b.y;
}
bool anglecmp(const dot &a, const dot &b) {
    if (a.angle == b.angle)
        return (a.x - dts[0].x) * (a.x - dts[0].x) + (a.y - dts[0].y) * (a.y - dts[0].y)
     >
    (b.x - dts[0].x) * (b.x - dts[0].x) + (b.y - dts[0].y) * (b.y - dts[0].y)
    ?true:false;
    return a.angle < b.angle;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n;  ++i) {
        cin >> dts[i].x >> dts[i].y;
    }
    sort(dts, dts + n, poscmp);
    for (int i = 1; i < n;  ++i) {
        dts[i].angle = atan3(dts[0].y - dts[i].y, dts[i].x - dts[0].x);
    }
    sort(dts + 1, dts + n, anglecmp);
    for (int i = 2; i < n;  ++i) {
        if (dts[i].angle == dts[i - 1].angle) {
            if (i == n - 1) {
                --n;
            } else {
                swap(dts[i], dts[n - 1]);
                 --n;
            }
        }
    }
    sort(dts + 1, dts + n, anglecmp);

    if (n >= 1) {
        tubao.push(dts[0]); tubao.push(dts[1]);
        ang.push(0); ang.push(dts[1].angle);
        double tang;
        for (int i = 2; i < n;  ++i) {
            tang = atan3(tubao.top().y - dts[i].y, dts[i].x - tubao.top().x);
            while (tang < ang.top()) {
                 //  cout << tang << endl;
                 //  cout << "pop" << tubao.top().x << ' ' << tubao.top().y << "when" << dts[i].x << ' ' << dts[i].y << endl;
                tubao.pop(); ang.pop();
                tang = atan3(tubao.top().y - dts[i].y, dts[i].x - tubao.top().x);
            }
            tubao.push(dts[i]); ang.push(tang);
        }
    }
     //  cout << tubao.size() << 's' << endl;
    double result = 0;
    dot fdot = tubao.top();
    dot tdot = tubao.top();
     //  printf("\n\n");
     //  cout << tubao.top().x << ' ' << tubao.top().y << endl;
    tubao.pop();
    while ( ! tubao.empty()) {
         //  cout << tubao.top().x << ' ' << tubao.top().y << endl;
        result += sqrt((tdot.x - tubao.top().x) * (tdot.x - tubao.top().x) + (tdot.y - tubao.top().y) * (tdot.y - tubao.top().y));
        tdot = tubao.top(); tubao.pop();
    }
    result += sqrt((tdot.x - fdot.x) * (tdot.x - fdot.x) + (tdot.y - fdot.y) * (tdot.y - fdot.y));
    printf(" % .1lf\n", result);
    return 0;
}