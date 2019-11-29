#ifndef BORDURE_H_INCLUDED
#define BORDURE_H_INCLUDED

#include "../interface/couleur.h"

class Bordure
{
    protected :
        Couleur m_bordure;

    public :
        /// Constructeurs
        Bordure(Couleur _bordure);
        Bordure();
        virtual Couleur getBordure () const;
};

///************************///
///    METHODES INLINES    ///
///************************///

inline Couleur Bordure::getBordure() const
{
    return m_bordure;
}

#endif // BORDURE_H_INCLUDED