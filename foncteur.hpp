/*#ifndef FONCTEUR
 #define FONCTEUR

 #include <iostream>
 #include <string>
 #include <vector>
 #include <algorithm>
 #include "sommet.hpp"

   //------------------------------------------------------------------------------------------
   class remplir_kruskal_init
   {
   public:
   remplir_kruskal_init() : n(0){

   }
   void operator()(Sommet* s)
   {
        s->set_numCC(n);
        n++;
   }
   private:
   int n;
   };
   //---------------------------------------------------------------------------------------
   class comparaison_poid
   {
   public:
   bool operator()(const std::pair<std::pair<Sommet*,Sommet*>,int>& a, const std::pair<std::pair<Sommet*,Sommet*>,int>& b)
   {
        return a.second < b.second;
   }

   private:
   };
   //-------------------------------------------------------------------------
   class ajust_numCC
   {
   public:

   ajust_numCC(int a, int b) : numCC_sJ(a), numCC_sI(b){
   }

   void operator()(Sommet* s)
   {
        if (s->get_numCC()==numCC_sJ)
        {
                s->set_numCC(numCC_sI);
        }
   }
   private:
   int numCC_sJ,numCC_sI;
   };
   //---------------------------------------------------

   class compteurPoidTot
   {
   public:
   compteurPoidTot() : poidTot(0){
   }

   void operator()(std::pair<std::pair<Sommet*,Sommet*>,int>&  a)
   {
        poidTot+= a.second;
   }
   int poidTot;

   };

 #endif */
