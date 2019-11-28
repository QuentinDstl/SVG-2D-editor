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
    double m_classe;
    std::string m_id;
    std::vector <Block*> m_Filles;
    Coords m_origine;
    Coords m_taille;
    Liaison m_liaison;
    Block* m_Mere;

public :

    /// Constructeurs
    Block(double classe, std::string _id, Coords _taille, Block* _Mere);
    Block();

    virtual ~Block()=default;

    /// Ajout et initialisation
    virtual void ajouterFille(double _classe,Coords _taille, std::string _id, Coords _refpos, Coords _basepos, bool _plan3D);
    virtual void ajouterFilleCouleur(double _classe,Coords _taille, std::string _id, Coords _refpos, Coords _basepos, bool _plan3D, Couleur _couleur);
    virtual void ajouterFilleBordure(double _classe,Coords _taille, std::string _id, Coords _refpos, Coords _basepos, bool _plan3D, Couleur _couleur, Couleur _bordure);
    virtual void initialiser(Coords _taille, std::string _id);
    virtual void initialiserLiaison(Coords _refpos, Coords _basepos, bool _plan3D);
    virtual void initialiserOrigine();

    /// Getteurs
    /* TOUS INLINE */
    virtual Block* getFille(unsigned int indice)const;
    virtual Coords getTaille()const;
    virtual Coords getOrigine()const;
    virtual Liaison getLiaison()const;
    virtual Block* getMere()const;
    virtual std::vector<Block*> getFilles () const;
    virtual std::string getId () const;
    virtual double getClasse () const;

    /// Dessiner
    virtual void dessiner(Svgfile &svgout)const;
    virtual void toutDessiner(Svgfile& svgout)const;
    virtual void dessinerLiaisonsBase(Svgfile &svgout)const;
    virtual void dessinerLiaisonsRef(Svgfile& svgout)const;
    virtual void toutDessinerLiaisons(Svgfile& svgout)const;
    virtual void dessinerId(Svgfile &svgout) const;
    virtual void toutDessinerId(Svgfile& svgout) const;

    /// Test
    virtual bool TestRefPos()const;

    /// Sauvegarde
    virtual void sauvegarde();
    virtual void sauvegarderScene1(std::vector <Block*> m_Filles);
    virtual void sauvegarderScene2(std::vector <Block*> m_Filles);
    virtual void chargementScene();

    /// Trouver un element
    virtual Block* parcourir(const std::string& id);

};

///FONCTIONS LIEES A LA CLASSE COORD
void ajouterBlock(Block &room,
                  Coords _taille, std::string _id,
                  Coords _refpos, Coords _basepos);

bool TestBordure(Coords m_taille, Coords m_refpos, Coords m_basepos, bool m_plan3D, Block* m_Mere);

bool TestBordureAdjacente(Coords m_taille, Coords m_refpos, Coords m_basepos, bool m_plan3D, Block* m_Mere);

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

inline double Block::getClasse()const
{
    return m_classe;
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

class BlockCouleur : public Block
{
protected :

    Couleur m_couleur;
    Couleur m_bordure;

public :

    /* OVERWRITING */
    /// Constructeurs
    BlockCouleur(double _classe,std::string _id, Coords _taille, Block* _Mere, Couleur _couleur);
    BlockCouleur(double _classe,std::string _id, Coords _taille, Block* _Mere, Couleur _couleur, Couleur _bordure);

    /// Ajout et initialisation
    //virtual void ajouterFille(Coords _taille, std::string _id, Coords _refpos, Coords _basepos, bool _plan3D, Couleur _couleur);
    //virtual void ajouterFille(Coords _taille, std::string _id, Coords _refpos, Coords _basepos, bool _plan3D, Couleur _couleur, Couleur _bordure);

    //virtual void initialiser(Coords _taille, std::string _id, Couleur _couleur);
    //virtual void initialiser(Coords _taille, std::string _id, Couleur _couleur, Couleur _bordure);

    /// Getteurs
    /* TOUS INLINE */
    virtual Couleur getCouleur()const;
    virtual Couleur getBordure()const;

    /// Dessiner
    virtual void dessiner(Svgfile &svgout)const;

    // TODO (qdesa#1#11/26/19): Pour Charles : Sauvegarde : elements de couleurs
    /// Sauvegarde
    /*virtual void sauvegarde();
    virtual void sauvegarderScene(std::vector <Block*> m_Filles);*/

    // TODO (qdesa#1#11/26/19): voir pour la fonction parcourir dans Block
    /// Trouver un element
    //virtual Block* parcourir(const std::string& id);
};

///************************///
///    METHODES INLINES    ///
///************************///

inline Couleur BlockCouleur::getCouleur()const
{
    return m_couleur;
}

inline Couleur BlockCouleur::getBordure()const
{
    return m_bordure;
}

#endif // BLOCK_H_INCLUDED
