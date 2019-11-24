#include "coords.h"
#include "../util/util.h"
#include <iostream>

Coords::Coords(double _x, double _y)
    : m_x{_x}, m_y{_y}
{}

Coords::Coords()
    : m_x{0}, m_y{0}
{}

Coords Coords::aleatoire(double amplitude)
{
    return { util::alea(-amplitude, amplitude),
             util::alea(-amplitude, amplitude) };
}

void Coords::afficher() const
{
    std::cout << "(" << m_x << ", " << m_y << ")";
}

void Coords::modifierX(double x)
{

    m_x = x;
}


void Coords::modifierY(double y)
{

    m_y = y;
}


double Coords::getX() const
{
    return m_x;
}

double Coords::getY() const
{
    return m_y;
}

/// Positions relatives
bool Coords::estAGauche(const Coords& autre) const
{
    return m_x < autre.m_x;
}

bool Coords::estADroite(const Coords& autre) const
{
    return m_x > autre.m_x;
}

bool Coords::estAuDessus(const Coords& autre) const
{
    return m_y < autre.m_y;
}

bool Coords::estAuDessous(const Coords& autre) const
{
    return m_y > autre.m_y;
}


/// Somme vectorielle
Coords operator+(const Coords& c1, const Coords& c2)
{
    return { c1.m_x + c2.m_x, c1.m_y + c2.m_y };
}

/// Soustraction vectorielle
Coords operator-(const Coords& c1, const Coords& c2)
{
    return { c1.m_x - c2.m_x, c1.m_y - c2.m_y };
}


/// Produit vectoriel
double operator*(const Coords& c1, const Coords& c2)
{
    return c1.m_x*c2.m_x + c1.m_y*c2.m_y ;
}

/// Multiplication par un réel
Coords operator*(double m, const Coords& c)
{
    return { m*c.m_x, m*c.m_y };
}


/// Test de comparaison (inferieur ou egal) entre 2 coords
bool operator<=(const Coords& c1, const Coords& c2)
{
    if(c1.m_x <= c2.m_x && c1.m_y <= c2.m_y) {
        return 1;
    }
    else {
        return 0;
    }
}

bool operator>=(const Coords& c1, const Coords& c2)
{
    if(c1.m_x >= c2.m_x && c1.m_y >= c2.m_y) {
        return 1;
    }
    else {
        return 0;
    }
}



/// Affichage d'un Coords
std::ostream& operator<<(std::ostream& out, const Coords& c)
{
    out << "{" << c.m_x << "," << c.m_y << "}";
    return out;
}
