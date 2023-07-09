#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

//char a[20];
//G2 A3 B3 C3 D3 E3 F3 G3 A4 B4 C4 D4 E4 F4
string down;
char name[20][5] = {"G2", "A3", "B3", "C3", "D3", "E3", "F3", "G3", "A4", "B4", "C4", "D4", "E4", "F4"};
const int inf = 0x3f3f3f3f;

char out[20000][4];

bool mark[20000]; //是否是永久节点
bool marklist[20000]; //是否放入临时节点中
int front[20000]; //最短的前驱

int sto[20000]; //最短距离
vector<int>list; //临时节点

string getbin(int n) //十进制转string
{
    string x;
    while(n != 0){
        int a;
        a = n % 2;
        x.insert(x.begin(),a+'0');
        n = n >> 1;
    }
    int k = x.size();
    for(; k < 14; k++)
    {
        x.insert(x.begin(), '0');
    }
    return x;
}

int power(int a, int b) //幂
{
    int e = 1;
    for(int i = 0; i < b; i++)
        e *= a;
    return e;
}

int getval(string down) //string转十进制
{
    int e = 0;
    for(int i = 0; i < 14; i++)
        e += (down[i] - '0') * power(2, 13-i);
    return e;

}

int f(int a, int b)
{
    int x = max(a,b);
    int y = min(a,b);
    if(x-y==2)
        return 3;

    if(x-y==7 || x-y==9 ||  (x-y==5 && (y+7<14 || x-7>=0)) )
        return 4;
    
    if(x-y==4)
        return 5;
    
    if(x-y==11 || (x-y==3 && (y+7<14 || x-7>=0) ) )
        return 6;
    
    if(x-y==6)
        return 7;
    
    if(x-y==13 || (x-y==1 && (y+7<14 || x-7>=0) ) )
        return 8;
    
    return 1000;
}

int F(string down)
{
    int ansn = 0;
    for(int i = 0; i < 14; i++)
    {
        if(down[i] == '1')
        {
            for(int j = i+1; j < 14; j++)
            {
                if(down[j] == '1')
                    ansn ^= f(i, j);
            }
        }
    }
    return ansn;
}

int diff(int a, int b)
{
    string aa = getbin(a);
    string bb = getbin(b);
    for(int i = 0; i < 14; i++)
        if(aa[i] != bb[i])
            return i;
}


int main()
{
    memset(sto, 0x3f, sizeof(sto));
    cin >> down;
    string origin = down;

    //cout << "test get bin 0 " << getbin(0) << endl;

    mark[getval(down)] = 1;
    sto[getval(down)] = 0;

    while(getval(down) != 0)
    {
    int downvalue = getval(down); //原先的值
    for(int i = 0; i < 14; i++) //遍历所有后继
    {
        down[i] = !(down[i]-'0')+'0';
        if(!mark[getval(down)])
        {
            if(sto[downvalue] + F(down) < sto[getval(down)])
            {
                front[getval(down)] = downvalue;
                sto[getval(down)] = sto[downvalue] + F(down);
            }
            //cout << sto[getval(down)] << " " << F(down) << endl;
            if(!marklist[getval(down)]){
                list.push_back(getval(down));
                marklist[getval(down)] = 1;
            }
                
        }
        down[i] = !(down[i]-'0')+'0';
    }
    int minp = 0;
    for(int i = 0; i < list.size(); i++)
    {
        //cout << "mark? " << mark[list[i]] << endl;
        if(sto[list[i]] < sto[list[minp]])
        minp = i;
        //测试
        //cout << list[i] << " ";

    }
    //cout << list[minp] << endl;
    //cout << "minp " <<  minp << endl;
    mark[list[minp]] = 1;
    //cout << list[minp] << endl;
    down = getbin(list[minp]);
    //cout << "down " << down << endl;
    //cout << "getval donw " << getval(down) << endl;
    marklist[list[minp]] = 0;
    list.erase(list.begin()+minp);
    //cout << down << endl;
    //cout << "sto getval down " << sto[getval(down)] << endl;
    }
    
    int a = 0;
    int i = 0;
    //cout << front[0] << " ";
    while(getbin(a) != origin){
        //cout << front[a] << " ";
        strcpy(out[i],name[diff(a,front[a])]);
        a = front[a];
        i++;
    }
    for(int j = i-1; j >= 0; j--)
    cout << out[j] << " ";
    cout << endl;
    cout << sto[0] << endl;


    

}