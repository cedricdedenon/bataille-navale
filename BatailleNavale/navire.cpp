#include "navire.hpp"

//Constructeurs
Navire::Navire()
{
    m_nom="";
    m_taille=3;
    m_orientation=droite;
    m_position.x=0;
    m_position.y=0;
    m_destruction=false;
}

Navire::Navire(string n, int t)
{
    m_nom=n;
    m_taille=t;
    m_destruction=false;
}

Navire::Navire(string n,int t, orientation o)
{
    m_nom=n;
    m_taille=t;
    m_orientation=o;
    m_position.x=0;
    m_position.y=0;
    m_destruction=false;
}

Navire::Navire(string n, int t, orientation o, coordonnees c)
{
    m_nom=n;
    m_taille=t;
    m_orientation=o;
    m_position.x=c.x;
    m_position.y=c.y;
    m_destruction=false;
}

//Destructeur
Navire:: ~Navire()
{

}

//Accesseurs
string Navire::getNom()
{
    return m_nom;
}

void Navire::setNom(string n)
{
    m_nom=n;
}

int Navire::getTaille()
{
    return m_taille;
}

void Navire::setTaille(int t)
{
    m_taille=t;
}

orientation Navire::getOrientation()
{
    return m_orientation;
}

void Navire::setOrientation(orientation o)
{
    m_orientation=o;
}

coordonnees Navire::getCoordonnees()
{
    return m_position;
}

void Navire::setCoordonnees(coordonnees c)
{
    m_position.x=c.x;
    m_position.y=c.y;
}

void Navire::setCoordonneesXY(int x, int y)
{
    m_position.x=x;
    m_position.y=y;
}

bool Navire::getDestruction()
{
    return m_destruction;
}

void Navire::setDestruction (bool d)
{
    m_destruction=d;
}

string Navire::getPlacementGrille(int x, int y)
{
    return m_placementGrille[y][x];
}

void Navire::setPlacementGrille(int x, int y, string data)
{
    m_placementGrille[y][x]=data;
}
