#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll inf = 1e14;
struct SegmentTree
{
	vector<ll> ST, L;
	int N;

	SegmentTree(vector<ll> &A)
	{
		N = A.size();

		// Recordar 4*N
		ST.resize(4*N);
		L.resize(4*N,0);

		build(1,0,N-1,A);
	}

	void build(int n, int l, int r, vector<ll> &A)
	{	
		// Chequeo si es hoja
		if(l == r)
		{
			ST[n] = A[r];
			return;
		}

		// Construyo los hijos
		build(2*n,l,(l+r)/2,A);
		build(2*n+1,(l+r)/2+1,r,A);

		// Computo los valores
		ST[n] = min(ST[2*n],ST[2*n+1]);
	}

	ll query(int i, int j)
	{
		return query(1,0,N-1,i,j);
	}

	// Computa la query(i,j) para el nodo n
	ll query(int n, int l, int r, int i, int j)
	{
		// Si hay que actualizar el nodo
		if(L[n] != 0)
		{
			// Actualizo el valor
			ST[n] += L[n];

			// Si no es hoja, marco a los hijos
			if(l != r)
			{
				L[2*n] += L[n];
				L[2*n+1] += L[n];
			}

			// Desmarco al nodo
			L[n] = 0;
		}

		// Caso 1: No chocan
		if(r < i || j < l) return inf;

		// Caso 2: Contenido totalmente
		if(i <= l && r <= j) return ST[n];

		// Caso 3: Ninguno de los anteriores
		// Le paso la query a los hijos

		return min(query(2*n,l,(l+r)/2,i,j),
					query(2*n+1,(l+r)/2+1,r,i,j));
	}

	// A[i,j] += v
	void update(int i, int j, ll v)
	{
		return update(1,0,N-1,i,j,v);
	}

	void update(int n, int l, int r, int i, int j, ll v)
	{
		// Si hay que actualizar el nodo
		if(L[n] != 0)
		{
			// Actualizo el valor
			ST[n] += L[n];

			// Si no es hoja, marco a los hijos
			if(l != r)
			{
				L[2*n] += L[n];
				L[2*n+1] += L[n];
			}

			// Desmarco al nodo
			L[n] = 0;
		}

		// Caso 1: No chocan
		if(j < l || r < i) return;

		// Caso 2: Contenido totalmente
		if(i <= l && r <= j)
		{
			// Actualizo el valor
			ST[n] += v;

			// Si no es hoja, marco a los hijos
			if(l != r)
			{
				L[2*n] += v;
				L[2*n+1] += v;
			}

			// Desmarco al nodo
			L[n] = 0;

			return;
		}

		// Caso 3: Ninguno de los anteriores
		// Actualizar a los hijos
		update(2*n,l,(l+r)/2,i,j,v);
		update(2*n+1,(l+r)/2+1,r,i,j,v);

		// Recomputo los valores
		ST[n] = min(ST[2*n],ST[2*n+1]);
	}
};

int main()
{
	vector<int> A = {1,2,7,9,2,3,5,1,2,9,8};
	SegmentTree ST(A);

	// query(2,5) = min([7,9,2,3]) = 2
	cout << ST.query(2,5) << '\n';

	// query(0,10) = min(A) = 1
	cout << ST.query(0,10) << '\n';

	return 0;
}