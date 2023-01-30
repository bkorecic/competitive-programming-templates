struct sparse_table{
    // O(nlogn) preprocessing, O(1) query en rango
    // para función idempotente (como min, max, gcd, etc)
    int n;
    vector <int> logs;
    vector <vector<ll>> table;
    sparse_table(vector <ll> &A){
        n = A.size();
        logs.resize(n+1);
        logs[1] = 0;
        for(int i=2; i<=n; i++){
            logs[i] = logs[i/2] + 1;
        }
        table.assign(logs[n]+1, vector<ll>(n,0)); 
        for(int i=0; i<=logs[n]; i++){
            int cur_len = 1 << i;
            for(int j=0; j+cur_len-1<n; j++){
                if(cur_len == 1){
                    table[i][j] = A[j];
                }
                else{
                    table[i][j] = min(table[i-1][j], table[i-1][j+cur_len/2]); 
                }
            }
        }
    }
    ll query(int i, int j){
        int p = logs[j-i+1];
        int len = 1 << p;
        return min(table[p][i], table[p][j-len+1]);
    } 
};
