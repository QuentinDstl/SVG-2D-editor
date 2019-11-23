#include "block.h"
#include "../svg/svgfile.h"
#include "liaison.h"

Block::Block(std::string _id, double _xOrigine, double _yOrigine, double _xTaille, double _yTaille)
    : m_id{_id}, m_origine{_xOrigine, _yOrigine}, m_taille{_xTaille, _yTaille}
{}

/// Constructeur avec Initialisation nul
Block::Block()
    : m_id{"A"}, m_origine{0,0}, m_taille{0,0}
{}

/// Initialisation (taille x, taille y, identifiant)
void Block::initialiser(double _xTaille, double _yTaille, std::string _id)
{

    m_taille.modifierX(_xTaille);
    m_taille.modifierY(_yTaille);
    m_id = _id;
}

/// Initialisation de la lisaison
// a partir de la methode de la class liaison
void Block::initialiserLiaison(double _refposX, double _refposY, double _baseposX, double _baseposY)
{

    Liaison _liaison{_refposX, _refposY, _baseposX, _baseposY,0};
    //_liaison.initialiser(_refposX, _refposY, _baseposX, _baseposY);
    m_liaison = &_liaison;
}

/// Initialisation de m_origine
// recupere l'origine de la mere et la soustrait a sa position de reference
void Block::initialiserOrigine()
{

    m_origine = m_liaison->getRefpos() - m_liaison->getBasepos();
}

/// Dessine le block
// appel de la fonction svg pour dessiner un bloc sans contour
void Block::dessiner(Svgfile &svgout)const
{
    svgout.addRectangle(m_origine.getX(), m_origine.getY(),
                        m_origine.getX(), m_origine.getY() + m_taille.getY(),
                        m_origine.getX() + m_taille.getX(), m_origine.getY(),
                        m_origine.getX() + m_taille.getX(), m_origine.getY() + m_taille.getY(),
                        "grey");
}


void Block::ajouterFille(double _xTaille, double _yTaille, std::string _id,
                         double _refposX, double _refposY, double _baseposX, double _baseposY)
{
    Block* nouv = new Block{_id, 0, 0, _xTaille, _yTaille};
    //nouv->initialiser(_xTaille, _yTaille, _id);
    nouv->initialiserLiaison(_refposX, _refposY, _baseposX, _baseposY);
    nouv->initialiserOrigine();
    m_Filles.push_back(nouv);
}


void ajouterBlock(Block &room,
                  double _xTaille, double _yTaille, std::string _id,
                  double _refposX, double _refposY, double _baseposX, double _baseposY)
{

    room.initialiser(_xTaille, _yTaille, _id);
    room.initialiserLiaison(_refposX, _refposY, _baseposX, _baseposY);
    room.initialiserOrigine();
}



Block* Block::getFille(unsigned int indice)const {

    return m_Filles[indice];
}

///************************///
///  CLASS FILLE COULEUR   ///
///************************///

CouleurBlock::CouleurBlock(Couleur _couleur) : m_couleur{_couleur}
{ }

// overwriting de dessiner pour afficher la couleur
void CouleurBlock::dessiner(Svgfile &svgout)const
{
    svgout.addRectangle(m_origine.getX(), m_origine.getY(),
                        m_origine.getX(), m_origine.getY() + m_taille.getY(),
                        m_origine.getX() + m_taille.getX(), m_origine.getY(),
                        m_origine.getX() + m_taille.getX(), m_origine.getY() + m_taille.getY(),
                        m_couleur);
}
