#include "graph.hpp"
#include "surcharge.hpp"
#include "central.hpp"
#include "vulnerabilite.hpp"

void menu(Graph& a,Centralisation& cent);
void load_file_text_menu(std::string& file, std::string& pond_file);
void logo_menu();

void menu_centra(bool& prox, bool& propre, bool& deg,bool& inter,Graph& a,Centralisation& cent);
void menu_output(bool& prox, bool propre, bool& deg,bool& inter,Graph& a,Centralisation& cent);


int main(int argc, char const *argv[])
{

        std::string name_file, name_pond;
        logo_menu();
        load_file_text_menu(name_file,name_pond);

        Graph a(name_file, name_pond);
        //  Connexite(&a);
        Centralisation cent(&a);
        menu(a,cent);

/*
        Graph a("res.txt", "res_pond.txt");
        Centralisation cent(&a);
        std::cout << a;
        cent.centra_all();
        cent.afficher_all();
        a.creer_svg((std::map<Sommet*,float> &)cent.get_res_deg(),(std::map<Sommet*,float> &)cent.get_res_prox(),(std::map<Sommet*,float> &)cent.get_res_inter(),(std::map<Sommet*,float> &)cent.get_res_propre());
        //kconnexite(&a,&cent); */


        return 0;
}

void logo_menu(){

        std::cout

                <<"\t"    <<" ____                 _              ____                 _" <<std::endl
                <<"\t"    <<"/ ___|_   _  __ _  __| | __ _       / ___|_ __ __ _ _ __ | |__"  <<std::endl
                <<"\t"    <<"| |  _| | | |/ _` |/ _` |/ _` |_____| |  _| '__/ _` | '_ \\| '_ \\" <<std::endl
                <<"\t"    <<"| |_| | |_| | (_| | (_| | (_| |_____| |_| | | | (_| | |_) | | | |"<<std::endl
                <<"\t"    <<"\\____|\\__,_|\\__,_|\\__,_|\\__,_|      \\____|_|  \\__,_| .__/|_| |_|" <<std::endl
                <<"\t"    <<"                                                  |_|          "<< std::endl << std::endl;

        std::cout <<"\t"    <<"---------------------------------------------------------------------" << std::endl;

}

void load_file_text_menu(std::string& file, std::string& pond_file)
{

        std::cout << "1 - Load_file" <<std::endl;
        do {

                std::cout << "Saisir le fichier du graph : ";
                std::cin >> file;
                std::cin.ignore();
                std::cout << std::endl << "Saisir le fichier de ponderation correspondant du graph : ";
                std::cin >> pond_file;
                std::cin.ignore();

        } while(file.size()==0 || pond_file.size()==0);
}


void menu(Graph& a,Centralisation& cent)
{
        bool calculate_centra_prox(false);
        bool calculate_centra_propre(false);
        bool calculate_centra_deg(false);
        bool calculate_centra_inter(false);
        bool quitter(false);
        std::ofstream b("graph.txt");

        int choix(0);
        do {
                choix=0;
                std::cout << std::endl
                          << "1 - Calculer la centralisation" << std::endl
                          << "2 - Sauvegarder la centralisation " << std::endl
                          << "3 - Sauvegarder le graph" << std::endl
                          << "4 - Afficher le graph en console" << std::endl
                          << "5 - Afficher le graph en svg" << std::endl
                          << "6 - Supprimer une arete" << std::endl
                          << "7 - Afficher la connexite" << std::endl
                          << "8 - Quit" << std::endl
                          << "> ";
                std::cin >> choix;

                switch (choix) {
                case 1:
                        menu_centra(calculate_centra_prox,calculate_centra_propre,calculate_centra_deg,calculate_centra_inter,a,cent);
                        break;
                case 2:
                        menu_output(calculate_centra_prox,calculate_centra_propre,calculate_centra_deg,calculate_centra_inter,a,cent);
                        break;
                case 3:
                        b << a;
                        std::cout << "....Done" << std::endl;
                        break;
                case 4:
                        std::cout << a;
                        break;
                case 5:
                        if(calculate_centra_deg)
                                a.creer_svg((std::map<Sommet*,float> &)cent.get_res_deg(),(std::map<Sommet*,float> &)cent.get_res_prox(),(std::map<Sommet*,float> &)cent.get_res_inter(),(std::map<Sommet*,float> &)cent.get_res_propre());
                        else
                                std::cout << "Erreur : Pour creer le fichier SVG calculer au moins la centralite de degres" << std::endl << std::endl;
                        break;
                case 6:
                        delete_arete(a.get_tab_arete());
                        std::cout << "....Done" << std::endl;
                        break;

                case 7:
                        Connexite(&a);
                        break;
                case 8:
                        quitter=true;
                        break;
                default:
                        std::cerr << "Erreur dans le choix" << std::endl;
                        break;
                }
        }
        while(!quitter);
}

