#ifndef LIAISON_H_INCLUDED
#define LIAISON_H_INCLUDED

#include "coords.h"

class Liaison
{
protected :
    Coords m_refposMere;
    Coords m_refpos;

    bool memeplan;

public :
    //Liaison(Coords _refpos);
    Liaison();
    ~Liaison() = default;

    void initialiser(double _refposMereX, double _refposMereY, double _refposX, double _refposY);

    Coords getRefpos();
    Coords getRefposMere();
};

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
