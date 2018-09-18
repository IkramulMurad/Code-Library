#include <bits/stdc++.h>
using namespace std;

const int mx = 205;
vector <vector <int> > g(mx);
int l[mx], r[mx];
bool visited[mx];

bool dfs(int u){
    for(int i = 0; i < g[u].size(); ++i){
        int v = g[u][i];
        if(!visited[v]){
            visited[v] = true;
            if(l[v] == -1 or dfs(l[v])){
                l[v] = u;
                r[u] = v;
                return true;
            }
        }
    }
    return false;
}

int bpm(int n){
    int total = 0;
    memset(l, -1, sizeof(l));
    memset(r, -1, sizeof(r));

    for(int i = 0; i < n; ++i){
        memset(visited, false, sizeof(visited));
        if(dfs(i)) ++total;
    }
    return total;
}

int main(){
    for(int i = 0; i < mx; ++i) g[i].clear();

    g[0].push_back(7);
    g[0].push_back(8);
    g[2].push_back(6);
    g[2].push_back(9);
    g[3].push_back(8);
    g[4].push_back(8);
    g[4].push_back(9);
    g[5].push_back(11);

    printf("Total BPM: %d\n", bpm(12));

    return 0;
}
