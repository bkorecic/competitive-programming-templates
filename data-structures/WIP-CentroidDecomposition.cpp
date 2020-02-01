#include <bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int,int> ii;

struct CentroidDecomposition{
    vector <vector<int>> tree;
    vector <int> sub_size, layer, parent; // subtree size, node layer in centroid tree
    vector <bool> removed; // removed nodes
    int n;
    CentroidDecomposition(vector <vector<int>> &adj){
        n = adj.size();
        layer.resize(n);
        sub_size.resize(n);
        removed.assign(n,false);
        build(0,0,adj);
    }

    int build(int root, int l, vector<vector<int>> &adj){
        int s = calc_size(root,root,adj);
        int c = find_centroid(root,root,s,adj);
        removed[c] = true;
        layer[c] = l;
        for(int v : adj[c]){
            if(removed[v]) continue;
            int c2 = build(v, l+1, adj);
            tree[c].pb(c2);
            tree[c2].pb(c);
            parent[c2] = c;
        }
        return c;
    }

    int calc_size(int u, int p, vector<vector<int>> &adj){
        int ans = 1;
        for(int v : adj[u]){
            if(!removed[v] && v != p){
                ans += calc_size(v, u, adj); 
            }
        }
        sub_size[u] = ans; 
        return ans;
    }

    int find_centroid(int u, int p, int s, vector<vector<int>> &adj){ // s: component size
        for(int v : adj[u]){
            if(!removed[v] && v != p && sub_size[v] > s/2){
                return find_centroid(v, u, s, adj);
            }
        }
        return u;
    }

    int lca(int u, int v){
        while(u != v){
            if(layer[u] > layer[v]){
                u = parent[u]; 
            }
            else{
                v = parent[v];
            }
        }
        return u;
    } 

    void print_tree(){
        int u;
        for(int i=0; i<n; i++){
            if(layer[i] == 0){
                u = i; break;
            }
        }
        vector <bool> visited(n,false);
        visited[u] = true;
        cout << "0: " << u << '\n';
        queue <int> q;
        q.push(u);
        int depth = 1;
        while(true){
            cout << depth << ": ";
            u = q.front(); q.pop();
            for(int v : tree[u]){
                if(!visited[v]){
                    q.push(v);
                    cout << v << ' ';
                }
            } cout << '\n';
        }
    }
};

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    vector <vector<int>> adj(n);
    for(int i=0; i<n-1; i++){
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    CentroidDecomposition cd(adj);
    cd.print_tree();
    return 0;
}
