#ifndef CENTRAL
#define CENTRAL

#define INF 9999999
#define INT_NULL 7990


#include <iostream>
#include <vector>
#include "sommet.hpp"
#include "arete.hpp"
#include "graph.hpp"
#include <map>
#include <queue>
#include <math.h>

class Centralisation
{
public:
Centralisation(Graph* a);
~Centralisation();

std::map<Sommet*,float> centra_prox();
std::map<Sommet*,float>  centra_deg();
std::map<Sommet*,float> centra_propre();
void dijkstra(int sommet_depart);
void set_all_unvisited();
int min_sommet();
bool getVisited_bool();
void setVisited_bool(bool a, int s);
bool chemin_a_ver_b(int a, int b);
void afficher_prox();
float calcul_d(int Si, int Sj);

//--------------------gett all result--------------------------




private:
//--------UTILE AU FONCTIONNEMENT DE LA CLASS---------------
Graph* m_graph;
std::vector<Sommet*>* m_sommet;
std::vector<Arete*>* m_arete;
std::vector<bool> m_marque;
std::vector<int> m_distance;
std::vector<int> m_pred;
//-------RECEPTIONNE LE RESULTATS DES FONCTIONS CENTRALISATION------------
//std::vector<std::pair<Sommet*,float> > resultat_prox; // Stock les resultats de centra_prox. A chaque Sommet associe sont coef de centralité
std::map<Sommet*,float> resultat_prox;
std::map<Sommet*,float> resultat_deg;
std::map<Sommet*,float> resultat_propre;
};


#endif
