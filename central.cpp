#include "central.hpp"

Centralisation::Centralisation(Graph* a) : m_graph(a){
        m_sommet = a->get_tab_sommet();
        m_arete = a->get_tab_arete();

        for(int i=0; i<m_sommet->size(); i++)
        {
                m_pred.push_back(0);
                m_marque.push_back(false);
                m_distance.push_back(INF);
        }
}

Centralisation::~Centralisation(){
}

std::map<Sommet*,float> Centralisation::centra_prox(){

        float totDist=0;
        for(std::vector<Sommet*>::iterator it = m_sommet->begin(); it != m_sommet->end(); ++it)
        {
                totDist = 0;
                for(std::vector<Sommet*>::iterator it2 = m_sommet->begin(); it2!=m_sommet->end(); ++it2)
                {
                        totDist+=calcul_d((*it)->get_id(),(*it2)->get_id());
                }
                resultat_prox[*it]=(1/totDist)*(m_sommet->size()-1);
        }
        return resultat_prox;
}


float Centralisation::calcul_d(int Si, int Sj)
{
        dijkstra(Si);
        return (float)m_distance[Sj];
}

void Centralisation::set_all_unvisited(){

        for(int i=0; i<m_marque.size(); ++i)
        {
                m_marque[i]=false;
                m_pred[i]=0;
        }

}


void Centralisation::setVisited_bool(bool a, int s)
{
        m_marque[s]=a;
}

bool Centralisation::chemin_a_ver_b(int a,int b)
{
        bool chemin_existe = false;
        Sommet* sA = (*m_sommet)[a];
        Sommet* sB = (*m_sommet)[b];
        for(std::vector<Sommet*>::iterator it = sA->get_adja()->begin(); it!= sA->get_adja()->end(); ++it )
        {
                if(*it == sB)
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
        for(int i=0; i < m_sommet->size(); ++i)
        {
                if(!m_marque[i] && m_distance[i] < dMin)
                {
                        dMin = m_distance[i];
                        sMin = i;
                }
        }

        return sMin;

}

void Centralisation::dijkstra(int sommet_depart)
{
        // INIT ----------------------------------------------------------------------------------
        // Tout les sommet sont non marquer et a distance infinie de s0
        int poid_adj=0;
        set_all_unvisited();
        for(int i=0; i<m_distance.size(); ++i )
        {
                m_distance[i] = INF;
        }
        // le sommet de depart a une distance de 0 par rapport a lui meme
        m_distance[sommet_depart] = 0;
        // --------------------------------------------------------------------------------------


        for(int i=0; i<m_sommet->size(); ++i)
        {
                int s =min_sommet();
                setVisited_bool(true,s);


                for(int j=0; j<m_sommet->size(); j++)
                {
                        if(chemin_a_ver_b(s,j))                         // Si il existe un chemin allant du sommet s est adjacent a J
                        {
                                for(std::vector<Sommet*>::iterator it=(*m_sommet)[s]->get_adja()->begin(); it != (*m_sommet)[s]->get_adja()->end(); ++it)
                                {
                                        if(*it ==  (*m_sommet)[j])
                                        {
                                                for(auto it : *m_arete)
                                                {
                                                        if(std::make_pair((*m_sommet)[s],(*m_sommet)[j])== *(it->get_pair()))
                                                        {
                                                                poid_adj = it->get_poid();
                                                        }
                                                }
                                                // On récupere le poid entre le chemin s et J
                                        }
                                }
                                if(m_distance[s]+ poid_adj < m_distance[j])
                                {
                                        m_distance[j] = m_distance[s]+ poid_adj;
                                        m_pred[j]=s;
                                }
                        }
                }

        }
}

void Centralisation::afficher_prox()
{
        std::map<Sommet*,float>::iterator it;
        for(it= resultat_prox.begin(); it!=resultat_prox.end(); ++it)
        {
                if(it->first!=nullptr)
                {
                        std::cout << "Sommet " << it->first->get_nom()
                                  << " : "
                                  << it->second << std::endl;
                }
        }
        std::cout << "---------------------" << std::endl;

        for(it = resultat_deg.begin(); it!=resultat_deg.end(); ++it)
        {
                if(it->first!=nullptr)
                {
                        std::cout << "Sommet " << it->first->get_nom()
                                  << " : "
                                  << it->second << std::endl;
                }
        }

        std::cout << "---------------------" << std::endl;

        for(it = resultat_propre.begin(); it!=resultat_propre.end(); ++it)
        {
                if(it->first!=nullptr)
                {
                        std::cout << "Sommet " << it->first->get_nom()
                                  << " : "
                                  << it->second << std::endl;
                }
        }
}

std::map<Sommet*,float>  Centralisation::centra_deg() {

        float deg = 0;
        for(std::vector<Sommet*>::iterator it = m_sommet->begin(); it != m_sommet->end(); ++it)
        {
                deg = 0;
                for(std::vector<Sommet*>::iterator it2=(*it)->get_adja()->begin(); it2!=(*it)->get_adja()->end(); ++it2)
                {
                        deg++;

                }
                resultat_deg[*it]=(deg)/(m_sommet->size()-1);
        }
        return resultat_deg;
}

std::map<Sommet*,float> Centralisation::centra_propre() {

//----------INITIALISATION-------------------


        float lambda=0;
        float lambdaMoinsUn=0;
        float ci=0;
        float totCi=0;

        std::map<Sommet*,float> file_ci;
        for(std::vector<Sommet*>::iterator it = m_sommet->begin(); it != m_sommet->end(); ++it)
        {
                resultat_propre[*it]=1;  // Tous a 1
        }
//---------BOUCLE-----------------------------------

        do
        {
                lambdaMoinsUn = lambda;
                lambda = 0;
                totCi = 0;

                for(std::map<Sommet*,float>::iterator it1=resultat_propre.begin(); it1!=resultat_propre.end(); ++it1)
                {
                        for(std::vector<Sommet*>::iterator it2 = it1->first->get_adja()->begin(); it2!=it1->first->get_adja()->end(); ++it2)
                        {
                                ci+=resultat_propre[*it2];
                                totCi+=ci;
                                file_ci[*it2]=ci;

                        }
                }
                lambda = sqrt(totCi*totCi);


                for(std::map<Sommet*,float>::iterator it3 = file_ci.begin(); it3!=file_ci.end(); ++it3)
                {
                        resultat_propre[it3->first]=it3->second/lambda;
                }

        } while(lambda-lambdaMoinsUn>1000);

        return resultat_propre;
}
