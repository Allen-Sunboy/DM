#include <iostream>

using namespace std;

int n, l;
int w[20][20]; // 长度
int c[20][20]; // 花费
int p0 = 0;
const int INF = 0x3f3f3f3f;
int val = INF;
int list[20];
bool choose[20];
int final[20];

void dfs(int x, int vall, int cost) {
    if (cost > l)
        return;
    if (vall >= val)
        return;
    if (x == n + 1) {
        if (vall < val) {
            val = vall;
            for (int i = 1; i <= n; i++)
                final[i] = list[i];
        }

        return;
    }
    for (int i = 1; i <= n; i++) {
        if (choose[i] == 0) {
            choose[i] = 1;
            list[x] = i;
            dfs(x + 1, vall + w[list[x - 1]][list[x]],
                cost + c[list[x - 1]][list[x]]);
            choose[i] = 0;
        }
    }
    return;
}

int main() {
    cin >> n >> l;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> w[i][j];

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> c[i][j];

    dfs(1, 0, 0);
    if (val == INF)
        cout << -1 << endl;
    else {
        cout << val << endl;
        for (int i = 1; i <= n; i++)
            cout << final[i] << " ";
    }
}