#include "grille.hpp"

//Constructeur
Grille::Grille()
{
    int i=0,j=0;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            this->m_grille[i][j]="-";
        }
    }
};

//Déstructeur
Grille:: ~Grille(){

}

//Accesseurs
string Grille::getGrille(int i, int j)
{
    return this->m_grille[i][j];
}

void Grille::setGrille(int i, int j, string coord){
    this->m_grille[i][j] = coord;
}

//Sélectionne un nombre aléatoire parmi les nb nombres
int Grille::nbAleatoire(int nb)
{
    return rand()%nb;
}

//Teste si les coordonnées du navire entre dans la grille (retourne true si oui, false sinon)
bool Grille::testcoordonneesNavire(Navire *nav)
{
    bool test=true;
    switch(nav->getOrientation()){
    case haut:
        if((nav->getCoordonnees().y - nav->getTaille()+1) < 0){
            test=false;
        }
        break;
    case bas:
        if((nav->getCoordonnees().y + nav->getTaille()-1) >= N){
            test=false;
        }
        break;
    case gauche:
        if((nav->getCoordonnees().x - nav->getTaille()+1) < 0){
            test=false;
        }
        break;
    case droite:
        if((nav->getCoordonnees().x + nav->getTaille()-1) >= N){
            test=false;
        }
        break;
    }
    return test;
}

//Teste si un navire est déjà présent sur la grille à la même place (retourne false si oui, true sinon)
bool Grille::testNaviresurGrille(Navire *nav)
{
    int i(0),j(0);
    bool test=true;
    switch(nav->getOrientation()){
    case haut:
        for(i=nav->getCoordonnees().y,j=nav->getCoordonnees().x;i>(nav->getCoordonnees().y - nav->getTaille());i--){
            if(this->m_grille [i][j]=="X"){
                test=false;
            }
        }
        break;

    case bas:
        for(i=nav->getCoordonnees().y,j=nav->getCoordonnees().x;i<(nav->getCoordonnees().y + nav->getTaille());i++){
            if(this->m_grille [i][j]=="X"){
                test=false;
            }
        }
        break;

    case gauche:
        for(j=nav->getCoordonnees().x,i=nav->getCoordonnees().y;j>(nav->getCoordonnees().x - nav->getTaille());j--){
            if(this->m_grille [i][j]=="X"){
                test=false;
            }
        }
        break;

    case droite:
        for(j=nav->getCoordonnees().x,i=nav->getCoordonnees().y;j<(nav->getCoordonnees().x + nav->getTaille());j++){
            if(this->m_grille [i][j]=="X"){
            test=false;
            }
        }
        break;
    }
    return test;
}

//Placement des "X" sur la grille
void Grille::placeNavire(Navire *nav)
{
    int i=0,j=0;
    switch(nav->getOrientation()){
        case haut:
            for(i=nav->getCoordonnees().y,j=nav->getCoordonnees().x;i>(nav->getCoordonnees().y - nav->getTaille());i--){
                    this->m_grille[i][j]="X";
                    nav->setPlacementGrille(j,i,"X");
            }
            break;

        case bas:
            for(i=nav->getCoordonnees().y,j=nav->getCoordonnees().x;i<(nav->getCoordonnees().y + nav->getTaille());i++){
                    this->m_grille[i][j]="X";
                    nav->setPlacementGrille(j,i,"X");
            }
            break;

        case gauche:
            for(j=nav->getCoordonnees().x,i=nav->getCoordonnees().y;j>(nav->getCoordonnees().x - nav->getTaille());j--){
                    this->m_grille[i][j]="X";
                    nav->setPlacementGrille(j,i,"X");
            }
            break;

        case droite:
            for(j=nav->getCoordonnees().x,i=nav->getCoordonnees().y;j<(nav->getCoordonnees().x + nav->getTaille());j++){
                    this->m_grille[i][j]="X";
                    nav->setPlacementGrille(j,i,"X");
            }
            break;
    }
}

//Retourne le nom du navire en fonction de l'index donné en paramètre
string Grille::nomNavire(int n)
{
    string nom;
    switch (n){
        case 0: nom="PORTE_AVIONS";
                break;
        case 1: nom="CROISEUR";
                break;
        case 2: nom="CONTRE_TORPILLEURS";
                break;
        case 3: nom="SOUS_MARIN";
                break;
        case 4: nom="TORPILLEUR";
             break;
    }
    return nom;
}

//Retourne la taille du navire en fonction de l'index donné en paramètre
int Grille::tailleNavire(int n)
{
    int t=0;
    switch (n){
        case 0: t=5;
                break;
        case 1: t=4;
                break;
        case 2: t=3;
                break;
        case 3: t=3;
                break;
        case 4: t=2;
                break;
    }
    return t;
}

//Retourne l'orientation du navire en fonction de l'index donné en paramètre
orientation Grille::choixOrientation (int n)
{
    orientation o=haut;
    switch(n){
        case 0: o=haut; break;
        case 1: o=bas; break;
        case 2: o=gauche; break;
        case 3: o=droite; break;
    }
    return o;
}

//Génére et place aléatoirement les navires sur la grille
void Grille::initTabNavires(Navire tabNavires[NB_NAVIRES])
{
    coordonnees c_n;
    int i=0;
    for(i=0;i<NB_NAVIRES;i++)
    {
      Navire *n = new Navire(this->nomNavire(i),this->tailleNavire(i));
      do{
            c_n.x=this->nbAleatoire(N);
            c_n.y=this->nbAleatoire(N);
            n->setCoordonnees(c_n);
            n->setOrientation(this->choixOrientation(this->nbAleatoire(NB_ORIENTATION)));

        }while(!(this->testcoordonneesNavire(n) && this->testNaviresurGrille(n)));
        this->placeNavire(n);
        tabNavires[i]=(*n);
        delete n;
    }
}

//Initialise un tableau contenant toutes les tailles des navires présents sur la grille
void Grille::initTabTaille(int tabTaille[NB_NAVIRES],Navire tabNav[NB_NAVIRES])
{
    int i(0);
    for(i=0;i<NB_NAVIRES;i++)
    {
        tabTaille[i]=tabNav[i].getTaille();
    }
}
