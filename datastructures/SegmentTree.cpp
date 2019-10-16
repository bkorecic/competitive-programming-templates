struct SegmentTree{
	vector <ll> tree;
	int N;
	SegmentTree(vector <ll> &A){
		N = A.size();
		tree.resize(4*N);
		build(0, 0, N-1, A);
	}

	ll merge(ll a, ll b){
		return a + b;
	}

	void build(int n, int l, int r, vector <ll> &A){
		if(l == r){ // caso hoja
			tree[n] = A[l];
			return;
		}
		int mid = (l+r)/2; // caso general
		build(2*n+1, l, mid, A);
		build(2*n+2, mid+1, r, A);
		tree[n] = merge(tree[2*n+1], tree[2*n+2]);
	}

	ll query(int i, int j){
		return(query(0, 0, N-1, i, j));
	}

	ll query(int n, int l, int r, int i, int j){
		if(i <= l && r <= j){ // contenido completamente
			return tree[n];
		}
		if(r < i || j < l){ // fuera del rango
			return 0;
		}
		int mid = (l+r)/2; // contenido parcialmente
		ll a = query(2*n+1, l, mid, i, j);
		ll b = query(2*n+2, mid+1, r, i, j);
		return merge(a, b);
	}

	void update(int i, ll v){
		update(0, 0, N-1, i, v);
	}

	void update(int n, int l, int r, int i, ll v){
		if(l == r && r == i){ // hoja
			tree[n] = v;
			return;
		}
		if(i < l || r < i) return; // fuera del rango
		int mid = (l+r)/2; // contenido parcialmente
		update(2*n+1, l, mid, i, v);
		update(2*n+2, mid+1, r, i, v);
		tree[n] = merge(tree[2*n+1], tree[2*n+2]);
	}
};
