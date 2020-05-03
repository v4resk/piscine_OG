#include "arete.hpp"

Arete::Arete(int id,Sommet* i, Sommet* j) : m_id(id){
        m_pair.first = i;
        m_pair.second = j;
};
//----------------------------------------------------
//-------------------AFFICHAGE----------------------
//--------------------------------------------------
void Arete::afficher(std::ostream& flux)
{
        flux << "Id: " << m_id << " "
             << m_pair.first->get_nom()
             << "---"
             << m_pair.second->get_nom()
             << "     Poid: "
             << m_poid;
}
//----------------------------------------------------
//--------------Getteur-----------------------------
//------------------------------------------------
int Arete::get_poid()
{
        return m_poid;
}
int Arete::get_id()
{
        return m_id;
}
std::pair<Sommet*,Sommet*>* Arete::get_pair()
{
        return &m_pair;
}
int Arete::get_X1()
{
        return m_pair.first->get_X();
}
int Arete::get_Y1()
{
        return m_pair.first->get_Y();
}
int Arete::get_X2()
{
        return m_pair.second->get_X();
}

int Arete::get_Y2()
{
        return m_pair.second->get_Y();
}

//-----------------------------------------------
//-------------Setteur---------------------------
//------------------------------------------------

void Arete::set_poid(int poid)
{
        m_poid = poid;
}
