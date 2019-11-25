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
    Liaison *m_liaison;

public :
    Block(std::string _id, double _xOrigine, double _yOrigine, double _xTaille, double _yTaille,Block* _pere);
    Block();

    ~Block()=default;

    void ajouterFille(double _xTaille, double _yTaille, std::string _id,
                      double _refposX, double _refposY, double _baseposX, double _baseposY, Block* _pere);
    void initialiser(double _xTaille, double _yTaille, std::string _id);
    void initialiserLiaison(double _refposX, double _refposY, double _baseposX, double _baseposY);
    void initialiserOrigine();



    /// dessiner
    void dessiner(Svgfile &svgout)const;
    void dessinerLiaisonsBase(Svgfile &svgout)const;
    void dessinerLiaisonsRef(Svgfile& svgout)const;
    void toutDessiner(Svgfile& svgout, Block &Racine);

    /// sauvegarde
    void sauvegarde();
    void sauvegarderScene(std::vector <Block*> m_Filles);

    /// getteurs
    Block* getFille(unsigned int indice)const;

    std::string getId () const
    {
        return m_id;
    }
    Block* getPere () const
    {
        return m_pere;
    }
    std::vector <Block*> getFilles () const
    {
        return m_Filles;
    }
};


void ajouterBlock(Block &room,
                  double _xTaille, double _yTaille, std::string _id,
                  double _refposX, double _refposY, double _baseposX, double _baseposY);


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

Block* parcourir(Block& fils,const std::string& id);

#endif // BLOCK_H_INCLUDED
