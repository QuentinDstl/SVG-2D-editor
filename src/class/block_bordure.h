#ifndef BLOCK_BORDURE_H_INCLUDED
#define BLOCK_BORDURE_H_INCLUDED

#include "block.h"
#include "bordure.h"


class BlockBordure : public Block, public Bordure
{
public:
    /// Constructeurs
    BlockBordure(double _classe,std::string _id, Coords _taille, Couleur _couleur, Bordure _bordure, Block* _Mere);
    BlockBordure();

    void dessiner(Svgfile & svgout)const;
};

#endif // BLOCK_BORDURE_H_INCLUDED

//class BlockBordureGlissire : public BlockBordure, public liasion
