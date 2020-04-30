#include <iostream>
#include <sstream>
#include "arete.hpp"
#include "graph.hpp"
#include "sommet.hpp"
#include "central.hpp"

using namespace std;

void delete_arete(vector<Arete*>* A)
{
        int buf_id;

        cout<<"entrez l'id de l'arete que voulez supprimer: ";
        std::cin>> buf_id;
        cout<<endl;

        Sommet* extr_1 = (*A)[buf_id]->get_pair()->first;
        Sommet* extr_2 = (*A)[buf_id]->get_pair()->second;
        std::vector<Sommet*>::iterator it_temp;

        A->erase(A->begin()+buf_id);

        for(std::vector<Sommet*>::iterator it = extr_1->get_adja()->begin(); it != extr_1->get_adja()->end(); ++it)
        {
                if(*it == extr_2)
                {
                        it_temp = it;
                        break;
                }

        }
        extr_1->get_adja()->erase(it_temp);

        for(std::vector<Sommet*>::iterator it = extr_2->get_adja()->begin(); it != extr_2->get_adja()->end(); ++it)
        {
                if(*it == extr_1)
                {
                        it_temp = it;
                        break;
                }

        }
        extr_2->get_adja()->erase(it_temp);

}
/*
   void kConnexite(Graph G)
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

   //  indice = G->trouver_comp_connexe_kosaraju();
        }

        std::cout<<"la connexité du graph est : "<<indice<<endl;

   } */

void Connexite(Graph *G)
{
        int ordre_init,n_sommet;

        ordre_init =  G->get_tab_sommet()->size();//On recupere l'ordre du graph

        delete_arete((G->get_tab_arete())); //On supprime une arete
        n_sommet =  G->parcour_BFS(0);//On recupere le nombre de sommet parcouru avec l'arete en moins
        std::cout << std::endl << "N Sommet : " << n_sommet;

        if(ordre_init != n_sommet) //Si l'ordre intiale est different du nombre de sommet parcouru alors le graph n'est plus connexe
        {
                std::cout<<"Le graph n'est plus connexe"<<endl;
        }
        else              //Sinon il est connexe
        {
                std::cout<<"Le graph est toujours connexe"<<endl;
        }
}
