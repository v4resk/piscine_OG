#ifndef GRAPH
#define GRAPH

#include <iostream>
#include <string>
#include <vector>
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




private:
std::ifstream fichier, fichier_pond;
std::vector<Sommet*> m_sommet;
std::vector<Arete*> m_arete;
int taille,ordre,orientation,poid;
int m_x,m_y,m_id;
int Si,Sj;
char m_nom;

};






#endif
