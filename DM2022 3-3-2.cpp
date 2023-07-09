#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
const int maxn = 50;
const long long inf = 1000000000003;
int n, m;

long long m_cap[maxn][maxn];
long long m_flow[maxn][maxn];
long long n_cap[maxn];
long long n_flow[maxn];

bool check[maxn];
int pre[maxn];

bool bfs(int s, int t)
{
    queue<int> que;
    memset(pre, 1, sizeof(pre));
    memset(check, 0, sizeof(check));
    pre[s] = s;
    check[s] = 1;
    que.push(s);
    int p;
    if(n_cap[s] <= n_flow[s])
        return 0;
    while(!que.empty())
    {
        p = que.front();
        // cout << p << endl;
        que.pop();
        for(int i = 0; i <= n+1; i++){
            if((m_cap[p][i] > m_flow[p][i] || m_cap[p][i] == -1) && (n_cap[i] > n_flow[i] || n_cap[i] == -1) && !check[i])
            {
                pre[i] = p;
                check[i] = 1;
                if(i == t)
                    return 1;
                que.push(i);
            }
        }
    }
    return 0;
}
long long result(int s, int t)
{
    long long maxm_flow = 0;
    long long d;
    while(bfs(s, t))
    {
        d = inf;
        for(int i = t; i != s; i = pre[i])
        {
            if(m_cap[pre[i]][i] != -1 && m_cap[pre[i]][i] - m_flow[pre[i]][i] < d)
                d = m_cap[pre[i]][i] - m_flow[pre[i]][i];
            if(n_cap[i] != -1 && n_cap[i] - n_flow[i] < d)
                d = n_cap[i] - n_flow[i];
        }
        d =  min(d, n_cap[s] - n_flow[s]);
        for(int i = t; i != s; i = pre[i])
        {
            m_flow[pre[i]][i] += d;
            m_flow[i][pre[i]] += d;
            n_flow[i] += d;
        }
        n_flow[s] += d;
        maxm_flow += d;
    }
    return maxm_flow;
}
int main()
{
    cin >> n >> m;
    for(int i = 0; i <= n; i++)
        cin >> n_cap[i];
    n_cap[n+1] = -1;
    for(int i = 0; i < m; i++)
    {
        int u, v, c;
        cin >> u >> v >> c;
        if(c == -1)
        {
            m_cap[u][v] = -1;
            continue;
        }
        if(m_cap[u][v] == -1)
            continue;
        m_cap[u][v] += c;
    }
    cout << result(0, n+1) << endl;
}