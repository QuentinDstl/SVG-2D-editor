#ifndef BLOCK_CERCLE_H_INCLUDED
#define BLOCK_CERCLE_H_INCLUDED

#include "block.h"

class BlockCercle : public Block
{
public:

    /// constructeurs
    BlockCercle(std::string _id, double _rayon, Couleur _couleur, Block* _Mere);
    BlockCercle();

    virtual void initialiserLiaison(double _angle, Coords _basepos, bool _plan3D);

    /// getteurs
    // INLINE
    virtual double getRayon()const;
    //virtual Coords getOrigine()const;
    //virtual Liaison getLiaison()const;

    /// dessiner
    virtual void dessiner(Svgfile &svgout)const;

    /// test
    virtual bool TestRefPos()const;

};


///************************///
///    METHODES INLINES    ///
///************************///

inline double BlockCercle::getRayon()const
{
    return m_taille.getX();
}

// a voir pour changer et faire le centre du cercle
/*
inline Coords BlockCercle::getOrigine()const
{
    return m_taille.getX();
}

inline Coords BlockCercle::getLiaison()const
{
    return m_taille.getX();
}
*/

#endif // BLOCK_CERCLE_H_INCLUDED
