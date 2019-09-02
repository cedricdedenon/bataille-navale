#ifndef GRILLE_HPP
#define GRILLE_HPP

#include "navire.hpp"
#include "constantes.hpp"

class Grille{
private:
    string m_grille[N][N];

public:
    Grille();
    ~Grille();

public:
    string getGrille(int i,int j);
    void setGrille(int i, int j, string coord);
    int nbAleatoire(int nb);
    bool testcoordonneesNavire(Navire *nav);
    bool testNaviresurGrille(Navire *nav);
    string nomNavire(int n);
    int tailleNavire(int n);
    orientation choixOrientation (int n);
    void placeNavire(Navire *nav);
    void initTabNavires(Navire tabNavires[NB_NAVIRES]);
    void initTabTaille(int tabTaille[NB_NAVIRES],Navire tabNavires[NB_NAVIRES]);
};

#endif // GRILLE_HPP
