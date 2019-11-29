
#include "block.h"
#include "../svg/svgfile.h"
#include "liaison.h"
#include "block_cercle.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream> /// Pour les fichiers
#include <sstream> /// Pour les ostringstream

#define HAUTEUR_SCENE 600
#define LARGEUR_SCENE 1000

/// Definition lecture fichier :
#define FICHIER "sauvegarde.rom"

///*************************///
///      CONSTRUCTEURS      ///
///*************************///

/* constructeur de base */
Block::Block (std::string _id, Coords _taille, Couleur _couleur, Block* _Mere) :
    m_id{_id}, m_origine{0,0}, m_taille{_taille}, m_couleur{_couleur}, m_Mere{_Mere}, m_liaison{{0,0},{0,0},0}
{}

/* Constructeur avec Initialisation nul */
Block::Block() : m_id{"A"}, m_origine{0,0}, m_taille{0,0}, m_couleur{10,10,10}, m_Mere{nullptr}, m_liaison{{0,0},{0,0},0}
{}

///*************************///
///          AJOUT          ///
///*************************///

/* Creer une fille */
// cree une nouvelle fille a partir de la mere
void Block::ajouterFille(std::string _id, Coords _taille, Couleur _couleur, Coords _refpos, Coords _basepos, bool _plan3D)
{
    Block* nouv = new Block{_id, _taille, _couleur, this};
    nouv->initialiserLiaison(_refpos, _basepos, _plan3D);
    nouv->initialiserOrigine();
    m_Filles.push_back(nouv);

    //methode qui teste de la position du nouveau block dans la scene
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

/*
 Creer une fille couleur avec bordures
// cree une nouvelle fille a partir de la mere
void Block::ajouterFilleBordure(double _classe,Coords _taille, std::string _id, Coords _refpos, Coords _basepos, bool _plan3D, Couleur _couleur, Couleur _bordure)
{
    BlockBordure* nouv = new BlockBordure{_classe,_id, _taille, this, _couleur, _bordure};
    nouv->initialiserLiaison(_refpos, _basepos, _plan3D);
    nouv->initialiserOrigine();
    m_Filles.push_back(nouv);
}*/

/*void Block::ajouterFilleCercle(double _classe,double _rayon, std::string _id, double _angle, Coords _basepos, bool _plan3D, Couleur _couleur)
{
    BlockCercle* nouv = new BlockCercle{_id, _rayon, _couleur, this};
    nouv->initialiserLiaison(_angle, _basepos, _plan3D);
    nouv->initialiserOrigine();
    m_Filles.push_back(nouv);
}*/

///*************************///
///      INITIALISATION     ///
///*************************///

/* Initialisation du block */
// reinitialise le bloc a nul
void Block::initialiser(std::string _id, Coords _taille, Couleur _couleur)
{
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
    if(_plan3D == 1) {
            _plan = m_Mere->getLiaison().getPlan() + 1;
    }
    else {
        if(m_Mere!=NULL) {
            _plan = m_Mere->getLiaison().getPlan();
        }
        else {
            _plan = 0;
        }
    }
    m_liaison.setteur(_refpos,_basepos,_plan);
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
            if(TestBordure(m_taille, m_liaison.getRefpos(), m_liaison.getBasepos(), m_liaison.getPlan(), m_Mere))
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
///SAUVEGARDE ET CHARGEMENT///
///************************///

/* Sauvegarde global de la scène */
/*void Block::sauvegarde()
{
    sauvegarderScene1(m_Filles);
}

/* Sauvegarde des filles pour la sauvegarde standard */
// Methode qui recupere un vecteur de pointeur de block pour les sauvegarder
/*void Block::sauvegarderScene1(std::vector <Block*> s)
{
    std::ofstream ofs{FICHIER};

    for (auto i : s)///Niveau 0
    {
        if ((i->m_classe) == 0)
        {
            ofs << i->m_classe << " " << i->m_id << " " << i->m_taille.getX() << " " << i->m_taille.getY() << " " << i->m_liaison.getRefpos().getX() << " " << i->m_liaison.getRefpos().getY() << " " << i->m_liaison.getBasepos().getX() << " " << i->m_liaison.getBasepos().getY() << " " << i->m_liaison.getPlan() << std::endl;
        }
        ofs << "[" << std::endl;
        for ( auto v : i->m_Filles)///Niveau 1
        {
            if ((v->m_classe) == 0){
                ofs << "    " << v->m_classe << " " << v->m_id << " " << v->m_taille.getX() << " " << v->m_taille.getY() << " " << v->m_liaison.getRefpos().getX() << " " << v->m_liaison.getRefpos().getY() << " " << v->m_liaison.getBasepos().getX() << " " << v->m_liaison.getBasepos().getY() << " " << v->m_liaison.getPlan() << std::endl;
            }
            /*if ((v->m_classe) == 1){
                BlockBordure* a1 = dynamic_cast<BlockBordure*>(v);
                ofs << "    " << a1->m_classe << " " << a1->m_id << " " << a1->m_taille.getX() << " " << a1->m_taille.getY() << " " << a1->m_liaison.getRefpos().getX() << " " << a1->m_liaison.getRefpos().getY() << " " << a1->m_liaison.getBasepos().getX() <<" "<< a1->m_liaison.getBasepos().getY() << " " << a1->m_liaison.getPlan()<<" "<< (int)a1->getCouleur().getRouge() << " " << (int)a1->getCouleur().getVert() << " " << (int)a1->getCouleur().getBleu() << " " << (int)a1->getBordure().getRouge() << " " << (int)a1->getBordure().getVert() << " " << (int)a1->getBordure().getBleu() <<  std::endl;
            }
            if ((v->m_classe) == 2){
                BlockBordure* b1 = dynamic_cast<BlockBordure*>(v);
                ofs << "    " << b1->m_classe << " " << b1->m_id << " " << b1->m_taille.getX() << " " << b1->m_taille.getY() << " " << b1->m_liaison.getRefpos().getX() << " " << b1->m_liaison.getRefpos().getY() << " " << b1->m_liaison.getBasepos().getX() <<" "<< b1->m_liaison.getBasepos().getY() << " " << b1->m_liaison.getPlan()<<" "<< (int)b1->getCouleur().getRouge() << " " << (int)b1->getCouleur().getVert() << " " << (int)b1->getCouleur().getBleu() <<  std::endl;
            }
            if ((v->m_classe) == 3){
                BlockCercle* c1 = dynamic_cast<BlockCercle*>(v);
                ofs << "    " << c1->m_classe << " " << c1->m_id << " " << c1->m_rayon << " " << c1->m_angle << " " <<  std::endl;
            }*/

            /*ofs << "    [" << std::endl;


            for ( auto z : v->m_Filles )///Niveau 2
            {
                ofs << "        " << z->m_classe << " " << z->m_id << " " << z->m_taille.getX() << " " << z->m_taille.getY() << " " << z->m_liaison.getRefpos().getX() << " " << z->m_liaison.getRefpos().getY() << " " << z->m_liaison.getBasepos().getX() << " " << z->m_liaison.getBasepos().getY()<< " " << z->m_liaison.getPlan() <<  std::endl;
                ofs << "        [" << std::endl;
                for ( auto b : z->m_Filles )///Niveau 3
                {
                    ofs << "            " << b->m_classe << " " << b->m_id << " " << b->m_taille.getX() << " " << b->m_taille.getY() << " " << b->m_liaison.getRefpos().getX() << " " << b->m_liaison.getRefpos().getY() << " " << b->m_liaison.getBasepos().getX() << " " << b->m_liaison.getBasepos().getY()<< " " << b->m_liaison.getPlan() <<  std::endl;
                    ofs << "            [" << std::endl;
                    for ( auto r : b->m_Filles )///Niveau 4
                    {
                        ofs << "                " << r->m_classe << " " << r->m_id << " " << r->m_taille.getX() << " " << r->m_taille.getY() << " " << r->m_liaison.getRefpos().getX() << " " << r->m_liaison.getRefpos().getY() << " " << r->m_liaison.getBasepos().getX() << " " << r->m_liaison.getBasepos().getY()<< " " << r->m_liaison.getPlan() <<  std::endl;
                    }
                    ofs << "            ]" << std::endl;
                }
                ofs << "        ]" << std::endl;
            }
            ofs << "    ]" << std::endl;
        }
        ofs << "]" << std::endl;
    }
}

/* Sauvegarde des filles pour la sauvegarde après la lecture du fichier de sauvegarde pour vérification */
// Methode qui recupere un vecteur de pointeur de block pour les sauvegarder
/*void Block::sauvegarderScene2(std::vector <Block*> s)
{
    std::ofstream ofs{"sauvegarde2.rom"};

    for (auto i : s)///Niveau 0
    {
        ofs << i->m_classe << " " << i->m_id << " " << i->m_taille.getX() << " " << i->m_taille.getY() << " " << i->m_liaison.getRefpos().getX() << " " << i->m_liaison.getRefpos().getY() << " " << i->m_liaison.getBasepos().getX() << " " << i->m_liaison.getBasepos().getY() << " " << i->m_liaison.getPlan() << std::endl;
        ofs << "[" << std::endl;
        for ( auto v : i->m_Filles)///Niveau 1
        {
            ofs << "    " << v->m_classe << " " << v->m_id << " " << v->m_taille.getX() << " " << v->m_taille.getY() << " " << v->m_liaison.getRefpos().getX() << " " << v->m_liaison.getRefpos().getY() << " " << v->m_liaison.getBasepos().getX() << " " << v->m_liaison.getBasepos().getY()<< " " << v->m_liaison.getPlan() <<  std::endl;
            ofs << "    [" << std::endl;
            for ( auto z : v->m_Filles )///Niveau 2
            {
                ofs << "        " << z->m_classe << " " << z->m_id << " " << z->m_taille.getX() << " " << z->m_taille.getY() << " " << z->m_liaison.getRefpos().getX() << " " << z->m_liaison.getRefpos().getY() << " " << z->m_liaison.getBasepos().getX() << " " << z->m_liaison.getBasepos().getY()<< " " << z->m_liaison.getPlan() <<  std::endl;
            }
            ofs << "    ]" << std::endl;
        }
        ofs << "]" << std::endl;
    }
}


void Block::chargementScene()
{
    int niveau = 0;
    /// Ouverture d'un fichier en lecture (ifstream => input file stream)
    std::ifstream ifs{FICHIER};
    /// Test ouverture, si problème alors quitter avec description de l'échec
    if ( !ifs )
        throw std::runtime_error( "Can't read/open data.txt" );
    /// Ok à partir d'ici le fichier est bien ouvert

    /// Lecture ligne par ligne : TRES IMPORTANT
    std::string ligne;
    std::getline(ifs, ligne);

    /// On a une ligne avec contenu, avec on va fabriquer un "flot chaîne"
    /// pour lire dedans comme si c'était une saisie clavier !
    std::istringstream iss{ligne};
    double classe,tailleX,tailleY,refposX,refposY,baseposX,baseposY;
    uint8_t rouge,vert,bleu;
    std::string id;
    bool plan3D;
    /// l'objet  iss  se comporte comme std::cin !
    iss >> classe ;
    iss >> id >> tailleX >> tailleY >> refposX >> refposY >> baseposX >> baseposY >> plan3D >> rouge >> vert >> bleu;

    ajouterFille(classe, {tailleX,tailleY},id, {refposX,refposY}, {baseposX,baseposY}, plan3D,{rouge,vert,bleu});

    std::cout << classe << id << tailleX << tailleY << refposX << refposY << baseposX << baseposY << plan3D << std::endl << std::endl ;

    while ( std::getline(ifs, ligne) )
    {
        /*Niv 1*//*if ( ligne.size()>=1 && ligne[0]=='[' && niveau==0 )
        {
            niveau = 1;
            std::cout << "Acces Niveau 1" << std::endl<< std::endl;
            std::getline(ifs, ligne);
        }
        if ( ligne[0]==']' && niveau == 1 )
        {
            niveau = 0;
            std::cout << "Fermeture du niveau 1" << std::endl<< std::endl;
        }
        if ( ligne[4]!='[' && ligne[4]!=']' && niveau == 1 )
        {
            std::cout << "Lecture du niveau 1" << std::endl<< std::endl;
            std::istringstream iss{ligne};
            iss >> classe ;
            iss >> id >> tailleX >> tailleY >> refposX >> refposY >> baseposX >> baseposY >> plan3D;
            std::cout << classe << id << tailleX << tailleY << refposX << refposY << baseposX << baseposY << plan3D << std::endl << std::endl ;
            getFille(0)->ajouterFille(classe, {tailleX,tailleY},id, {refposX,refposY}, {baseposX,baseposY}, plan3D,{rouge,vert,bleu});
        }
        /*Niv 2*//*if ( ligne.size()>=4 && ligne[4]=='[' && niveau==1 )
        {
            niveau = 2;
            std::cout << "Acces niveau 2" << std::endl<< std::endl;
            std::getline(ifs, ligne);
        }
        if (ligne[4]==']' && niveau == 2 )
        {
            niveau = 1;
            std::cout << "Fermeture du niveau 2" << std::endl<< std::endl;
        }
        if ( ligne[8]!='[' && ligne[8]!=']' && niveau == 2 )
        {
            std::cout << "Lecture du niveau 2" << std::endl<< std::endl;
            std::istringstream iss{ligne};
            iss >> classe ;
            iss >> id >> tailleX >> tailleY >> refposX >> refposY >> baseposX >> baseposY >> plan3D;
            std::cout << classe << id << tailleX << tailleY << refposX << refposY << baseposX << baseposY << plan3D << std::endl << std::endl ;
            getFille(0)->getFille(0)->ajouterFille(classe, {tailleX,tailleY},id, {refposX,refposY}, {baseposX,baseposY}, plan3D,{rouge,vert,bleu});
        }

    }/// Passage à la ligne suivante (prochain tour de boucle)
    sauvegarderScene2(m_Filles);
}*/


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
                  std::string _id, Coords _taille, Couleur _couleur,
                  Coords _refpos, Coords _basepos)
{
    room.initialiser(_id, _taille, _couleur);
    room.initialiserLiaison(_refpos, _basepos, 0);
    room.initialiserOrigine();
    //std::cout << "[i] position de la liaison : " << bRoom.getLiaison().getBasepos() << std::endl;
}

///************************///
///   FONCTIONS DE COORDS  ///
///************************///

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

Block* parcourir(Coords taille, Coords origine, const Block &room)
{
    // si on est en bout de chaine
    if (!room.getFilles().size())
    {
        return nullptr;
    }
    // sinon on se ballade dans les filles
    for(const auto& petit_fils : room.getFilles())
    {
        // si le petit fils a les bonnes coordonnees
        if (petit_fils->getTaille()==taille && petit_fils->getOrigine()==origine)
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
            p = parcourir(taille,origine,*petit_fils);

            if(p != nullptr)
            {
                return p;
            }
        }
    }
    return nullptr;
}

