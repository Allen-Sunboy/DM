#include <iostream>
using namespace std;

int n, m;
int a[200][200];   // matrix
int out[10100][5]; // out m
int ans[300];      // mark

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int i0, j0, v0;
        cin >> i0 >> j0 >> v0;
        out[i][0] = j0;
        out[i][1] = v0;
        if (a[i0][j0] > 0)
            a[i0][j0] = -1;
        if (a[i0][j0] == 0)
            a[i0][j0] = v0;
        out[i][2] = ans[i0];
        ans[i0] = i;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            cout << a[i][j] << " ";
        cout << endl;
    }

    for (int i = 1; i <= n; i++)
        cout << ans[i] << endl;
    for (int i = 1; i <= m; i++)
        cout << out[i][0] << " " << out[i][1] << " " << out[i][2] << endl;
}