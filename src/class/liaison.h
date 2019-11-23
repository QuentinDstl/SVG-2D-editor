#ifndef LIAISON_H_INCLUDED
#define LIAISON_H_INCLUDED

#include "coords.h"

class Liaison
{
protected :
    Coords m_refpos;
    Coords m_basepos;

    bool m_plan;

public :
    Liaison(double _refposX, double _refposY, double _baseposX, double _baseposY, bool _plan);
    Liaison();
    ~Liaison() = default;

    void initialiser(double _refposX, double _refposY, double _baseposX, double _baseposY);

    Coords getBasepos();
    Coords getRefpos();
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
