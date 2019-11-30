#ifndef BLOCK_CERCLE_BORDURE_H_INCLUDED
#define BLOCK_CERCLE_BORDURE_H_INCLUDED

#include "block_cercle.h"
#include "bordure.h"

class BlockCercleBordure : public BlockCercle, public Bordure
{
public :
    BlockCercleBordure(double _classe, std::string _id, double _rayon, Couleur _couleur, Couleur _bordure, Block* _Mere);
    BlockCercleBordure();

    void dessiner(Svgfile &svgout)const;
};

#endif // BLOCK_CERCLE_BORDURE_H_INCLUDED
