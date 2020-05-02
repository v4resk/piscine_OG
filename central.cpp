#include "central.hpp"

//-------------------------------------------------------------------
//-----------------------FONCTEUR UTILE------------------------------

class compar_Sommet
{
public:
        bool operator()(Sommet *s1, Sommet *s2)
        {
                return (s1->get_id() == s2->get_id());
        }
};

class compar_Sommet_trie
{
public:
        bool operator()(Sommet *s1, Sommet *s2)
        {
                return (s1->get_id() < s2->get_id());
        }
};

//---------------------------------------------------------------------
//---------------------------------------------------------------------
Centralisation::Centralisation(Graph *a) : m_graph(a)
{
        m_sommet = a->get_tab_sommet();
        m_arete = a->get_tab_arete();

        for (int i = 0; i < m_sommet->size(); i++)
        {
                m_pred.push_back(0);
                m_marque.push_back(false);
                m_distance.push_back(INF);
        }
}

Centralisation::~Centralisation()
{
}
//--------------------------------------------------------------------
//-------------------------------------------------------------------
//--------------------------Geter de Resultats--------------------------

std::map<Sommet *, float> &Centralisation::get_res_prox()
{
        return resultat_prox;
}

std::map<Sommet *, float> &Centralisation::get_res_propre()
{
        return resultat_propre;
}
std::map<Sommet *, float> &Centralisation::get_res_deg()
{
        return resultat_deg;
}

std::map<Sommet *, float> &Centralisation::get_res_inter()
{
        return resultat_inter;
}

std::vector<int> Centralisation::get_m_distance()
{
        return m_distance;
}

//-----------------------------------------------------------------------
//----------------------------------------------------------------------
//---------------------------Afficher resultats-------------------------

void Centralisation::afficher_res_prox()
{
        std::map<Sommet *, float>::iterator it;
        std::cout << std::endl
                  << "----------------------"
                  << std::endl
                  << "centralité de Proximite"
                  << std::endl
                  << "--------------------"
                  << std::endl;
        for (it = resultat_prox.begin(); it != resultat_prox.end(); ++it)
        {
                if (it->first != nullptr)
                {
                        std::cout << "Sommet: " << it->first->get_nom()
                                  << " Brute: "
                                  << it->second
                                  << " Normaliser: "
                                  << it->second * (m_sommet->size() - 1)
                                  << std::endl;
                }
        }
        std::cout << "---------------------" << std::endl;
}

void Centralisation::afficher_res_deg()
{
        std::map<Sommet *, float>::iterator it;
        std::cout << std::endl
                  << "----------------------"
                  << std::endl
                  << "centralité de degres"
                  << std::endl
                  << "--------------------"
                  << std::endl;
        for (it = resultat_deg.begin(); it != resultat_deg.end(); ++it)
        {
                if (it->first != nullptr)
                {
                        std::cout << "Sommet: " << it->first->get_nom()
                                  << " Brute: "
                                  << it->second
                                  << " Normaliser: "
                                  << it->second / (m_sommet->size() - 1)
                                  << std::endl;
                }
        }
        std::cout << "---------------------" << std::endl;
}

void Centralisation::afficher_res_propre()
{
        std::map<Sommet *, float>::iterator it;
        std::cout << std::endl
                  << "----------------------"
                  << std::endl
                  << "centralité de vecteur propre"
                  << std::endl
                  << "--------------------"
                  << std::endl;
        for (it = resultat_propre.begin(); it != resultat_propre.end(); ++it)
        {
                if (it->first != nullptr)
                {
                        std::cout << "Sommet: " << it->first->get_nom()
                                  << " Brute: "
                                  << it->second
                                  << " Normaliser: -"
                                  << std::endl;
                }
        }
        std::cout << "---------------------" << std::endl;
}

