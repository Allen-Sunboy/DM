#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;
const int maxn = 999999;
struct edge { int v, w; };
struct node {
    int dis, u;
    bool operator>(const node& a) const { return dis > a.dis; }
};
vector<edge> e[maxn];
int dis[maxn], vis[maxn];
priority_queue<node, vector<node>, greater<node> > q;

void dijkstra(int n, int s) {
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0; //s = start
    q.push({0, s});
    while (!q.empty()) {
        int u = q.top().u;
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto ed : e[u]) {
            int v = ed.v, w = ed.w;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                q.push({dis[v], v});
            }
        }
    }
}

int main()
{	
    int n;
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        e[u].push_back({v,w});
        e[v].push_back({u,w});
    }
    int a, b;
    cin >> a >> b;
    dijkstra(a,b);
    cout << dis[a] << endl;
}