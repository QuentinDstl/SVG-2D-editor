#include "block_cercle.h"
#include <math.h>

#define PI 3.1415926535

///*************************///
///       OVERWRITING       ///
///*************************///

/// constructeurs
BlockCercle::BlockCercle(double _classe, std::string _id, double _rayon, Couleur _couleur, Block* _Mere)
    : Block(_classe, _id,
{
    _rayon,0
}, _couleur, _Mere)
{ }
BlockCercle::BlockCercle() : Block()
{ }

/// dessiner
void BlockCercle::dessiner(Svgfile &svgout)const
{
    svgout.addDisk(m_origine.getX(), m_origine.getY(),m_taille.getX(), m_couleur);
}


/// test
bool BlockCercle::TestRefPos()const
{
    bool test = 0;

    if(RefPosDansCercle(*m_liaison, m_taille))
    {
        if(BasePosDansBlocMere(*m_liaison, m_Mere))
        {
            if(MemePlan(*m_liaison, m_Mere))
            {
                if(TestBordureRecCercle(m_taille, m_liaison->getRefpos(), m_liaison->getBasepos(), m_liaison->getPlan(), m_id, m_Mere))
                {
                    test = 1;
                }
            }
            else
            {
                test = 1;
            }
        }
        else
        {
            std::cout << "[e]" << m_id << " : " << "Appui non situe sur le bloc mere" << std::endl;
        }
    }
    else
    {
        std::cout << "[e]" << m_id << " : " <<  "Appui non situe sur le bloc fille" << std::endl;
    }
    return test;
}

bool RefPosDansCercle(Liaison m_liaison, Coords m_taille)
{

    if(m_liaison.getRefpos().getX() <= m_taille.getX() && m_liaison.getRefpos().getY() <= m_taille.getX())
    {
        if(m_liaison.getRefpos().getX() >= -(m_taille.getX()) && m_liaison.getRefpos().getY() >= -(m_taille.getX()))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

bool TestBordureRecCercle(Coords m_taille, Coords m_refpos, Coords m_basepos, unsigned int m_plan, std::string m_id, Block *m_Mere)
{

    bool test = 0;

    if(RefPosSurBordureCercle(m_refpos, m_taille))
    {
        if(BasePosSurBordure(m_basepos, m_Mere))
        {
            if(TestBordureAdjacenteRecCercle(m_taille, m_refpos, m_basepos, m_plan, m_id, m_Mere))
            {
                test = 1;
            }
        }
        else
        {
            std::cout << "[e]" << m_id << " : " << "Appui non situe sur la bordure du bloc mere" << std::endl;
        }
    }
    else
    {
        std::cout << "[e]" << m_id << " : " << "Appui non situe sur la bordure du bloc fille" << std::endl;
    }
    return test;
}

bool RefPosSurBordureCercle(Coords m_refpos, Coords m_taille)
{

    if((abs(m_refpos.getX()) + abs(m_refpos.getY()) == m_taille.getX()))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

bool TestBordureAdjacenteRecCercle(Coords m_taille, Coords m_refpos, Coords m_basepos, unsigned int m_plan, std::string m_id, Block* m_Mere)
{

    bool test = 0;

    if(CercleADroiteDeMereRec(m_refpos, m_taille, m_basepos, m_Mere))
    {
        test = 1;
    }
    else if(CercleAGaucheDeMereRec(m_refpos, m_taille, m_basepos))
    {
        test = 1;
    }
    else if(CercleEnDessousDeMereRec(m_refpos, m_taille, m_basepos, m_Mere))
    {
        test = 1;
    }
    else if(CercleAuDessusDeMereRec(m_refpos, m_taille, m_basepos))
    {

        test = 1;
    }
    else
    {
        std::cout << "[e]" << m_id << " : " << "Appui situe dans le bloc mere" << std::endl;
    }

    return test;
}

bool CercleADroiteDeMereRec(Coords m_refpos, Coords m_taille, Coords m_basepos, Block* m_Mere)
{

    if(m_refpos.getX() == -(m_taille.getX()) && m_basepos.getX() == m_Mere->getTaille().getX())
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

bool CercleAGaucheDeMereRec(Coords m_refpos, Coords m_taille, Coords m_basepos)
{

    if(m_refpos.getX() == m_taille.getX() && m_basepos.getX() == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

bool CercleEnDessousDeMereRec(Coords m_refpos, Coords m_taille, Coords m_basepos, Block* m_Mere)
{

    if(m_refpos.getY() == -(m_taille.getX()) && m_basepos.getY() == m_Mere->getTaille().getY())
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

bool CercleAuDessusDeMereRec(Coords m_refpos, Coords m_taille, Coords m_basepos)
{

    if(m_refpos.getY() == m_taille.getX() && m_basepos.getY() == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}



//m_liaison.setteur({m_origine.getX() + m_taille.getX()*cos(_angle*(PI/180)),m_origine.getY() + m_taille.getX()*sin(_angle*(PI/180))},_basepos,_plan3D);
