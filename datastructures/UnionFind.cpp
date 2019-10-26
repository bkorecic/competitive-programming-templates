struct DSU{ //Disjoint Set Union
    vector <int> parent, sz; // sz es size
    DSU(int n){
        parent.resize(n);
        sz.resize(n);
        for(int i=0; i<n; i++){
            parent[i] = i;
            sz[i] = 1;
        }
    }
    int find_set(int v){
        if(v == parent[v]) return v;
        return parent[v] = find_set(parent[v]);
    }
    void union_set(int a, int b){
        a = find_set(a);
        b = find_set(b);
        if(a != b){
            if(size[a] < size[b])
                swap(a,b);
            parent[b] = a;
            size[a] += size[b];
        }
    }
};
