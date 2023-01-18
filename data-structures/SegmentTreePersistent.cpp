// Same time complexity as normal SegmentTree
// Additional O(log(n)) memory per update
// Tested on https://cses.fi/problemset/task/1737
template <typename T, T merge(T, T)>
struct Node{
    Node *left=0, *right=0;
	int i, j;
    T val;
	Node() {}
	Node(int _i, int _j) : i(_i), j(_j) {}
	Node(vector <T> &A){
		int N = int(A.size());
		i = 0, j = N-1;
		build(A);
	}

    void build(vector <ll> &A){
        if(i == j){
			val = A[i];
			return;
		}
        int mid = (i+j)/2;
        left = new Node<T,merge>(i, mid);
        right = new Node<T,merge>(mid+1, j);
        left->build(A);
        right->build(A);
		val = merge(left->val, right->val);
    }

    Node *update(int t, ll v){
        if(t < i || j < t){
            return this;
        }
        if(i == j){
            Node *ret = new Node<T,merge>(*this);
			ret->val = v;
            return ret;
        }
        Node *ret = new Node<T,merge>(i, j);
        ret->left = left->update(t, v);
        ret->right = right->update(t, v);
        ret->val = merge(ret->left->val, ret->right->val);
        return ret;
    }

    ll query(int l, int r){
        if(l <= i && j <= r) return val;
		int mid = (i+j)/2;
		if(mid < l || r < i) return right->query(l, r);
		else if(j < l || r < mid+1) return left->query(l, r);
        return merge(left->query(l, r), right->query(l, r));
    }
};
