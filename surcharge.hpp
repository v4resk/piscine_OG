#ifndef SURCH
#define SURCH

#include "graph.hpp"


std::ostream &operator<<(std::ostream& flux, Graph& racine)
{
        racine.afficher(flux);
        flux << std::endl;
        return flux;
}

#endif
