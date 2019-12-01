#ifndef LIAISON_GLISSIERE_H_INCLUDED
#define LIAISON_GLISSIERE_H_INCLUDED

#include "liaison.h"

class LiaisonGlissiere : public Liaison
{
protected :
    Coords m_finbasepos;
public :

    /// constructeurs
    LiaisonGlissiere(Coords _refpos, Coords _basepos, Coords _finbasepos, unsigned int _plan);
    LiaisonGlissiere();

    /// getteurs et setteurs
    virtual Coords getFinbasepos();
    virtual void setteurG(Coords _refpos, Coords _basepos, unsigned int _plan);

};

///************************///
///    METHODES INLINES    ///
///************************///

inline Coords LiaisonGlissiere::getFinbasepos()
{
    return m_finbasepos;
}
#endif // LIAISON_GLISSIERE_H_INCLUDED
