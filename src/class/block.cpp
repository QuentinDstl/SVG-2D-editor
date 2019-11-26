#include "block.h"
#include "../svg/svgfile.h"
#include "liaison.h"

/// definition lecture fichier :
#define FICHIER "sauvegarde.rom"

///*************************///
///      CONSTRUCTEURS      ///
///*************************///

/* constructeur de base */
Block::Block(std::string _id, Coords _taille, Block* _Mere) : m_id{_id}, m_origine{0,0}, m_taille{_taille}, m_Mere{_Mere}
{}

/* Constructeur avec Initialisation nul */
Block::Block() : m_id{"A"}, m_origine{0,0}, m_taille{0,0}, m_Mere{nullptr}
{}

///*************************///
/// AJOUT ET INITIALISATION ///
///*************************///

/* Initialisation du block */
// reinitialise le bloc a nul
void Block::initialiser(Coords _taille, std::string _id)
{
    m_origine = {0,0};
    m_taille = {_taille.getX(),_taille.getY()};
    m_id = _id;
    m_Mere = NULL;
}

/* Initialisation de la lisaison */
// a partir de la methode de la class liaison
void Block::initialiserLiaison(Coords _refpos, Coords _basepos, bool _plan3D)
{
    m_liaison.setteur(_refpos,_basepos,_plan3D);
}

/* Initialisation de m_origine */
// recupere l'origine de la mere et la soustrait a sa position de reference
void Block::initialiserOrigine()
{
    if(m_Mere == nullptr)
    {
        m_origine = m_liaison.getBasepos() - m_liaison.getRefpos();
    }
    else
    {
        m_origine = m_Mere->getOrigine() + m_liaison.getBasepos() - m_liaison.getRefpos();
    }
}

/* Creer une fille */
// cree une nouvelle fille a partir de la mere
void Block::ajouterFille(Coords _taille, std::string _id, Coords _refpos, Coords _basepos, bool _plan3D)
{
    Block* nouv = new Block{_id, _taille, this};
    nouv->initialiserLiaison(_refpos, _basepos, _plan3D);
    nouv->initialiserOrigine();
    m_Filles.push_back(nouv);

    //methode qui teste si le block est bien relié au block mere
    if(!(nouv->TestRefPos()))
    {
        delete m_Filles[m_Filles.size()-1];
        m_Filles.erase(m_Filles.begin()+m_Filles.size()-1);
        std::cout << "Liaison incorrect" << std::endl;
    }
    else
    {
        std::cout << nouv->m_origine << std::endl;
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
                        "grey");
}

/* Dessin de toutes des Filles */
// methode recursive qui appel la methode dessiner
// attention elle ne dessine que les filles du block this
void Block::toutDessiner(Svgfile& svgout) const
{
    // si le tableau de fille est vide c'est donc une feuille
    if (!m_Filles.size())
    {}
    else
    {
        for(auto petit_fils : m_Filles)
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
    svgout.addCross(m_Mere->getOrigine().getX() + m_liaison.getBasepos().getX(), m_Mere->getOrigine().getY() + m_liaison.getBasepos().getY(), 6, "black");
}

/* Dessin liaison de reference */
// affichage svg d'une croix rouge a l'emplacement de la liaison de reference
void Block::dessinerLiaisonsRef(Svgfile& svgout)const
{
    svgout.addCross(m_origine.getX() + m_liaison.getRefpos().getX(), m_origine.getY() + m_liaison.getRefpos().getY(), 4, "red");
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
    std::cout << m_id << " : " << m_id.size() << std::endl;
    svgout.addText(m_origine.getX()+(m_taille.getX()/2) - (m_id.size())*3.5,m_origine.getY()+(m_taille.getY()/2)+3.5,m_id,"black");
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

    if(m_liaison.getRefpos() <= m_taille)
    {
        if(m_liaison.getBasepos() <= m_Mere->getTaille())
        {
            if(TestBordure(m_taille, m_liaison.getRefpos(), m_liaison.getBasepos(), m_liaison.getPlan3D(), m_Mere))
            {
                test = 1;
            }
        }
        else
        {
            std::cout << "Appui non situe sur le bloc mere" << std::endl;
        }
    }
    else
    {
        std::cout << "Appui non situe sur le bloc fille" << std::endl;
    }
    return test;
}

///************************///
///       SAUVEGARDE       ///
///************************///

/* Sauvegarde global de la scène */
//a modifier pour toutes les filles
void Block::sauvegarde()
{
    sauvegarderScene(m_Filles);
}


/* Sauvegarde des filles */
// methode qui recupere un vercteur de pointeur de block pour les sauvegarder
void Block::sauvegarderScene(std::vector <Block*> s)
{
    std::ofstream ofs{FICHIER};

    for (auto i : s)///Niveau 0
    {
        ofs << i->m_id << " " << i->m_taille.getX() << " " << i->m_taille.getY() << " " << i->m_origine.getY() << " " << i->m_origine.getX() << std::endl;
        ofs << "[" << std::endl;
        for ( auto v : i->m_Filles)///Niveau 1
        {
            ofs << "    " << v->m_id << " " << v->m_taille.getX() << " " << v->m_taille.getY() << " " << v->m_origine.getY() << " " << v->m_origine.getX() << std::endl;
            ofs << "    [" << std::endl;
            for ( auto z : v->m_Filles )///Niveau 2
            {
                ofs << "        "<< z->m_id << " " << z->m_taille.getX() << " " << z->m_taille.getY() << " " << z->m_origine.getY() << " " << z->m_origine.getX() << std::endl;
            }
            ofs << "    ]" << std::endl;
        }
        ofs << "]" << std::endl;
    }
}

///************************///
///   TROUVER UN ELEMENT   ///
///************************///

/* Trouver l'id */
// methode recursive de parcours qui cherche l'id
// elle renvois le pointeur sur le bloc si l'id correspond sinon elle renvoit un nullptr
Block* Block::parcourir(const std::string& id)
{
    // si on est en bout de chaine
    if (!m_Filles.size())
    {
        return nullptr;
    }
    // sinon
    for(auto petit_fils : m_Filles)
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
            p = petit_fils->parcourir(id);

            if(p != nullptr)
            {
                return p;
            }
        }
    }
    return nullptr;
}

