#ifndef GRAPH
#define GRAPH

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <iterator>
#include <fstream>
#include "arete.hpp"
#include "sommet.hpp"
#include "svgfile.hpp"
#include <algorithm>
#include <math.h>
#include <list>
#include <stack>
//#include "central.hpp"


class Graph {
public:


Graph(std::string nom_fichier, std::string fichier_ponderation) :  fichier(nom_fichier), fichier_pond(fichier_ponderation){

        if(!fichier || !fichier_pond)
        {
                std::cerr << "File load error";
                exit(0);
        }
        fichier >> orientation;
        fichier >> ordre;

        for(int i=0; i<ordre; i++)
        {
                fichier >> m_id >> m_nom >> m_x >> m_y;
                m_sommet.push_back(new Sommet(m_id,m_nom,m_x,m_y));
        }

        fichier >> taille;

        for(int i=0; i<taille; i++)
        {
                fichier >> m_id >> Si >> Sj;
                ajouter_adjacents(Si,Sj);
                m_arete.push_back(new Arete(m_id,getSommet_numeroN(Si),getSommet_numeroN(Sj)));

        }

        fichier_pond  >> taille;
        for(int i=0; i<taille; i++)
        {
                fichier_pond >> m_id >> poid;
                ajouter_poid(m_id,poid);
        }

        fichier_pond.close();
        fichier.close();
}

int get_ordre()
{
        return ordre;
}

void creer_svg(std::map<Sommet*,float> res_deg)
{
        Svgfile svgOUT("testokartier.svg",1000,1000);
        std::string color = "red";
        Sommet smin, smax;
        int ratioX, ratioY;

// calcul du min et du max
        for (auto s : m_sommet)
        {
                if (s->get_X()<smin.get_X())
                        smin.set_X(s->get_X());

                if (s->get_Y()<smin.get_Y())
                        smin.set_Y(s->get_Y());

                if (s->get_X()>smax.get_X())
                        smax.set_X(s->get_X());

                if (s->get_Y()>smax.get_Y())
                        smax.set_Y(s->get_Y());
        }



        ratioX = 1000/(smax.get_X() - smin.get_X() + 2);
        ratioY = 1000/(smax.get_Y() - smin.get_Y() + 2);

        svgOUT.addGrid(ratioX, 0, "green");

        for(auto k : m_arete)
        {

                svgOUT.addLine(k->get_X1()*ratioX,k->get_Y1()*ratioY,k->get_X2()*ratioX,k->get_Y2()*ratioY, "black");
        }



        for (auto s : res_deg)
        {

                std::string b(1, s.first->get_nom());

                switch((int)s.second)
                {
                case 0:
                        color = "grey";
                        break;
                case 1:
                        color = "aqua";
                        break;
                case 2:
                        color = "teal";
                        break;
                case 3:
                        color = "olive";
                        break;
                case 4:
                        color = "maroon";
                        break;
                case 5:
                        color = "red";
                        break;
                default:
                        color = "grey";
                        break;
                }


                svgOUT.addDisk((s.first->get_X())*ratioX, (s.first->get_Y())*ratioY,5, color);
                svgOUT.addText((s.first->get_X())*ratioX-5, (s.first->get_Y())*ratioY-7,b, "purple");
        }




}
int search_poid_entre(Sommet* p,Sommet* succ){
        for(auto a : m_arete)
        {
                if((a->get_pair()->first==p && a->get_pair()->second == succ) || (a->get_pair()->first==succ && a->get_pair()->second == p))
                {
                        int poid = a->get_poid();
                }
        }
        return poid;
}

void ajouter_poid(int m_id,int poid)
{
        m_arete[m_id]->set_poid(poid);
}

std::vector<Sommet*>* get_tab_sommet()
{
        return &m_sommet;
}

std::vector<Arete*>* get_tab_arete()
{
        return &m_arete;
}

void ajouter_adjacents(int Si, int Sj)
{
        Sommet* m_Si = getSommet_numeroN(Si);
        Sommet* m_Sj = getSommet_numeroN(Sj);


        if(!orientation)
        {
                if(m_Sj != nullptr && m_Si != nullptr)
                {
                        m_Si->ajouter_adjacents(m_Sj);
                        m_Sj->ajouter_adjacents(m_Si);

                }
        }
        else
        {
                if(m_Sj != nullptr && m_Si != nullptr)
                        m_Si->ajouter_adjacents(m_Sj);
        }





}


Sommet* getSommet_numeroN(int numero)
{
        if(numero < ordre && numero >= 0)
        {
                return m_sommet[numero];
        }
        else
                return nullptr;
}

void afficher(std::ostream& flux)
{
        if(!orientation)
                flux << "Graph non oriente"<< std::endl;
        else
                flux << "Graph oriente" << std::endl;

        for(int i=0; i<m_sommet.size(); i++)
        {
                flux << std::endl << "--------" << std::endl;
                m_sommet[i]->afficher(flux);
        }

        flux << std::endl
             << "--------------------------------------"
             << std::endl
             << "Aretes"
             << std::endl
             << "-------------------------";

        for(int i=0; i<m_arete.size(); ++i)
        {
                flux << std::endl << "--------" << std::endl;
                m_arete[i]->afficher(flux);
        }
}

int get_orientation()
{
        return orientation;
}
int parcour_BFS(int nbr_s0)
{
        int ordre = -1;
        Sommet* s0 = getSommet_numeroN(nbr_s0);
        Sommet* temp = nullptr;
        std::queue<Sommet*> file;
        set_all_unvisited();

        s0->setVisited_bool(true);
        s0->setPred(s0);
        file.push(s0);

        std::cout << std::endl << "Parcour BFS a partir du sommet "<< nbr_s0 << std::endl;

        while (!file.empty())
        {
                // On defile l'element rentrer en premier dans la file
                temp = file.front();
                file.pop();

                for(auto it : temp->ObtenirAdjacents())
                {
                        if(!it->getVisited_bool())         // Si pas visiter
                        {
                                it->setVisited_bool(true);
                                it->setPred(temp);
                                file.push(it);

                        }
                }
        }

        for(int i=0; i<m_sommet.size(); ++i)
        {
                if(!m_sommet[i]->getVisited_bool())
                        ordre++;
        }

        return ordre;
}

void parcour_DFS(int m_id /*,int* date*/){
        Sommet* s0 = getSommet_numeroN(m_id);
        //  s0->setDate(date,false);
        s0->setVisited_bool(true);
        //  date++;
        for(auto it: s0->ObtenirAdjacents())
        {
                if(!it->getVisited_bool())
                {
                        parcour_DFS(it->ObtenirId() /*,date*/);
                        it->setPred(s0);
                }


                // s0->setDate(date,true);
                //    date++;
        }
}

void init_parcour_DFS(int m_id)
{
        //  set_all_date_zero();
        set_all_unvisited();
        parcour_DFS(m_id /*,&date*/);

}
std::vector<std::vector<int> > kosaraju(int V, std::vector<std::vector<int> > adj)
{
        std::vector<bool> visited(V, false);
        std::stack<int> stack;
        for (int i = 0; i < V; i++)
        {
                if (!visited[i])
                {
                        //  FillStack(i, visited, adj, stack);
                }
        }

        std::vector<std::vector<int> > transpose = Transpose(V, adj);

        fill(visited.begin(), visited.end(), false);

        std::vector<std::vector<int> > connectedComponents;
        while(!stack.empty())
        {
                int node = stack.top();
                stack.pop();
                if(!visited[node])
                {
                        std::vector<int> component;
                        CollectConnectedComponents(node, visited, transpose, component);
                        connectedComponents.push_back(component);
                }

        }
        return connectedComponents;
}

void FillStack(int node, std::vector<bool> &visited, std::vector<std::vector<int> > &adj, std::stack<int> &stack)
{
        visited[node] = true;
        for (auto next : adj[node])
        {
                if (!visited[next])
                {
                        FillStack(next, visited, adj, stack);
                }
        }
        stack.push(node);
}

std::vector<std::vector<int> > Transpose(int V, std::vector<std::vector<int> > adj)
{
        std::vector<std::vector<int> > transpose(V);
        for (int i = 0; i < V; i++)
        {
                for (auto next : adj[i])
                {
                        transpose[next].push_back(i);
                }
        }

        return transpose;
}

void CollectConnectedComponents(int node, std::vector<bool> &visited,
                                std::vector<std::vector<int> > &adj, std::vector<int> &component)
{
        visited[node] = true;
        component.push_back(node);
        for(auto next : adj[node])
        {
                if(!visited[next])
                {
                        CollectConnectedComponents(next, visited, adj, component);
                }
        }
}

void afficher_bfs(int m_id)
{
        std::vector<Sommet*>::iterator it;
        Sommet* s0 = m_sommet[m_id];
        //On parcour le tableau de sommet
        for(it=m_sommet.begin(); it!=m_sommet.end(); ++it)
        {
                if(*it != s0)                 // si pas le sommet initiale
                {
                        if((*it)->getVisited_bool())         // Si le sommet a également été visiter
                        {
                                std::cout << (*it)->ObtenirId() << "<---"; // On affiche le premier sommet de la liste ayant ete visite
                                Sommet* pred = (*it)->getPred();
                                if(pred != nullptr)
                                {

                                        while (pred != s0) {
                                                std::cout << pred->ObtenirId() << "<--";
                                                pred = pred->getPred();
                                        }
                                }
                                std::cout << s0->ObtenirId() <<  std::endl;
                        }
                }
        }
}

void afficher_dfs(int m_id)
{
        std::cout << std::endl << "Parcour DFS a partir du sommet "<< m_id << std::endl;
        afficher_bfs(m_id);
}

// Marche seulement pour graphe non orienter
int trouver_comp_connexe()
{
        int indice_connexe = 0;
        // On note dans sommet leur comp connexe
        for(auto it: m_sommet)
        {
                if(it->getConnex() == -1)// Si il n'est pas dans une comp connexe
                {
                        init_parcour_DFS(it->ObtenirId());
                        it->setConnex(indice_connexe);
                        for(auto it2 : m_sommet)
                        {
                                if(it2->getPred() != nullptr && it2->getConnex() == -1)
                                        (it2)->setConnex(indice_connexe);
                        }
                        indice_connexe++;
                }
        }

        // On crée une map de composant connexe
        for(auto it: m_sommet)
        {
                m__comp_connexe[it->getConnex()].push_back(it);
        }

        return indice_connexe;
}

/*int trouver_comp_connexe_kosaraju(Graph *G)
   {
        int V,indice = 0;
        std::vector<std::vector<int> > adj;

        //adj = G->get_tab_sommet();
        auto connectedComponents = kosaraju(V, adj);
        std::cout << "le graph contient " << connectedComponents.size() << " Composants fortements connexes." << std::endl;

        indice = connectedComponents.size();

         for(auto component : connectedComponents)
           {
             cout << "\t";
             for(auto node : component)
           {
           cout << node << " ";
           }
             cout << endl;
           }
        return indice;
   } */


void afficher_composant_connexe()
{
        std::map<int,std::vector<Sommet*> >::iterator map_it;
        std::vector<Sommet*>::iterator vec_it;

        for(map_it = m__comp_connexe.begin(); map_it!= m__comp_connexe.end(); ++map_it)
        {
                std::cout << "composant connexe n°" << map_it->first << " : " << std::endl;
                for(vec_it=(*map_it).second.begin(); vec_it != (*map_it).second.end(); ++vec_it)
                {
                        std::cout << (*vec_it)->ObtenirId() << " ";
                }
                std::cout << std::endl;
        }
}

/*void set_centra(Centralisation* a)
   {
        central =a;
   } */

void supprimer_adja(int s, int s_sup)
{
        getSommet_numeroN(s)->supprimer_adja(s_sup);
}

private:

void set_all_unvisited()
{
        for(auto it : m_sommet)
        {
                it->setVisited_bool(false);
                it->setPred(nullptr);
        }
}

std::ifstream fichier, fichier_pond;
std::vector<Sommet*> m_sommet;
std::vector<Arete*> m_arete;
std::map<int,std::vector<Sommet*> > m__comp_connexe;
int taille,ordre,orientation,poid;
int m_x,m_y,m_id;
int Si,Sj;
char m_nom;
//Centralisation central;

};





#endif
