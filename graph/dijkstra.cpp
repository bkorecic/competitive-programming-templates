/* Dijkstra's algorithm for shortest path
 * O((|V|+|E|)log|V|) runtime using priority_queue
 */
typedef pair<ll, int> par;
const ll INF = 1e18;
priority_queue <par, vector<par>, greater<par>> pq;
vector <ll> d(n, INF);
d[0] = 0;
pq.push({0, 0});
while(!pq.empty()){
  auto [w, u] = pq.top(); // structured binding, C++17 only
  pq.pop();
  if(w != d[u]) // already marked node
    continue;
  for(auto [v, len] : adj[u]){
    if(d[u] + len < d[v]){
      d[v] = d[u] + len;
      pq.push({d[v], v});
    }
  }
}