/*  */
//
bool TestBordure(Coords m_taille, Coords m_refpos, Coords m_basepos, bool m_plan3D, Block *m_Mere)
{
    bool test = 0;

    if(m_refpos.getX() == 0 || m_refpos.getX() == m_taille.getX() || m_refpos.getY() == 0 || m_refpos.getY() == m_taille.getY())
    {
        if(m_basepos.getX() == 0 || m_basepos.getX() == m_Mere->getTaille().getX() || m_basepos.getY() == 0 || m_basepos.getY() == m_Mere->getTaille().getY())
        {
            if(TestBordureAdjacente(m_taille, m_refpos, m_basepos, m_plan3D,m_Mere))
            {
                test = 1;
            }
        }
        else
        {
            std::cout << "Appui non situe sur la bordure du bloc mere" << std::endl;
        }
    }
    else
    {
        std::cout << "Appui non situe sur la bordure du bloc fille" << std::endl;
    }
    return test;
}

/*  */
//
bool TestBordureAdjacente(Coords m_taille, Coords m_refpos, Coords m_basepos, bool m_plan3D, Block* m_Mere)
{
    bool test = 0;

    if(m_plan3D == 0)
    {
        if(m_refpos.getX() == 0 && m_basepos.getX() == m_Mere->getTaille().getX())
        {
            test = 1;
        }
        else if(m_refpos.getX() == m_taille.getX() && m_basepos.getX() == 0)
        {
            test = 1;
        }
        else if(m_refpos.getY() == 0 && m_basepos.getY() == m_Mere->getTaille().getY())
        {
            test = 1;
        }
        else if(m_refpos.getY() == m_taille.getY() && m_basepos.getY() == 0)
        {
            test = 1;
        }
        else
        {
            std::cout << "Appui situe dans le bloc mere" << std::endl;
        }
    }
    else
    {
        test = 1;
    }
    return test;
}

/*  */
//
void ajouterBlock(Block &bRoom,
                  Coords _taille, std::string _id,
                  Coords _refpos, Coords _basepos)
{
    bRoom.initialiser(_taille, _id);
    bRoom.initialiserLiaison(_refpos, _basepos, 0);
    bRoom.initialiserOrigine();
    //std::cout << "[i] position de la liaison : " << bRoom.getLiaison().getBasepos() << std::endl;
}

///************************///
///   CLASS FILLE COULEUR  ///
///************************///

/*  */
//
CouleurBlock::CouleurBlock(Couleur _couleur) : m_couleur{_couleur}
{ }

/*  */
// overwriting de dessiner pour afficher la couleur en plus
void CouleurBlock::dessiner(Svgfile &svgout)const
{
    svgout.addRectangle(m_origine.getX(), m_origine.getY(),
                        m_origine.getX(), m_origine.getY() + m_taille.getY(),
                        m_origine.getX() + m_taille.getX(), m_origine.getY(),
                        m_origine.getX() + m_taille.getX(), m_origine.getY() + m_taille.getY(),
                        m_couleur);
}
