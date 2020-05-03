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

int get_orientation()
{
        return orientation;
}

void creer_svg(std::map<Sommet*,float> res_deg,std::map<Sommet*,float>res_prox,std::map<Sommet*,float>res_inter,std::map<Sommet*,float>res_propre)
{
        //Initialisation du sujet SVG
        Svgfile svgOUT("Output.svg",1000,1000);
        //Création couleur sommet
        std::string color = "red";
        //Paramètre pour calcul ratio
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

        //Calcul ratio

        ratioX = 1000/(smax.get_X() - smin.get_X() + 2);
        ratioY = 1000/(smax.get_Y() - smin.get_Y() + 2);

        //Légende SVG
        std::string TextColor = "darkslategray";

        svgOUT.addText(10, 50, "Couleur des sommets = degrés",TextColor);
        svgOUT.addText(10, 80, "Pondération des arêtes en bleu", TextColor);
        svgOUT.addText(10, 110, "Indice de proximité en orange", TextColor);
        svgOUT.addText(10, 140, "Indice d'intermédiarité en rouge", TextColor);
        svgOUT.addText(10, 170, "Indice propre en marron", TextColor);

        // Grille SVG
        //svgOUT.addGrid(ratioX, 0, "grey");

        // Arête + poid SVG
        for(auto k : m_arete)
        {
                svgOUT.addText(((k->get_X2()*ratioX+k->get_X1()*ratioX)/2-9),((k->get_Y2()*ratioY+k->get_Y1()*ratioY)/2-5),k->get_poid(), "navy");
                svgOUT.addLine(k->get_X1()*ratioX,k->get_Y1()*ratioY,k->get_X2()*ratioX,k->get_Y2()*ratioY, "black");


                //Source: Pour la création des triangle, mon ami Loïs PUSZYNSKI du TD4 m'a aidé
                if(orientation)
                {
                        float angle,a,b,c;

                        a=100;
                        b=(k->get_X2()-k->get_X1())*ratioX;
                        c=(k->get_Y2()-k->get_Y1())*ratioY;
                        angle=acos((a*b)/(100*sqrt(c*c+b*b)));
                        angle-=3.141592;

                        if(c<0)
                                angle=-angle;

                        //std::cout<<angle;
                        svgOUT.addTriangle(k->get_X2()*ratioX,k->get_Y2()*ratioY,(k->get_X2()*ratioX)+12*cos(angle-3.141592/8),(k->get_Y2()*ratioY)+12*sin(angle-3.141592/8),(k->get_X2()*ratioX)+12*cos(angle+3.141592/8),(k->get_Y2()*ratioY)+12*sin(angle+3.141592/8),"black");
                }
                if(!orientation)
                {
                        float angle,a,b,c;

                        a=100;
                        b=(k->get_X1()-k->get_X2())*ratioX;
                        c=(k->get_Y1()-k->get_Y2())*ratioY;
                        angle=acos((a*b)/(100*sqrt(c*c+b*b)));
                        angle-=3.141592;

                        if(c<0)
                                angle=-angle;

                        //std::cout<<angle;
                        svgOUT.addTriangle(k->get_X1()*ratioX,k->get_Y1()*ratioY,(k->get_X1()*ratioX)+12*cos(angle-3.141592/8),(k->get_Y1()*ratioY)+12*sin(angle-3.141592/8),(k->get_X1()*ratioX)+12*cos(angle+3.141592/8),(k->get_Y1()*ratioY)+12*sin(angle+3.141592/8),"black");

                        a=100;
                        b=(k->get_X2()-k->get_X1())*ratioX;
                        c=(k->get_Y2()-k->get_Y1())*ratioY;
                        angle=acos((a*b)/(100*sqrt(c*c+b*b)));
                        angle-=3.141592;

                        if(c<0)
                                angle=-angle;

                        //std::cout<<angle;
                        svgOUT.addTriangle(k->get_X2()*ratioX,k->get_Y2()*ratioY,(k->get_X2()*ratioX)+12*cos(angle-3.141592/8),(k->get_Y2()*ratioY)+12*sin(angle-3.141592/8),(k->get_X2()*ratioX)+12*cos(angle+3.141592/8),(k->get_Y2()*ratioY)+12*sin(angle+3.141592/8),"black");
                }
        }

        //Création sommet(couleur indice deg + name SVG
        for (auto s : res_deg)
        {

                std::string b(1, s.first->get_nom());

                switch((int)s.second)
                {
                case 0:
                        color = "cornflowerblue";
                        break;
                case 1:
                        color = "cadetblue";
                        break;
                case 2:
                        color = "olive";
                        break;
                case 3:
                        color = "darkgoldenrod";
                        break;
                case 4:
                        color = "indianred";
                        break;
                case 5:
                        color = "tomato";
                        break;
                default:
                        color = "slateblue";
                        break;
                }


                svgOUT.addDisk((s.first->get_X())*ratioX, (s.first->get_Y())*ratioY,5, color);
                svgOUT.addText((s.first->get_X())*ratioX-5, (s.first->get_Y())*ratioY-7,b, "purple");
        }

        //Récup indice de prox + normalisation

        for(std::map<Sommet*,float>::iterator it=res_prox.begin(); it!=res_prox.end(); ++it)
        {
                it->second*=(m_sommet.size()-1);
        }

        for (auto z : res_prox)
        {
                std::string NormProx = std::to_string(z.second);
                NormProx.resize(5);
                svgOUT.addText((z.first->get_X())*ratioX+10, (z.first->get_Y())*ratioY-7,NormProx, "orange");
        }

        for(std::map<Sommet*,float>::iterator it=res_prox.begin(); it!=res_prox.end(); ++it)
        {
                it->second*=(m_sommet.size()-1);
        }

        //Récup indice de inter
        for (std::map<Sommet *, float>::iterator it = res_inter.begin(); it != res_inter.end(); ++it)
        {
                it->second /= (((m_sommet.size() * m_sommet.size()) - (3 * m_sommet.size() + 2)) / 2);
        }

        for (auto z : res_inter)
        {
                std::string NormProx = std::to_string(z.second);
                NormProx.resize(5);
                svgOUT.addText((z.first->get_X())*ratioX+10, (z.first->get_Y())*ratioY+5,NormProx, "chocolate");
        }

        for (std::map<Sommet *, float>::iterator it = res_inter.begin(); it != res_inter.end(); ++it)
        {
                it->second *= (((m_sommet.size() * m_sommet.size()) - (3 * m_sommet.size() + 2)) / 2);
        }
        //Recup indice propre


        for (auto z : res_propre)
        {
                std::string NormProx = std::to_string(z.second);
                NormProx.resize(5);
                svgOUT.addText((z.first->get_X())*ratioX+10, (z.first->get_Y())*ratioY+17,NormProx, "brown");
        }
}
int search_poid_entre(Sommet* p,Sommet* succ){
        int poid = 0;
        for(auto a : m_arete)
        {
                if((a->get_pair()->first==p && a->get_pair()->second == succ) || (a->get_pair()->first==succ && a->get_pair()->second == p))
                {
                        poid = a->get_poid();
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


int parcour_BFS(int nbr_s0)
{
        int ordre = 0;
        Sommet* s0 = getSommet_numeroN(nbr_s0);
        Sommet* temp = nullptr;
        std::queue<Sommet*> file;
        set_all_unvisited();

        s0->setVisited_bool(true);
        s0->setPred(s0);
        file.push(s0);

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
                if(m_sommet[i]->getVisited_bool())
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
