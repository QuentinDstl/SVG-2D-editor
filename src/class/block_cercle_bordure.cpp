#include "block_cercle_bordure.h"

///constructeurs
BlockCercleBordure::BlockCercleBordure(double _classe, std::string _id, double _rayon, Couleur _couleur, Couleur _bordure, Block* _Mere)
    : BlockCercle(_classe, _id, _rayon, _couleur, _Mere), Bordure{_bordure}
{}

BlockCercleBordure::BlockCercleBordure()
    : BlockCercle(), Bordure()
{}

/// dessiner
void BlockCercleBordure::dessiner(Svgfile &svgout)const
{
    svgout.addDisk(m_origine.getX(), m_origine.getY(),m_taille.getX()-0.6, m_couleur);
    svgout.addCircle(m_origine.getX(), m_origine.getY(),m_taille.getX()-0.6, m_largeur, m_bordure);
}
