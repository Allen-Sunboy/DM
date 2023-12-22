#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int n, m, s, t, k;
vector<int> a[10200];
queue<int> l;
int ans0; // number

void bfs() {
    l.push(s);
    for (int i = 0; i < k; i++) {
        int num = l.size();
        while (num--) {
            for (int i = 0; i < a[l.front()].size(); i++)
                l.push(a[l.front()][i]);
            l.pop();
        }
    }
    while (!l.empty()) {
        if (l.front() == t)
            ans0++;
        l.pop();
        if (ans0 > 1000003)
            ans0 %= 1000003;
    }
}
int main() {
    cin >> n >> m >> s >> t >> k;
    int vi, vj;
    for (int i = 1; i <= m; i++) {
        cin >> vi >> vj;
        a[vi].insert(a[vi].begin(), vj);
    }
    bfs();
    cout << ans0;
}
