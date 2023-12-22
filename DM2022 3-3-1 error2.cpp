#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

#define maxn 250
#define INF 0x3f3f3f3f

struct Edge {
    int from, to, cap, flow;
    Edge(int u, int v, int c, int f) : from(u), to(v), cap(c), flow(f) {}
};

int n, m;
vector<Edge> edges;
vector<int> G[maxn];
int a[maxn], p[maxn];

int list[maxn];
int listnum;

void AddEdge(int from, int to, int cap, int f) {
    edges.push_back(Edge(from, to, cap, f));
    edges.push_back(Edge(to, from, 0, 0));
    int m = edges.size();
    G[from].push_back(m - 2);
    G[to].push_back(m - 1);
}

int Maxflow(int s, int t) {
    int flow = 0;
    memset(a, 0, sizeof(a));
    queue<int> Q;
    Q.push(s);
    a[s] = INF;
    while (!Q.empty()) {
        int x = Q.front();
        Q.pop();
        for (int i = 0; i < G[x].size(); i++) {
            Edge &e = edges[G[x][i]];
            if (!a[e.to] && e.cap > e.flow) {
                p[e.to] = G[x][i];
                a[e.to] = min(a[x], e.cap - e.flow);
                Q.push(e.to);
            }
        }
        if (a[t])
            break;
    }
    if (!a[t])
        return -1;
    for (int u = t; u != s; u = edges[p[u]].from) {
        list[listnum] = u;
        listnum++;
        edges[p[u]].flow += a[t];
        edges[p[u] ^ 1].flow -= a[t];
    }
    list[listnum] = s;
    listnum++;
    flow += a[t];

    return flow;
}

int s, t;

int main() {
    cin >> n >> m >> s >> t;
    // cout << m << endl;
    for (int i = 0; i < m; i++) {
        int u, v, c, f;
        cin >> u >> v >> c >> f;
        // cout << i << endl;
        AddEdge(u, v, c, f);
    }
    int result = Maxflow(s, t);
    if (result == -1)
        cout << -1 << endl;
    else {
        cout << listnum << " " << result << endl;
        for (int i = listnum - 1; i >= 0; i--) {
            cout << list[i] << " ";
        }
    }
}