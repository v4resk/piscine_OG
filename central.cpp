#include "central.hpp"

//---------------------------------------------------------------------
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
//--------------------------------------------------------------------
//-------------------------------------------------------------------
//--------------------------Geter de Resultats--------------------------

std::map<Sommet*,float>& Centralisation::get_res_prox(){
        return resultat_prox;
}

std::map<Sommet*,float>& Centralisation::get_res_propre(){
        return resultat_propre;
}
std::map<Sommet*,float>&Centralisation::get_res_deg(){
        return resultat_deg;
}

//-----------------------------------------------------------------------
//----------------------------------------------------------------------
//---------------------------Afficher resultats-------------------------

void Centralisation::afficher_res_prox(){
        std::map<Sommet*,float>::iterator it;
        std::cout << std::endl
                  << "----------------------"
                  <<std::endl
                  << "centralité de Proximite"
                  << std::endl
                  << "--------------------"
                  << std::endl;
        for(it= resultat_prox.begin(); it!=resultat_prox.end(); ++it)
        {
                if(it->first!=nullptr)
                {
                        std::cout << "Sommet: " << it->first->get_nom()
                                  << " Brute: "
                                  << it->second
                                  <<  " Normaliser: "
                                  << it->second*(m_sommet->size()-1)
                                  << std::endl;
                }
        }
        std::cout << "---------------------" << std::endl;
}

void Centralisation::afficher_res_deg(){
        std::map<Sommet*,float>::iterator it;
        std::cout << std::endl
                  << "----------------------"
                  <<std::endl
                  << "centralité de degres"
                  << std::endl
                  << "--------------------"
                  << std::endl;
        for(it= resultat_deg.begin(); it!=resultat_deg.end(); ++it)
        {
                if(it->first!=nullptr)
                {
                        std::cout << "Sommet: " << it->first->get_nom()
                                  << " Brute: "
                                  << it->second
                                  <<  " Normaliser: "
                                  << it->second/(m_sommet->size()-1)
                                  << std::endl;
                }
        }
        std::cout << "---------------------" << std::endl;
}

