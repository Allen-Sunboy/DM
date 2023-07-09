#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector <int> a[202000];
bool dfs_check[202000];
bool bfs_check[202000];
int m, n;
vector <int> que;
int ans1;
queue <int> l;

void dfs(int x)
{
    if(dfs_check[x] == 1)
        return;
    
    dfs_check[x] = 1;
    cout << x << " ";

    for(int i = 0; i < a[x].size(); i++)
    {
        dfs(a[x][i]);
    }
    return;
}

void bfs()
{
    while(!l.empty()){
        for(int i = 0; i < a[l.front()].size(); i++ )
            if(bfs_check[a[l.front()][i]]==0)
            {
                l.push(a[l.front()][i]);
                bfs_check[a[l.front()][i]] = 1;
            }
                
        //
        //cout << a[l.front()][0] << endl;
        
        cout << l.front() << " ";
        l.pop();
    }

}


int main()
{
    int s;
    cin >> n >> m >> s;
    int vi, vj;
    for(int i = 1; i <= m; i++)
    {
        cin >> vi >> vj;
        a[vi].insert(a[vi].begin(),vj);
    }
    //cout << a[1][0] << endl;
    bfs_check[s] = 1;
    l.push(s);
    bfs();
    cout << endl;
    dfs(s);


}