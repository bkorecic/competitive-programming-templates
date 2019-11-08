typedef long long ll;

struct SegmentTree{
    //O(n) build, O(nlogn) query&update
    vector <ll> tree;
    vector <ll> lazy;
    int N;
    SegmentTree(vector <ll> &A){
        N = A.size();
        tree.resize(4*N);
        lazy.assign(4*N, 0);
        build(0, 0, N-1, A);
    }
 
    ll merge(ll a, ll b){
        return a+b;
    }
 
    void build(int n, int l, int r, vector <ll> &A){
        if(l == r){
            tree[n] = A[l];
            return;
        }
        int mid = (l+r)/2;
        build(2*n+1, l, mid, A);
        build(2*n+2, mid+1, r, A);
        tree[n] = merge(tree[2*n+1], tree[2*n+2]);
    }
 
    ll query(int i, int j){
        return query(0, 0, N-1, i, j);
    }
 
    ll query(int n, int l, int r, int i, int j){
        if(lazy[n] != 0){ // update pendiente
            tree[n] += lazy[n]*(r-l+1);
            if(l != r){
                lazy[2*n+1] += lazy[n];
                lazy[2*n+2] += lazy[n];
            }
            lazy[n] = 0;
        }
        if(i <= l && r <= j){ // contenido completamente
            return tree[n];
        }
        if(r < i || j < l){ // fuera del rango
            return 0;
        }
        int mid = (l+r)/2; // contenido parcialmente
        ll a = query(2*n+1, l, mid, i, j);
        ll b = query(2*n+2, mid+1, r, i, j);
        return merge(a,b);
    }
 
    void update(int i, int j, ll val){
        return update(0, 0, N-1, i, j, val);
    }
 
    void update(int n, int l, int r, int i, int j, ll val){
        if(lazy[n] != 0){ // update pendiente
            tree[n] += lazy[n]*(r-l+1);
            if(l != r){
                lazy[2*n+1] += lazy[n];
                lazy[2*n+2] += lazy[n];
            }
            lazy[n] = 0;
        }
        if(r < i || j < l) return; // fuera del rango
        if(i <= l && r <= j){ // contenido completamente
            tree[n] += val*(r-l+1);
            if(l != r){
                lazy[2*n+1] += val;
                lazy[2*n+2] += val;
            }
            return;
        }
        int mid = (l+r)/2; // contenido parcialmente
        update(2*n+1, l, mid, i, j, val);
        update(2*n+2, mid+1, r, i, j, val);
        tree[n] = merge(tree[2*n+1], tree[2*n+2]);
    }
};
