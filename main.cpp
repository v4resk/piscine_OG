#include "graph.hpp"
#include "surcharge.hpp"
#include "central.hpp"
int main(int argc, char const *argv[]) {

        Graph a("reseau.txt", "ponderation.txt");
        Centralisation cent(&a);
        std::cout << a;

//-------------Prox------------------------
        cent.centra_prox();
        cent.centra_deg();
        cent.centra_propre();
        cent.afficher_prox();
//----------------------------------------
        a.creer_svg();

        //---------------------------------------------------------

        return 0;
}