void Centralisation::afficher_res_inter()
{
        std::map<Sommet *, float>::iterator it;
        std::cout << std::endl
                  << "----------------------"
                  << std::endl
                  << "centralité de vecteur intermediaire"
                  << std::endl
                  << "--------------------"
                  << std::endl;
        for (it = resultat_inter.begin(); it != resultat_inter.end(); ++it)
        {
                if (it->first != nullptr)
                {
                        std::cout << "Sommet: " << it->first->get_nom()
                                  << " Brute: "
                                  << it->second
                                  << " Normaliser: "
                                  << it->second / (((m_sommet->size() * m_sommet->size()) - (3 * m_sommet->size() + 2)) / 2)
                                  << std::endl;
                }
        }
        std::cout << "---------------------" << std::endl;
}

void Centralisation::afficher_all()
{
        afficher_res_prox();
        afficher_res_deg();
        afficher_res_propre();
        afficher_res_inter();
}

//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//----------------------Normaliser et denormaliser une map de resultat---------------------------------

void Centralisation::normaliser_res_deg()
{
        for (std::map<Sommet *, float>::iterator it = resultat_deg.begin(); it != resultat_deg.end(); ++it)
        {
                it->second *= (m_sommet->size() - 1);
        }
}

void Centralisation::un_normaliser_res_deg()
{
        for (std::map<Sommet *, float>::iterator it = resultat_deg.begin(); it != resultat_deg.end(); ++it)
        {
                it->second /= (m_sommet->size() - 1);
        }
}

void Centralisation::normaliser_res_prox()
{
        for (std::map<Sommet *, float>::iterator it = resultat_deg.begin(); it != resultat_deg.end(); ++it)
        {
                it->second /= (m_sommet->size() - 1);
        }
}

void Centralisation::un_normaliser_res_prox()
{
        for (std::map<Sommet *, float>::iterator it = resultat_deg.begin(); it != resultat_deg.end(); ++it)
        {
                it->second *= (m_sommet->size() - 1);
        }
}

void Centralisation::normaliser_res_inter()
{
        for (std::map<Sommet *, float>::iterator it = resultat_inter.begin(); it != resultat_inter.end(); ++it)
        {
                it->second /= (((m_sommet->size() * m_sommet->size()) - (3 * m_sommet->size() + 2)) / 2);
        }
}

void Centralisation::un_normaliser_res_inter()
{
        for (std::map<Sommet *, float>::iterator it = resultat_inter.begin(); it != resultat_inter.end(); ++it)
        {
                it->second *= (((m_sommet->size() * m_sommet->size()) - (3 * m_sommet->size() + 2)) / 2);
        }
}
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//------------------Fonction calcul centralité------------------------------

std::map<Sommet *, float> Centralisation::centra_prox()
{

        for (auto it1 : *m_sommet)
        {
                float totDist = 0;
                for (auto it2 : *m_sommet)
                {
                        totDist += dijkstra(it1->get_id(), it2->get_id());
                }
                resultat_prox[it1] = (1.0 / totDist);
        }
        return resultat_prox;
}

std::map<Sommet *, float> Centralisation::centra_deg()
{

        float deg = 0;
        for (std::vector<Sommet *>::iterator it = m_sommet->begin(); it != m_sommet->end(); ++it)
        {
                deg = 0;
                if ((*it)->get_adja() != nullptr)
                        for (std::vector<Sommet *>::iterator it2 = (*it)->get_adja()->begin(); it2 != (*it)->get_adja()->end(); ++it2)
                        {
                                deg++;
                        }
                resultat_deg[*it] = (deg);
        }
        return resultat_deg;
}

