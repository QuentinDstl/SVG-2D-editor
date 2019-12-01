#include "block.h"
#include "../svg/svgfile.h"
#include "block_cercle.h"
#include "block_bordure.h"
#include "block_cercle_bordure.h"
#include "../interface/menu.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream> /// Pour les fichiers
#include <sstream> /// Pour les ostringstream

#define HAUTEUR_SCENE 600
#define LARGEUR_SCENE 1000
#define MAX_COLOR 100

/// Definition lecture fichier :
#define FICHIERSAUV "src/rom/sauvegarde.rom"
#define FICHIERTEST "src/rom/sauvegarde2.rom"

///*************************///
///      CONSTRUCTEURS      ///
///*************************///

/* constructeur de base */
Block::Block (double _classe, std::string _id, Coords _taille, Couleur _couleur, Block* _Mere) :
    m_classe{_classe}, m_id{_id}, m_origine{0,0}, m_taille{_taille}, m_couleur{_couleur}, m_Mere{_Mere}, m_liaison{nullptr}
{}

/* Constructeur avec Initialisation nul */
Block::Block() :
    m_classe{0}, m_id{"A"}, m_origine{0,0}, m_taille{0,0}, m_couleur{10,10,10}, m_Mere{nullptr}, m_liaison{nullptr}
{}

///*************************///
///          AJOUT          ///
///*************************///

/* Creer une fille */
// cree une nouvelle fille a partir de la mere
void Block::ajouterFille(double _classe, std::string _id, Coords _taille, Couleur _couleur, Coords _refpos, Coords _basepos, bool _plan3D)
{
    Block* nouv = new Block{_classe, _id, _taille, _couleur, this};
    nouv->initialiserLiaison(_refpos, _basepos, _plan3D);
    nouv->initialiserOrigine();
    m_Filles.push_back(nouv);

    //methode qui teste de la position du nouveau block dans la scene
    if(!(nouv->TestRefPos()))
    {
        delete m_Filles[m_Filles.size()-1];
        m_Filles.erase(m_Filles.begin()+m_Filles.size()-1);
        std::cout << "[e] liaison incorrect" << std::endl;
    }
}

void Block::ajouterFilleGlissiere(double _classe, std::string _id, Coords _taille, Couleur _couleur, Coords _refpos, Coords _basepos, Coords _baseposfin, bool _plan3D)
{
    Block* nouv = new Block{_classe, _id, _taille, _couleur, this};
    if(_basepos == _baseposfin)
        nouv->initialiserLiaison(_refpos, _basepos, _plan3D);
    else
        nouv->initialiserGlissiere(_refpos, _basepos, _baseposfin, _plan3D);
    nouv->initialiserOrigine();
    m_Filles.push_back(nouv);

    //methode qui teste de la position du nouveau block dans la scene
    if(!(nouv->TestRefPos()))
    {
        delete m_Filles[m_Filles.size()-1];
        m_Filles.erase(m_Filles.begin()+m_Filles.size()-1);
        std::cout << "[e] liaison incorrect" << std::endl;
    }
}


// Creer une fille couleur avec bordures
// cree une nouvelle fille a partir de la mere
void Block::ajouterFilleBordure(double _classe, std::string _id, Coords _taille, Couleur _couleur, Couleur _bordure, Coords _refpos, Coords _basepos, bool _plan3D)
{
    BlockBordure* nouv = new BlockBordure{_classe,_id, _taille, _couleur, _bordure, this};
    nouv->initialiserLiaison(_refpos, _basepos, _plan3D);
    nouv->initialiserOrigine();
    m_Filles.push_back(nouv);

    if(!(nouv->TestRefPos()))
    {
        delete m_Filles[m_Filles.size()-1];
        m_Filles.erase(m_Filles.begin()+m_Filles.size()-1);
        std::cout << "[e] liaison incorrect" << std::endl;
    }
}

