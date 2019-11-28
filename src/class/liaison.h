#ifndef LIAISON_H_INCLUDED
#define LIAISON_H_INCLUDED

#include "coords.h"

class Block;

class Liaison
{
protected :

    Coords m_refpos;
    Coords m_basepos;
    bool m_plan;

public :

    /// constructeurs
    Liaison(Coords _refpos, Coords _basepos, bool _plan3D);
    Liaison();
    ~Liaison() = default;

    /// getteurs et setteurs
    void setteur(Coords _refpos, Coords _basepos, bool _plan3D);
    Coords getBasepos() const;
    Coords getRefpos() const;
    bool getPlan() const;
};

///************************///
///    METHODES INLINES    ///
///************************///

inline Coords Liaison::getBasepos() const
{
    return m_basepos;
}


inline Coords Liaison::getRefpos() const
{
    return m_refpos;
}



inline bool Liaison::getPlan() const
{
    return m_plan;
}

#endif // LIAISON_H_INCLUDED

/// CLASS FILLE GLISSIERE

/*#ifndef LIAISON_G_H_INCLUDED
#define LIAISON_G_H_INCLUDED

#include "liaison.h"
class Liaison_g : public Liaison
{
private :
    Coords m_endpos;
    unsigned int m_refFille;
public :
    Liaison_g(Coords _refpos, Coords _endpos, unsigned int _refFille);
};

#endif // LIAISON_G_H_INCLUDED*/

