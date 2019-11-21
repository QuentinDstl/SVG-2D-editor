#include <iostream>

#include "liaison.h"

/*Liaison::Liaison(double _xRef, double _yRef) : m_refpos{_xRef, _yRef}
{ }*/


Liaison::Liaison()
: m_refpos{0,0}, m_refposMere{0,0}, memeplan{0}
{}


void Liaison::initialiser(double _refposMereX, double _refposMereY, double _refposX, double _refposY) {

    m_refposMere.modifierX(_refposMereX);
    m_refposMere.modifierY(_refposMereY);
    m_refpos.modifierX(_refposX);
    m_refpos.modifierY(_refposY);
}


Coords Liaison::getRefpos() {

    return m_refpos;
}


Coords Liaison::getRefposMere() {

    return m_refposMere;
}

/// CLASS FILLE GLISSIERE

/*Liaison_g::Liaison_g(Coords _refpos, Coords _endpos, unsigned int _refFille) : Liaison{_refpos}, m_endpos {_endpos}, m_refFille {_refFille}
{ }*/



