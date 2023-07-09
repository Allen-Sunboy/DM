#include <iostream>
using namespace std;
const long long inf = 1000000000000003;
long long n, m;
const long long maxn = 4003;
long long g[maxn][maxn];
long long mincost[maxn];
long long near[maxn];
long long sum = 0;
long long X[maxn];
long long Y[maxn];
bool vis[maxn];

long long length(long long i, long long j)
{
    long long xi = min(X[i], X[j]);
    long long xj = max(X[i], X[j]);
    long long yi = min(Y[i], Y[j]);
    long long yj = max(Y[i], Y[j]);
    long long len = (xj - xi) * (xj - xi) * (xj - xi) + (yj - yi) * (yj - yi) * (yj - yi);
    return len;
}
void prim(int s){
    for(int i = 1; i <= n; i++)
    {
        if(i == s)
            mincost[i] = 0;
        else
            mincost[i] = g[s][i];
        near[i] = s;
    }
    long long minn, p;
    for(int i = 1; i <= n; i++)
    {
        minn = inf;
        for(int j = 1; j <= n; j++)
        {
            if(mincost[j] != 0 && mincost[j] < minn)
            {
                minn = mincost[j];
                p = j;
            }
        }
        if(minn == inf)
            break;
        sum += minn;
        for(int j = 1; j <= n; j++)
        {
            if(g[p][j] < mincost[j])
            {
                mincost[j] = g[p][j];
                near[j] = p;
            }
        }
    }
}

int main()
{
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> X[i] >> Y[i];
    }
    for(int i = 1; i <= n; i++)
        for(int j = 1; j < i; j++){
            g[i][j] = length(i, j);
            g[j][i] = length(i, j);
        }
    prim(1);
    cout << sum << endl;
}