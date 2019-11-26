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
#define HAUTEUR_SCENE 600
#define LARGEUR_SCENE 1000

//void creerScene(Block* room); // option avec iterateur
void creerScene(Block& room);
void dessinerScene(const Block &room); // a voir pour mettre en const le Block

int main()
{
    Block room;
    Block* blockIterateur = &room; //option avec iterateur

    creerScene(room);
    dessinerScene(room);

    /// on cherche un bloc selon son id
    if (room.parcourir("arm1") == nullptr)
    {
        std::cout << "[i] id fausse" << std::endl;
    }
    else
    {
    std::cout << "id trouve : " << room.parcourir("arm1")->getId() << std::endl;
    }

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

// NOTE (qdesa#1#11/26/19): voir avec charly si il veut passer par cette techique
// dans le cadre de l'utilisation du polymorphisme il est necessaire de passer par des adresses ou pointeurs
/*
void creerScene(Block* iterateur)
{


    ajouterBlock(*iterateur, {LARGEUR_SCENE,HAUTEUR_SCENE}, "room", {0,0}, {0,0});
    iterateur->ajouterFille({LARGEUR_SCENE,50}, "sol", {LARGEUR_SCENE/2,50}, {LARGEUR_SCENE/2,HAUTEUR_SCENE}, 1);


    iterateur->getFille(0)->ajouterFille({25,350}, "arm", {0,350}, {0,0}, 0);
    iterateur->getFille(0)->ajouterFille({25,HAUTEUR_SCENE-50}, "arm", {25,HAUTEUR_SCENE-50}, {LARGEUR_SCENE,0}, 0);
    iterateur->getFille(0)->getFille(0)->ajouterFille({60,20}, "arm", {0,0}, {25,HAUTEUR_SCENE/2}, 0);
    iterateur->getFille(0)->ajouterFille({25,50}, "block", {0,50}, {LARGEUR_SCENE/2,0}, 0);

    //ajouterBlock(room, LARGEUR_SCENE, HAUTEUR_SCENE, "room", 0, 0, 0, 0);

    //iterateur->ajouterFille(LARGEUR_SCENE, 50, "sol", LARGEUR_SCENE/2, HAUTEUR_SCENE, LARGEUR_SCENE/2, 50);
    //iterateur = (iterateur->getFille(0));
*/
void creerScene(Block &room)
{

    ajouterBlock(room, {LARGEUR_SCENE,HAUTEUR_SCENE}, "room", {0,0}, {0,0});
    room.ajouterFille({LARGEUR_SCENE,50}, "sol", {LARGEUR_SCENE/2,50}, {LARGEUR_SCENE/2,HAUTEUR_SCENE}, 1);

    //room.getFille(0)->ajouterFille({200,50}, "arm", {0,50}, {0,0}, 0);
    //room.getFille(0)->getFille(0)->ajouterFille({20,20}, "arm", {0,0}, {200,0}, 0);
    //room.getFille(0)->ajouterFille({200,50}, "arm", {0,70}, {0,0}, 0);
    //room.getFille(0)->ajouterFille({200,50}, "arm", {0,50}, {0,0}, 0);

    room.getFille(0)->ajouterFille({25,HAUTEUR_SCENE-50}, "arm1", {0,HAUTEUR_SCENE-50}, {0,0}, 0);
    room.getFille(0)->ajouterFille({25,HAUTEUR_SCENE-50}, "arm2", {25,HAUTEUR_SCENE-50}, {LARGEUR_SCENE,0}, 0);
    room.getFille(0)->getFille(0)->ajouterFille({60,20}, "arm3", {0,0}, {25,HAUTEUR_SCENE/2}, 0);
    room.getFille(0)->ajouterFille({25,50}, "block", {0,50}, {LARGEUR_SCENE/2,0}, 0);

}

void dessinerScene(const Block &room)
{
    Svgfile svgout;
    /* attention il faut dessiner le room à part */
    //room.dessiner(svgout);

    room.toutDessiner(svgout);
    std::cout << "[i] croix rouge = position de reference / croix noir = position de base" << std::endl;
    room.toutDessinerLiaisons(svgout);
    room.toutDessinerId(svgout);
}
