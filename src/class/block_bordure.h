#ifndef BLOCK_BORDURE_H_INCLUDED
#define BLOCK_BORDURE_H_INCLUDED

#include "block.h"
#include "block_bordure.h"
#include "bordure.h"


class BlockBordure : public Block, Bordure
{
    public:
        /// Constructeurs
        BlockBordure(double _classe, std::string _id, Coords _taille, Block* _Mere,Couleur _couleur,Bordure _bordure);
        BlockBordure();
};

#endif // BLOCK_BORDURE_H_INCLUDED

