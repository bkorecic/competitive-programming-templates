template <class T>
struct SegmentTree{
  int N;
  vector <T> tree;
  vector <T> lazy;
  SegmentTree(vector <T> &A){
    N = A.size();
    tree.resize(4*N);
    lazy.assign(4*N, T());
    build(0, 0, N-1, A);
  }

  T merge(T a, T b){ // !
  }
  
  void build(int n, int i, int j, vector <T> &A){
    if(i == j){
      tree[n] = A[i];
      return;
    }
    int mid = (i+j)/2;
    build(2*n+1, i, mid, A);
    build(2*n+2, mid+1, j, A);
    tree[n] = merge(tree[2*n+1], tree[2*n+2]);
  }

  T query(int l, int r){
    return query(0, 0, N-1, l, r);
  }

  T query(int n, int i, int j, int l, int r){
    if(lazy[n] != 0){
        tree[n] += lazy[n]*(j-i+1);
        if(i != j){
            lazy[2*n+1] += lazy[n];
            lazy[2*n+2] += lazy[n];
        }
        lazy[n] = 0;
    }
    if(l <= i && j <= r) return tree[n];
    int mid = (i+j)/2;
    if(mid < l || r < i)
      return query(2*n+2, mid+1, j, l, r);
    if(j < l || r < mid+1)
      return query(2*n+1, i, mid, l, r);
    return merge(
        query(2*n+1, i, mid, l, r),
        query(2*n+2, mid+1, j, l, r));
  }

  void update(int l, int r, T val){
    update(0, 0, N-1, l, r, val);
  }
  
  void update(int n, int i, int j, int l, int r, T val){
    if(lazy[n] != 0){
        tree[n] += lazy[n]*(j-i+1);
        if(i != j){
            lazy[2*n+1] += lazy[n];
            lazy[2*n+2] += lazy[n];
        }
        lazy[n] = 0;
    }
    if(r < i || j < l) return;
    if(l <= i && j <= r){
        tree[n] += val*(j-i+1);
        if(i != j){
            lazy[2*n+1] += val;
            lazy[2*n+2] += val;
        }
        return;
    }
    int mid = (i+j)/2;
    update(2*n+1, i, mid, l, r, val);
    update(2*n+2, mid+1, j, l, r, val);
    tree[n] = merge(tree[2*n+1], tree[2*n+2]);
  }
};
