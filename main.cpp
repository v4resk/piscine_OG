#include "graph.hpp"
#include "surcharge.hpp"
#include "central.hpp"

int main(int argc, char const *argv[])
{

        Graph a("res.txt", "res_pond.txt");
        Centralisation cent(&a);
        std::cout << a;

//-------------Prox------------------------
        cent.centra_prox(); //NUL
        cent.centra_deg(); //Ok
        cent.centra_propre(); // A verifier
        //cent.centra_intermediaire(); // a faire
        cent.afficher_all();
        cent.file_out_res_all();
//----------------------------------------
        a.creer_svg();

//-------------------------------------------

        return 0;
}
