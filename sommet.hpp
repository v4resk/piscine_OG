#ifndef SOMMET
#define SOMMET

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <iterator>

class Sommet {

public:
Sommet(int id = 0, char nom = '\0', int x=0, int y=0) : m_x(x),m_y(y),m_id(id),m_nom(nom){
};

int ObtenirId() const
{
        return m_id;
}

std::vector<Sommet*>& ObtenirAdjacents()
{
        return m_adjacents;
}

char get_nom()
{
        return m_nom;
}

int get_id()
{
        return m_id;
}

std::vector<Sommet*>* get_adja()
{
        if(m_adjacents.size()!=0)
                return &m_adjacents;
        else
                return nullptr;
}

void ajouter_adjacents(Sommet* adja)
{
        bool pas_deja_dans_tab = true;
        for(std::vector<Sommet*>::iterator it= m_adjacents.begin(); it != m_adjacents.end(); ++it)
        {
                if((*it)==adja)
                        pas_deja_dans_tab = false;
        }
        if(pas_deja_dans_tab)
                m_adjacents.push_back(adja);
}


void afficher(std::ostream& flux)
{
        flux << "Nom: "
             << m_nom
             << std::endl
             << "Id: "
             << m_id
             << std::endl
             << "x="
             << m_x
             << " y="
             << m_y
             << std::endl
             << "Liste Adjacents: ";

        for(int i=0; i<m_adjacents.size(); i++)
        {
                flux << m_adjacents[i]->m_nom;
        }
}

void setVisited_bool(bool val)
{
        m_visited = val;
}

void setPred(Sommet* predeseceur)
{
        m_pred = predeseceur;
}

Sommet* getPred()
{
        return m_pred;
}

bool getVisited_bool()
{
        return m_visited;
}

void setConnex(int a)
{
        comp_connexe = a;
}

int getConnex()
{
        return comp_connexe;
}

int get_X()
{
        return m_x;
}

int get_Y()
{
        return m_y;
}

void set_X(int x)
{
        m_x =x;
}

void set_Y(int y)
{
        m_y =y;
}


private:
std::vector<Sommet*> m_adjacents;
bool m_visited;
Sommet* m_pred;
int m_x,m_y,m_id;
char m_nom;
int comp_connexe;

};

#endif
