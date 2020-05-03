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
//---------------------------------------------
Arete(int id,Sommet* i, Sommet* j);
//-------------Affichage----------------------
void afficher(std::ostream& flux);
//--------------Setteur--------------------
void set_poid(int poid);
//------------Getteur-------------------------
int get_poid();
int get_id();
std::pair<Sommet*,Sommet*>* get_pair();
int get_X1();
int get_Y1();
int get_X2();
int get_Y2();


private:
std::pair<Sommet*,Sommet*> m_pair;
int m_id,m_poid;


};




#endif
