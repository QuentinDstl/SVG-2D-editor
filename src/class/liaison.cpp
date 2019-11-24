#include <iostream>

#include "liaison.h"

/// Constructeur (reference de postion x, reference de postion y, position de base x, position de base y, bool : est il dans le plan)
Liaison::Liaison(Coords _refpos, Coords _basepos, bool _plan3D, Block* _Mere)
    : m_refpos{_refpos}, m_basepos{_basepos}, m_plan3D{_plan3D}, m_Mere{_Mere}
{}

/// Constructeur avec Initialisation nul
Liaison::Liaison()
    : m_refpos{0,0}, m_basepos{0,0}, m_plan3D{0}
{}



/// CLASS FILLE GLISSIERE

/*Liaison_g::Liaison_g(Coords _refpos, Coords _endpos, unsigned int _refFille) : Liaison{_refpos}, m_endpos {_endpos}, m_refFille {_refFille}
{ }*/



