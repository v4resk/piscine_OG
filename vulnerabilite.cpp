#include <iostream>
#include <sstream>
#include "arete.hpp"
#include "graph.hpp"
#include "sommet.hpp"

using namespace std;

void delete_arete(vector<Arete> A)
{
  int buf_id;

  cout<<"entrez l'id de l'arete que voulez supprimer: ";
  std::cin>> buf_id;
  cout<<endl;

  A.erase(A.begin()+buf_id);

}

void kConnexite(Graph *G)
{
int orientation;
int indice = 0;

orientation = G->get_orientation();

if(orientation == 0)
{
   indice =  G->trouver_comp_connexe();
    
}
if(orientation == 1)
{

    /// Appel Kosaraju
}


}





