#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include "affichage.cc"


using namespace std;
//typedef struct coord{int abs; int ord;} coord;


void pointRandom(int n, coord point[]) {
	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		point[i].abs = rand()%613 ; 
		point[i].ord = rand()%793 ; 

		//cout << i << " : " << point[i].abs << " " <<	point[i].ord << endl ; 
	}
}
int carre(int n) {
	return n * n;
}

void distances(int n, int m, coord points[], int edge[][3]) {
	int last = 0;
	for (int i = 0; i < n; ++i)	{
		for (int j = i+1; j < n; j++){
			//cout << last << " " <<i <<" " << j << endl ;
			edge[last][0] = i;
			edge[last][1] = j;
			edge[last][2] =  carre(points[i].abs - points[j].abs) + carre(points[i].ord - points[j].ord) ;

			last++;
		}
	}
	/*
	for (int i = 0; i < m; ++i)	{
		cout << "Distance : " << edge[i][0] << "-" << edge[i][1] << " = " << edge[i][2] << endl ; 

	}
	*/
}

int compare(const void * a,const void * b){
	int ret = ( (int*) a)[2] - ( (int*) b)[2] ; 
	//cout << ( (int*) a)[2] << " - " << ( (int*) b)[2] << " = " << ret << endl;
	return ret; 
}

void tri(int m, int edge[][3]) {
	for (int i = 0; i < m; i++){
	 	cout << "PreTri " << i << ": " << edge[i][0] << "-" << edge[i][1] << " = " << edge[i][2] << endl ; 
	}

	qsort(edge, m, sizeof(edge[0]), compare);
	cout << endl ;
	for (int i = 0; i < m; i++){
	 	cout << "Tri " << i << ": " << edge[i][0] << "-" << edge[i][1] << " = " << edge[i][2] << endl ; 
	}
}


void kruskal(int n , int edge[][3] , int arbre[][2]) {
	cout << "Debut kruskal " << endl;
	int m=n*(n-1)/2;   // Le nombre de paires de points.

	tri(m, edge) ;
	// arbre est vide

	int comp[n] ;
	for (int i = 0; i < n; ++i)	{
		comp[i] = i;
	}

	cout << endl;
	cout << "Tri + comp : Ok" << endl;
	cout << "M = " << m << endl ;

	for (int i = 0; i < m; ++i)	{
		cout << "Tour:" << i << endl;
		cout << "Edge : " << edge[i][0] << " " << edge[i][1] << " " << edge[i][2] << endl;
		//cout << "Comp : " << comp[edge[i][0]]] << " " << comp[edge[i][1]]] << endl;
		cout << endl;
		cout << endl;

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
	int n = 5;             //Le nombre de points.
	cout << "Entrer le nombre de points:   =5" << endl;
	//cin >> n;

	int m=n*(n-1)/2;   // Le nombre de paires de points.

 
	coord point[n];    // Les coordonnees des points dans le plan.
	int edge[m][3];    // Les paires de points et le carre de leur longueur.
	int arbre[n-1][2]; // Les aretes de l'arbre de Kruskal. 



	pointRandom(n, point) ;
	for (int i = 0; i < n; ++i)	{
		cout << "Point[" << i << "] : " <<  point[i].abs << " - " << point[i].ord << endl ;
	}
	
	distances(n, m, point, edge) ; 
	cout << endl;
	for (int i = 0; i < m; i++){
	 	cout << "Edge[" << i << "]: " << edge[i][0] << "-" << edge[i][1] << " = " << edge[i][2] << endl ; 
	}
	cout << endl;
	
	tri(n, edge) ;
	//kruskal(n, edge, arbre) ;

	//affichageGraphique(n, point, arbre) ;

	return EXIT_SUCCESS;
}