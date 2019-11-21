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
void ajouterBlock(Block &room,
                  double _xTaille, double _yTaille, std::string _id,
                  double _refposMereX, double _refposMereY, double _refposX, double _refposY);



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




void creerScene(Block &room) {

    ajouterBlock(room, LARGEUR_SCENE, HAUTEUR_SCENE, "room", 0, 0, 0, 0);
}




void dessinerScene(const Block &room)
{
    Svgfile svgout;

    room.dessiner(svgout);
}


void ajouterBlock(Block &room,
                  double _xTaille, double _yTaille, std::string _id,
                  double _refposMereX, double _refposMereY, double _refposX, double _refposY)
{

    room.initialiser(_xTaille, _yTaille, _id);
    room.initialiserLiaison(_refposMereX, _refposMereY, _refposX, _refposY);
    room.initialiserOrigine();
}
