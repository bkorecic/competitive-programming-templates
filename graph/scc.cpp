/* Tarjan's SCC algorithm
 * O(|V|+|E|) runtime, O(|V|) memory
 * comp[u] = scc of u, comps = list of scc
 */
struct SCC {
  int n, time = 0;
  vector <int> val, comp, z, comps;
  vector <vector<int>> adj;
  SCC(int _n){
    n = _n;
    adj.resize(n);
    val.resize(n);
    comp = vector<int>(n, -1);
  }
  void add(int u, int v){
    adj[u].push_back(v);
  }
  int dfs(int u){
    int low = val[u] = ++time;
    z.push_back(u);
    for(int v : adj[u]) if(comp[v] == -1) // comp[v] == -1 and val[v] != 0 => in stack
      low = min(low, val[v] ? val[v] : dfs(v));
    if(low == val[u]){
      comps.push_back(u);
      for(int v = -1; v != u;){
        comp[v = z.back()] = u;
        z.pop_back();
      }
    }
    return val[u] = low;
  }
  void run(){
    for(int i=0; i<n; i++) if(!val[i]) dfs(i);
    //reverse(comps.begin(), comps.end()); // optional
  }
};
