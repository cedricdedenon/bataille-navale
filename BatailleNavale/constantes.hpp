#ifndef CONSTANTES_HPP
#define CONSTANTES_HPP

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
using namespace std;

const int N=10;
const int NB_ORIENTATION=4;
const int NB_NAVIRES=5;
const int TAILLE=10;

// NAVIRE (orientation + coordonnées)
typedef enum {
        haut=0, bas=1, gauche=2, droite=3} orientation;

struct coordonnees{
        int x;
        int y;
};
typedef coordonnees coordonnees;

// ORDINATEUR
//Structure pour une pseudo intelligence artificielle de l'ordinateur
struct AlgoIA{
        vector<string> tabAlgoIA;
        int index;
        int nb;
        bool flag;
};
typedef AlgoIA AlgoIA;

#endif // CONSTANTES_HPP
