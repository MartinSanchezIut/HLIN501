#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "affichage.cc"


using namespace std;

/*           ______ ______ _____ _____ _    _          _____ ______ 
 *     /\   |  ____|  ____|_   _/ ____| |  | |   /\   / ____|  ____|
 *    /  \  | |__  | |__    | || |    | |__| |  /  \ | |  __| |__   
 *   / /\ \ |  __| |  __|   | || |    |  __  | / /\ \| | |_ |  __|  
 *  / ____ \| |    | |     _| || |____| |  | |/ ____ \ |__| | |____ 
 * /_/    \_\_|    |_|    |_____\_____|_|  |_/_/    \_\_____|______|
*/
void pointRandom(int n, coord point[]) {
	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		point[i].abs = rand()%613 ; 
		point[i].ord = rand()%793 ; 
	}
}

/*           ______ ______ _____ _____ _    _          _____ ______ 
 *     /\   |  ____|  ____|_   _/ ____| |  | |   /\   / ____|  ____|
 *    /  \  | |__  | |__    | || |    | |__| |  /  \ | |  __| |__   
 *   / /\ \ |  __| |  __|   | || |    |  __  | / /\ \| | |_ |  __|  
 *  / ____ \| |    | |     _| || |____| |  | |/ ____ \ |__| | |____ 
 * /_/    \_\_|    |_|    |_____\_____|_|  |_/_/    \_\_____|______|
*/


void voisinRandom(int n, int m, vector<int> voisins[]) {
	srand(time(NULL));

	int x,y;
	for(int i=0;i<m;i++){
		do {
			x=rand()%n;
			y=rand()%n;
		}
		while(x==y || find(voisins[x].begin(),voisins[x].end(),y)!=voisins[x].end());
		
		voisins[x].push_back(y);
		voisins[y].push_back(x);
	}
}

void parcoursLargeur(int n, vector<int> voisins[], int niveau[], int ordre[], int pere[]) {
	int dv[n];
	for (int i = 0; i < n; ++i)	{ dv[i] = 0; }

	int racine = 0;

	niveau[racine] = 0;
	ordre[racine] = 1;
	pere[racine] = 1;

	vector<int> AT ;
	AT.push_back(racine) ;

	int temps = 2;
	while(AT.size() != 0) {
		int v = AT.at(0) ; AT.erase(AT.begin()) ;
		vector<int> voisinsdeV= voisins[v] ;

		for (int i = 0; i < voisinsdeV.size(); ++i){
			if (dv[i] == 0) {
				dv[i] = 1;
				AT.push_back(i);
				ordre[i] = temps; temps++;
				pere[i] = v;
				niveau[i] = niveau[v] +1;
			}
		}
	}
}

void ecritureNiveaux(int n, int niveau[]) {
	int nbExclu = 0;

	for (int i = 0; i < n; ++i)	{
		int nb = 0;
		int match = i;

		for (int j = 0; j < n; ++j)	{
			if (niveau[j] == match) {
				nb++;
			}
		}

		if (nb > 0) {
			cout << "Il y a " << nb << " sommets de niveau "<< match << endl;
		}
		nbExclu = nbExclu + nb;

	}
	cout << "Il y a " << n - nbExclu << " sommet qui ne sont pas dans la composante de 0" << endl ;

}

int main(){
	int n = 5;                                    // Le nombre de sommets.
	int m = 10;                                    // Le nombre d'aretes.
	cout << "Entrer le nombre de sommets: =5"; cout << endl;
	//cin >> n;
	cout << "Entrer le nombre d'aretes:  =10"; cout << endl;
	//cin >> m;


	vector<int> voisins[n];                   // Les listes des voisins. 
	int pere[n];                              // L'arbre en largeur.
	int ordre[n];                             // L'ordre de parcours.
	int niveau[n];                            // Le niveau du point.

	voisinRandom(n, m, voisins) ; cout << endl;
	for (int i = 0; i < n; ++i)	{
		cout << "Voisins de " << i << " : ";
		for (int j = 0; j < voisins[i].size(); ++j){
			cout << voisins[i].at(j) << " " ;
		}
		cout << endl;
	}


	parcoursLargeur(n, voisins, niveau, ordre, pere) ;  cout << endl;
	cout << "Parcour en largeur " << endl; cout << endl;

	ecritureNiveaux(n, niveau) ; cout << endl;


	coord coords[n];  
	pointRandom(n, coords);
	cout << "DeBUG" << endl ;
	for (int i = 0; i < n; ++i)
	{
		cout << "Cord(" << i <<") = " << coords[i].abs << " : " << coords[i].ord << endl;
	}

	int arbre[m][2];
	int iterator = 0;
	for (int i = 0; i < n; ++i)	{
		for (int j = 0; j < voisins[i].size(); ++j){
			arbre[iterator][0] = i;
			arbre[iterator][1] = j;
			iterator++;
		}
	}
	cout << iterator << endl;
	for (int i = 0; i < iterator; ++i)
	{
		cout << "Arrete " << arbre[i][0] << " - " << arbre[i][1] << endl;
	}

	affichageGraphique(n, coords, arbre) ;

	return EXIT_SUCCESS;
}
