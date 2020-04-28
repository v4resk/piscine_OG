#include "graph.hpp"
#include "surcharge.hpp"
#include "central.hpp"

void menu(Graph& a,Centralisation& cent);
void load_file_text_menu(std::string& file, std::string& pond_file);
void logo_menu();

void menu_centra(bool& prox, bool& propre, bool& deg,Graph& a,Centralisation& cent);
void menu_output(bool& prox, bool propre, bool& deg,Graph& a,Centralisation& cent);


int main(int argc, char const *argv[])
{

        std::string name_file, name_pond;

        logo_menu();
        load_file_text_menu(name_file,name_pond);

        Graph a(name_file, name_pond);
        Centralisation cent(&a);
        std::cout << a;

        menu(a,cent);

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
                std::cout << std::endl << "Saisir le fichier du graph : ";
                std::cin >> pond_file;
                std::cin.ignore();

        } while(file.size()==0 || pond_file.size()==0);
}


void menu(Graph& a,Centralisation& cent)
{
        bool calculate_centra_prox(false);
        bool calculate_centra_propre(false);
        bool calculate_centra_deg(false);
        bool quitter(false);

        int choix(0);
        do {
                choix=0;
                std::cout << std::endl
                          << "1 - Calculate the centralisation" << std::endl
                          << "2 - Save centralisation " << std::endl
                          << "3 - Afficher le graph en consol" << std::endl
                          << "4 - Afficher le graph en svg" << std::endl
                          << "5 - Quit" << std::endl
                          << "> ";
                std::cin >> choix;

                switch (choix) {
                case 1:
                        menu_centra(calculate_centra_prox,calculate_centra_propre,calculate_centra_deg,a,cent);
                        break;
                case 2:
                        menu_output(calculate_centra_prox,calculate_centra_propre,calculate_centra_deg,a,cent);
                        break;
                case 3:
                        std::cout << a;
                        break;
                case 4:
                        a.creer_svg();
                        break;
                case 5:
                        quitter=true;
                        break;
                default:
                        std::cerr << "Erreur dans le choix" << std::endl;
                        break;
                }
        }
        while(!quitter);
}

void menu_centra(bool& prox, bool& propre, bool& deg,Graph& a,Centralisation& cent)
{
        bool precedent=false;

        std::cout << std::endl << "-------------------------------------" << std::endl;
        std::cout << "MENU DES SAUVEGARDES"
                  << std::endl <<"--------------------------------------" << std::endl;
        int choix(0);
        do {
                choix =0;
                std::cout << std::endl
                          << "1 - Calcul centraliter de vecteur propre" << std::endl
                          << "2 - Calcul centraliter de degres" << std::endl
                          << "3 - Calcul centraliter de proximite" << std::endl
                          << "4 - Tout calculer" << std::endl
                          << "5 - Precedent" << std::endl
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
                        cent.centra_all();
                        cent.afficher_all();
                        prox=true;
                        propre=true;
                        deg=true;
                        break;
                case 5:
                        precedent=true;
                        break;
                default:
                        std::cerr << "Erreur dans le choix" << std::endl;
                        break;

                }

        } while(!precedent);

}
void menu_output(bool& prox, bool propre, bool& deg,Graph& a,Centralisation& cent)
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
                          << "4 - Tout sauvegarder" << std::endl
                          << "5 - Precedent" << std::endl
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
                        if(propre && deg && prox) {
                                cent.file_out_res_all();
                                std::cout <<std::endl << "...Done";
                        }
                        else
                                std::cout << std::endl
                                          <<"Erreur: calculer avant de sauvegarder"<<std::endl;
                        break;
                case 5:
                        precedent=true;
                        break;
                default:
                        std::cerr << "Erreur dans le choix" << std::endl;
                        break;

                }

        } while(!precedent);
}
