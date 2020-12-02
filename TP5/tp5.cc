#include <iostream>
#include <vector>

using namespace std;

const int N=5;
const int B=6;
const int INF=9999;                      //La valeur infinie.    

void floydWarshall(int longueur[][N],int dist[][N],int chemin[][N]) {

	for (int i = 0; i < N; ++i)	{
		dist[i][i] = 0;
		chemin[i][i] = i;

		for (int j = 0; j < N; ++j){		
			if (longueur[i][j] < INF) {
				dist[i][j] = longueur[i][j];
				chemin[i][j] = j;
			}else {
				dist[i][j] = INF;
				chemin[i][j] = -1;
			}
		}
	}


	for (int k = 0; k < N; ++k)	{
		for (int i = 0; i < N; ++i)	{
			for (int j = 0; j < N; ++j)	{
				if (dist[i][j] > dist[i][k] + dist[k][j]) {
					dist[i][j] = dist[i][k] + dist[k][j] ;  // Racourcis
					chemin[i][j] = chemin[i][k] ;
				}
			}
		}
	}

	for (int i = 0; i < N; ++i)	{
		if (dist[i][i] < 0) {
			cout << "Il existe un cycle orienté de poid <0" << endl;
		}
	}
}


void affichage(int dist[][N],int chemin[][N]){
 
    for(int depart = 0 ; depart < N ;++depart){
      for(int arrive = 0 ; arrive < N ;++arrive){
 
        int courant = depart;
        cout << courant << "->";
        while(chemin[courant][arrive] != arrive && chemin[courant][arrive] != -1){
          cout << courant << "->";
          courant = chemin[courant][arrive];
        }
        cout << arrive << " : dist = " << dist[courant][arrive] << endl;
      }
    }
}


void itineraire(int i,int j,int chemin[][N]) {
	int courant = i;
	int arrive = j;

    cout << courant << "->";
    while(chemin[courant][arrive] != arrive && chemin[courant][arrive] != -1){
    	cout << courant << "->";
        courant = chemin[courant][arrive];
    }
    cout << arrive << endl;
}



void fermetureTransitive(int arc[][B], int fermeture[][B]) {
    for(int i = 0; i < B; i++) {
        for(int j = 0; j < B; j++) {
            fermeture[i][j] = arc[i][j];
        }
        fermeture[i][i] = 1;
    }

    for(int k = 0; k < B; k++) {
        for(int i = 0; i < B; i++) {
            for(int j = 0; j < B; j++) {

                if (fermeture[i][k] == 1 && fermeture[k][j] == 1) {
                	fermeture[i][j] = 1;
                }
                //fermeture[i][j] = fermeture[i][j] || (fermeture[i][k] && fermeture[k][j]);
            }
        }
    }

}

void compFortConnexe(int n, int fermeture[][B]){
	bool marque[n] ;
	for (int i = 0; i < n; ++i)	{
		marque[i] = false;
	}

	for (int i = 0; i < n; ++i)	{
		if (!marque[i]) {
			cout << "{" << i;
			for (int j = i+1; j < n; ++j){
				
				if( fermeture[i][j] == 1 && fermeture[j][i] == 1) {
					cout << ", " << j;
					marque[j] = true;
				}
			}
			cout << "} ";
			marque[i] = true ;
		}
	}
	cout << endl;
}


int main(){
  
  int longueur[N][N]=
  			  {{0,2,INF,4,INF},   //Les longueurs des arcs.
		      {INF,0,2,INF,INF}, //longueur[i][j]=INF si l'arc ij n'existe pas
		      {INF,INF,0,2,INF},
		      {INF,-3,INF,0,2},
		      {2,INF,INF,INF,0}};                
 
  int dist[N][N];                        //Le tableau des distances.
  int chemin[N][N];                      //Le tableau de la premiere etape du chemin de i a j.
  
  floydWarshall(longueur,dist,chemin);
  
  affichage(dist,chemin); 
  cout << "----" << endl;

  bool valid;
  do{
  	int depart;
  	cout << "Point de départ ?:" << endl ;
  	cin >> depart;

  	int arrive;
  	cout << "Point d'arivée ?:" << endl ;
  	cin >> arrive;

  	valid = depart < 5 && depart > -1 && arrive < 5 && arrive > -1;
  	if (valid) {
 		itineraire(depart, arrive, chemin) ;
  	}else {
  		cout << "Mauvaise saisie !" << endl;
  	}
  }while(valid);

 	

	int arc[B][B]={{0,0,0,1,0,1},//La matrice d’adjacences du graphe oriente D.
				   {1,0,1,1,0,0},
				   {0,0,0,1,0,0},
				   {0,0,0,0,1,1},
				   {0,0,1,0,0,1},
				   {0,0,1,0,0,0}};

	int fermeture[B][B];         // La matrice de la fermeture transitive de D.

	fermetureTransitive(arc, fermeture) ;

	cout << endl;
	for (int i = 0; i < B; ++i)	{
		for (int j = 0; j < B; ++j){
			cout << fermeture[i][j] << " ";
		}
		cout << endl;
	}
	compFortConnexe(B, fermeture);

  return EXIT_SUCCESS;
}
