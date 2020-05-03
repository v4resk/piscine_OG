#include "sommet.hpp"

//----------------------------------------------
Sommet::Sommet(int id, char nom, int x, int y) : m_x(x),m_y(y),m_id(id),m_nom(nom){
};
//----------------------------------------------
//--------------Getteur------------------------
//---------------------------------------------
std::vector<Sommet*>& Sommet::ObtenirAdjacents()
{
        return m_adjacents;
}
char Sommet::get_nom()
{
        return m_nom;
}
int Sommet::get_id() const
{
        return m_id;
}
std::vector<Sommet*>* Sommet::get_adja()
{
        if(m_adjacents.size()!=0)
                return &m_adjacents;
        else
                return nullptr;
}
Sommet* Sommet::getPred()
{
        return m_pred;
}
bool Sommet::getVisited_bool()
{
        return m_visited;
}
int Sommet::get_X()
{
        return m_x;
}
int Sommet::get_Y()
{
        return m_y;
}

//----------------------------------------------
//----------Setteur----------------------------
//---------------------------------------------
void Sommet::ajouter_adjacents(Sommet* adja)
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
void Sommet::supprimer_adja(int s)
{
        std::vector<Sommet*>::iterator temp = m_adjacents.end();
        for(std::vector<Sommet*>::iterator it= m_adjacents.begin(); it != m_adjacents.end(); ++it)
        {
                if((*it)->get_id()==s)
                        temp = it;
        }
        if(temp!= m_adjacents.end())
                m_adjacents.erase(temp);
}

void Sommet::setVisited_bool(bool val)
{
        m_visited = val;
}

void Sommet::setPred(Sommet* predeseceur)
{
        m_pred = predeseceur;
}
void Sommet::set_X(int x)
{
        m_x =x;
}
void Sommet::set_Y(int y)
{
        m_y =y;
}
//------------------------------------------------
//----------------AFFICHAGE----------------------
//-----------------------------------------------
void Sommet::afficher(std::ostream& flux)
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
//--------------------------------------------
//--------------------------------------------
//-------------------------------------------
