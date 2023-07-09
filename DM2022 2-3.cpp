#include <iostream>
#include <vector>
#include <iomanip>
#include <cstring>
using namespace std;

int n;
double v[102000]; //单线生产速率，单位是万
double s[102000]; //建立一条产线所需时间
vector<pair<int, double>> p[102000]; //前置技术，及其所需数量（改为所需时间了）
vector<int> h[102000];
int d[102000]; //负度
vector <int> list; //排序后的
bool inlist[201000];

double timen(int k, double ne)
{
    double a = v[k];
    double ti = 0;
    while(a * s[k] < ne){
        ti += s[k];
        ne -= a * s[k];
        a += v[k];
    }
    ti += ne / a;
    return ti;
}
int main()
{
    double maxtime[102000];
    memset(maxtime,0,sizeof(maxtime));
    cin >> n;
    for(int i = 1; i <= n-1; i++)
        cin >> v[i];
    for(int i = 1; i <= n-1; i++)
        cin >> s[i];
    for(int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        d[i] = x;
        for(int j = 1; j <= x; j++)
        {
            int x1;
            double x2;
            cin >> x1 >> x2;
            h[x1].push_back(i);
            p[i].push_back({x1, timen(x1, x2)});
        }
    }
    int listnum = 0;
    while(listnum < n){
        for(int i = 1; i <= n; i++)
        {
            if(d[i] == 0 && inlist[i] == 0)
            {
                list.push_back(i);
                inlist[i] = 1;
                for(int j = 0; j < h[i].size(); j++)
                {
                    d[h[i][j]]--;
                }
                listnum++;
            }
        }
    }



    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < p[list[i]].size(); j++)
        {
            maxtime[list[i]] = max(maxtime[list[i]], maxtime[p[list[i]][j].first] + p[list[i]][j].second);
        }
    }
    cout << fixed << setprecision(2) << maxtime[n];
}