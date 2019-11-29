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

/*
///Main Version CHARGEMENT depuis fichier
int main()
{
    Block room;
    Block* blockIterateur = &room; //option avec iterateur

    ajouterBlock(room, {LARGEUR_SCENE,HAUTEUR_SCENE}, "room", {0,0}, {0,0});

    room.chargementScene();

    return 0;
}
*/

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
        //room.sauvegarde();
    }

    return 0;
}


// dans le cadre de l'utilisation du polymorphisme il est necessaire de passer par des adresses ou reference
void creerScene(Block* iterateur)
{
    ajouterBlock(*iterateur, 0, "room", {LARGEUR_SCENE,HAUTEUR_SCENE}, {50,200,200}, {0,0}, {0,0});
    iterateur->ajouterFille(0, "sol", {LARGEUR_SCENE,50}, {50,50,50}, {LARGEUR_SCENE/2,50}, {LARGEUR_SCENE/2,HAUTEUR_SCENE}, 1);

    //on rentre dans les filles
    iterateur = iterateur->getFille(0);
    iterateur->ajouterFille(0, "arm1", {25,HAUTEUR_SCENE-50}, {250,0,0}, {0,HAUTEUR_SCENE-50}, {0,0}, 0);
   // iterateur->ajouterFilleBordure(1, {25,HAUTEUR_SCENE-50}, "arm2", {25,HAUTEUR_SCENE-50}, {LARGEUR_SCENE,0}, 0, {200,100,100}, {0,10,0});
    iterateur->ajouterFille(0, "block", {25,50}, {50,50,50}, {15,45}, {LARGEUR_SCENE/2,0}, 1);

    //on rentre dans les filles
    /*iterateur = iterateur->getFille(0);
    iterateur->ajouterFille("arm3", {60,20}, {50,150,100}, {0,0}, {25,HAUTEUR_SCENE/2}, 0);

    iterateur = trouverRacine(*iterateur);
    iterateur = iterateur->getFille(0);
    iterateur = iterateur->getFille(1);
    iterateur->ajouterFille("arm4", {60,20}, {200,150,100}, {60,10}, {0,HAUTEUR_SCENE/2}, 0);
    iterateur = iterateur->getFille(0);
    iterateur->ajouterFille("object1", {100,100}, {50,50,50}, {60,10},{0,10},0);

    //iterateur = trouverRacine(*iterateur);
    //iterateur = iterateur->getFille(0)->getFille(0)->getFille(0); // on est sur arm3
    //iterateur->ajouterFilleCercle(3,20,"cercle",270,{60,20},0,{50,50,50});*/

}

void dessinerScene(const Block &room)
{
    Svgfile svgout;
    /* attention il faut dessiner le room à part */
    room.dessiner(svgout);
    room.getFille(0)->dessiner(svgout);
    room.getFille(0)->getFille(0)->dessiner(svgout);
    room.getFille(0)->getFille(1)->dessiner(svgout);
    //toutDessiner(svgout,room);

    std::cout << "[i] croix rouge = position de reference / croix noir = position de base" << std::endl;
    room.toutDessinerLiaisons(svgout);
    room.toutDessinerId(svgout);
}

void toutDessiner(Svgfile &svgout,const Block &room)
{
    if (!room.getFilles().size())
    {}
    else
    {
        for(const auto& petit_fils : room.getFilles())
        {
                //BlockCercle* petit_fils_cercle = dynamic_cast<BlockCercle*>(petit_fils);

                /*if(petit_fils_cercle)
                    petit_fils_cercle->dessiner(svgout);

                else*/
                petit_fils->dessiner(svgout);
        }
            //toutDessiner(svgout,*petit_fils);
    }
}

