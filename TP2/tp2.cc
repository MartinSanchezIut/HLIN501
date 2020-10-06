#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include "affichage.cc"


using namespace std;
//typedef struct coord{int abs; int ord;} coord;




void pointRandom(int n, coord points[]) {
	srand(time(NULL));

	for (int i = 0; i < n; ++i) {
		points[i].abs = rand()%613 ; 
		points[i].ord = rand()%793 ; 

		cout << i << " : " << points[i].abs << " " <<	points[i].ord << endl ; 
	}
}

void distances(int n, int m, coord points[], int edge[][3]) {

	for (int i = 0; i < n; ++i)	{
		for (int j = 0; j < n; j++){
			
			edge[i][0] = i;
			edge[i][1] = j;
			edge[i][2] =  (points[i].abs - points[j].abs)^2 + (points[i].ord - points[j].ord)^2 ;


			cout << "Distance : " << edge[i][0] << "-" << edge[i][1] << " = " << edge[i][2] << endl ; 

		}
	}
}

int compare(const void * a,const void * b){ return ((int*)a)[2] - ((int*)b)[2]; }

void tri(int m, int edge[][3]) {
	qsort(edge, m, sizeof(edge[0]), compare);

	for (int i = 0; i < m; i++){
		cout << "Tri : " << edge[i][0] << "-" << edge[i][1] << " = " << edge[i][2] << endl ; 
	}
}


void kruskal(int n , int edge[][3] , int arbre[][2]) {
	tri(n, edge) ;
	// arbre est vide

	int comp[n] ;
	for (int i = 0; i < n; ++i)	{
		comp[i] = i;
	}

	int m=n*(n-1)/2;   // Le nombre de paires de points.
	for (int i = 0; i < m; ++i)	{
		if (comp[edge[i][0]]  !=  comp[edge[i][1]]) {

			int aux = comp[edge[i][0]];
			arbre[i][0] = edge[i][0] ;
			arbre[i][1] = edge[i][1] ;


			for (int z = 0; z < n; ++z){

				if (comp[z] == aux) {
					comp[z] = edge[i][1] ;
				}
			}
		}
	}
}


int main() {
	int n = 50;             //Le nombre de points.
	cout << "Entrer le nombre de points:   =50" << endl;
	//cin >> n;

	int m=n*(n-1)/2;   // Le nombre de paires de points.

 
	coord point[n];    // Les coordonnees des points dans le plan.

	int edge[m][3];    // Les paires de points et le carre de leur longueur.

	int arbre[n-1][2]; // Les aretes de l'arbre de Kruskal. 



	pointRandom(n, point) ; cout << endl;
	distances(n, m, point, edge) ; cout << endl;
	tri(n, edge) ;

	//kruskal(n, edge, arbre) ;

	affichageGraphique(n, point, arbre) ;

	return EXIT_SUCCESS;
}