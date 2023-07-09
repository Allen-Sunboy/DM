#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
int p;
bool con[20][20];
vector<int> sto[20];
int color[20];
int num = 0;
int d[20];
int list[20];

int comp(int &a, int &b)
{
    return d[a] > d[b];
}

int main()
{
    cin >> n >> p;
    for(int i = 0; i < p; i++)
    {
        int u, v;
        cin >> u >> v;
        con[u][v] = 1;
        con[v][u] = 1;
        d[u]++;
        d[v]++;
    }
    // for(int i = 1; i <= n; i++)
    // 	cout << d[i] << " ";
    // cout << endl;

    for(int i = 1; i <= n; i++)
        list[i] = i;
    
    sort(list+1, list+n+1, comp);
    
    // for(int i = 1; i <= n; i++)
    // 	cout << list[i] << " ";
    // cout << endl;
    for(int i = 1; i <= n; i++)
        color[i] = 1;

    // if(p == 0)
    // {
    // 	cout << 1 << endl;
    // 	for(int i = 1; i <= n; i++)
    // 		cout << i << " ";
    // }
    for(int i = 1; i <= n; i++)
    {
        for(int j = i+1; j <= n; j++)
        {
            if(con[list[i]][list[j]] && color[list[i]] == color[list[j]])
            {
                color[list[j]]++;
            }
        }
    }
    for(int i = 1; i <= n; i++)
        num = max(num, color[i]);
    cout << num << endl;
    for(int i = 1; i <= n; i++)
        cout << color[i] << " ";

        



    
}