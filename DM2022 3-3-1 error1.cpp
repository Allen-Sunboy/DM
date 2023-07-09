#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

int n, m, s, t;

long long direction[50], from[50], delta[50];
const long long inf = 100000000003;


class Graph{
    public:
    pair<long long, long long> edge[50][50]; //first = c, second = f

    long long Flow(int i, int j){
        return edge[i][j].second;
    }
    long long Capacity(int i, int j){
        return edge[i][j].first;
    }
    void AddEdge(int u, int v, long long c, long long f)
    {
        edge[u][v].first = c;
        edge[u][v].second = f;
    }
};

Graph G;

void label_dfs(int u)
{
    for(int v = 1; v <= n; v++)
    {
        if(direction[v] != 0)
            continue;
        if(G.edge[u][v].first > 0)
        {
            long long c = G.Capacity(u, v);
            long long f = G.Flow(u, v);
            if(c > f)
            {
                direction[v] = 1;
                from[v] = u;
                delta[v] = min(delta[u], c-f);
                G.edge[u][v].second += delta[v];
                // cout << "delta" << v  << delta[v] << endl; //test
                label_dfs(v);
            }
        }
        else if(G.edge[v][u].first > 0)
        {
            long long f = G.Capacity(v, u);
            if(f > 0)
            {
                direction[v] = -1;
                from[v] = u;
                delta[v] = min(delta[u], f);
                G.edge[v][u].second -= delta[v];
                // cout << "delta" << v <<  "fanxiang " << delta[v] << endl;
                label_dfs(v);
            }
        }
    }
}

void label_bfs()
{
    static long long q[51];
    long long hd = 0, tl = 0;
    q[tl++] = s;
    while(hd < tl)
    {
        int u = q[hd++];
        for(int v = 1; v <= n; v++)
        {
            if(direction[v] != 0)
                continue;
            if(G.edge[u][v].first > 0)
            {
                long long c = G.Capacity(u, v);
                long long f = G.Flow(u, v);
                if(c > f)
                {
                    direction[v] = 1;
                    from[v] = u;
                    delta[v] = min(delta[u], c-f);
                    G.edge[u][v].second += delta[v];
                    q[tl++] = v;
                    // cout << "delta" << v  << delta[v] << endl; //test
                }
            }
            else if(G.edge[v][u].first > 0)
            {
                long long f = G.Capacity(v, u);
                if(f > 0)
                {
                    direction[v] = -1;
                    from[v] = u;
                    delta[v] = min(delta[u], f);
                    G.edge[v][u].second -= delta[v];
                    q[tl++] = v;
                    // cout << "delta" << v <<  "fanxiang " << delta[v] << endl;
                }

            }
        }

    }
}

bool label()
{
    label_bfs();
    return direction[t] != 0;

}

int main()
{
    cin >> n >> m >> s >> t;
    for(int i = 0; i < m; i++)
    {
        int u, v;
        long long c, f;
        cin >> u >> v >> c >> f;
        G.AddEdge(u, v, c, f);
    }
    delta[s] = inf;

    // cout << delta[1] << endl; //test
    if(label())
    {
        long long pathLength = 0;
        static long long Path[50];
        for(int v = t; v != s; v = from[v])
        {
            Path[pathLength++] = v;
            // cout << "delta " << v << " " << delta[v] << endl;
        }
        Path[pathLength++] = s;
        cout << pathLength << " " << delta[t] << endl;
        for(int i = pathLength-1; i >= 0; i--)
            cout << Path[i] << " ";
        cout << endl;

        // for(int i = 1; i <= n; i++)
        // 	cout << delta[i] << " "; //test

    }
    else
        cout << -1 << endl;
    
}