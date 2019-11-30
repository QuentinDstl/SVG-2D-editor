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
};

#endif // BORDURE_H_INCLUDED