void Centralisation::afficher_res_propre(){
        std::map<Sommet*,float>::iterator it;
        std::cout << std::endl
                  << "----------------------"
                  <<std::endl
                  << "centralité de vecteur propre"
                  << std::endl
                  << "--------------------"
                  << std::endl;
        for(it= resultat_propre.begin(); it!=resultat_propre.end(); ++it)
        {
                if(it->first!=nullptr)
                {
                        std::cout << "Sommet: " << it->first->get_nom()
                                  << " Brute: "
                                  << it->second
                                  <<  " Normaliser: -"
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
}

//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//----------------------Normaliser et denormaliser une map de resultat---------------------------------

void Centralisation::normaliser_res_deg(){
        for(std::map<Sommet*,float>::iterator it=resultat_deg.begin(); it!=resultat_deg.end(); ++it)
        {
                it->second*=(m_sommet->size()-1);
        }
}

void Centralisation::un_normaliser_res_deg(){
        for(std::map<Sommet*,float>::iterator it=resultat_deg.begin(); it!=resultat_deg.end(); ++it)
        {
                it->second/=(m_sommet->size()-1);
        }
}

void Centralisation::normaliser_res_prox(){
        for(std::map<Sommet*,float>::iterator it=resultat_deg.begin(); it!=resultat_deg.end(); ++it)
        {
                it->second/=(m_sommet->size()-1);
        }
}

void Centralisation::un_normaliser_res_prox(){
        for(std::map<Sommet*,float>::iterator it=resultat_deg.begin(); it!=resultat_deg.end(); ++it)
        {
                it->second*=(m_sommet->size()-1);
        }
}
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//------------------Fonction calcul centralité------------------------------

std::map<Sommet*,float> Centralisation::centra_prox(){

        for(std::vector<Sommet*>::iterator it = m_sommet->begin(); it != m_sommet->end(); ++it)
        {
                float totDist = 0;
                for(std::vector<Sommet*>::iterator it2 = m_sommet->begin(); it2!=m_sommet->end(); ++it2)
                {
                        totDist+=calcul_d((*it)->get_id(),(*it2)->get_id());
                }
                resultat_prox[*it]=(1/totDist);
        }
        return resultat_prox;
}


std::map<Sommet*,float>  Centralisation::centra_deg() {

        float deg = 0;
        for(std::vector<Sommet*>::iterator it = m_sommet->begin(); it != m_sommet->end(); ++it)
        {
                deg = 0;
                if((*it)->get_adja()!=nullptr)
                        for(std::vector<Sommet*>::iterator it2=(*it)->get_adja()->begin(); it2!=(*it)->get_adja()->end(); ++it2)
                        {
                                deg++;

                        }
                resultat_deg[*it]=(deg);
        }
        return resultat_deg;
}


std::map<Sommet*,float> Centralisation::centra_propre() {
        //----------INITIALISATION-------------------
        float lambda=0;
        float lambdaMoinsUn=0;
        float ci=0;
        std::map<Sommet*,float> map_ci;
        std::vector<float> vec_ci;

        for(std::vector<Sommet*>::iterator it = m_sommet->begin(); it != m_sommet->end(); ++it)
        {
                resultat_propre[*it]=1;  // Tous a 1
        }
        //---------BOUCLE----------------------------------
        do {
                lambdaMoinsUn = lambda;
                lambda = 0;

                for(std::map<Sommet*,float>::iterator it1=resultat_propre.begin(); it1!=resultat_propre.end(); ++it1)
                {
                        ci=0;
                        if((*it1).first->get_adja()!=nullptr)
                                for(std::vector<Sommet*>::iterator it2 = it1->first->get_adja()->begin(); it2!=it1->first->get_adja()->end(); ++it2)
                                {
                                        ci+=resultat_propre[*it2];
                                }
                        map_ci[it1->first]=ci;
                }

                for(std::map<Sommet*,float>::iterator it = map_ci.begin(); it!=map_ci.end(); ++it)
                {
                        lambda+=(float)pow(it->second,2);
                }
                lambda=sqrt(lambda);

                for(std::map<Sommet*,float>::iterator it = map_ci.begin(); it!=map_ci.end(); ++it)
                {
                        resultat_propre[it->first]=it->second/lambda;
                }


        } while(lambda-lambdaMoinsUn>1000);

        return resultat_propre;
}

void Centralisation::centra_all()
{
        centra_deg();
        centra_prox();
        centra_propre();
}

//--------------------------------------------------------------------------
//-------------------------------------------------------------------------
//----------------------Fonction Auxilliaire------------------------------

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

        if(sA->get_adja()!=nullptr && sB->get_adja()!=nullptr)
                for(std::vector<Sommet*>::iterator it = sA->get_adja()->begin(); it!= sA->get_adja()->end(); ++it )
                {
                        if(*it!=nullptr && sB !=nullptr)
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
                if(s==INT_NULL)
                        break;
                setVisited_bool(true,s);


                for(int j=0; j<m_sommet->size(); j++)
                {

                        if(s!=INT_NULL)
                        {
                                if(chemin_a_ver_b(s,j))                           // Si il existe un chemin allant du sommet s a J
                                {

                                        for(std::vector<Sommet*>::iterator it=(*m_sommet)[s]->get_adja()->begin(); it != (*m_sommet)[s]->get_adja()->end(); ++it)               // Parcour les adjacents de s
                                        {
                                                if(*it ==  (*m_sommet)[j])              // Si on trouve J
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

                                                if(m_distance[s]+ poid_adj < m_distance[j])
                                                {
                                                        m_distance[j] = m_distance[s]+ poid_adj;
                                                        m_pred[j]=s;
                                                }
                                        }
                                }
                        }
                }

        }
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//-------------------Fonction Output fichier--------------------------------

void Centralisation::file_out_res_deg(std::string filename){

        std::ofstream file(filename);

        std::map<Sommet*,float>::iterator it;
        file << std::endl
             << "----------------------"
             <<std::endl
             << "centralité de degres"
             << std::endl
             << "--------------------"
             << std::endl;
        for(it= resultat_deg.begin(); it!=resultat_deg.end(); ++it)
        {
                if(it->first!=nullptr)
                {
                        file << "Sommet: " << it->first->get_nom()
                             << " Brute: "
                             << it->second
                             <<  " Normaliser: "
                             << it->second/(m_sommet->size()-1)
                             << std::endl;
                }
        }
        file << "---------------------" << std::endl;
}

void Centralisation::file_out_res_prox(std::string filename){

        std::ofstream file(filename);

        std::map<Sommet*,float>::iterator it;
        file << std::endl
             << "----------------------"
             <<std::endl
             << "centralité de Proximité"
             << std::endl
             << "--------------------"
             << std::endl;
        for(it= resultat_prox.begin(); it!=resultat_prox.end(); ++it)
        {
                if(it->first!=nullptr)
                {
                        file << "Sommet: " << it->first->get_nom()
                             << " Brute: "
                             << it->second
                             <<  " Normaliser: "
                             << it->second*(m_sommet->size()-1)
                             << std::endl;
                }
        }
        file << "---------------------" << std::endl;
}

void Centralisation::file_out_res_propre(std::string filename){

        std::ofstream file(filename);

        std::map<Sommet*,float>::iterator it;
        file << std::endl
             << "----------------------"
             <<std::endl
             << "centralité de vecteur propre"
             << std::endl
             << "--------------------"
             << std::endl;
        for(it= resultat_propre.begin(); it!=resultat_propre.end(); ++it)
        {
                if(it->first!=nullptr)
                {
                        file << "Sommet: " << it->first->get_nom()
                             << " Brute: "
                             << it->second
                             <<  " Normaliser: -"
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
}
