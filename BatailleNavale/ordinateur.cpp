#include "ordinateur.hpp"

//Tableau contenant toutes les coordonnées pour la bataille navale
string tabchoixOrdinateur [N][N]={
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

//Stocke toutes les coordonnées générée aléatoirement (de l'ordinateur) dans un tableau dynamique
vector<string> TabchoixOrdinateurIdentique;

//Constructeur
Ordinateur::Ordinateur()
{
    this->m_choixOrdinateur = "null";
}

//Destructeur
Ordinateur:: ~Ordinateur()
{
    this->videTabChoixOrdiIdentique();
}

//Accesseur
void Ordinateur::setChoixOrdinateur(string choix){
    this->m_choixOrdinateur = choix;
}

//Sélectionne un nombre aléatoire parmi les nb nombres
int Ordinateur::nbAleatoire(int nb)
{
    return rand()%nb;
}

//Génére aléatoirement une coordonnée correcte
string Ordinateur::CoordonneesAleaOrdi()
{
    srand(time(nullptr));
    int c_x(0),c_y(0);
    string choixOrdinateur;

    do{
        c_x=this->nbAleatoire(N);
        c_y=this->nbAleatoire(N);
        choixOrdinateur=tabchoixOrdinateur[c_y][c_x];
    }while(testchoixOrdinateurIdentique(choixOrdinateur,TabchoixOrdinateurIdentique));

    TabchoixOrdinateurIdentique.push_back(choixOrdinateur);
    return choixOrdinateur;
}

//Algorithme de l'intelligence artificielle. Si l'ordinateur touche l'adversaire, il testera ensuite
//successivement les coordonnées en haut, à gauche, en bas puis à droite de l'impact
string Ordinateur::AlgoIAOrdi(AlgoIA algo)
{
    coordonnees c;
    string cinter,cinit;

    do{
        cinit=algo.tabAlgoIA[algo.nb];
        this->m_choixOrdinateur = cinit;
        c = this->choixOrdinateur();

        switch(algo.index)
        {
            case 0: cinter=tabchoixOrdinateur[(c.y)-1][c.x];
                    algo.index++;
                    break;

            case 1: cinter=tabchoixOrdinateur[c.y][(c.x)-1];
                    algo.index++;
                    break;

            case 2: cinter=tabchoixOrdinateur[(c.y)+1][c.x];
                    algo.index++;
                    break;

            case 3: cinter=tabchoixOrdinateur[c.y][(c.x)+1];
                    algo.flag=true;
                    break;

            default: algo.flag=true;
        }

        if(algo.flag==true)
        {
            algo.flag=false;
            algo.index=0;
            algo.tabAlgoIA.pop_back();
            algo.nb--;
        }
    }while(testchoixOrdinateurIdentique(cinter,TabchoixOrdinateurIdentique));
    TabchoixOrdinateurIdentique.push_back(cinter);
    return cinter;
}

//Teste si le choix de l'ordinateur est une coordonnée correcte (retourne true si oui, false sinon)
bool Ordinateur::testchoixOrdinateur(string choixOrdinateur)
{
    unsigned int i(0),j(0);
    bool test=false;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            if((choixOrdinateur.compare(tabchoixOrdinateur[i][j]))==0){
                test=true;
            }
        }
    }
    return test;
}

//Teste si le choix de l'ordinateur est déjà une coordonnée qu'il a précédemment entrée (retourne true si oui, false sinon)
bool Ordinateur::testchoixOrdinateurIdentique(string choixOrdinateur,vector<string> TabchoixOrdinateurIdentique)
{
    unsigned int i(0);
    bool test=false;
    for(i=0;i<TabchoixOrdinateurIdentique.size();i++)
    {
        if(choixOrdinateur.compare(TabchoixOrdinateurIdentique[i])==0)
        {
            test=true;
        }
    }
    return test;
}

//Converti les coordonnées de l'ordinateur (type string) en coordonnées exploitables pour l'algorithme (type coordonnees)
coordonnees Ordinateur::choixOrdinateur()
{
    coordonnees coord;
    int i(0),j(0);
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            if((this->m_choixOrdinateur.compare(tabchoixOrdinateur[i][j]))==0){
                coord.x=j;
                coord.y=i;
            }
        }
    }
    return coord;
}

//Teste si les coordonnées de l'ordinateur permetten de "toucher" un navire de l'adversaire (retourne true si oui, false sinon)
bool Ordinateur::testCoordonneesOrdinateur(coordonnees coord,Grille *grille)
{
    bool test=false;
    if(grille->getGrille(coord.y,coord.x)=="X")
    {
        test=true;
    }
    return test;
}

//Place un 'X' sur la grille si l'ordinateur "a touché" l'adversaire
void Ordinateur::placeCoordonneesOrdinateur(coordonnees coord,Grille *tabOrdinateur,Grille *grille)
{
    if(grille->getGrille(coord.y,coord.x)=="X")
    {
        tabOrdinateur->setGrille(coord.y,coord.x,"X");
    }
}

//Désallocation dynamique
void Ordinateur::videTabChoixOrdiIdentique()
{
    while(TabchoixOrdinateurIdentique.size()!=0)
    {
        TabchoixOrdinateurIdentique.pop_back();
    }
}
