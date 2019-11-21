#include <iostream>

#include "liaison.h"

/// Constructeur (reference de postion x, reference de postion y, position de base x, position de base y, bool : est il dans le plan)
Liaison::Liaison(double _refposX, double _refposY, double _baseposX, double _baseposY, bool _plan)
    : m_refpos{_refposX,_refposY}, m_basepos{_baseposX,_baseposY}, m_plan{_plan}
{}

/// Constructeur avec Initialisation nul
Liaison::Liaison()
    : m_refpos{0,0}, m_basepos{0,0}, m_plan{0}
{}

/// Initialisation (reference de postion x, reference de postion y, position de base x, position de base y)
void Liaison::initialiser(double _refposX, double _refposY, double _baseposX, double _baseposY)
{

    m_refpos.modifierX(_refposX);
    m_refpos.modifierY(_refposY);
    m_basepos.modifierX(_baseposX);
    m_basepos.modifierY(_baseposY);
}


Coords Liaison::getBasepos()
{

    return m_basepos;
}


Coords Liaison::getRefpos()
{

    return m_refpos;
}

/// CLASS FILLE GLISSIERE

/*Liaison_g::Liaison_g(Coords _refpos, Coords _endpos, unsigned int _refFille) : Liaison{_refpos}, m_endpos {_endpos}, m_refFille {_refFille}
{ }*/



