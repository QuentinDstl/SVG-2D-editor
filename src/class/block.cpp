#include "block.h"
#include "../svg/svgfile.h"
#include "liaison.h"

/*Block::Block(double _xOrigine, double _yOrigine, double _xTaille, double _yTaille, std::string _id, double xRef, double yRef)
: m_origine{_xOrigine, _yOrigine}, m_taille{_xTaille, _yTaille}, m_id{_id}, m_liaison{xRef, yRef}
{}*/

Block::Block()
: m_origine{0,0}, m_taille{0,0}, m_id{"A"}
{}



void Block::initialiser(double _xTaille, double _yTaille, std::string _id) {

    m_taille.modifierX(_xTaille);
    m_taille.modifierY(_yTaille);
    m_id = _id;
}


void Block::initialiserLiaison(double _refposMereX, double _refposMereY, double _refposX, double _refposY) {

    Liaison _liaison;
    _liaison.initialiser(_refposMereX, _refposMereY, _refposX, _refposY);
    m_liaison = &_liaison;
}



void Block::initialiserOrigine() {

    m_origine = m_liaison->getRefposMere() - m_liaison->getRefpos();
}


void Block::dessiner(Svgfile &svgout)const
{
    svgout.addRectangle(m_origine.getX(), m_origine.getY(),
                        m_origine.getX(), m_origine.getY() + m_taille.getY(),
                        m_origine.getX() + m_taille.getX(), m_origine.getY(),
                        m_origine.getX() + m_taille.getX(), m_origine.getX() + m_taille.getY(),
                        "grey");
}


void Block::ajouterFille(double _xTaille, double _yTaille, std::string _id,
                         double _refposMereX, double _refposMereY, double _refposX, double _refposY)
{
    Block* nouv = new Block;
    nouv->initialiser(_xTaille, _yTaille, _id);
    nouv->initialiserLiaison(_refposMereX, _refposMereY, _refposX, _refposY);
    nouv->initialiserOrigine();
    m_Filles.push_back(nouv);
}
