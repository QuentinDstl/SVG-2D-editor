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
        Coords m_taille;
        Coords m_origine;

        Liaison *m_liaison;

        //Couleur m_bordure
        //Couleur m_couleur
    public :
        //Block(double _xOrigine, double _yOrigine, double _xTaille, double _yTaille, std::string _id);
        Block();
        ~Block()=default;

        void ajouterFille(double _xTaille, double _yTaille, std::string _id,
                          double _refposMereX, double _refposMereY, double _refposX, double _refposY);
        void initialiser(double _xTaille, double _yTaille, std::string _id);
        void initialiserLiaison(double _refposMereX, double _refposMereY, double _refposFilleX, double _refposFilleY);
        void initialiserOrigine();

        void dessiner(Svgfile &svgout)const;
};


#endif // BLOCK_H_INCLUDED
