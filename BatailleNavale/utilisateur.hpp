#ifndef UTILISATEUR_HPP
#define UTILISATEUR_HPP

#include "navire.hpp"
#include "grille.hpp"

class Utilisateur{
private:
    string m_choixUtilisateur;

public:
    Utilisateur();
    ~Utilisateur();

public:
    void setChoixUtilisateur(string choix);
    bool testchoixUtilisateur();
    bool testchoixUtilisateurIdentique(vector<string> TabchoixUtilisateurIdentique);
    coordonnees choixUtilisateur();
    bool testCoordonnees(coordonnees coord,Grille *tabUtilisateur,Grille *grille);
    bool partieTerminee(Navire tabNavires[NB_NAVIRES]);
};

#endif // UTILISATEUR_HPP