void menu_centra(bool& prox, bool& propre, bool& deg,bool& inter,Graph& a,Centralisation& cent)
{
        bool precedent=false;

        std::cout << std::endl << "-------------------------------------" << std::endl;
        std::cout << "MENU DES CENTRALITES"
                  << std::endl <<"--------------------------------------" << std::endl;
        int choix(0);
        do {
                choix =0;
                std::cout << std::endl
                          << "1 - Calcul centralite de vecteur propre" << std::endl
                          << "2 - Calcul centralite de degres" << std::endl
                          << "3 - Calcul centralite de proximite" << std::endl
                          << "4 - Calcul centralite intermediaire" << std::endl
                          << "5 - Tout calculer" << std::endl
                          << "6 - afficher la centralite global" << std::endl
                          << "7 - Precedent" << std::endl
                          << "> ";
                std::cin >> choix;

                switch (choix) {
                case 1:
                        cent.centra_propre();
                        cent.afficher_res_propre();
                        propre=true;
                        break;
                case 2:
                        cent.centra_deg();
                        cent.afficher_res_deg();
                        deg=true;
                        break;
                case 3:
                        cent.centra_prox();
                        cent.afficher_res_prox();
                        prox=true;
                        break;
                case 4:
                        cent.centra_inter();
                        cent.afficher_res_inter();
                        inter=true;
                case 5:
                        cent.centra_all();
                        cent.afficher_all();
                        prox=true;
                        propre=true;
                        deg=true;
                        inter=true;
                        break;
                case 6:
                        if(inter && deg && propre && prox)
                                vulnerabiliteGlobal(&a,cent);
                        else
                                std::cout << "Erreur: calcule toutes les centralisations avant" << std::endl << std::endl;
                        break;
                case 7:
                        precedent=true;
                        break;
                default:
                        std::cerr << "Erreur dans le choix" << std::endl;
                        break;

                }

        } while(!precedent);

}
void menu_output(bool& prox, bool propre, bool& deg,bool& inter,Graph& a,Centralisation& cent)
{
        bool precedent=false;

        std::cout << std::endl << "-------------------------------------" << std::endl;
        std::cout << "MENU DES CENTRALITE"
                  << std::endl <<"--------------------------------------" << std::endl;
        int choix(0);
        do {
                choix =0;
                std::cout << std::endl
                          << "1 - sauvegarder centraliter de vecteur propre" << std::endl
                          << "2 - sauvegarder centraliter de degres" << std::endl
                          << "3 - sauvegarder centraliter de proximite" << std::endl
                          << "4 - sauvegarder centraliter intermediaire" << std::endl
                          << "5 - Tout sauvegarder" << std::endl
                          << "6 - Precedent" << std::endl
                          << "> ";
                std::cin >> choix;

                switch (choix) {
                case 1:
                        if(propre) {
                                cent.file_out_res_propre();
                                std::cout <<std::endl << "...Done";
                        }
                        else
                                std::cout << std::endl
                                          <<"Erreur: calculer avant de sauvegarder" << std::endl;
                        break;
                case 2:
                        if(deg) {
                                cent.file_out_res_deg();
                                std::cout <<std::endl << "...Done";
                        }
                        else
                                std::cout << std::endl
                                          <<"Erreur: calculer avant de sauvegarder"<<std::endl;
                        break;
                case 3:
                        if(prox) {
                                cent.file_out_res_prox();
                                std::cout <<std::endl << "...Done";
                        }
                        else
                                std::cout << std::endl
                                          <<"Erreur: calculer avant de sauvegarder"<<std::endl;
                        break;
                case 4:
                        if(inter) {
                                cent.file_out_res_inter();
                                std::cout <<std::endl << "...Done";
                        }
                        else
                                std::cout << std::endl
                                          <<"Erreur: calculer avant de sauvegarder"<<std::endl;
                        break;
                case 5:
                        if(propre && deg && prox) {
                                cent.file_out_res_all();
                                std::cout <<std::endl << "...Done";
                        }
                        else
                                std::cout << std::endl
                                          <<"Erreur: calculer avant de sauvegarder"<<std::endl;
                        break;
                case 6:
                        precedent=true;
                        break;
                default:
                        std::cerr << "Erreur dans le choix" << std::endl;
                        break;

                }

        } while(!precedent);
}
