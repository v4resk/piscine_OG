#ifndef ARETE
#define ARETE


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "arete.hpp"
#include "sommet.hpp"
#include <algorithm>

class Arete
{
public:

Arete(int id,Sommet* i, Sommet* j) : m_id(id){
        m_pair.first = i;
        m_pair.second = j;
};

void afficher(std::ostream& flux)
{
        flux << "Id: " << m_id << " "
             << m_pair.first->get_nom()
             << "---"
             << m_pair.second->get_nom()
             << "     Poid: "
             << m_poid;
}

void set_poid(int poid)
{
        m_poid = poid;
}

int get_poid()
{
        return m_poid;
}

int get_id()
{
        return m_id;
}

std::pair<Sommet*,Sommet*>* get_pair()
{
        return &m_pair;
}

int get_X1()
{
        return m_pair.first->get_X();
}

int get_Y1()
{
        return m_pair.first->get_Y();
}

int get_X2()
{
        return m_pair.second->get_X();
}

int get_Y2()
{
        return m_pair.second->get_Y();
}

private:
std::pair<Sommet*,Sommet*> m_pair;
int m_id,m_poid;


};




#endif
