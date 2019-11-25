#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED

#include <vector>
#include <iostream>

#include "liaison.h"
#include "../svg/svgfile.h"

class Block
{
protected :
    std::string m_id;
    std::vector <Block*> m_Filles;
    Coords m_origine;
    Coords m_taille;

    Liaison *m_liaison;
    Block* m_Mere;

    //Couleur m_bordure
    //Couleur m_couleur
public :
    Block(std::string _id, Coords _taille, Block* _Mere);
    Block();

    ~Block()=default;

    void ajouterFille(Coords _taille, std::string _id, Coords _refpos, Coords _basepos, bool _plan3D);
    void initialiser(Coords _taille, std::string _id);
    void initialiserLiaison(Coords _refpos, Coords _basepos, bool _plan3D);
    void initialiserOrigine();

    Block* getFille(unsigned int indice)const;
    Coords getTaille()const;
    Coords getOrigine()const;
    Liaison* getLiaison()const;
    Block* getMere()const;

    void dessiner(Svgfile &svgout)const;

    bool TestRefPos()const;
};


///FONCTIONS LIEES A LA CLASSE COORD
void ajouterBlock(Block &room,
                  Coords _taille, std::string _id,
                  Coords _refpos, Coords _basepos);

bool TestBordure(Coords m_taille, Coords m_refpos, Coords m_basepos, bool m_plan3D, Block* m_Mere);

bool TestBordureAdjacente(Coords m_taille, Coords m_refpos, Coords m_basepos, bool m_plan3D, Block* m_Mere);




///METHODES INLINE

inline Block* Block::getFille(unsigned int indice)const {

    return m_Filles[indice];
}


inline Coords Block::getTaille()const {

    return m_taille;
}


inline Coords Block::getOrigine()const {

    return m_origine;
}


inline Liaison* Block::getLiaison()const {

    return m_liaison;
}


inline Block* Block::getMere()const {

    return m_Mere;
}

#endif // BLOCK_H_INCLUDED
