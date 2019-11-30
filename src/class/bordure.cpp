#include "bordure.h"
#include "../svg/svgfile.h"
#include "../util/util.h"
#include <iostream>

///*************************///
///      CONSTRUCTEURS      ///
///*************************///

Bordure::Bordure(Couleur _bordure)
    : m_bordure{_bordure}, m_largeur{LARGEUR_BORDURE}
{}

Bordure::Bordure()
    : m_bordure{0, 0, 0}, m_largeur{LARGEUR_BORDURE}
{}
