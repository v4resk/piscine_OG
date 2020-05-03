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
Sommet(int id = 0, char nom = '\0', int x=0, int y=0);
//----------------getter------------------------------
std::vector<Sommet*>& ObtenirAdjacents();
char get_nom();
int get_id() const;
std::vector<Sommet*>* get_adja();
Sommet* getPred();
bool getVisited_bool();
int get_X();
int get_Y();
//---------------Setteur------------------------------
void ajouter_adjacents(Sommet* adja);
void supprimer_adja(int s);
void setVisited_bool(bool val);
void setPred(Sommet* predeseceur);
void set_X(int x);
void set_Y(int y);
//------------affichage-------------------------------
void afficher(std::ostream& flux);

private:
std::vector<Sommet*> m_adjacents;
bool m_visited;
Sommet* m_pred;
int m_x,m_y,m_id;
char m_nom;
};

#endif
