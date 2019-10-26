struct Node{
    Node *left, *right;
    int val;
    Node(int a=0, Node *b=NULL, Node *c=NULL){
        val = a;
        left = b;
        right = c;
    }
    void build(int l, int r){
        if(l == r) return;
        left = new Node();
        right = new Node();
        int mid = (l+r)/2;
        left -> build(l, mid);
        right -> build(mid+1, r);
    }

    Node *update(int l, int r, int i, ll v){
        if(i < l || r < i){
            return this;
        }
        if(l == r){
            Node *ret = new Node(val, left, right);
            ret -> val += v;
            return ret;
        }
        int mid = (l+r)/2;
        Node *ret = new Node(val);
        ret -> left = left -> update(l, mid, i, v);
        ret -> right = right -> update(mid+1, r, i, v);
        ret -> val = ret -> left -> val + ret -> right -> val;
        return ret;
    }

    ll query(int l, int r, int i, int j){
        if(r < i || j < l) return 0;
        if(i <= l && r <= j) return val;
        int mid = (l+r)/2;
        return left -> query(l, mid, i, j) 
               + right -> query(mid+1,r, i, j);
    }
};

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
	int N = 10;
    vector <Node*> root;
    root.emplace_back(new Node());
    root[0] -> build(0,N-1); // 10 espacios
    root[0] = root[0] -> update(0, N-1, 0, 10); // update en mismo root
    root[1] = root[0] -> update(0, N-1, 1, 5); // nueva versión
	cout << root[0] -> query(0, N-1, 0, 2) << '\n'; // 10
	cout << root[1] -> query(0, N-1, 0, 2) << '\n'; // 15
    return 0;
}