////////////////////////////////////////////////////////////////
////                                                        ////
////                                                        ////
////                  CLASS FILLE COULEUR                   ////
////                                                        ////
////                                                        ////
////////////////////////////////////////////////////////////////

///*************************///
///       OVERWRITING       ///
///*************************///

/*
BlockBordure::BlockBordure(double _classe,std::string _id, Coords _taille, Block* _Mere, Couleur _couleur, Couleur _bordure): Block(_classe,_id, _taille, _Mere, _couleur),m_bordure{_bordure}
{ }


// overwriting de dessiner pour afficher la couleur en plus
void BlockBordure::dessiner(Svgfile &svgout)const
{
    if(m_bordure != m_couleur)
        svgout.addRectangle(m_origine.getX(), m_origine.getY(),
                            m_origine.getX(), m_origine.getY() + m_taille.getY(),
                            m_origine.getX() + m_taille.getX(), m_origine.getY(),
                            m_origine.getX() + m_taille.getX(), m_origine.getY() + m_taille.getY(),
                            m_couleur,2,m_bordure);
    else
        svgout.addRectangle(m_origine.getX(), m_origine.getY(),
                            m_origine.getX(), m_origine.getY() + m_taille.getY(),
                            m_origine.getX() + m_taille.getX(), m_origine.getY(),
                            m_origine.getX() + m_taille.getX(), m_origine.getY() + m_taille.getY(),
                            m_couleur);
}
*/
