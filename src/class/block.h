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
    Coords m_origine;
    Coords m_taille;
    Couleur m_couleur;

    Block* m_Mere;
    Liaison m_liaison;
    std::vector <Block*> m_Filles;

public :


    ///CONSTRUCTEURS
    Block (std::string _id, Coords _taille, Couleur _couleur, Block* _Mere);
    Block();

    virtual ~Block()=default;

    ///AJOUT
    virtual void ajouterFille(std::string _id, Coords _taille, Couleur _couleur, Coords _refpos, Coords _basepos, bool _plan3D);
    //virtual void ajouterFilleBordure(double _classe,Coords _taille, std::string _id, Coords _refpos, Coords _basepos, bool _plan3D, Couleur _couleur, Couleur _bordure);
    //virtual void ajouterFilleCercle(double _classe,double _rayon, std::string _id, double _angle, Coords _basepos, bool _plan3D, Couleur _couleur);

    ///INITIALIALISATION
    virtual void initialiser(std::string _id, Coords _taille, Couleur _couleur);
    virtual void initialiserLiaison(Coords _refpos, Coords _basepos, bool _plan3D);
    virtual void initialiserOrigine();

    ///GETTEURS
    /* TOUS INLINE */
    virtual Block* getFille(unsigned int indice)const;
    virtual Coords getTaille()const;
    virtual Coords getOrigine()const;
    virtual Liaison getLiaison()const;
    virtual Block* getMere()const;
    virtual std::vector<Block*> getFilles () const;
    virtual std::string getId () const;

    ///DESSINER
    virtual void dessiner(Svgfile &svgout)const;
    virtual void dessinerLiaisonsBase(Svgfile &svgout)const;
    virtual void dessinerLiaisonsRef(Svgfile& svgout)const;
    virtual void toutDessinerLiaisons(Svgfile& svgout)const;
    virtual void dessinerId(Svgfile &svgout) const;
    virtual void toutDessinerId(Svgfile& svgout) const;

    ///TEST DES COORDS
    virtual bool TestRefPos()const;

    ///SAUVEGARDE
    /*virtual void sauvegarde();
    virtual void sauvegarderScene1(std::vector <Block*> m_Filles);
    virtual void sauvegarderScene2(std::vector <Block*> m_Filles);
    virtual void chargementScene();*/


};

///**********************************///
///FONCTIONS LIEES A LA CLASSE BLOCK ///
///**********************************///

///AJOUT
void ajouterBlock(Block &room,
                  std::string _id, Coords _taille, Couleur _couleur,
                  Coords _refpos, Coords _basepos);

///TEST DES COORDS
bool TestBordure(Coords m_taille, Coords m_refpos, Coords m_basepos, bool m_plan3D, Block* m_Mere);

bool TestBordureAdjacente(Coords m_taille, Coords m_refpos, Coords m_basepos, bool m_plan3D, Block* m_Mere);

//PARCOURS ET RACINE
Block* trouverRacine(Block &block);
Block* parcourir(std::string id, const Block &room);
Block* parcourir(Coords taille, Coords origine, const Block &room);

///************************///
///    METHODES INLINES    ///
///************************///

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

#endif // BLOCK_H_INCLUDED
