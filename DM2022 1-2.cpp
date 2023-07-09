#include <iostream>
using namespace std;
long long a[200][200];
long long b[200][200];
long long c[200][200];
long long  n, m, s, t, k;
const long long  maxn = 1000003;
void p()
{
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            for(int k = 1; k <= n; k++)
                c[i][j] = ((c[i][j] % maxn) + (( (a[i][k] % maxn) *  (b[k][j]%maxn) ) % maxn)) % maxn;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
        {
            b[i][j] = c[i][j];
            c[i][j] = 0;
        }
}
int main()
{
    cin >> n >> m >> s >> t >> k;
    int x0, y0;
    for(int i = 0; i < m; i++)
    {
        cin >> x0 >> y0;
        a[x0][y0]++;
        b[x0][y0]++;
    }
    while(--k)
        p();
    cout << b[s][t];
}
