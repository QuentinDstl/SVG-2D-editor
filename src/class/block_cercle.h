#ifndef BLOCK_CERCLE_H_INCLUDED
#define BLOCK_CERCLE_H_INCLUDED

#include "block.h"

class BlockCercle : public Block
{
    public:
        /// Constructeurs
        BlockCercle(double _classe, std::string _id, double _rayon, Couleur _couleur, Block* _Mere);
        BlockCercle();

        /// Getteurs
        // INLINE
        virtual double getRayon()const;
        //virtual Coords getOrigine()const;
        //virtual Liaison getLiaison()const;

        /// Dessiner
        virtual void dessiner(Svgfile &svgout)const;

        /// Test
        virtual bool TestRefPos()const;

};

bool RefPosDansCercle(Liaison m_liaison, Coords m_taille);

bool TestBordureRecCercle(Coords m_taille, Coords m_refpos, Coords m_basepos, unsigned int m_plan, std::string m_id, Block *m_Mere);
bool RefPosSurBordureCercle(Coords m_refpos, Coords m_taille);

bool TestBordureAdjacenteRecCercle(Coords m_taille, Coords m_refpos, Coords m_basepos, unsigned int m_plan, std::string m_id, Block* m_Mere);
bool CercleADroiteDeMereRec(Coords m_refpos, Coords m_taille, Coords m_basepos, Block* m_Mere);
bool CercleAGaucheDeMereRec(Coords m_refpos, Coords m_taille, Coords m_basepos);
bool CercleEnDessousDeMereRec(Coords m_refpos, Coords m_taille, Coords m_basepos, Block* m_Mere);
bool CercleAuDessusDeMereRec(Coords m_refpos, Coords m_taille, Coords m_basepos);


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
