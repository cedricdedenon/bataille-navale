#ifndef NAVIRE_H
#define NAVIRE_H

#include "constantes.hpp"

class Navire
{
private:
    string m_nom;
    int m_taille;
    orientation m_orientation;
    coordonnees m_position;
    bool m_destruction;
    string m_placementGrille[N][N];

public:
    Navire();
    Navire(string n, int t);
    Navire(string n, int t, orientation o);
    Navire(string n, int t, orientation o, coordonnees c);
    ~Navire();

public:
    string getNom();
    void setNom(string n);
    int getTaille();
    void setTaille(int t);
    orientation getOrientation();
    void setOrientation(orientation o);
    coordonnees getCoordonnees();
    void setCoordonnees(coordonnees c);
    void setCoordonneesXY(int x, int y);
    bool getDestruction();
    void setDestruction (bool d);
    string getPlacementGrille(int x, int y);
    void setPlacementGrille(int x, int y, string data);
};

#endif // NAVIRE_H
