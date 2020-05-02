#include <iostream>
#include <sstream>
#include "arete.hpp"
#include "graph.hpp"
#include "sommet.hpp"
#include "central.hpp"
#include <algorithm>

using namespace std;

void delete_arete(vector<Arete *> *A)
{
        int buf_id;

        cout << "entrez l'id de l'arete que voulez supprimer: ";
        std::cin >> buf_id;
        cout << endl;

        Sommet *extr_1 = (*A)[buf_id]->get_pair()->first;
        Sommet *extr_2 = (*A)[buf_id]->get_pair()->second;
        std::vector<Sommet *>::iterator it_temp;

        A->erase(A->begin() + buf_id);

        for (std::vector<Sommet *>::iterator it = extr_1->get_adja()->begin(); it != extr_1->get_adja()->end(); ++it)
        {
                if (*it == extr_2)
                {
                        it_temp = it;
                        break;
                }
        }
        extr_1->get_adja()->erase(it_temp);

        for (std::vector<Sommet *>::iterator it = extr_2->get_adja()->begin(); it != extr_2->get_adja()->end(); ++it)
        {
                if (*it == extr_1)
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
        int ordre_init, n_sommet;

        ordre_init = G->get_tab_sommet()->size(); //On recupere l'ordre du graph

        delete_arete((G->get_tab_arete())); //On supprime une arete
        n_sommet = G->parcour_BFS(0);       //On recupere le nombre de sommet parcouru avec l'arete en moins
        std::cout << std::endl
                  << "N Sommet : " << n_sommet;

        if (ordre_init != n_sommet) //Si l'ordre intiale est different du nombre de sommet parcouru alors le graph n'est plus connexe
        {
                std::cout << "Le graph n'est plus connexe" << endl;
        }
        else //Sinon il est connexe
        {
                std::cout << "Le graph est toujours connexe" << endl;
        }
}

void afficherVulneGlobal(float V_global_prox, float V_global_deg, float V_global_propre /*,float V_global_inter*/)
{
        std::cout << " La centralite de proximité globale est: " << V_global_prox << endl;
        std::cout << "La centralite de degre globale est: " << V_global_prox << endl;
        std::cout << "La centralite de vecteur propre globale est: " << V_global_prox << endl;
        //std::cout<<"La centralite d'intermediarite globale est: "<<V_global_prox<<endl;
}

void vulnerabiliteGlobal(Graph *G, Centralisation cent)
{
        float V_global_prox = 0;
        float V_global_propre = 0;
        float V_global_deg = 0;
        // int V_global_inter = 0;

        std::map<Sommet *, float>::iterator it;
        std::map<Sommet *, float> resultat_prox = cent.get_res_prox();
        std::map<Sommet *, float> resultat_deg = cent.get_res_deg();
        std::map<Sommet *, float> resultat_propre = cent.get_res_propre();
        //  std::map<Sommet *, float> resultat_inter = cent.get_res_inter();

        for (it = resultat_prox.begin(); it != resultat_prox.end(); ++it)
        {
                V_global_prox = V_global_prox + (G->get_ordre() - 1) - (it->second * (G->get_tab_sommet()->size() - 1));
        }

        for (it = resultat_deg.begin(); it != resultat_deg.end(); ++it)
        {

                V_global_deg = V_global_deg + (G->get_ordre() - 1) - it->second * (G->get_tab_sommet()->size() - 1);
        }

        for (it = resultat_propre.begin(); it != resultat_propre.end(); ++it)
        {
                V_global_propre = V_global_propre + it->first->get_nom();
        }

        /*   for (it = resultat_inter.begin(); it != resultat_inter.end(); ++it)
           {
           V_global_inter  = V_global_inter + (G->get_ordre()-1)-it->second*(G->get_tab_sommet()->size()-1);
           }*/

        V_global_prox = V_global_prox / ((G->get_ordre() ^ 2 - 3 * G->get_ordre() + 2) / 2 * G->get_ordre() - 3);
        V_global_deg = V_global_deg / ((G->get_ordre() ^ 2 - 3 * G->get_ordre() + 2) / 2 * G->get_ordre() - 3);
        V_global_propre = V_global_propre / ((G->get_ordre() ^ 2 - 3 * G->get_ordre() + 2) / 2 * G->get_ordre() - 3);
        //  V_global_inter = V_global_inter/((G->get_ordre()^2-3*G->get_ordre()+2)/2*G->get_ordre()-3);

        afficherVulneGlobal(V_global_prox, V_global_deg, V_global_propre);
}

void kconnexite(Graph *G,Centralisation cent)
{
        std::vector<float> kconnexe;
        cent.centra_inter();

        for (int i = 0; i < G->get_tab_sommet()->size(); i++)
        {
                for (int j = 0; j < G->get_tab_sommet()->size(); j++)
                {
                        cent.get
                }
        }

        auto min_connexe = std::min_element(kconnexe.begin(), kconnexe.end());

        std::cout<<"ce graph est "<< *min_connexe <<"-arrete-connexe"<<endl;
}
