#include "menu.h"

bool menu(Block *racine)
{
    Block* iterateur = trouverRacine(*racine);
    bool fin = true;
    char typeCommande;
    std::cin >> typeCommande;
    switch (typeCommande)
    {
        case '@':
        {
            std::string nom;
            std::cin >> nom;

            iterateur = parcourir(nom,*racine);
            if(iterateur==nullptr)
            {
                std::cout << std::endl;
                std::cout << "[e] " << nom << " n'existe pas"<<std::endl;
            }
            else
            {
                std::string commande;
                std::cin >> commande;
                if(commande == "move")
                {
                    int deplacement = 0;
                    std::cin >> deplacement;
                    iterateur->translation(deplacement);
                    break;
                }
                else
                {
                    std::cout<<std::endl;
                    std::cout << "[e] " << commande << " n'est pas reconnu" << std::endl;
                }

            }
        }
        break;

        case '!':
        {

        }
        break;

        default:
        {
            std::cout << "[e] " << typeCommande << " n'est pas reconnu" << std::endl;
        }
        break;
    }

    dessinerScene(*racine);
    //std::cout << "trouver racine : " << trouverRacine(*blockIterateur)->getId() << std::endl;

    return fin;
}

// dans le cadre de l'utilisation du polymorphisme il est necessaire de passer par des adresses ou reference
void creerScene(Block* iterateur)
{
    ajouterBlock(*iterateur, 0, "room", {LARGEUR_SCENE,HAUTEUR_SCENE}, {50,200,200}, {0,0}, {0,0});
    iterateur->ajouterFilleBordure(0, "sol", {LARGEUR_SCENE,50}, {0,101,200}, {0, 250,0}, {LARGEUR_SCENE/2,50}, {LARGEUR_SCENE/2,HAUTEUR_SCENE}, true);

    //on rentre dans les filles
    iterateur = iterateur->getFille(0);

    iterateur->ajouterFille(0, "arm1", {25,HAUTEUR_SCENE-50}, {99,0,0}, {0,HAUTEUR_SCENE-50}, {0,0}, false);

    iterateur->ajouterFilleGlissiereBordure(0, "robot", {25,50}, {180,180,40}, {0,0,0}, {12,50}, {200,0}, {LARGEUR_SCENE-200,0}, false);
    iterateur = iterateur->getFille(1);
    iterateur->ajouterFilleCercleBordure(0, "tete", 20, {180,180,40}, {0,0,0}, {0,20}, {12,0},false);
    iterateur = iterateur->getFille(0);
    iterateur->ajouterFilleCercleBordure(0, "oeil", 6, {200,20,20}, {0,0,0}, {0,0}, {-7,0}, true);
    iterateur->ajouterFilleCercleBordure(0, "oeil", 6, {200,20,20}, {0,0,0}, {0,0}, {7,0}, true);

    iterateur = iterateur->getMere();
    iterateur->ajouterFilleBordure(0, "arm", {25,10}, {180,180,40}, {0,0,0}, {0,5}, {25,15}, false);
    iterateur->ajouterFilleBordure(0, "arm", {25,10}, {180,180,40}, {0,0,0}, {25,5}, {0,15}, false);
    iterateur->ajouterFilleBordure(0, "", {25,15}, {220,220,60}, {0,0,0}, {0,0}, {0,35}, true);

    iterateur = iterateur->getFille(1);
    iterateur->ajouterFilleCercleBordure(0, "hand", 5, {220,220,60}, {0,0,0}, {-5,0}, {25,5}, false);

    iterateur = iterateur->getMere();
    iterateur = iterateur->getFille(2);
    iterateur->ajouterFilleCercleBordure(0, "hand", 5, {220,220,60}, {0,0,0}, {5,0}, {0,5}, false);
}

void dessinerScene(const Block &room)
{
    Svgfile svgout;
    /* attention il faut dessiner le room à part */
    room.dessiner(svgout);
    toutDessiner(svgout,room);
    //toutDessinerPlan(svgout,room,2);

    std::cout << "[i] croix rouge/bleu = position de reference / croix noir/blanc = position de base" << std::endl;
    room.toutDessinerLiaisons(svgout);
    //room.toutDessinerId(svgout);
}

void toutDessiner(Svgfile &svgout,const Block &room)
{
    if (!room.getFilles().size())
    {}
    else
    {
        for(const auto& petit_fils : room.getFilles())
        {
            petit_fils->dessiner(svgout);
            toutDessiner(svgout,*petit_fils);
        }

    }
}

void toutDessinerPlan(Svgfile &svgout,const Block &room, unsigned int plan)
{
    if (!room.getFilles().size())
    {}
    else
    {
        for(const auto& petit_fils : room.getFilles())
        {
            std::cout << " " << petit_fils->getLiaison()->getPlan() << ",";
            if (petit_fils->getLiaison()->getPlan() <= plan)
                petit_fils->dessiner(svgout);
            toutDessinerPlan(svgout,*petit_fils,plan);
        }

    }
}
