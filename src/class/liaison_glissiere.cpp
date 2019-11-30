#include "liaison_glissiere.h"

///*************************///
///      CONSTRUCTEURS      ///
///*************************///

/* Constructeur */
LiaisonGlissiere::LiaisonGlissiere(Coords _refpos, Coords _basepos, Coords _finbasepos, unsigned int _plan)
    : Liaison(_refpos, _basepos, _plan), m_finbasepos{_finbasepos}
{}

/* Constructeur avec Initialisation nul */
LiaisonGlissiere::LiaisonGlissiere()
    : Liaison(), m_finbasepos{0,0}
{}

///*************************///
///        SETTEURS         ///
///*************************///

/* Setteur de liaison avec glissiere */
void LiaisonGlissiere::setteurG(Coords _refpos, Coords _basepos, unsigned int _plan)
{
    setteur(_refpos,_basepos,_plan);
    m_plan = _plan;
}
