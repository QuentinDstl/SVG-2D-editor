#include "block_cercle.h"
#include <math.h>

#define PI 3.1415926535

///*************************///
///       OVERWRITING       ///
///*************************///

/// constructeurs
BlockCercle::BlockCercle(double _classe, std::string _id, double _rayon, Block* _Mere,Couleur _couleur) : Block(_classe, _id, {_rayon,0}, _Mere,_couleur)
{ }
BlockCercle::BlockCercle() : Block()
{ }

void BlockCercle::initialiserLiaison(double _angle, Coords _basepos, bool _plan3D)
{
    m_liaison.setteur({m_origine.getX() + m_taille.getX()*cos(_angle*(PI/180)),m_origine.getY() + m_taille.getX()*sin(_angle*(PI/180))},_basepos,_plan3D);
}

/// dessiner
void BlockCercle::dessiner(Svgfile &svgout)const
{
    svgout.addDisk(m_origine.getX(), m_origine.getY(),m_taille.getX(),"grey");
}

/// test
bool BlockCercle::TestRefPos()const
{
    return 0;
}
