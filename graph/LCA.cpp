struct LCA{ // Uses Binary Lifting. O(nlogn) preprocessing, O(logn) query.
    int n, l, timer=0;
    vector <vector<int>> up;
    vector <int> enter, exit;
    LCA(vector <vector<int>> &adj, int root=0){
        n = adj.size();
        l = ceil(log2(n));
        enter.resize(n);
        exit.resize(n);
        up.resize(n, vector<int>(l+1));
        dfs(root, root, adj);
    }

    void dfs(int u, int p, vector<vector<int>> &adj){
        enter[u] = timer++;
        up[u][0] = p;
        for(int j=1; j<=l; j++){
            up[u][j] = up[up[u][j-1]][j-1]; 
        }
        for(int v : adj[u]){
            if(v != p) dfs(v, u, adj);
        }
        exit[u] = timer++;
    }

    bool is_ancestor(int u, int v){ // v is ancestor of u
        return enter[u] <= enter[v] && exit[u] >= exit[v]; 
    }

    int query(int u, int v){
        if(is_ancestor(u,v)) return u;
        if(is_ancestor(v,u)) return v;
        for(int i=l; i>=0; i--){
            if(!is_ancestor(up[u][i], v)){
                u = up[u][i]; 
            }
        }
        return up[u][0];
    } 
};
