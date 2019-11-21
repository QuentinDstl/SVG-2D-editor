#ifndef COORDS_H_INCLUDED
#define COORDS_H_INCLUDED

class Coords
{
    private :
        double m_x;
        double m_y;
    public :
        Coords(double _x, double _y);
        Coords();

        static Coords aleatoire(double amplitude);

        void afficher() const;
        void modifierX(double x);
        void modifierY(double y);

        double getX() const;
        double getY() const;

        /// Positions relatives
        bool estAGauche(const Coords& autre) const;
        bool estADroite(const Coords& autre) const;
        bool estAuDessus(const Coords& autre) const;
        bool estAuDessous(const Coords& autre) const;

        /// Somme vectorielle
        friend Coords operator+(const Coords& c1, const Coords& c2);

        /// Soustraction vectorielle
        friend Coords operator-(const Coords& c1, const Coords& c2);

        /// Produit vectoriel
        friend double operator*(const Coords& c1, const Coords& c2);

        /// Multiplication par un réel
        friend Coords operator*(double m, const Coords& c);

};


#endif // COORDS_H_INCLUDED