void Block::ajouterFilleGlissiereBordure(double _classe, std::string _id, Coords _taille, Couleur _couleur, Couleur _bordure, Coords _refpos, Coords _basepos, Coords _baseposfin, bool _plan3D)
{
    BlockBordure* nouv = new BlockBordure{_classe,_id, _taille, _couleur, _bordure, this};
    if(_basepos == _baseposfin)
        nouv->initialiserLiaison(_refpos, _basepos, _plan3D);
    else
        nouv->initialiserGlissiere(_refpos, _basepos, _baseposfin, _plan3D);
    nouv->initialiserOrigine();
    m_Filles.push_back(nouv);

    //methode qui teste de la position du nouveau block dans la scene
    if(!(nouv->TestRefPos()))
    {
        delete m_Filles[m_Filles.size()-1];
        m_Filles.erase(m_Filles.begin()+m_Filles.size()-1);
        std::cout << "[e] liaison incorrect" << std::endl;
    }
}

void Block::ajouterFilleCercle(double _classe, std::string _id, double _rayon, Couleur _couleur, Coords _refpos, Coords _basepos, bool _plan3D)
{
    BlockCercle* nouv = new BlockCercle{_classe, _id, _rayon, _couleur, this};
    nouv->initialiserLiaison(_refpos, _basepos, _plan3D);
    nouv->initialiserOrigine();
    m_Filles.push_back(nouv);

    if(!(nouv->TestRefPos()))
    {
        delete m_Filles[m_Filles.size()-1];
        m_Filles.erase(m_Filles.begin()+m_Filles.size()-1);
        std::cout << "[e] liaison incorrect" << std::endl;
    }
}

void Block::ajouterFilleCercleGlissiere(double _classe, std::string _id, double _rayon, Couleur _couleur, Coords _refpos, Coords _basepos, Coords _baseposfin, bool _plan3D)
{
    BlockCercle* nouv = new BlockCercle{_classe, _id, _rayon, _couleur, this};
    if(_basepos == _baseposfin)
        nouv->initialiserLiaison(_refpos, _basepos, _plan3D);
    else
        nouv->initialiserGlissiere(_refpos, _basepos, _baseposfin, _plan3D);
    nouv->initialiserOrigine();
    m_Filles.push_back(nouv);

    if(!(nouv->TestRefPos()))
    {
        delete m_Filles[m_Filles.size()-1];
        m_Filles.erase(m_Filles.begin()+m_Filles.size()-1);
        std::cout << "[e] liaison incorrect" << std::endl;
    }
}

void Block::ajouterFilleCercleBordure(double _classe, std::string _id, double _rayon, Couleur _couleur, Couleur _bordure, Coords _refpos, Coords _basepos, bool _plan3D)
{
    BlockCercleBordure* nouv = new BlockCercleBordure{_classe, _id, _rayon, _couleur, _bordure, this};
    nouv->initialiserLiaison(_refpos, _basepos, _plan3D);
    nouv->initialiserOrigine();
    m_Filles.push_back(nouv);

    if(!(nouv->TestRefPos()))
    {
        delete m_Filles[m_Filles.size()-1];
        m_Filles.erase(m_Filles.begin()+m_Filles.size()-1);
        std::cout << "[e] liaison incorrect" << std::endl;
    }
}

void Block::ajouterFilleCercleGlissiereBordure(double _classe, std::string _id, double _rayon, Couleur _couleur, Couleur _bordure, Coords _refpos, Coords _basepos, Coords _baseposfin, bool _plan3D)
{
    BlockCercleBordure* nouv = new BlockCercleBordure{_classe, _id, _rayon, _couleur, _bordure, this};
    if(_basepos == _baseposfin)
        nouv->initialiserLiaison(_refpos, _basepos, _plan3D);
    else
        nouv->initialiserGlissiere(_refpos, _basepos, _baseposfin, _plan3D);
    nouv->initialiserOrigine();
    m_Filles.push_back(nouv);

    if(!(nouv->TestRefPos()))
    {
        delete m_Filles[m_Filles.size()-1];
        m_Filles.erase(m_Filles.begin()+m_Filles.size()-1);
        std::cout << "[e] liaison incorrect" << std::endl;
    }
}

