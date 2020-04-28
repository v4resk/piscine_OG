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

class Graph {
public:


Graph(std::string nom_fichier, std::string fichier_ponderation) :  fichier(nom_fichier), fichier_pond(fichier_ponderation){

        if(!fichier)
                exit(0);
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

void creer_svg()
{
        Svgfile svgOUT("testokartier",1000,1000);
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


        for (auto s : m_sommet)
        {
                std::string b(1, s->get_nom());
                svgOUT.addDisk(s->get_X()*ratioX, s->get_Y()*ratioY,5, color);
                svgOUT.addText(s->get_X()*ratioX-5, s->get_Y()*ratioY-7,b, "purple");
        }


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
void parcour_BFS(int nbr_s0)
{

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
}

void parcour_DFS(int m_id/*,int* date*/){
        Sommet* s0 = getSommet_numeroN(m_id);
      //  s0->setDate(date,false);
        s0->setVisited_bool(true);
      //  date++;
        for(auto it: s0->ObtenirAdjacents())
        {
                if(!it->getVisited_bool())
                {
                        parcour_DFS(it->ObtenirId()/*,date*/);
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
        int date = 0;
        parcour_DFS(m_id/*,&date*/);

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

void trouver_comp_connexe_kosaraju()
{

}


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

};






#endif
