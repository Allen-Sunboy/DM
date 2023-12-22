#include <assert.h>
#include <stdio.h>
#include <string.h>

const int INF = 0x3fffffff;
const int MAXN = 40;

int inline min(int a, int b) { return a < b ? a : b; }

//
// 记录结点标号（结点编号从 1 开始）
// direction[u] = 1 表示标号为正，-1 表示标号为负，0 表示未标号
// from[u] 表示结点 u 是因为哪个结点才得到标号的
// delta[u] 表示从源到 u 的增流路径上最大的可增流量
//
int direction[MAXN + 1], from[MAXN + 1], delta[MAXN + 1];

int n, m, s, t;

class Graph {
public:
    // TODO: 选择适合本题的图数据结构并实现

    // 返回指定边的流量
    int Flow(/*TODO*/) { return /* TODO */; }

    // 返回指定边的容量
    int Capacity(/*TODO*/) { return /* TODO */; }

    // 添加一条从 u 到 v 的单向边，容量为 c，流量为 f
    void AddEdge(int u, int v, int c, int f) { /* TODO */ }
} G;

//
// 适用于 Ford-Fulkerson 算法的标号过程，基于深度优先搜索给所有结点标号
//
void label_dfs(int u) {
    for (each v /* TODO: 枚举每一个 v 满足 (u, v) 在图中 */) {
        // 如果 v 访问过，跳过该结点
        if (direction[v] != 0)
            continue;
        int c = G.Capacity(/*TODO*/);
        int f = G.Flow(/*TODO*/);
        if (/* TODO: 判断是否需要更新 v 的标号 */) {
            // TODO: 更新标号
            label_dfs(v); // 从 v 出发，搜索邻接的未标号结点
        }
    }
    for (/* TODO: 枚举每一个 v 满足 (v, u) 在图中 */) {
        // TODO: 仿照以上代码补全反向标号过程
    }
}

//
// 适用于 Edmonds-Karp 算法的标号过程，基于广度优先搜索给所有结点标号
//
void label_bfs() {
    static int q[MAXN + 1];
    int hd = 0, tl = 0;
    q[tl++] = s; // 第一个搜索源点
    while (hd < tl) {
        int u = q[hd++]; // 按入队顺序取出未标号结点
        for (each v /* TODO: 枚举每一个 v 满足 (u, v) 在图中 */) {
            // 如果 v 访问过，跳过该结点
            if (direction[v] != 0)
                continue;
            int c = G.Capacity(/*TODO*/);
            int f = G.Flow(/*TODO*/);
            if (/* TODO: 判断是否需要更新 v 的标号 */) {
                // TODO: 更新标号
                q[tl++] = v; // 从 v 出发，搜索邻接的未标号结点
            }
        }
        for (/* TODO: 枚举每一个 v 满足 (v, u) 在图中 */) {
            // TODO: 仿照以上代码补全反向标号过程
        }
    }
}

//
// Ford-Fulkerson 及 Edmonds-Karp 算法中的标号过程。
//
bool label() {
    // TODO: 初始化标号数组
    // 深度/广度优先搜索的调用入口，基于 bfs 或 dfs 实现均可
    label_dfs(s);
    // OR
    // label_bfs();
    // 通过汇点是否被标号判断允许流是否存在
    return direction[t] != 0;
}

void printPath() {
    int pathLength = 0;
    static int Path[MAXN + 1];
    // 根据记录的 from 数组，从汇点倒推出增流路径
    for (int v = t; v != s; v = from[v]) {
        Path[pathLength++] = v;
    }
    // TODO: 按照题目要求向标准输出中打印结果
}

void init() {
    scanf("%d%d%d%d", &n, &m, &s, &t);
    for (int i = 0; i < m; i++) {
        int u, v, c, f;
        scanf("%d%d%d%d", &u, &v, &c, &f);
        G.AddEdge(u, v, c, f);
    }
}

int main() {
    init();
    if (label()) {
        printPath();
    } else {
        printf("-1\n");
    }
}