std::map<Sommet *, float> Centralisation::centra_propre()
{
        //----------INITIALISATION-------------------
        float lambda = 0;
        float lambdaMoinsUn = 0;
        float ci = 0;
        std::map<Sommet *, float> map_ci;
        std::vector<float> vec_ci;

        for (std::vector<Sommet *>::iterator it = m_sommet->begin(); it != m_sommet->end(); ++it)
        {
                resultat_propre[*it] = 1; // Tous a 1
        }
        //---------BOUCLE----------------------------------
        do
        {
                lambdaMoinsUn = lambda;
                lambda = 0;

                for (std::map<Sommet *, float>::iterator it1 = resultat_propre.begin(); it1 != resultat_propre.end(); ++it1)
                {
                        ci = 0;
                        if ((*it1).first->get_adja() != nullptr)
                                for (std::vector<Sommet *>::iterator it2 = it1->first->get_adja()->begin(); it2 != it1->first->get_adja()->end(); ++it2)
                                {
                                        ci += resultat_propre[*it2];
                                }
                        map_ci[it1->first] = ci;
                }

                for (std::map<Sommet *, float>::iterator it = map_ci.begin(); it != map_ci.end(); ++it)
                {
                        lambda += (float)pow(it->second, 2);
                }
                lambda = sqrt(lambda);

                for (std::map<Sommet *, float>::iterator it = map_ci.begin(); it != map_ci.end(); ++it)
                {
                        resultat_propre[it->first] = it->second / lambda;
                }

        } while (lambda - lambdaMoinsUn > 1000);

        return resultat_propre;
}

void Centralisation::centra_all()
{
        centra_deg();
        centra_prox();
        centra_propre();
        centra_inter();
}

std::map<Sommet *, float> Centralisation::centra_inter()
{

        return resultat_inter;
}

//--------------------------------------------------------------------------
//-------------------------------------------------------------------------
//----------------------Fonction Auxilliaire------------------------------

void Centralisation::set_all_unvisited()
{

        for (int i = 0; i < m_marque.size(); ++i)
        {
                m_marque[i] = false;
                m_pred[i] = nullptr;
        }
}

bool Centralisation::chemin_a_ver_b(int a, int b)
{
        bool chemin_existe = false;
        Sommet *sA = (*m_sommet)[a];
        Sommet *sB = (*m_sommet)[b];

        //  if(sA->get_adja()!=nullptr || sB->get_adja()!=nullptr)
        for (std::vector<Sommet *>::iterator it = sA->get_adja()->begin(); it != sA->get_adja()->end(); ++it)
        {
                //  if(*it!=nullptr && sB !=nullptr)
                if (*it == sB)
                {
                        chemin_existe = true;
                }
        }

        return chemin_existe;
}

int Centralisation::min_sommet()
{
        int dMin = INF;
        int sMin = INT_NULL;
        for (int i = 0; i < m_sommet->size(); ++i)
        {

                if (!m_marque[i] && m_distance[i] < dMin)
                {
                        dMin = m_distance[i];
                        sMin = i;
                }
        }

        return sMin;
}

float Centralisation::dijkstra(int sommet_depart, int sommet_fin)
{

        auto comp = [](std::pair<Sommet *, double> p1, std::pair<Sommet *, double> p2) {
                return p2.second < p1.second;
        };
        std::priority_queue<std::pair<Sommet *, int>, std::vector<std::pair<Sommet *, int>>, decltype(comp)> file(comp);
        std::vector<int> m_dist(m_sommet->size(), INF);
        int poid_adj = 0;

        file.push(std::make_pair((*m_sommet)[sommet_depart], 0));
        m_dist[sommet_depart] = 0;

        while (!file.empty())
        {
                Sommet *s = file.top().first;
                int s_int = s->get_id();
                int d = file.top().second;

                file.pop();
                if (d <= m_dist[s_int])
                {
                        for (std::vector<Sommet *>::iterator it = s->get_adja()->begin(); it != s->get_adja()->end(); ++it)
                        {
                                for (auto it1 : *m_arete)
                                {
                                        if (std::make_pair((*m_sommet)[s_int], (*m_sommet)[(*it)->get_id()]) == *(it1->get_pair()) || std::make_pair(((*m_sommet)[(*it)->get_id()]), (*m_sommet)[s_int]) == *(it1->get_pair()))
                                        {
                                                poid_adj = it1->get_poid();
                                        }
                                }
                                if (m_dist[s_int] + poid_adj < m_dist[(*it)->get_id()])
                                {
                                        m_dist[(*it)->get_id()] = m_dist[s_int] + poid_adj;
                                        file.push(std::make_pair(*it, m_dist[(*it)->get_id()]));

                                        m_pred[(*it)->get_id()] = s;
                                }
                        }
                }
        }
        m_distance = m_dist;
        return m_dist[sommet_fin];
}

