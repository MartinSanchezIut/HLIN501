#include <cstdlib>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void ecrireComposantes(int n, int m, int comp[]) {
	cout << endl;

	for (int a = 1; a < n + 1; ++a){
		int x = 0;
		//cout << "Recherche des " << a << " conexités" << endl ;

		for (int i = 0; i < n; ++i){
			int goal = comp[i] ;
			int count = 0;
			//cout << "On cherche comp[" << i << "] = " << comp[i] << endl;

			for (int j = 0; j < n; ++j){
				if(comp[j] == goal) {
					count++ ;
					//cout << " " << count << " ";
				}
			}
			//cout << endl;

			if (count == a) {
				x++;
			}
		}
		cout << "Composantes de " << a << " sommets = " << x/a << endl ;
	}	
	cout << endl;
}

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
			int min, max;
			if (comp[x] > comp[y]) {
				max = comp[x];
				min = comp[y];
			}else {
				max = comp[y];
				min = comp[x];
			}

			//int aux = comp[x];
			//cout << "Comp(" << x << ") : " << aux << endl;

			for ( int z = 0 ; z < n ; z++ ) {
			//	cout << "Comp(" << z << ") : " << comp[z] ;

				if ( comp[z] == max ) {  	 	// ( comp[z] == comp[y] )  
					comp[z] = min;					// 	comp[z] = aux;
			//		cout << "  (modif)" << endl;		
				}else {
			//		cout << endl;
				}
			}
			//cout << endl ;
		}
		cout << endl;
	}

	cout << endl;
	for ( int i = 0 ; i < n ; i++ ) {
		cout << comp[i] << endl;
	}
}


int main() {
	int n;     // Nombre de sommets.
	int m;     // Nombre d’aretes.
	
	cout << "Entrer le nombre de sommets:  " << endl;
	cin >> n;
	cout << "Entrer le nombre d’aretes:   " ;
	cin >> m;

	int edge[m][2];    // Tableau des aretes.
	int comp[n]; // comp[i] est le numero de la composante contenant i.

	grapheRandom(n,m, edge);
	composantes(n,m, edge, comp);
	ecrireComposantes(n, m, comp) ;

	return EXIT_SUCCESS;
}



