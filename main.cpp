#include "graph.hpp"
#include "surcharge.hpp"
#include "central.hpp"

int main(int argc, char const *argv[])
{

        Graph a("guadeloupe.txt", "pondeguada.txt");
        Centralisation cent(&a);
        std::cout << a;

        a.creer_svg();

//-------------Prox------------------------
      //  cent.centra_prox();
        cent.centra_deg();
        cent.centra_propre();
        cent.afficher_prox();
//----------------------------------------


//-------------------------------------------

        return 0;
}