///*************************///
///      INITIALISATION     ///
///*************************///

/* Initialisation du block */
// reinitialise le bloc a nul
void Block::initialiser(double _classe, std::string _id, Coords _taille, Couleur _couleur)
{
    m_classe = _classe;
    m_id = _id;
    m_origine = {0,0};
    m_taille = {_taille.getX(),_taille.getY()};
    m_couleur = _couleur;
    m_Mere = nullptr;
}

/* Initialisation de la lisaison */
// a partir de la methode de la class liaison
void Block::initialiserLiaison(Coords _refpos, Coords _basepos, bool _plan3D)
{
    unsigned int _plan;
    if(_plan3D)
    {
        _plan = m_Mere->getLiaison()->getPlan() + 1;
    }
    else
    {
        if(m_Mere!=NULL)
        {
            _plan = m_Mere->getLiaison()->getPlan();
        }
        else
        {
            _plan = 0;
        }
    }
    m_liaison = new Liaison(_refpos,_basepos,_plan);
}

void Block::initialiserGlissiere(Coords _refpos, Coords _basepos, Coords _baseposfin, bool _plan3D)
{
    unsigned int _plan;
    if(_plan3D)
    {
        _plan = m_Mere->getLiaison()->getPlan() + 1;
    }
    else
    {
        if(m_Mere!=NULL)
        {
            _plan = m_Mere->getLiaison()->getPlan();
        }
        else
        {
            _plan = 0;
        }
    }
    //LiaisonGlissiere* glissiere = dynamic_cast<LiaisonGlissiere*>()
    // test
    LiaisonGlissiere* nouv = new LiaisonGlissiere(_refpos,_basepos,_baseposfin,_plan);
    m_liaison = nouv;
    //m_liaison = new LiaisonGlissiere(_refpos,_basepos,_baseposfin,_plan);
}

/* Initialisation de m_origine */
// recupere l'origine de la mere et la soustrait a sa position de reference
void Block::initialiserOrigine()
{
    if(m_Mere == nullptr)
    {
        m_origine = m_liaison->getBasepos() - m_liaison->getRefpos();
    }
    else
    {
        m_origine = m_Mere->getOrigine() + m_liaison->getBasepos() - m_liaison->getRefpos();
    }
}


///*************************///
///         DESSINER        ///
///*************************///

/* Dessin d'un block */
// appel de la methode svg pour dessiner un bloc sans contour
void Block::dessiner(Svgfile &svgout)const
{
    svgout.addRectangle(m_origine.getX(), m_origine.getY(),
                        m_origine.getX(), m_origine.getY() + m_taille.getY(),
                        m_origine.getX() + m_taille.getX(), m_origine.getY(),
                        m_origine.getX() + m_taille.getX(), m_origine.getY() + m_taille.getY(),
                        m_couleur);
}

void Block::toutDessiner(Svgfile &svgout) const
{
    if (!m_Filles.size())
    {}
    else
    {
        for(const auto& petit_fils : m_Filles)
        {
            petit_fils->dessiner(svgout);
            petit_fils->toutDessiner(svgout);
        }

    }
}

