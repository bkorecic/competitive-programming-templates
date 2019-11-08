struct Hash{
    ll MOD; // 1e9+7, 1e9+123
    ll B; // 127, 139
    vector <ll> pot; 
    vector <ll> H;
    int n;
    Hash(string &s, ll _B, ll _MOD){
        n = s.length(); 
        B = _B;
        MOD = _MOD;
        pot.resize(n+1);
        H.resize(n);
        H[n-1] = s[n-1];
        for(int i = n-2; i>=0; i--){
            H[i] = (s[i] + H[i+1]*B)%MOD;
        }
        pot[0] = 1;
        for(int i=1; i<n+1; i++){
            pot[i] = (pot[i-1]*B)%MOD;
        }
    }
    ll hash(int i, int j){
        ll resta;
        if(j == n-1) resta = 0;
        else resta = H[j+1]*pot[j-i+1]%MOD;
        return (H[i] - resta + MOD)%MOD;
    }
};
