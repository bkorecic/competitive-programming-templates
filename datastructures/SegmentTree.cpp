#include <bits/stdc++.h>
#define f first
#define s second
#define mp make_pair

using namespace std;

typedef long long ll;

struct SegmentTree{
	vector <ll> tree;
	int N;

	SegmentTree(vector <ll> &A){ //inicialización
		N = A.size();
		tree.resize(4*N); // le damos 4*N de espacio a tree
		build(0, 0, N-1, A); // construimos desde el nodo cero, con rango 0 a N-1 y con el vector A.
	}

	ll merge(ll a, ll b){ // esta es la operación que se
		return a + b; // hace entre los nodos al combinarlos
	}

	void build(int n, int l, int r, vector <ll> &A){
		//n es el índice de nodo actual en tree
		//l y r es el rango del arreglo original que el nodo actual está mirando
		//A es el vector original
		if(l == r){ // caso hoja
			tree[n] = A[l];
			return;
		}
		int mid = (l+r)/2;
		build(2*n+1, l, mid, A); // construimos para cada hijo
		build(2*n+2, mid+1, r, A);
		tree[n] = merge(tree[2*n+1], tree[2*n+2]); // combinamos los hijos
	}

	ll query(int i, int j){ // le pasa el query a la raíz del árbol
		return(query(0, 0, N-1, i, j));
	}

	ll query(int n, int l, int r, int i, int j){
		//n es el índice del nodo actual y l,r el rango que este está viendo
		//i,j son los índices del rango objetivo al que queremos sacarle la respuesta
		if(l>=i && r<=j){ //en este caso, el rango objetivo está totalmente contenido 
			return tree[n]; //en el rango actual y simplemente retornamos lo que está en el nodo
		}
		if(r<i || l>j){ //en este caso, el rango objetivo está afuera del rango actual
			return 0; //y retornamos el neutro (en el caso de la suma, es cero)
		}
		int mid = (l+r)/2; //si no se cumplió que está contenido totalmente o fuera,
		ll a = query(2*n+1, l, mid, i, j); //entonces está parcialmente contenido
		ll b = query(2*n+2, mid+1, r, i, j); //y hay que llamar a sus dos hijos
		return merge(a, b);
	}

	void update(int i, ll v){
		update(0, 0, N-1, i, v); //le pasa la actualización al nodo raíz
	}

	void update(int n, int l, int r, int i, ll v){
		if(l == r && r == i){ //caso en el que llegamos al nodo hoja que queremos actualizar
			tree[n] = v;
			return;
		}
		int mid = (l+r)/2;
		if(i < l || r < i) return; //si estamos fuera del rango ojetivo, cortamos la recursión
		update(2*n+1, l, mid, i, v);
		update(2*n+2, mid+1, r, i, v);
		tree[n] = merge(tree[2*n+1], tree[2*n+2]); //se actualiza a los dos hijos y al nodo actual con ellos
	}
};

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	vector <ll> A = {1, 2, 3, 4, 5, 6}; // el vector tiene que ser del tipo que recibe el SegmentTree (ll en este caso)
	SegmentTree ST(A); // construimos un segment tree ST a partir de A
	cout << ST.query(0,5) << endl; // Suma de {1,2,3,4,5,6} = 21
	cout << ST.query(0,0) << endl; // Suma de {1} = 1
	ST.update(0,6); // {6,1,2,3,4,5,6}
	cout << ST.query(0,5) << endl; // Suma de {6,2,3,4,5,6} = 26
	cout << ST.query(0,0) << endl; // Suma de {1} = 6
	return 0;
}