#ifndef BORDURE_H_INCLUDED
#define BORDURE_H_INCLUDED

#include "../interface/couleur.h"

#define LARGEUR_BORDURE 1

class Bordure
{
protected :
    Couleur m_bordure;
    double m_largeur;

public :
    /// Constructeurs
    Bordure(Couleur _bordure);
    Bordure();

    virtual ~Bordure()=default;

    virtual Couleur getBordure();
    virtual double getLargeur();
};

///************************///
///    METHODES INLINES    ///
///************************///

inline Couleur Bordure::getBordure()
{
    return m_bordure;
}

inline double Bordure::getLargeur()
{
    return m_largeur;
}

#endif // BORDURE_H_INCLUDED
