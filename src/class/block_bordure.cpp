#include "block_bordure.h"

BlockBordure::BlockBordure(double _classe,std::string _id, Coords _taille, Block* _Mere,Couleur _couleur, Bordure _bordure)
: Block{_classe, _id, _taille, _couleur, _Mere}, Bordure{_bordure}
{}

/* Constructeur avec Initialisation nul */
BlockBordure::BlockBordure()
: Block{}, Bordure{}
{}
