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
#define HAUTEUR_SCENE 800
#define LARGEUR_SCENE 1200

void creerScene(Block* room);
void dessinerScene(const Block &room);

int main()
{
    Block room;
    Block* blockIterateur = &room;

    std::ofstream file {FICHIER};
    if (!file)
    {
        std::cerr << "Ouverture impossible du fichier : " << FICHIER;
    }

    else
    {
        room.sauvegarde();
    }

    creerScene(blockIterateur);
    dessinerScene(room);

    return 0;
}

// TODO : voir pour terminer l'iterateur
void creerScene(Block* iterateur)
{
    //ajouterBlock(room, LARGEUR_SCENE, HAUTEUR_SCENE, "room", 0, 0, 0, 0);
    iterateur->ajouterFille(LARGEUR_SCENE, 50, "sol", LARGEUR_SCENE/2, HAUTEUR_SCENE, LARGEUR_SCENE/2, 50);
    iterateur = (iterateur->getFille(0));
}

void dessinerScene(const Block &room)
{
    Svgfile svgout;

    room.dessiner(svgout);
    room.getFille(0)->dessiner(svgout);
}
