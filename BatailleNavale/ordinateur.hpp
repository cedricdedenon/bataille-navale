#ifndef ORDINATEUR_HPP
#define ORDINATEUR_HPP

#include "navire.hpp"
#include "grille.hpp"

class Ordinateur{
private:
    string m_choixOrdinateur;

public:
    Ordinateur();
    ~Ordinateur();

public:
    void setChoixOrdinateur(string choix);
    int nbAleatoire(int nb);
    string CoordonneesAleaOrdi();
    string AlgoIAOrdi(AlgoIA algo);
    bool testchoixOrdinateur(string choixOrdinateur);
    bool testchoixOrdinateurIdentique(string choixOrdinateur,vector<string> TabchoixOrdinateurIdentique);
    coordonnees choixOrdinateur();
    bool testCoordonneesOrdinateur(coordonnees coord,Grille *grille);
    void placeCoordonneesOrdinateur(coordonnees coord,Grille *tabOrdinateur,Grille *grille);
    void videTabChoixOrdiIdentique();
};

#endif // ORDINATEUR_HPP
