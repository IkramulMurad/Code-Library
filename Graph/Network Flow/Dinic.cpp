#include <bits/stdc++.h>
using namespace std;
 
struct Edge{
    int v, flow, cap, revIdx;
   
    Edge(){}
    Edge(int v, int flow, int cap, int revIdx) : v(v), flow(flow), cap(cap), revIdx(revIdx) {}
};
 
typedef vector <vector <Edge> > vve;
const int inf = 1e9;
const int mx = 105;
vve g(mx);
int level[mx];
int start[mx];
 
void addEdge(int u, int v, int c, vve &g){
    Edge a(v, 0, c, g[v].size());
    Edge b(u, 0, 0, g[u].size());
 
    g[u].push_back(a);
    g[v].push_back(b);
}
 
bool bfs(int s, int t){
    memset(level, -1, sizeof(level));
    level[s] = 0;
 
    queue <int> q;
    q.push(s);
 
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int i = 0; i < g[u].size(); ++i){
            Edge &edge = g[u][i];
            int &v = edge.v;
            if(level[v] == -1 and edge.flow < edge.cap){
                q.push(v);
                level[v] = level[u] + 1;
                if(v == t) return true;
            }
        }
    }
    return false;
}
 
int dfs(int u, int t, int prevFlow){
    if(u == t) return prevFlow;
 
    for(int &i = start[u]; i < g[u].size(); ++i){
        Edge &edge = g[u][i];
        int &v = edge.v;
 
        if(level[v] == level[u] + 1 and edge.flow < edge.cap){
            int minFlowTillNow = min(prevFlow, edge.cap - edge.flow);
            int minPathFlow = dfs(v, t, minFlowTillNow);
            if(minPathFlow > 0){
                edge.flow += minPathFlow;
                g[v][edge.revIdx].flow -= minPathFlow;
                return minPathFlow;
            }
        }
    }
    return 0;
}
 
int dinic(int s, int t){
    if(s == t) return 0;
    int maxFlow = 0;
    while(bfs(s, t)){
        memset(start, 0, sizeof(start));
        while(int flow = dfs(s, t, inf)){
            maxFlow += flow;
        }
    }
    return maxFlow;
}
 
int main(){
    //freopen("in.txt", "r", stdin);
 
    addEdge(0, 1, 10, g);
    addEdge(0, 2, 10, g);
    addEdge(1, 2, 2, g);
    addEdge(1, 3, 4, g);
    addEdge(1, 4, 8, g);
    addEdge(2, 4, 9, g);
    addEdge(3, 5, 10, g);
    addEdge(4, 3, 6, g);
    addEdge(4, 5, 10, g);

    cout << "Max flow: " << dinic(0, 5) << endl;
 
    return 0;
}
