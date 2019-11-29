#include <iostream>

#include "liaison.h"
#include "coords.h"

///*************************///
///      CONSTRUCTEURS      ///
///*************************///

/* Constructeur */
// prend en parametre :
//(reference de postion x, reference de postion y, position de base x, position de base y, bool : est il dans le plan)
Liaison::Liaison(Coords _refpos, Coords _basepos, bool _plan)
: m_refpos{_refpos}, m_basepos{_basepos}, m_plan{_plan}
{}

/* Constructeur avec Initialisation nul */
Liaison::Liaison()
: m_refpos{0,0}, m_basepos{0,0}, m_plan{0}
{}

///*************************///
///        SETTEURS         ///
///*************************///

void Liaison::setteur(Coords _refpos, Coords _basepos, bool _plan)
{
    m_refpos = _refpos;
    m_basepos = _basepos;
    m_plan = _plan;
}

/// CLASS FILLE GLISSIERE

/*Liaison_g::Liaison_g(Coords _refpos, Coords _endpos, unsigned int _refFille) : Liaison{_refpos}, m_endpos {_endpos}, m_refFille {_refFille}
{ }*/



