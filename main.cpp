#include <iostream>
#include <fstream>
#include <vector>

#include "src/class/block.h"
#include "src/class/coords.h"
#include "src/class/liaison.h"
#include "src/interface/couleur.h"
#include "src/svg/svgfile.h"
#include "src/util/util.h"

/// lecture fichier
#define FICHIER "sauvegarde.rom"

/// define scene
#define HAUTEUR_SCENE 400
#define LARGEUR_SCENE 600

void creerScene(Block &room);
void dessinerScene(const Block &room);

int main()
{

    Block room;

    std::ofstream file {FICHIER};


    if (!file)
    {
        std::cerr << "Can't write/open sauvegarde.rom\n";
    }


    creerScene(room);
    dessinerScene(room);


    return 0;
}

void creerScene(Block &room)
{

    ajouterBlock(room, {LARGEUR_SCENE,HAUTEUR_SCENE}, "room", {0,0}, {0,0});
    std::cout << " - position de la liaison : " << room.getLiaison().getBasepos() << std::endl << std::endl;
    room.ajouterFille({LARGEUR_SCENE,50}, "sol", {LARGEUR_SCENE/2,50}, {LARGEUR_SCENE/2,HAUTEUR_SCENE}, 1);
    //room.getFille(0)->ajouterFille({200,50}, "arm", {0,50}, {0,0}, 0);
    //room.getFille(0)->getFille(0)->ajouterFille({20,20}, "arm", {0,0}, {200,0}, 0);
    //room.getFille(0)->ajouterFille({200,50}, "arm", {0,70}, {0,0}, 0);
    //room.getFille(0)->ajouterFille({200,50}, "arm", {0,50}, {0,0}, 0);
    room.getFille(0)->ajouterFille({25,350}, "arm", {0,350}, {0,0}, 0);
    room.getFille(0)->ajouterFille({25,HAUTEUR_SCENE-50}, "arm", {25,HAUTEUR_SCENE-50}, {LARGEUR_SCENE,0}, 0);
    room.getFille(0)->getFille(0)->ajouterFille({60,20}, "arm", {0,0}, {25,HAUTEUR_SCENE/2}, 0);
    room.getFille(0)->ajouterFille({25,50}, "block", {0,50}, {LARGEUR_SCENE/2,0}, 0);
}

void dessinerScene(const Block &room)
{
    Svgfile svgout;

    //room.dessiner(svgout);

    ///Affichage pointeur par pointeur => créer la boucle de parcours de l'arbre
    room.getFille(0)->dessiner(svgout);
    /*room.getFille(0)->getFille(0)->dessiner(svgout);
    room.getFille(0)->getFille(1)->dessiner(svgout);
    room.getFille(0)->getFille(0)->getFille(0)->dessiner(svgout);
    room.getFille(0)->getFille(2)->dessiner(svgout);*/
}
