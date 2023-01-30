// Heavy Light decomposition of a tree
// Queries in O(log²(n))
// requires: segment_tree
// querying on edges: store edge value in child, change enter[u] in query
template <class T, T merge(T, T)>
struct heavy_light{
	// depth: node depth;
	// sz: subtree size
	// enter: discovery time (index in euler tour)
	// par: parent node
	// head: head of node's chain
	vector <int> depth, sz, enter, par, head;
	segment_tree <T, merge> st;
	vector <T> euler;
	vector <vector <int>> &adj;
	vector <T> &val;
	int time=0;
	/* adj: adjacency list
	 * val: value associated with each node
	 * merge: merge function for queries
	 */
	heavy_light(vector <vector <int>> &_adj, vector <T> &_val, int root=0) : adj(_adj), val(_val) {
		int n = int(adj.size());
		depth.resize(n); sz.resize(n);
		enter.resize(n); par.resize(n);
		euler.resize(n); head.resize(n);
		par[root] = -1;
		depth[root] = 0;
		dfs1(root);
		dfs2(root, root);
		st = segment_tree <T, merge>(euler);
	}
	void dfs1(int u){ // first dfs, computes depth and sz
		sz[u]=1;
		for(int v : adj[u]){
			if(v != par[u]){
				par[v] = u;
				depth[v] = depth[u]+1;
				dfs1(v);
				sz[u] += sz[v];
			}
		}
	}
	void dfs2(int u, int h){ // second dfs, computes hld
		head[u] = h;
		enter[u] = time++;
		euler[enter[u]] = val[u];
		int mx=-1;
		for(int v : adj[u]){
			if(par[u] != v && (mx==-1 || sz[v]>sz[mx])) mx=v;
		}
		if(mx != -1) dfs2(mx, h);
		for(int v : adj[u]){
			if(v != par[u] && v != mx)
				dfs2(v, v);
		}
	}
	T query(int u, int v){
		T ans = T(); // identity element
		while(head[u] != head[v]){ // find LCA
			if(depth[head[u]] > depth[head[v]]) swap(u, v);
			ans = merge(ans, st.query(enter[head[v]], enter[v]));
			v = par[head[v]];
		}
		if(depth[u] > depth[v]) swap(u, v); // make sure "u" is LCA
		ans = merge(ans, st.query(enter[u], enter[v])); // enter[u]+1 for edge queriesk
		return ans;
	}
	void update(int u, T x){
		st.update(enter[u], x);
	}
};
