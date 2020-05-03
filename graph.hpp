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

class Graph {
public:

Graph(std::string nom_fichier, std::string fichier_ponderation);
//----------Getteur---------------------------------------
int get_ordre();
int get_orientation();
std::vector<Sommet*>* get_tab_sommet();
std::vector<Arete*>* get_tab_arete();
Sommet* getSommet_numeroN(int numero);
//-------------SVG--------------------------------
void creer_svg(std::map<Sommet*,float> res_deg,std::map<Sommet*,float>res_prox,std::map<Sommet*,float>res_inter,std::map<Sommet*,float>res_propre);
//-------------Setteur-------------------------
void ajouter_poid(int m_id,int poid);
//-------------Aux-------------------------------
int search_poid_entre(Sommet* p,Sommet* succ);
void ajouter_adjacents(int Si, int Sj);
void afficher(std::ostream& flux);
int parcour_BFS(int nbr_s0);
void parcour_DFS(int m_id /*,int* date*/);
void init_parcour_DFS(int m_id);
void afficher_bfs(int m_id);
void afficher_dfs(int m_id);
void supprimer_adja(int s, int s_sup);

private:

void set_all_unvisited();

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
