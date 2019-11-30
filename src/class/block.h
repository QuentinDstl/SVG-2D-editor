#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED

#include <vector>
#include <iostream>

#include "liaison_glissiere.h"
#include "../svg/svgfile.h"
#include "../interface/couleur.h"

class Block
{

protected :

    double m_classe;
    std::string m_id;
    Coords m_origine;
    Coords m_taille;
    Couleur m_couleur;

    Block* m_Mere;
    Liaison *m_liaison;
    std::vector <Block*> m_Filles;

public :


    ///CONSTRUCTEURS
    Block (double m_classe, std::string _id, Coords _taille, Couleur _couleur, Block* _Mere);
    Block();

    virtual ~Block()=default;

    ///AJOUT
    virtual void ajouterFille(double m_clase, std::string _id, Coords _taille, Couleur _couleur, Coords _refpos, Coords _basepos, bool _plan3D);
    virtual void ajouterFilleGlissiere(double _classe, std::string _id, Coords _taille, Couleur _couleur, Coords _refpos, Coords _basepos, Coords _baseposfin, bool _plan3D);
    virtual void ajouterFilleBordure(double _classe, std::string _id, Coords _taille, Couleur _couleur, Couleur _bordure, Coords _refpos, Coords _basepos, bool _plan3D);
    virtual void ajouterFilleGlissiereBordure(double _classe, std::string _id, Coords _taille, Couleur _couleur, Couleur _bordure, Coords _refpos, Coords _basepos, Coords _baseposfin, bool _plan3D);
    virtual void ajouterFilleCercle(double _classe, std::string _id, double _rayon, Couleur _couleur, Coords _refpos, Coords _basepos, bool _plan3D);
    virtual void ajouterFilleCercleGlissiere(double _classe, std::string _id, double _rayon, Couleur _couleur, Coords _refpos, Coords _basepos, Coords _baseposfin, bool _plan3D);
    virtual void ajouterFilleCercleBordure(double _classe, std::string _id, double _rayon, Couleur _couleur, Couleur _bordure, Coords _refpos, Coords _basepos, bool _plan3D);
    virtual void ajouterFilleCercleGlissiereBordure(double _classe, std::string _id, double _rayon, Couleur _couleur, Couleur _bordure, Coords _refpos, Coords _basepos, Coords _baseposfin, bool _plan3D);

    ///INITIALIALISATION
    virtual void initialiser(double m_classe, std::string _id, Coords _taille, Couleur _couleur);
    virtual void initialiserLiaison(Coords _refpos, Coords _basepos, bool _plan3D);
    virtual void initialiserGlissiere(Coords _refpos, Coords _basepos, Coords _baseposfin, bool _plan3D);
    virtual void initialiserOrigine();

    ///GETTEURS
    /* TOUS INLINE */
    virtual Block* getFille(unsigned int indice)const;
    virtual Coords getTaille()const;
    virtual Coords getOrigine()const;
    virtual Liaison* getLiaison()const;
    virtual Block* getMere()const;
    virtual std::vector<Block*> getFilles () const;
    virtual std::string getId () const;
    virtual double getClasse () const;
    virtual Couleur getCouleur () const;

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
    virtual void sauvegarde();
    virtual void sauvegarderScene1(std::vector <Block*> m_Filles);
    virtual void chargementScene();

    ///TRANSLATION
    //virtual void translation(int distance);
};


///**********************************///
///FONCTIONS LIEES A LA CLASSE BLOCK ///
///**********************************///

///AJOUT
void ajouterBlock(Block &room,
                  double _classe, std::string _id, Coords _taille, Couleur _couleur,
                  Coords _refpos, Coords _basepos);

///TEST DES COORDS
bool MemePlan(Liaison &m_liaison, Block *m_Mere);
bool RefPosDansBloc(Liaison &m_liaison, Coords m_taille);
bool BasePosDansBlocMere(Liaison &m_liaison, Block* m_Mere);

bool TestBordure(Coords m_taille, Coords m_refpos, Coords m_basepos, unsigned int m_plan, std::string m_id, Block *m_Mere);
bool RefPosSurBordure(Coords m_refpos, Coords m_taille);
bool RefPosSurBordure(Coords m_refpos, Coords m_taille);
bool BasePosSurBordure(Coords m_basepos, Block* m_Mere);

bool TestBordureAdjacente(Coords m_taille, Coords m_refpos, Coords m_basepos, unsigned int m_plan, std::string m_id, Block* m_Mere);
bool BlocADroiteDeMere(Coords m_refpos, Coords m_basepos, Block* m_Mere);
bool BlocAGaucheDeMere(Coords m_refpos, Coords m_basepos, Coords m_taille);
bool BlocEnDessousDeMere(Coords m_refpos, Coords m_basepos, Block* m_Mere);
bool BlocAuDessusDeMere(Coords m_refpos, Coords m_basepos, Coords m_taille);

///PARCOURS ET RACINE
Block* trouverRacine(Block &block);
Block* parcourir(std::string id, const Block &room);
Block* trouverCollision(Block &block, Block &room);

///************************///
///    METHODES INLINES    ///
///************************///

inline Block* Block::getFille(unsigned int indice) const
{
    return m_Filles[indice];
}

inline Coords Block::getTaille() const
{
    return m_taille;
}

inline Coords Block::getOrigine() const
{
    return m_origine;
}

inline Liaison* Block::getLiaison() const
{
    return m_liaison;
}

inline Block* Block::getMere() const
{
    return m_Mere;
}

inline double Block::getClasse() const
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

inline Couleur Block::getCouleur () const
{
    return m_couleur;
}

#endif // BLOCK_H_INCLUDED