/* Dessin liaison de base */
// affichage svg d'une croix noir a l'emplacement de la liaison de base
void Block::dessinerLiaisonsBase(Svgfile& svgout)const
{
    // on regarde si la couleur de la mere et de la fille n'a pas une de ses valeurs trop foncee (definir avec MAX_COLOR : valeur de reference)
    std::string couleur {"white"};
    if ((((int)getMere()->getCouleur().getBleu() > MAX_COLOR) && ((int)m_couleur.getBleu() > MAX_COLOR))
            || (((int)(int)getMere()->getCouleur().getVert() > MAX_COLOR) && ((int)m_couleur.getBleu() > MAX_COLOR))
            || (((int)(int)getMere()->getCouleur().getRouge() > MAX_COLOR) && ((int)m_couleur.getBleu() > MAX_COLOR)))
        couleur = "black";
    LiaisonGlissiere* glissiere = dynamic_cast<LiaisonGlissiere*>(m_liaison);
    if (glissiere)
    {
        // dessin de la croix position de base fin
        svgout.addCross(m_Mere->getOrigine().getX() + glissiere->getFinbasepos().getX(), m_Mere->getOrigine().getY() + glissiere->getFinbasepos().getY(), 6, couleur);
        // dessin du trait
        svgout.addLine(m_Mere->getOrigine().getX() + glissiere->getBasepos().getX(), m_Mere->getOrigine().getY() + glissiere->getBasepos().getY(),
                       m_Mere->getOrigine().getX() + glissiere->getFinbasepos().getX(), m_Mere->getOrigine().getY() + glissiere->getFinbasepos().getY(), couleur);
    }

    // dessin de la croix position de base
    svgout.addCross(m_Mere->getOrigine().getX() + m_liaison->getBasepos().getX(), m_Mere->getOrigine().getY() + m_liaison->getBasepos().getY(), 6, couleur);

}

/* Dessin liaison de reference */
// affichage svg d'une croix rouge a l'emplacement de la liaison de reference
void Block::dessinerLiaisonsRef(Svgfile& svgout)const
{
    std::string couleur {"red"};
    // si la fille est de couleur rouge alors on change la couleur
    if ((int)m_couleur.getRouge() > 200)
        couleur = "blue";
    svgout.addCross(m_origine.getX() + m_liaison->getRefpos().getX(), m_origine.getY() + m_liaison->getRefpos().getY(), 4, couleur);
}

/* Dessin de toutes les liaisons */
// appel les deux methodes de dessin de liaisons recursivement
// la croix de la ref de base est plus grande et est donc affichee en premier
// cela permet d'eviter que l'une cache l'autre, sachant qu'elles sont censees etre superposees
void Block::toutDessinerLiaisons(Svgfile& svgout) const
{
    // si le tableau de fille est vide c'est donc une feuille
    if (!m_Filles.size())
    { }
    else
    {
        for(auto petit_fils : m_Filles)
        {
            petit_fils->dessinerLiaisonsBase(svgout);
            petit_fils->dessinerLiaisonsRef(svgout);
            petit_fils->toutDessinerLiaisons(svgout);
        }
    }
}

/* Affichage de l'ID */
// methode qui permet d'afficher l'id d'un bloc sur le svg
void Block::dessinerId(Svgfile &svgout) const
{
    // on ecrit le nom du bloc en noir uniquement si la couleur du block de base n'est pas trop sombre
    if (((int)m_couleur.getBleu() > MAX_COLOR) || ((int)m_couleur.getVert() > MAX_COLOR) || ((int)m_couleur.getRouge() > MAX_COLOR))
        svgout.addText(m_origine.getX()+(m_taille.getX()/2) - (m_id.size())*3.5,m_origine.getY()+(m_taille.getY()/2)+3.5,m_id,"black");
    else
        svgout.addText(m_origine.getX()+(m_taille.getX()/2) - (m_id.size())*3.5,m_origine.getY()+(m_taille.getY()/2)+3.5,m_id,"white");
}

/* Affichage de tous les ID */
// methode recursive qui utilise dessinerId pour afficher tous les Id
void Block::toutDessinerId(Svgfile& svgout) const
{
    // si le tableau de fille est vide c'est donc une feuille
    if (!m_Filles.size())
    { }
    else
    {
        for(auto petit_fils : m_Filles)
        {
            petit_fils->dessinerId(svgout);
            petit_fils->toutDessinerId(svgout);
        }
    }
}

