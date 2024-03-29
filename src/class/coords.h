#ifndef COORDS_H_INCLUDED
#define COORDS_H_INCLUDED

#include <iostream>

class Coords
{
private :

    double m_x;
    double m_y;

public :

    /// constructeurs
    Coords(double _x, double _y);
    Coords();

    /// aleatoire
    static Coords aleatoire(double amplitude);

    /// getteurs & setteurs
    void modifierX(double x);
    void modifierY(double y);
    double getX() const;
    double getY() const;

    /// Positions relatives
    bool estAGauche(const Coords& autre) const;
    bool estADroite(const Coords& autre) const;
    bool estAuDessus(const Coords& autre) const;
    bool estAuDessous(const Coords& autre) const;

    /// Operateurs vectoriels

    // Somme vectorielle
    friend Coords operator+(const Coords& c1, const Coords& c2);

    // Soustraction vectorielle
    friend Coords operator-(const Coords& c1, const Coords& c2);

    // Produit vectoriel
    friend double operator*(const Coords& c1, const Coords& c2);

    // Multiplication par un r�el
    friend Coords operator*(double m, const Coords& c);

    // Comparaison vectoriel
    friend bool operator<=(const Coords& c1, const Coords& c2);
    friend bool operator>=(const Coords& c1, const Coords& c2);
    friend bool operator==(const Coords& c1, const Coords& c2);

    // Affichage d'un Coords
    friend std::ostream& operator<<(std::ostream& out, const Coords& c);

};


#endif // COORDS_H_INCLUDED
