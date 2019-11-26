#include "coords.h"
#include "../util/util.h"
#include <iostream>

///*************************///
///      CONSTRUCTEURS      ///
///*************************///

/* Constructeur */
Coords::Coords(double _x, double _y)
    : m_x{_x}, m_y{_y}
{}

/* Constructeur avec initialisation a 0 */
Coords::Coords()
    : m_x{0}, m_y{0}
{}

///*************************///
///  ALEATOIRE & AFFICHAGE  ///
///*************************///

// NOTE (qdesa#3#11/26/19): a virer si c'est pas utilise
/* Creation de coordonees aleatoires */
Coords Coords::aleatoire(double amplitude)
{
    return { util::alea(-amplitude, amplitude),
             util::alea(-amplitude, amplitude) };
}

// FIXME (qdesa#2#11/26/19): premiere technique d'affichage de coords
/* affichage de Coords*/
void Coords::afficher() const
{
    std::cout << "(" << m_x << ", " << m_y << ")";
}

///*************************///
///   GETTEURS & SETTEURS   ///
///*************************///

/* setteur de m_x */
void Coords::modifierX(double x)
{
    m_x = x;
}

/* setteur de m_y */
void Coords::modifierY(double y)
{
    m_y = y;
}

/* getteur de m_x */
double Coords::getX() const
{
    return m_x;
}

/* getteur de m_y */
double Coords::getY() const
{
    return m_y;
}

///*************************///
///   POSITIONS RELATIVES   ///
///*************************///

/* position a gauche de autre */
bool Coords::estAGauche(const Coords& autre) const
{
    return m_x < autre.m_x;
}

/* position a droite de autre */
bool Coords::estADroite(const Coords& autre) const
{
    return m_x > autre.m_x;
}

/* position au dessus de autre */
bool Coords::estAuDessus(const Coords& autre) const
{
    return m_y < autre.m_y;
}

/* position au dessous de autre */
bool Coords::estAuDessous(const Coords& autre) const
{
    return m_y > autre.m_y;
}

///*************************///
///  OPERATIONS VECTORIELS  ///
///*************************///

/* Somme vectorielle */
Coords operator+(const Coords& c1, const Coords& c2)
{
    return { c1.m_x + c2.m_x, c1.m_y + c2.m_y };
}

/* Soustraction vectorielle */
Coords operator-(const Coords& c1, const Coords& c2)
{
    return { c1.m_x - c2.m_x, c1.m_y - c2.m_y };
}


/* Produit vectoriel */
double operator*(const Coords& c1, const Coords& c2)
{
    return c1.m_x*c2.m_x + c1.m_y*c2.m_y ;
}

/* Multiplication par un réel */
Coords operator*(double m, const Coords& c)
{
    return { m*c.m_x, m*c.m_y };
}


/* Comparaison vectoriel (<=) */
bool operator<=(const Coords& c1, const Coords& c2)
{
    if(c1.m_x <= c2.m_x && c1.m_y <= c2.m_y)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/* Comparaison vectoriel (>=) */
bool operator>=(const Coords& c1, const Coords& c2)
{
    if(c1.m_x >= c2.m_x && c1.m_y >= c2.m_y)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

///*************************///
///  AFFICHAGE D'UN COORDS  ///
///*************************///

// FIXME (qdesa#2#11/26/19): deuxieme technique d'affichage de coords
/* Affichage d'un coords */
std::ostream& operator<<(std::ostream& out, const Coords& c)
{
    out << "{" << c.m_x << "," << c.m_y << "}";
    return out;
}
