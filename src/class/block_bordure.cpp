#include "block_bordure.h"

BlockBordure::BlockBordure(double _classe,std::string _id, Coords _taille, Couleur _couleur, Bordure _bordure, Block* _Mere)
    : Block{_classe, _id, _taille, _couleur, _Mere}, Bordure{_bordure}
{}

/* Constructeur avec Initialisation nul */
BlockBordure::BlockBordure()
    : Block{}, Bordure{}
{}


void BlockBordure::dessiner(Svgfile & svgout)const
{
    svgout.addRectangle(m_origine.getX(), m_origine.getY(),
                        m_origine.getX(), m_origine.getY() + m_taille.getY(),
                        m_origine.getX() + m_taille.getX(), m_origine.getY(),
                        m_origine.getX() + m_taille.getX(), m_origine.getY() + m_taille.getY(),
                        m_couleur, 2, m_bordure);
}
