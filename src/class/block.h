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
    Coords m_origine;
    Coords m_taille;
    Liaison *m_liaison;

public :
    Block(std::string _id, double _xOrigine, double _yOrigine, double _xTaille, double _yTaille);
    Block();

    ~Block()=default;

    void ajouterFille(double _xTaille, double _yTaille, std::string _id,
                      double _refposX, double _refposY, double _baseposX, double _baseposY);
    void initialiser(double _xTaille, double _yTaille, std::string _id);
    void initialiserLiaison(double _refposX, double _refposY, double _baseposX, double _baseposY);
    void initialiserOrigine();

    Block* getFille(unsigned int indice)const;

    void dessiner(Svgfile &svgout)const;
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

#endif // BLOCK_H_INCLUDED
