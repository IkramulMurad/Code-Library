#include <bits/stdc++.h>
using namespace std;

const int mx = 100;
const int inf = 1e9;
int rg[mx][mx];
int parent[mx];
int nodes;

bool bfs(int s, int t){
    memset(parent, -1, sizeof(parent));
    queue <int> q;
    q.push(s);

    while(!q.empty()){
        int u = q.front(); q.pop();
        //0 base node label
        for(int v = 0; v < nodes; ++v){
            if(parent[v] == -1 and rg[u][v] > 0){
                q.push(v);
                parent[v] = u;
                if(v == t) return true;
            }
        }
    }
    return false;
}

int edmondKarp(int s, int t){
    int maxFlow = 0;
    while(bfs(s, t)){
        int minPathFlow = inf;
        for(int v = t; v != s; v = parent[v]){
            int u = parent[v];
            minPathFlow = min(minPathFlow, rg[u][v]);
        }

        for(int v = t; v != s; v = parent[v]){
            int u = parent[v];
            rg[u][v] -= minPathFlow;
            rg[v][u] += minPathFlow;
        }

        maxFlow += minPathFlow;
    }
    return maxFlow;
}

int main(){
    //freopen("in.txt", "r", stdin);

    nodes = 6;
    rg[0][1] = 10;
    rg[0][2] = 10;
    rg[1][2] = 2;
    rg[1][3] = 4;
    rg[1][4] = 8;
    rg[2][4] = 9;
    rg[3][5] = 10;
    rg[4][3] = 6;
    rg[4][5] = 10;

    cout << "Max flow: " << edmondKarp(0, 5) << endl;

    return 0;
}
