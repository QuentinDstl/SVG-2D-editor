#include <iostream>
#include <fstream>
#include <vector>

#include "src/class/block_cercle.h"
#include "src/class/coords.h"
#include "src/class/liaison.h"
#include "src/class/bordure.h"
#include "src/class/block_bordure.h"
#include "src/interface/couleur.h"
#include "src/svg/svgfile.h"
#include "src/util/util.h"
#include "src/class/block.h"

/// Lecture fichier
#define FICHIER "sauvegarde.rom"

/// Define scene
#define HAUTEUR_SCENE 600
#define LARGEUR_SCENE 1000

void creerScene(Block* room);
void dessinerScene(const Block &room);
void toutDessiner(Svgfile &svgout, const Block &room);
void toutDessinerPlan(Svgfile &svgout,const Block &room, unsigned int plan);

/*
///Main Version CHARGEMENT depuis fichier
int main()
{
    Block room;
    Block* blockIterateur = &room;

    ajouterBlock(room, 0, "room", {LARGEUR_SCENE,HAUTEUR_SCENE}, {50,200,200}, {0,0}, {0,0});

    room.chargementScene();

    dessinerScene(room);

    return 0;
}*/



///Main version CREATION puis sauvegarde
int main()
{
    Block room;
    Block* blockIterateur = &room;

    creerScene(blockIterateur);
    dessinerScene(room);

    std::cout << "trouver racine : " << trouverRacine(*blockIterateur)->getId() << std::endl;

    ///sauvegarde et chargement
    std::ofstream file {FICHIER};
    if (!file)
    {
        std::cerr << "Ouverture impossible du fichier : " << FICHIER;
    }
    else
    {
        room.sauvegarde();
    }

    return 0;
}


// dans le cadre de l'utilisation du polymorphisme il est necessaire de passer par des adresses ou reference
void creerScene(Block* iterateur)
{
    ajouterBlock(*iterateur, 0, "room", {LARGEUR_SCENE,HAUTEUR_SCENE}, {50,200,200}, {0,0}, {0,0});
    iterateur->ajouterFilleBordure(2, "sol", {LARGEUR_SCENE,50}, {0,101,200}, {0, 250,0}, {LARGEUR_SCENE/2,50}, {LARGEUR_SCENE/2,HAUTEUR_SCENE}, true);

    //on rentre dans les filles
    iterateur = iterateur->getFille(0);
    iterateur->ajouterFille(0, "arm1", {25,HAUTEUR_SCENE-50}, {99,0,0}, {0,HAUTEUR_SCENE-50}, {0,0}, false);
    iterateur->ajouterFilleBordure(2, "robot", {25,50}, {180,180,40}, {0,0,0}, {12,50}, {LARGEUR_SCENE/2,0}, false);

    iterateur = iterateur->getFille(1);
    iterateur->ajouterFilleCercleBordure(3, "tete", 20, {180,180,40}, {0,0,0}, {0,20}, {12,0},false);

    iterateur = iterateur->getFille(0);
    iterateur->ajouterFilleCercleBordure(3, "oeil", 6, {200,20,20}, {0,0,0}, {0,0}, {-7,0}, true);
    iterateur->ajouterFilleCercleBordure(3, "oeil", 6, {200,20,20}, {0,0,0}, {0,0}, {7,0}, true);

    iterateur = iterateur->getMere();
    iterateur->ajouterFilleBordure(2, "arm", {25,10}, {180,180,40}, {0,0,0}, {0,5}, {25,15}, false);
    iterateur->ajouterFilleBordure(2, "arm", {25,10}, {180,180,40}, {0,0,0}, {25,5}, {0,15}, false);
    iterateur->ajouterFilleBordure(2, "", {25,15}, {220,220,60}, {0,0,0}, {0,0}, {0,35}, true);

    iterateur = iterateur->getFille(1);
    iterateur->ajouterFilleCercleBordure(3, "hand", 5, {220,220,60}, {0,0,0}, {-5,0}, {25,5}, false);

    iterateur = iterateur->getMere();
    iterateur = iterateur->getFille(2);
    iterateur->ajouterFilleCercleBordure(3, "hand", 5, {220,220,60}, {0,0,0}, {5,0}, {0,5}, false);
}

void dessinerScene(const Block &room)
{
    Svgfile svgout;
    /* attention il faut dessiner le room à part */
    room.dessiner(svgout);
    toutDessiner(svgout,room);
    //toutDessinerPlan(svgout,room,2);

    std::cout << "[i] croix rouge/bleu = position de reference / croix noir/blanc = position de base" << std::endl;
    //room.toutDessinerLiaisons(svgout);
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
            /*
            BlockCercle* petit_fils_cercle = dynamic_cast<BlockCercle*>(petit_fils);

            if(petit_fils_cercle)
                petit_fils_cercle->dessiner(svgout);

            else
            */
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
            /*
            BlockCercle* petit_fils_cercle = dynamic_cast<BlockCercle*>(petit_fils);

            if(petit_fils_cercle)
                petit_fils_cercle->dessiner(svgout);

            else
            */
            std::cout << " " << petit_fils->getLiaison()->getPlan() << ",";
            if (petit_fils->getLiaison()->getPlan() <= plan)
                petit_fils->dessiner(svgout);
            toutDessinerPlan(svgout,*petit_fils,plan);
        }

    }
}

