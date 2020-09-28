#include <cstdlib>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;


void grapheRandom(int n , int m , int edge[][2]) {
	cout << endl << "Graphe Random" <<endl;
	srand(time(NULL));

	for ( int i = 0 ; i < m ; i++ ) {
		do {
			edge[i][0] = rand()%n;
			edge[i][1] = rand()%n;
		}while(edge[i][0] == edge[i][1]) ;

		cout << edge[i][0] << "->" << edge[i][1] << endl;
	}

	cout << endl;
}


void composantes(int n, int m, int edge[][2], int comp[]) {
	cout << "Debut conposantes : " << endl ;

	for ( int x = 0 ; x < n ; x++ ){
		comp[x] = x;
		cout << x << " <- " << comp[x] << endl ; 
	}
	cout << endl ;


	for ( int i = 0 ; i < m ; i++ ){
		int x = edge[i][0];
		int y = edge[i][1];

		cout << "Arrete : " << x << " -> " << y << endl;


		if ( comp[x] != comp[y] ){ 
			int aux = comp[x];
			//cout << "Comp(" << x << ") : " << aux << endl;

			for ( int z = 0 ; z < n ; z++ ) {
				cout << "Comp(" << z << ") : " << comp[z] ;

				if ( comp[z] == comp[y] ) {
					comp[z] = aux;
					cout << "  (modif)" << endl;		
				}else {
					cout << endl;
				}
			}
			cout << endl ;
		}
		cout << endl;
	}

	cout << endl;
	for ( int i = 0 ; i < n ; i++ ) {
		cout << comp[i] << endl;
	}
}


int main() {
	int n = 4;     // Nombre de sommets.
	int m = 6;     // Nombre d’aretes.
	
	cout << "Entrer le nombre de sommets:  (4) " << endl;
	//cin >> n;
	cout << "Entrer le nombre d’aretes:  (6) " ;
	//cin >> m;

	int edge[m][2];    // Tableau des aretes.
	int comp[n]; // comp[i] est le numero de la composante contenant i.

	grapheRandom(n,m, edge);
	composantes(n,m, edge, comp);

	return EXIT_SUCCESS;
}



