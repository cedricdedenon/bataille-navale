#include "utilisateur.hpp"

//Tableau contenant toutes les coordonnées pour la bataille navale
string tabchoixUtilisateur [N][N]={
    {"A1", "B1", "C1", "D1", "E1", "F1", "G1", "H1", "I1", "J1"},
    {"A2", "B2", "C2", "D2", "E2", "F2", "G2", "H2", "I2", "J2"},
    {"A3", "B3", "C3", "D3", "E3", "F3", "G3", "H3", "I3", "J3"},
    {"A4", "B4", "C4", "D4", "E4", "F4", "G4", "H4", "I4", "J4"},
    {"A5", "B5", "C5", "D5", "E5", "F5", "G5", "H5", "I5", "J5"},
    {"A6", "B6", "C6", "D6", "E6", "F6", "G6", "H6", "I6", "J6"},
    {"A7", "B7", "C7", "D7", "E7", "F7", "G7", "H7", "I7", "J7"},
    {"A8", "B8", "C8", "D8", "E8", "F8", "G8", "H8", "I8", "J8"},
    {"A9", "B9", "C9", "D9", "E9", "F9", "G9", "H9", "I9", "J9"},
    {"A10", "B10", "C10", "D10", "E10", "F10", "G10", "H10", "I10", "J10"}
};

//Constructeur
Utilisateur::Utilisateur()
{
    this->m_choixUtilisateur = "null";
}

//Destructeur
Utilisateur:: ~Utilisateur()
{

}

//Accesseur
void Utilisateur::setChoixUtilisateur(string choix)
{
    this->m_choixUtilisateur = choix;
}

//Teste si le choix de l'utilisateur est une coordonnée correcte (retourne true si oui, false sinon)
bool Utilisateur::testchoixUtilisateur()
{
    int i(0),j(0);
    bool test=false;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            if((this->m_choixUtilisateur.compare(tabchoixUtilisateur[i][j]))==0){
                test=true;
            }
        }
    }
    return test;
}

//Teste si le choix de l'utilisateur est déjà une coordonnée qu'il a précédemment entré (retourne true si oui, false sinon)
bool Utilisateur::testchoixUtilisateurIdentique(vector<string> TabchoixUtilisateurIdentique)
{
    unsigned int i(0);
    bool test=false;
    for(i=0;i<TabchoixUtilisateurIdentique.size();i++)
    {
        if(this->m_choixUtilisateur.compare(TabchoixUtilisateurIdentique[i])==0)
        {
            test=true;
        }
    }
    return test;
}

//Converti les coordonnées de l'utilisateur (type string) en coordonnées exploitables pour l'algorithme (type coordonnees)
coordonnees Utilisateur::choixUtilisateur()
{
    coordonnees coord;
    int i(0),j(0);
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            if((this->m_choixUtilisateur.compare(tabchoixUtilisateur[i][j]))==0){
                coord.x=j;
                coord.y=i;
            }
        }
    }
    return coord;
}

//Teste si les coordonnées de l'utilisateur permettent de "toucher" un navire de l'adversaire (retourne true si oui, false sinon)
bool Utilisateur::testCoordonnees(coordonnees coord, Grille *tabUtilisateur, Grille *grille)
{
    bool test=false;
   if(grille->getGrille(coord.y,coord.x)=="X"){
        tabUtilisateur->setGrille(coord.y,coord.x,"X");
        test=true;
    }
    return test;
}

//Teste si tous les navires de l'adversaire sont détruits (retourne true si oui, false sinon)
bool Utilisateur::partieTerminee(Navire tabNavires[NB_NAVIRES])
{
    unsigned int i(0),cpt(0);
    bool test=false;
    for(i=0;i<NB_NAVIRES;i++){
        if(tabNavires[i].getDestruction()==true){
            cpt++;
        }
    }

    if(cpt==NB_NAVIRES){
        test=true;
    }
    return test;
}
