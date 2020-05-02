#ifndef CENTRAL
#define CENTRAL


#define INF 9999999
#define INT_NULL 7990
#define PAS_DE_PRED 8990

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
//---------------Calcule de centralité------------------------------
std::map<Sommet*,float> centra_prox();
std::map<Sommet*,float>  centra_deg();
std::map<Sommet*,float> centra_propre();
std::map<Sommet*,float> centra_inter(); // a fair

void centra_all();
//--------------Auxilliaire-------------------------------------------
float dijkstra(int sommet_depart, int sommet_fin);
std::vector< std::vector< std::pair<int,std::vector<Sommet*> >* >* > dijkstra_mod(int sommet_depart);
float calculer_inter(std::vector< std::vector< std::pair<int,std::vector<Sommet*> >* >* > dij, int i);
bool les_deux_vecteur_sont_egaux(std::vector<Sommet*> v,std::vector<Sommet*> w);
void set_all_unvisited();
int min_sommet();
bool getVisited_bool();
void setVisited_bool(bool a, int s);
bool chemin_a_ver_b(int a, int b);
void afficher_prox();
float calcul_d(int Si, int Sj);

//--------------------gett all result--------------------------
std::map<Sommet*,float>& get_res_prox();
std::map<Sommet*,float>& get_res_deg();
std::map<Sommet*,float>& get_res_propre();
std::map<Sommet*,float>& get_res_inter();
std::vector<int> get_m_distance();
//------------------Afficher resultats--------------------------
void afficher_res_prox();
void afficher_res_deg();
void afficher_res_propre();
void afficher_res_inter();

void afficher_all();
//-----------------Normaliser Resultats-------------------------
void normaliser_res_deg();
void normaliser_res_prox();
void normaliser_res_inter(); // A fair

void un_normaliser_res_deg();
void un_normaliser_res_prox();
void un_normaliser_res_inter(); // A fair
//----------------File Output-----------------------------------
void file_out_res_deg(std::string filename="resultat_deg.txt");
void file_out_res_propre(std::string filename="resultat_propre.txt");
void file_out_res_prox(std::string filename="resultat_prox.txt");
void file_out_res_inter(std::string filename="resultat_inter.txt");

void file_out_res_all();

private:
//--------UTILE AU FONCTIONNEMENT DE LA CLASS---------------
Graph* m_graph;
std::vector<Sommet*>* m_sommet;
std::vector<Arete*>* m_arete;
std::vector<bool> m_marque;
std::vector<int> m_distance;
std::vector<Sommet*> m_pred;
//-------RECEPTIONNE LE RESULTATS DES FONCTIONS CENTRALISATION------------
//std::vector<std::pair<Sommet*,float> > resultat_prox; // Stock les resultats de centra_prox. A chaque Sommet associe sont coef de centralité
std::map<Sommet*,float> resultat_prox;
std::map<Sommet*,float> resultat_deg;
std::map<Sommet*,float> resultat_propre;
std::map<Sommet*,float> resultat_inter;

};


#endif
