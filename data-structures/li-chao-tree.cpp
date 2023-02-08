struct line{
	ll a,b;
	line(){}
	line(ll _a, ll _b) : a(_a), b(_b) {}
	ll eval(ll x) { return a*x+b; }
};

// Dynamic/persistent min Li Chao tree
// Tested on: https://codeforces.com/contest/319/problem/C (add_line, query)
// Tested on: https://www.acmicpc.net/problem/3319 (padd_line, query)
struct lc_node{
	lc_node *left=0, *right=0;
	ll i, j;
	line val;
	lc_node(ll _i, ll _j, line _val) : i(_i), j(_j), val(_val) {}

	// Non-persistent line add
	void add_line(ll a, ll b){
		line v(a,b);
		add_line(v);
	}

	void add_line(line &v){
		ll cur_left=val.eval(i), cur_right=val.eval(j);
		ll new_left=v.eval(i), new_right=v.eval(j);
		if(cur_left <= new_left && cur_right <= new_right) return;
		if(cur_left > new_left && cur_right > new_right){
			val=v;
			return;
		}
		ll mid = (i+j)>>1;
		if(cur_left > new_left) swap(val, v);
		if(val.eval(mid) < v.eval(mid)){
			if(!right) right = new lc_node(mid+1, j, v);
			else right->add_line(v);
		}
		else{
			swap(val, v);
			if(!left) left = new lc_node(i, mid, v);
			else left->add_line(v);
		}
	}
	
	// Persistent line add
	lc_node *padd_line(ll a, ll b){
		line v(a,b);
		return padd_line(v);
	}
	
	lc_node *padd_line(line &v){
		ll cur_left=val.eval(i), cur_right=val.eval(j);
		ll new_left=v.eval(i), new_right=v.eval(j);
		if(cur_left <= new_left && cur_right <= new_right) return this;
		lc_node *ret = new lc_node(*this);
		if(cur_left > new_left && cur_right > new_right){
			ret->val = v;
			return ret;
		}
		ll mid = (i+j)>>1;
		if(cur_left > new_left) swap(ret->val, v);
		if(ret->val.eval(mid) < v.eval(mid)){
			if(!ret->right) ret->right = new lc_node(mid+1, j, v);
			else ret->right = ret->right->padd_line(v);
		}
		else{
			swap(ret->val, v);
			if(!ret->left) ret->left = new lc_node(i, mid, v);
			else ret->left = ret->left->padd_line(v);
		}
		return ret;
	}
	ll query(ll x){
		if(i == j) return val.eval(x);
		ll mid = (i+j)>>1;
		if(x <= mid && left) return min(val.eval(x), left->query(x));
		else if(x >= mid+1 && right) return min(val.eval(x), right->query(x));
		return val.eval(x);
	}
};
