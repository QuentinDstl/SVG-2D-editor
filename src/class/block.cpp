#include "block.h"
#include "../svg/svgfile.h"
#include "liaison.h"

/// lecture fichier
#define FICHIER "sauvegarde.rom"

Block::Block(std::string _id, double _xOrigine, double _yOrigine, double _xTaille, double _yTaille, Block* _pere)
    : m_id{_id}, m_pere{_pere}, m_origine{_xOrigine, _yOrigine}, m_taille{_xTaille, _yTaille}
{}

/// Constructeur avec Initialisation nul
Block::Block()
    : m_id{"A"}, m_pere{nullptr}, m_origine{0,0}, m_taille{0,0}
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

void toutDessiner(Svgfile& svgout, Block &room)
{
    if (room.getFille(0) == nullptr)
    {
        std::cout << "pas de filles" << std::endl;
    }
    std::cout << "eror dessiner 2" << std::endl;

    for(auto petit_fils : room.getFilles())
    {
        if (petit_fils->getFille(0) == nullptr)
        {
            std::cout << "feuille" << std::endl;
        }

        else
        {
            std::cout << "pre dessiner branche" << std::endl;
            toutDessiner(svgout,*petit_fils);
            std::cout << "dessiner branche" << std::endl;
        }
    }
        std::cout << "eror dessiner 3" << std::endl;
}

void Block::ajouterFille(double _xTaille, double _yTaille, std::string _id,
                         double _refposX, double _refposY, double _baseposX, double _baseposY, Block* _pere)
{
    Block* nouv = new Block{_id, 0, 0, _xTaille, _yTaille, _pere};
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

///Sauvegarde global de la scène
//a modifier pour toutes les filles
void Block::sauvegarde()
{
    sauvegarderScene(m_Filles);
}

///Sauvegarde des filles
//a modifier pour toutes les filles
void Block::sauvegarderScene(std::vector <Block*> s)
{
    std::ofstream ofs{FICHIER};

    for ( size_t i=0; i<s.size(); ++i)
    {
        ofs << s[i]->m_id << " " << s[i]->m_taille.getX() << " " << s[i]->m_taille.getY() << " " << s[i]->m_origine.getY() << " " << s[i]->m_origine.getX() << std::endl;
    }

    ofs.close();
}

Block* Block::getFille(unsigned int indice)const
{

    return m_Filles[indice];
}

/// dessiner liaisons

void Block::dessinerLiaisonsBase(Svgfile& svgout)const
{
    svgout.addCross(m_liaison->getBasepos().getX(),m_liaison->getBasepos().getY(),5, "black");
}

void Block::dessinerLiaisonsRef(Svgfile& svgout)const
{
    svgout.addCross(m_liaison->getRefpos().getX(),m_liaison->getRefpos().getY(),5, "black");
}

///************************///
///   CLASS FILLE COULEUR  ///
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

///************************///
///   TROUVER UN ELEMENT   ///
///************************///

// on veut trouver l'indice
Block* parcourir(Block& fils,const std::string& id)
{
    if (fils.getFille(0) == nullptr)
    {
        return nullptr;
    }
    for(auto petit_fils : fils.getFilles())
    {
        if (petit_fils->getId() == id)
        {
            return petit_fils;
        }
        else if (petit_fils->getFille(0) == nullptr)
        { }
        else
        {
            Block* p;
            p = parcourir(*petit_fils, id);

            if(p != nullptr)
            {
                return p;
            }
        }
    }
    return nullptr;
}
