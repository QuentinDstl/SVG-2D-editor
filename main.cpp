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

    //ajouterBlock(room, LARGEUR_SCENE, HAUTEUR_SCENE, "room", 0, 0, 0, 0);
    room.ajouterFille(LARGEUR_SCENE, 50, "sol", LARGEUR_SCENE/2, HAUTEUR_SCENE, LARGEUR_SCENE/2, 50);
}




void dessinerScene(const Block &room)
{
    Svgfile svgout;

    room.dessiner(svgout);
    room.getFille(0)->dessiner(svgout);
}
