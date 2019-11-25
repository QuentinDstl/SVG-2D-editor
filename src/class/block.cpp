#include "block.h"
#include "../svg/svgfile.h"
#include "liaison.h"

/// lecture fichier
#define FICHIER "sauvegarde.rom"


///Constructeur
Block::Block(std::string _id, Coords _taille, Block* _Mere)
    : m_id{_id}, m_origine{0,0}, m_taille{_taille}, m_Mere{_Mere}
{}


/// Constructeur avec Initialisation nul
Block::Block()
    : m_id{"A"}, m_origine{0,0}, m_taille{0,0}, m_Mere{nullptr}
{}


///Initialisation du block
void Block::initialiser(Coords _taille, std::string _id) {

    m_origine = {0,0};
    m_taille = {_taille.getX(),_taille.getY()};
    m_id = _id;
    m_Mere = NULL;
}

/// Initialisation de la lisaison
// a partir de la methode de la class liaison
void Block::initialiserLiaison(Coords _refpos, Coords _basepos, bool _plan3D)
{
    m_liaison.setteur(_refpos,_basepos,_plan3D);
}

/// Initialisation de m_origine
// recupere l'origine de la mere et la soustrait a sa position de reference
void Block::initialiserOrigine()
{
    std::cout << "position de la liaison dans initialiser: " << m_liaison.getBasepos() << std::endl;
    //std::cout << "basepos:" << m_liaison->getBasepos() << std::endl;
    //std::cout << "refpos:" << m_liaison->getRefpos() << std::endl;
    if(m_Mere == nullptr) {
        std::cout << " == NULL"<< std::endl;
        m_origine = m_liaison.getBasepos() - m_liaison.getRefpos();
    }
    else {
        std::cout << " != NULL"<< std::endl;
        m_origine = m_Mere->getOrigine() + m_liaison.getBasepos() - m_liaison.getRefpos();
    //std::cout << "origineMere:" << m_Mere->getOrigine() << std::endl;
    }

    //std::cout << "origine:" << m_origine << std::endl;

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


void Block::ajouterFille(Coords _taille, std::string _id, Coords _refpos, Coords _basepos, bool _plan3D)
{

    std::cout << getLiaison().getBasepos();
    Block* nouv = new Block{_id, _taille, this};
    nouv->initialiserLiaison(_refpos, _basepos, _plan3D);
    nouv->initialiserOrigine();
    m_Filles.push_back(nouv);


    //fonction qui teste si le block est bien relié au block mere
    if(!(nouv->TestRefPos())) {
        delete m_Filles[m_Filles.size()-1];
        m_Filles.erase(m_Filles.begin()+m_Filles.size()-1);
        std::cout << "Liaison incorrect" << std::endl;
    }
    else {
        std::cout << m_origine << std::endl;
    }
}


///fonction de test de la liaison
//cette fonction renvoie un booléen : true si la liaison est ok, false si la liaison est mal initialisée
bool Block::TestRefPos()const {


    bool test = 0;

    if(m_liaison.getRefpos() <= m_taille) {
         if(m_liaison.getBasepos() <= m_Mere->getTaille()) {
            if(TestBordure(m_taille, m_liaison.getRefpos(), m_liaison.getBasepos(), m_liaison.getPlan3D(), m_Mere)) {
                test = 1;
            }
         }
         else {
            std::cout << "Appui non situe sur le bloc mere" << std::endl;
         }
    }
    else {
        std::cout << "Appui non situe sur le bloc fille" << std::endl;
    }

    return test;
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

bool TestBordure(Coords m_taille, Coords m_refpos, Coords m_basepos, bool m_plan3D, Block *m_Mere) {

    bool test = 0;

    if(m_refpos.getX() == 0 || m_refpos.getX() == m_taille.getX() || m_refpos.getY() == 0 || m_refpos.getY() == m_taille.getY()) {
        if(m_basepos.getX() == 0 || m_basepos.getX() == m_Mere->getTaille().getX() || m_basepos.getY() == 0 || m_basepos.getY() == m_Mere->getTaille().getY()) {
            if(TestBordureAdjacente(m_taille, m_refpos, m_basepos, m_plan3D,m_Mere)) {
                test = 1;
            }
        }
        else {
            std::cout << "Appui non situe sur la bordure du bloc mere" << std::endl;
        }
    }
    else {
        std::cout << "Appui non situe sur la bordure du bloc fille" << std::endl;
    }

    return test;
}




bool TestBordureAdjacente(Coords m_taille, Coords m_refpos, Coords m_basepos, bool m_plan3D, Block* m_Mere) {

    bool test = 0;

    if(m_plan3D == 0) {
        if(m_refpos.getX() == 0 && m_basepos.getX() == m_Mere->getTaille().getX()) {
            test = 1;
        }
        else if(m_refpos.getX() == m_taille.getX() && m_basepos.getX() == 0) {
            test = 1;
        }
        else if(m_refpos.getY() == 0 && m_basepos.getY() == m_Mere->getTaille().getY()) {
            test = 1;
        }
        else if(m_refpos.getY() == m_taille.getY() && m_basepos.getY() == 0) {
            test = 1;
        }
        else {
            std::cout << "Appui situe dans le bloc mere" << std::endl;
        }
    }
    else {
        test = 1;
    }

    return test;
}



void ajouterBlock(Block &bRoom,
                  Coords _taille, std::string _id,
                  Coords _refpos, Coords _basepos)
{
    bRoom.initialiser(_taille, _id);
    bRoom.initialiserLiaison(_refpos, _basepos, 0);
    std::cout << " position de la liaison initiale : " << bRoom.getLiaison().getBasepos() << std::endl;
    bRoom.initialiserOrigine();
    std::cout << " - position de la liaison : " << bRoom.getLiaison().getBasepos() << std::endl;
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
/*
Block* trouverId(Block* fils,const std::string& id, unsigned int& couche, std::vector <unsigned int>& branches)
{
    do
    {
        if (fils->m_id == id)
            return fils;

        branches[couche] += 1;
        trouverId();
    }while (branches[couche] =! fils->getFilles().size());
}
*/
