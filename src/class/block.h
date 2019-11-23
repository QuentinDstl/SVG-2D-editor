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

    //Couleur m_bordure
    //Couleur m_couleur
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


#endif // BLOCK_H_INCLUDED
