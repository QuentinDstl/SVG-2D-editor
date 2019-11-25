#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED

#include <vector>
#include <iostream>

#include "liaison.h"
#include "../svg/svgfile.h"
#include "../interface/couleur.h"

class Block
{
protected :

    std::string m_id;
    std::vector <Block*> m_Filles;
    Block* m_pere;
    Coords m_origine;
    Coords m_taille;

    Liaison m_liaison;
    Block* m_Mere;

public :

    /// constructeurs
    Block(std::string _id, Coords _taille, Block* _Mere);
    Block();

    ~Block()=default;

    /// ajout et initialisation
    void ajouterFille(Coords _taille, std::string _id, Coords _refpos, Coords _basepos, bool _plan3D);
    void initialiser(Coords _taille, std::string _id);
    void initialiserLiaison(Coords _refpos, Coords _basepos, bool _plan3D);
    void initialiserOrigine();

    /// getteurs
    Block* getFille(unsigned int indice)const;
    Coords getTaille()const;
    Coords getOrigine()const;
    Liaison getLiaison()const;
    Block* getMere()const;
    std::vector<Block*> getFilles () const;
    std::string getId () const;

    /// dessiner
    void dessiner(Svgfile &svgout)const;
    void dessinerLiaisonsBase(Svgfile &svgout)const;
    void dessinerLiaisonsRef(Svgfile& svgout)const;
    void toutDessiner(Svgfile& svgout)const;
    void toutDessinerLiaisons(Svgfile& svgout)const;

    /// test
    bool TestRefPos()const;

    /// sauvegarde
    void sauvegarde();
    void sauvegarderScene(std::vector <Block*> m_Filles);

    Block* parcourir(const std::string& id);

};


///FONCTIONS LIEES A LA CLASSE COORD
void ajouterBlock(Block &room,
                  Coords _taille, std::string _id,
                  Coords _refpos, Coords _basepos);

bool TestBordure(Coords m_taille, Coords m_refpos, Coords m_basepos, bool m_plan3D, Block* m_Mere);

bool TestBordureAdjacente(Coords m_taille, Coords m_refpos, Coords m_basepos, bool m_plan3D, Block* m_Mere);




///METHODES INLINE

inline Block* Block::getFille(unsigned int indice)const
{

    return m_Filles[indice];
}


inline Coords Block::getTaille()const
{

    return m_taille;
}


inline Coords Block::getOrigine()const
{

    return m_origine;
}

inline Liaison Block::getLiaison()const
{

    return m_liaison;
}


inline Block* Block::getMere()const
{

    return m_Mere;
}

inline std::string Block::getId () const
{

    return m_id;
}

inline std::vector<Block*> Block::getFilles () const
{

    return m_Filles;
}

///************************///
///  CLASS FILLE COULEUR   ///
///************************///

class CouleurBlock : public Block
{
protected :
    Couleur m_couleur;
    //Couleur m_bordure;
public :
    CouleurBlock(Couleur _couleur);
    // overwriting
    void dessiner(Svgfile &svgout)const;
};

#endif // BLOCK_H_INCLUDED