void Centralisation::(int sommet_depart)
{

        // Il faut ajouter le cout du chemin -> pair
        // Il faut ajouter une 3eme dimensions pour tout les autres pcc a partir du meme sommet_depart jusqu'au meme sommet mais appres la suppression
        //    -> [i] le sommet de fin         [j][k] chemin n°j

        // pcc_a_sommet_depart[i] est le sommet d'arriver
        // pcc_a_sommet_depart[i][j] chemin numero j   pour aller de sommet de depart a sommet d'arriver i
        // pcc_a_sommet_depart[i][j]->first poid du chemin n°j pour aller de sommet de depart a sommet d'arriver i
        //pcc_a_sommet_depart[i][j]->second  vecteur des sommet composant le chemin n°j pour aller de sommet de depart a sommet d'arriver i
        //pcc_a_sommet_depart[i][j]->second[k]  sommet du vecteur du chemin
        std::vector<std::vector<std::pair<int, std::vector<Sommet *>> *> *> pcc_a_sommet_depart;
        Sommet *pred = nullptr;
        int j = 0;
        int int_sommet_a_sup = INF;
        std::vector<int> sommet_temp_supprimer;
        std::vector<int> sommet_supprimer;
        std::vector<Sommet *> sommet_a_supp;
        do
        {
                auto comp = [](std::pair<Sommet *, double> p1, std::pair<Sommet *, double> p2) {
                        return p2.second < p1.second;
                };
                std::priority_queue<std::pair<Sommet *, int>, std::vector<std::pair<Sommet *, int>>, decltype(comp)> file(comp);
                std::vector<int> m_dist(m_sommet->size(), INF);
                set_all_unvisited();
                int poid_adj = 0;

                file.push(std::make_pair((*m_sommet)[sommet_depart], 0));
                m_dist[sommet_depart] = 0;

                while (!file.empty())
                {
                        Sommet *s = file.top().first;
                        int s_int = s->get_id();
                        int d = file.top().second;

                        file.pop();
                        if (d <= m_dist[s_int])
                        {
                                for (std::vector<Sommet *>::iterator it = s->get_adja()->begin(); it != s->get_adja()->end(); ++it)
                                {
                                        if ((*it)->get_id() != int_sommet_a_sup)
                                        {
                                                for (auto it1 : *m_arete)
                                                {
                                                        if (std::make_pair((*m_sommet)[s_int], (*m_sommet)[(*it)->get_id()]) == *(it1->get_pair()) || std::make_pair(((*m_sommet)[(*it)->get_id()]), (*m_sommet)[s_int]) == *(it1->get_pair()))
                                                        {
                                                                poid_adj = it1->get_poid();
                                                        }
                                                }

                                                if (m_dist[s_int] + poid_adj < m_dist[(*it)->get_id()])
                                                {
                                                        m_dist[(*it)->get_id()] = m_dist[s_int] + poid_adj;
                                                        file.push(std::make_pair(*it, m_dist[(*it)->get_id()]));

                                                        m_pred[(*it)->get_id()] = s;
                                                }
                                        }
                                }
                        }
                }
                //------------------------------------------------------------------
                //--------------On recupere les pcc pour aller-------------------
                //--------------de sommet_depart jusqu'a chaque sommet--------------
                //------------------------------------------------------------------
                // pcc_a_sommet_depart[i] est le sommet d'arriver
                // pcc_a_sommet_depart[i][j] chemin numero j   pour aller de sommet de depart a sommet d'arriver i
                // pcc_a_sommet_depart[i][j]->first poid du chemin n°j pour aller de sommet de depart a sommet d'arriver i
                //pcc_a_sommet_depart[i][j]->second  vecteur des sommet composant le chemin n°j pour aller de sommet de depart a sommet d'arriver i
                //pcc_a_sommet_depart[i][j]->second[k]  sommet du vecteur du chemin
                //std::vector< std::vector< std::pair<int,std::vector<Sommet*> > >* > pcc_a_sommet_depart;

                //-----------------------------------------------------------------------------
                //---------------------A chaque tour de dijsktra on stock le chemin ici--------
                //-----------------------------------------------------------------------------
                for (int i = 0; i < m_pred.size(); ++i)
                {
                        pcc_a_sommet_depart.push_back(new std::vector<std::pair<int, std::vector<Sommet *>> *>); // On cree [i] dans le quelle on stock un  vecteur de vecteur de chemin avec leur poid
                        (*pcc_a_sommet_depart[i]).push_back(new std::pair<int, std::vector<Sommet *>>);          // on cree [i][j]
                }
                //----------Netoyage------------------------------------
                while (pcc_a_sommet_depart.size() > m_sommet->size())
                {
                        pcc_a_sommet_depart.erase(pcc_a_sommet_depart.end() - 1);
                }

                //-------------------------------------------------------
                for (int i = 0; i < m_pred.size(); ++i)
                {
                        pred = m_pred[i];

                        while (pred != nullptr)
                        {
                                (*(*pcc_a_sommet_depart[i])[j]).second.push_back(pred);
                                (*(*pcc_a_sommet_depart[i])[j]).first = m_distance[i];
                                pred = m_pred[pred->get_id()];
                        }
                }

                j++;
                //--------Netoyage-------------------------------------------
                for (int i = 0; i < pcc_a_sommet_depart.size(); i++)
                {
                        while ((*pcc_a_sommet_depart[i]).size() > j)
                        {
                                pcc_a_sommet_depart[i]->resize(j);
                        }
                }
                //----------------------------------------------------------
                //----------------------------------------------------------------------------
                //----------------ON SUPRRIME LES ADJACENCE UNE PAR UNE ----------------------
                //------------ET ON REMET CELLES SUPPRIMER PRÉCÉDAMENT------------------------

                //Remplir la liste des sommet a supprimer :
                for (int i = 0; i < pcc_a_sommet_depart.size(); ++i)
                {

                        for (int k = 0; k < pcc_a_sommet_depart[i]->size(); ++k)
                        {

                                for (int l = 0; l < (*(*pcc_a_sommet_depart[i])[k]).second.size(); ++l)
                                {
                                        sommet_a_supp.push_back((*(*pcc_a_sommet_depart[i])[k]).second[l]);
                                }
                        }
                }
                // On supprime les doublons de la liste des sommets a supprimer:
                std::sort(sommet_a_supp.begin(), sommet_a_supp.end(), compar_Sommet_trie());
                sommet_a_supp.erase(std::unique(sommet_a_supp.begin(), sommet_a_supp.end(), compar_Sommet()), sommet_a_supp.end());
                // On supprime le sommet de depart de la liste ainsssi que ceux qui on deja ete supprimer
                for (std::vector<Sommet *>::iterator it = sommet_a_supp.begin(); it != sommet_a_supp.end(); ++it)
                {
                        if ((*it)->get_id() == sommet_depart)
                                sommet_a_supp.erase(it);

                        for (int i = 0; i < sommet_supprimer.size(); ++i)
                        {
                                if ((*it)->get_id() == sommet_supprimer[i])
                                        sommet_a_supp.erase(it);
                        }
                }
                // Pour tout les sommet on supprime le premier sommet de la liste de leur adjacent

                int_sommet_a_sup = (*sommet_a_supp.begin())->get_id();

                // On l'enleve de la liste des sommet a supprimer;
                // On push dans la liste des sommet supprimer

                //    sommet_temp_supprimer.push_back((*sommet_a_supp.begin())->get_id());
                sommet_supprimer.push_back((*sommet_a_supp.begin())->get_id());
                sommet_a_supp.erase(sommet_a_supp.begin());
                // On restaure un sommet de la liste des sommets deja supprimer (sommet_temp_supprimer) si elle n'est pas vide

                //---------------------------------------------------------------------
                //-----------------------DEBUG AFFICHAGE--------------------------------
                //----------------------------------------------------------------------
                for (int i = 0; i < pcc_a_sommet_depart.size(); ++i)
                {
                        std::cout << std::endl
                                  << "Sommet " << i << std::endl;
                        for (int k = 0; k < pcc_a_sommet_depart[i]->size(); ++k)
                        {
                                std::cout << "Chemin n°" << k << " : ";
                                for (int l = 0; l < (*(*pcc_a_sommet_depart[i])[k]).second.size(); ++l)
                                {
                                        std::cout << (*(*pcc_a_sommet_depart[i])[k]).second[l]->get_id() << " ";
                                }
                                std::cout << std::endl;
                        }
                        std::cout << std::endl
                                  << "-------------------" << std::endl;
                }

                std::cout << "Liste des sommet a sup : ";
                for (auto it : sommet_a_supp)
                {
                        std::cout << it->get_id() << " ";
                }

                //---------------------------------------------------------------------------
        } while (!sommet_a_supp.empty());
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//-------------------Fonction Output fichier--------------------------------

void Centralisation::file_out_res_deg(std::string filename)
{

        std::ofstream file(filename);

        std::map<Sommet *, float>::iterator it;
        file << std::endl
             << "----------------------"
             << std::endl
             << "centralité de degres"
             << std::endl
             << "--------------------"
             << std::endl;
        for (it = resultat_deg.begin(); it != resultat_deg.end(); ++it)
        {
                if (it->first != nullptr)
                {
                        file << "Sommet: " << it->first->get_nom()
                             << " Brute: "
                             << it->second
                             << " Normaliser: "
                             << it->second / (m_sommet->size() - 1)
                             << std::endl;
                }
        }
        file << "---------------------" << std::endl;
}

void Centralisation::file_out_res_prox(std::string filename)
{

        std::ofstream file(filename);

        std::map<Sommet *, float>::iterator it;
        file << std::endl
             << "----------------------"
             << std::endl
             << "centralité de Proximité"
             << std::endl
             << "--------------------"
             << std::endl;
        for (it = resultat_prox.begin(); it != resultat_prox.end(); ++it)
        {
                if (it->first != nullptr)
                {
                        file << "Sommet: " << it->first->get_nom()
                             << " Brute: "
                             << it->second
                             << " Normaliser: "
                             << it->second * (m_sommet->size() - 1)
                             << std::endl;
                }
        }
        file << "---------------------" << std::endl;
}

void Centralisation::file_out_res_propre(std::string filename)
{

        std::ofstream file(filename);

        std::map<Sommet *, float>::iterator it;
        file << std::endl
             << "----------------------"
             << std::endl
             << "centralité de vecteur propre"
             << std::endl
             << "--------------------"
             << std::endl;
        for (it = resultat_propre.begin(); it != resultat_propre.end(); ++it)
        {
                if (it->first != nullptr)
                {
                        file << "Sommet: " << it->first->get_nom()
                             << " Brute: "
                             << it->second
                             << " Normaliser: -"
                             << std::endl;
                }
        }
        file << "---------------------" << std::endl;
}

void Centralisation::file_out_res_inter(std::string filename)
{

        std::map<Sommet *, float>::iterator it;
        std::ofstream file(filename);
        file << std::endl
             << "----------------------"
             << std::endl
             << "centralité de vecteur intermediaire"
             << std::endl
             << "--------------------"
             << std::endl;
        for (it = resultat_inter.begin(); it != resultat_inter.end(); ++it)
        {
                if (it->first != nullptr)
                {
                        file << "Sommet: " << it->first->get_nom()
                             << " Brute: "
                             << it->second
                             << " Normaliser: "
                             << it->second / (((m_sommet->size() * m_sommet->size()) - (3 * m_sommet->size() + 2)) / 2)
                             << std::endl;
                }
        }
        file << "---------------------" << std::endl;
}

void Centralisation::file_out_res_all()
{
        file_out_res_propre();
        file_out_res_prox();
        file_out_res_deg();
        file_out_res_inter();
}