///************************///
///    METHODES DE TEST    ///
///************************///

/* methode de test de la liaison */
//cette methode renvoie un booléen : true si la liaison est ok, false si la liaison est mal initialisée
bool Block::TestRefPos()const
{
    bool test = 0;

    if(RefPosDansBloc(*m_liaison, m_taille))
    {
        if(BasePosDansBlocMere(*m_liaison, m_Mere))
        {
            if(MemePlan(*m_liaison, m_Mere))
            {
                if(TestBordure(m_taille, m_liaison->getRefpos(), m_liaison->getBasepos(), m_liaison->getPlan(), m_id, m_Mere))
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

///************************///
///       TRANSLATION      ///
///************************///

void Block::translation(int distance)
{
    if (distance == 0)
    { }

    else/// on verifie que il y a rien derriere sur le meme plan
    {
        // si on a bien une glissiere
        LiaisonGlissiere* glissiere = dynamic_cast<LiaisonGlissiere*>(m_liaison);
        if (glissiere)
        {
            int deplacement = 0;
            bool fin = false;
            // on va de la position a l'arrivee
            while((deplacement < abs(distance)) && (fin == false))
            {
                if (distance > 0)
                {
                    // on regarde l'axe de la glissiere
                    // vertical : depend de y
                    if (!(glissiere->getBasepos().getX() - glissiere->getFinbasepos().getX()))
                    {

                        /// on verifie que il y a rien devant sur le meme plan
                        //if()
                        {
                            fin = checkGlissiere(true,false);
                            if (fin)
                                fin = parcourirSetOrigine(true, false);
                        }
                    }

                    // horizontal : ici de x
                    if (!(glissiere->getBasepos().getY() - glissiere->getFinbasepos().getY()))
                    {
                        /// on verifie que il y a rien devant sur le meme plan
                        //if()
                        {
                            fin = checkGlissiere(true,true);
                            if (fin)
                                fin = parcourirSetOrigine(true, true);
                        }
                    }
                }

                else
                {
                    // on regarde l'axe de la glissiere
                    // vertical : y
                    if (!(glissiere->getBasepos().getX() - glissiere->getFinbasepos().getX()))
                    {
                        /// on verifie que il y a rien derriere sur le meme plan
                        //if()
                        {
                            fin = checkGlissiere(false,false);
                            if (fin)
                                fin = parcourirSetOrigine(false, false);
                        }
                    }

                    // horizontal : x
                    if (!(glissiere->getBasepos().getY() - glissiere->getFinbasepos().getY()))
                    {
                        /// on verifie que il y a rien derriere sur le meme plan
                        //if()
                        {
                            fin = checkGlissiere(false,true);
                            if (fin)
                                fin = parcourirSetOrigine(false, true);
                        }
                    }
                }
                deplacement++;
            }
        }
        else
        {
            std::cout << "[e] " << m_id << " n'est pas sur une glissiere" << std::endl;
        }
    }
}

// si gain = true : +
// si gain = false -
// si axe = true : x
// si axe = false : y

bool Block::parcourirSetOrigine(bool gain, bool axe)
{
    if(gain)
    {
        if(axe)
        {
            // on regarde si il y a collision
            if(checkNoCollision())
            {
                std::cout << "pas de collision" << std::endl;
                m_origine.modifierX(m_origine.getX()+1);
            }
            else
            {
                std::cout << "collision" << std::endl;
                return false;
            }
        }

        else
        {
            // on regarde si il y a collision
            if(checkNoCollision())
            {
                std::cout << "pas de collision" << std::endl;
                m_origine.modifierY(m_origine.getY()+1);
            }
            else
            {
                std::cout << "collision" << std::endl;
                return false;
            }
        }
    }
    else
    {
        if(axe)
        {
            // on regarde si il y a collision
            if(checkNoCollision())
            {
                std::cout << "pas de collision" << std::endl;
                m_origine.modifierX(m_origine.getX()-1);
            }
            else
            {
                std::cout << " collision" << std::endl;
                return false;
            }
        }

        else
        {
            // on regarde si il y a collision
            if(checkNoCollision())
            {
                std::cout << "pas de collision" << std::endl;
                m_origine.modifierY(m_origine.getY()-1);
            }
            else
            {
                std::cout << "collision" << std::endl;
                return false;
            }
        }
    }

    // si on est en bout de chaine
    if (!m_Filles.size())
    {
        std::cout << " -pas de fille" << std::endl;
    }
    else
    {
        // sinon on se ballade dans les filles
        for(const auto& petit_fils : m_Filles)
        {
            std::cout << " -etude fille" << std::endl;
            bool valeur = petit_fils->parcourirSetOrigine(gain,axe);
            std::cout << "crash" << std::endl;
            if(!valeur)
            {
                std::cout << " -sortie de boucle" << std::endl;
                return false;
            }
        }
    }
    return false;
}

// si gain = true : +
// si gain = false -
// si axe = true : x
// si axe = false : y
bool Block::checkGlissiere(bool gain, bool axe)
{
    LiaisonGlissiere* glissiere = dynamic_cast<LiaisonGlissiere*>(m_liaison);
    if(gain)
    {
        if(axe)
        {
            // on regarde si la positon de reference du bloc est bien dans la glissiere de sa mere
            if(((m_origine.getX() + m_liaison->getRefpos().getX()+1 <= m_Mere->getOrigine().getX() + glissiere->getFinbasepos().getX())
                    && (m_origine.getX() + m_liaison->getRefpos().getX()+1 >= m_Mere->getOrigine().getX() + glissiere->getBasepos().getX()))
                    || ((m_origine.getX() + m_liaison->getRefpos().getX()+1 >= m_Mere->getOrigine().getX() + glissiere->getFinbasepos().getX())
                        && (m_origine.getX() + m_liaison->getRefpos().getX()+1 <= m_Mere->getOrigine().getX() + glissiere->getBasepos().getX())))
            {
                return true;
            }
            else
            {
                std::cout << "[i] " << m_id << " est en fin de glissiere"<< std::endl;
                return false;
            }
        }

        else
        {
            // on regarde si la positon de reference du bloc est bien dans la glissiere de sa mere
            if(((m_origine.getY() + m_liaison->getRefpos().getY()+1 <= m_Mere->getOrigine().getY() + glissiere->getFinbasepos().getY())
                    && (m_origine.getY() + m_liaison->getRefpos().getY()+1 >= m_Mere->getOrigine().getY() + glissiere->getBasepos().getY()))
                    || ((m_origine.getY() + m_liaison->getRefpos().getY()+1 >= m_Mere->getOrigine().getY() + glissiere->getFinbasepos().getY())
                        && (m_origine.getY() + m_liaison->getRefpos().getY()+1 <= m_Mere->getOrigine().getY() + glissiere->getBasepos().getY())))
            {
                return true;
            }
            else
            {
                std::cout << "[i] " << m_id << " est en fin de glissiere"<< std::endl;
                return false;
            }
        }
    }
    else
    {
        if(axe)
        {
            // on regarde si la positon de reference du bloc est bien dans la glissiere de sa mere
            if(((m_origine.getX() + m_liaison->getRefpos().getX()-1 <= m_Mere->getOrigine().getX() + glissiere->getFinbasepos().getX())
                    && (m_origine.getX() + m_liaison->getRefpos().getX()-1 >= m_Mere->getOrigine().getX() + glissiere->getBasepos().getX()))
                    || ((m_origine.getX() + m_liaison->getRefpos().getX()-1 >= m_Mere->getOrigine().getX() + glissiere->getFinbasepos().getX())
                        && (m_origine.getX() + m_liaison->getRefpos().getX()-1 <= m_Mere->getOrigine().getX() + glissiere->getBasepos().getX())))
            {
                return true;
            }
            else
            {
                std::cout << "[i] " << m_id << " est en fin de glissiere"<< std::endl;
                return false;
            }
        }

        else
        {
            // on regarde si la positon de reference du bloc est bien dans la glissiere de sa mere
            if(((m_origine.getY() + m_liaison->getRefpos().getY()-1 <= m_Mere->getOrigine().getY() + glissiere->getFinbasepos().getY())
                    && (m_origine.getY() + m_liaison->getRefpos().getY()-1 >= m_Mere->getOrigine().getY() + glissiere->getBasepos().getY()))
                    || ((m_origine.getY() + m_liaison->getRefpos().getY()-1 >= m_Mere->getOrigine().getY() + glissiere->getFinbasepos().getY())
                        && (m_origine.getY() + m_liaison->getRefpos().getY()-1 <= m_Mere->getOrigine().getY() + glissiere->getBasepos().getY())))
            {
                return true;
            }
            else
            {
                std::cout << "[i] " << m_id << " est en fin de glissiere"<< std::endl;
                return false;
            }
        }
    }
}

bool Block::checkNoCollision()
{
    /// a faire dans le cadre d'un cercle
    /*BlockCercle* cercle = dynamic_cast <BlockCercle*> (this);
    // dans le cas d'un cercle
    if (cercle)
    {

    }
    // dans le cas de rectangle
    else*/
    {
        ///on le check avec tout les blocs du meme plan
        if(contactRectangle())
        {
            std::cout << m_id <<" collision !"<<std::endl;
            return true;
        }
    }

    // sinon on se ballade dans les filles
    for(const auto& petit_fils : m_Filles)
    {
        if (!petit_fils->checkNoCollision())
        {
            std::cout << "collision de petite fille ligne 1113"<<std::endl;
            return true;
        }
    }
    return false;
}


bool Block::contactRectangle ()
{
    if (!m_Filles.size())
    {
        return false;
    }
    Block* racine = trouverRacine(*this);
    for (const auto& petit_fils : racine->getFilles())
    {
        if(m_liaison->getPlan() == petit_fils->getLiaison()->getPlan())
        {
            if((m_origine.getX() >= petit_fils->getOrigine().getX() + petit_fils->getTaille().getX())
                    || (petit_fils->getOrigine().getX() >= m_origine.getX() + m_taille.getX())
                    || (m_origine.getY() >= petit_fils->getOrigine().getY() + petit_fils->getTaille().getY())
                    || (petit_fils->getOrigine().getY() >= m_origine.getY() + m_taille.getY()))
            {
                return true;
            }

            if (petit_fils->contactRectangle())
            {
                return true;
            }

        }
        else
        {
            return false;
        }
    }
}

///******************************************************************************************************************
///                                                                                                             *****
///                               FONCTIONS LIEES A LA CLASSE BLOCK                                             *****
///                                                                                                             *****
///******************************************************************************************************************

///************************///
///         AJOUT          ///
///************************///

/* Ajout d'un bloc sans pere */
//
void ajouterBlock(Block &room,
                  double _classe, std::string _id, Coords _taille, Couleur _couleur,
                  Coords _refpos, Coords _basepos)
{
    room.initialiser(_classe, _id, _taille, _couleur);
    room.initialiserLiaison(_refpos, _basepos, 0);
    room.initialiserOrigine();
    //std::cout << "[i] position de la liaison : " << bRoom.getLiaison()->getBasepos() << std::endl;
}

///************************///
///   FONCTIONS DE COORDS  ///
///************************///

bool MemePlan(Liaison &m_liaison, Block *m_Mere)
{

    if(m_liaison.getPlan() == m_Mere->getLiaison()->getPlan())
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

bool RefPosDansBloc(Liaison &m_liaison, Coords m_taille)
{

    if(m_liaison.getRefpos() <= m_taille)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

bool BasePosDansBlocMere(Liaison &m_liaison, Block* m_Mere)
{

    if(m_liaison.getBasepos() <= m_Mere->getTaille())
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

bool TestBordure(Coords m_taille, Coords m_refpos, Coords m_basepos, unsigned int m_plan, std::string m_id, Block *m_Mere)
{
    bool test = 0;

    if(RefPosSurBordure(m_refpos, m_taille))
    {
        if(BasePosSurBordure(m_basepos, m_Mere))
        {
            if(TestBordureAdjacente(m_taille, m_refpos, m_basepos, m_plan, m_id, m_Mere))
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

bool RefPosSurBordure(Coords m_refpos, Coords m_taille)
{

    if(m_refpos.getX() == 0 || m_refpos.getX() == m_taille.getX() || m_refpos.getY() == 0 || m_refpos.getY() == m_taille.getY())
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

bool BasePosSurBordure(Coords m_basepos, Block* m_Mere)
{

    if(m_basepos.getX() == 0 || m_basepos.getX() == m_Mere->getTaille().getX() || m_basepos.getY() == 0 || m_basepos.getY() == m_Mere->getTaille().getY())
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

bool TestBordureAdjacente(Coords m_taille, Coords m_refpos, Coords m_basepos, unsigned int m_plan, std::string m_id, Block* m_Mere)
{

    bool test = 0;

    if(m_plan == m_Mere->getLiaison()->getPlan())
    {
        if(BlocADroiteDeMere(m_refpos, m_basepos, m_Mere))
        {
            test = 1;
        }
        else if(BlocAGaucheDeMere(m_refpos, m_basepos, m_taille))
        {
            test = 1;
        }
        else if(BlocEnDessousDeMere(m_refpos, m_basepos, m_Mere))
        {
            test = 1;
        }
        else if(BlocAuDessusDeMere(m_refpos, m_basepos, m_taille))
        {

            test = 1;
        }
        else
        {
            std::cout << "[e]" << m_id << " : " << "Appui situe dans le bloc mere" << std::endl;
        }
    }
    else
    {
        test = 1;
    }
    return test;
}

bool BlocADroiteDeMere(Coords m_refpos, Coords m_basepos, Block* m_Mere)
{

    if(m_refpos.getX() == 0 && m_basepos.getX() == m_Mere->getTaille().getX())
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

bool BlocAGaucheDeMere(Coords m_refpos, Coords m_basepos, Coords m_taille)
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

bool BlocEnDessousDeMere(Coords m_refpos, Coords m_basepos, Block* m_Mere)
{

    if(m_refpos.getY() == 0 && m_basepos.getY() == m_Mere->getTaille().getY())
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

bool BlocAuDessusDeMere(Coords m_refpos, Coords m_basepos, Coords m_taille)
{

    if(m_refpos.getY() == m_taille.getY() && m_basepos.getY() == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

///************************///
///   PARCOURS ET RACINE   ///
///************************///

Block* trouverRacine(Block &block)
{
    if(block.getMere() == nullptr)
    {
        return &block;
    }
    else
    {
        Block* p;
        p = trouverRacine(*block.getMere());

        if(p != nullptr)
        {
            return p;
        }
    }
    return nullptr;
}

Block* parcourir(std::string id, const Block &room)
{
    // si on est en bout de chaine
    if (!room.getFilles().size())
    {
        return nullptr;
    }
    // sinon on se ballade dans les filles
    for(const auto& petit_fils : room.getFilles())
    {
        // si le petit fils a la bonne id on le retourne
        if (petit_fils->getId() == id)
        {
            return petit_fils;
        }
        // sinon si le petit fils est en bout de chaine
        else if (!petit_fils->getFilles().size())
        { }
        //sinon on le parcours à nouveau
        else
        {
            Block* p;
            p = parcourir(id,*petit_fils);

            if(p != nullptr)
            {
                return p;
            }
        }
    }
    return nullptr;
}
