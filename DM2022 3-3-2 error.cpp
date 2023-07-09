#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
const int maxn = 50;
const long long inf = 1000000000003;
int n, m;

long long capa[maxn][maxn];
long long flow[maxn][maxn];
long long cap[maxn];
long long flo[maxn];

bool vis[maxn];
int pre[maxn];
int direction[maxn];

bool bfs(int s, int t)
{
    queue<int> que;
    memset(pre, 1, sizeof(pre));
    memset(vis, 0, sizeof(vis));
    memset(direction, 0, sizeof(direction));
    pre[s] = s;
    vis[s] = 1;
    que.push(s);
    int p;

    if(cap[s] <= flo[s])
        return 0;
    
    for(int i = 1; i <= n+1; i++)
    {
        if((capa[s][i] > flow[s][i] || capa[s][i] == -1)  && (cap[i] > flo[i]) && cap[s] > flo[s])
        {
            direction[s] = 1;
            pre[i] = s;
            vis[i] = 1;
            if(i == t)
                return 1;
            que.push(i);
        }
    }
    que.pop();

    while(!que.empty())
    {
        p = que.front();
        // cout << p << endl;
        que.pop();
        for(int i = 1; i <= n+1; i++)
        {
            if((capa[p][i] > flow[p][i] || capa[p][i] == -1)&& (cap[i] > flo[i] || cap[i] == -1) && !vis[i])
            {
                // cout << "i" << i << endl;
                // cout << "r p i " << r[p][i] << endl;
                direction[p] = 1;
                pre[i] = p;
                vis[i] = 1;
                if(i == t)
                    return 1;
                que.push(i);
            }
            if(( flow[i][p] > 0 ) && !vis[i])
            {
                // cout << "i p = "<< i << " " << p << endl;
                // cout << "flow i p = " <<flow[i][p] << endl;
                direction[p] = -1;
                pre[i] = p;
                vis[i] = 1;
                que.push(i);
            }
        }
    }
    return 0;
}
long long ek(int s, int t)
{
    long long maxflow = 0;
    long long d;
    while(bfs(s, t))
    {
        d = inf;
        // cout << "pre" << endl;
        // for(int i = 0; i <= n+1; i++)
        // 	cout << pre[i] << " ";
        // cout << endl;

        // cout << "dir" << endl;
        // for(int i = 0; i <= n+1; i++)
        // 	cout << direction[i] << " ";
        // cout << endl;

        for(int i = t; i != s; i = pre[i])
        {
            if(direction[pre[i]] == 1)
            {
                if(capa[pre[i]][i] != -1 && capa[pre[i]][i] - flow[pre[i]][i] < d)
                    d = capa[pre[i]][i] - flow[pre[i]][i];
                if(cap[i] != -1 && cap[i] - flo[i] < d)
                    d = cap[i] - flo[i];
            }
            if(direction[pre[i]] == -1)
            {
                if(flow[i][pre[i]] < d && flow[i][pre[i]] > 0)
                    d = flow[i][pre[i]];
            }
        }
        d =  min(d, cap[s] - flo[s]);

        for(int i = t; i != s; i = pre[i])
        {
            if(direction[pre[i]] == 1)
            {
                flow[pre[i]][i] += d;
                flo[i] += d;
            }
            if(direction[pre[i]] == -1)
            {
                flow[i][pre[i]] -= d;
                flo[pre[i]] -= d;
            }
        }
        flo[s] += d;
        maxflow += d;
    // cout << d << endl;
    // for(int i = 0; i <= n+1; i++)
    // {
    // 	for(int j = 0; j <= n+1; j++)
    // 	{
    // 		cout << flow[i][j] << " ";
    // 	}
    // 	cout << endl;
    // }
    }
    return maxflow;
}
int main()
{
    cin >> n >> m;
    for(int i = 0; i <= n; i++)
        cin >> cap[i];
    cap[n+1] = -1;
    for(int i = 0; i < m; i++)
    {
        int u, v, c;
        cin >> u >> v >> c;
        if(c == -1)
        {
            capa[u][v] = -1;
            continue;
        }
        if(capa[u][v] == -1 || (capa[u][v] != -1 && capa[u][v] > c))
            continue;
        capa[u][v] = c;
    }
    // cout << "capa" << endl;
    // for(int i = 0; i <= n+1; i++)
    // {
    // 	for(int j = 0; j <= n+1; j++)
    // 	{
    // 		cout << capa[i][j] << " ";
    // 	}
    // 	cout << endl;
    // }
    cout << ek(0, n+1) << endl;
    
    // cout << "flow" << endl;
    // for(int i = 0; i <= n+1; i++)
    // {
    // 	for(int j = 0; j <= n+1; j++)
    // 	{
    // 		cout << flow[i][j] << " ";
    // 	}
    // 	cout << endl;
    // }

    // cout << "point flow" << endl;
    // for(int i = 0; i <= n+1; i++)
    // 	cout << flo[i] << " ";
    // cout << endl;
}