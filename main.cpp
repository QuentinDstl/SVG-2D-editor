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

void creerScene(Block* room);
void dessinerScene(const Block &room);

void toutDessiner(Svgfile &svgout, const Block &room);

///Main version CREATION puis sauvegarde
int main()
{
    Block room;
    Block* blockIterateur = &room;

    creerScene(blockIterateur);
    dessinerScene(room);

    std::cout << "couleur block object1 : ";
    BlockCouleur* bc = dynamic_cast<BlockCouleur*> (parcourir("object1",room));
    if(bc)
        bc->getCouleur().afficher();

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
    ajouterBlock(*iterateur, {LARGEUR_SCENE,HAUTEUR_SCENE}, "room", {0,0}, {0,0});
    iterateur->ajouterFille(0, {LARGEUR_SCENE,50}, "sol", {LARGEUR_SCENE/2,50}, {LARGEUR_SCENE/2,HAUTEUR_SCENE}, 1);

    //on rentre dans les filles
    iterateur = iterateur->getFille(0);

    iterateur->ajouterFille(0, {25,HAUTEUR_SCENE-50}, "arm1", {0,HAUTEUR_SCENE-50}, {0,0}, 0);
    iterateur->ajouterFilleBordure(0, {25,HAUTEUR_SCENE-50}, "arm2", {25,HAUTEUR_SCENE-50}, {LARGEUR_SCENE,0}, 0, {200,100,100}, {0,10,0});
    iterateur->ajouterFille(0, {25,50}, "block", {0,50}, {LARGEUR_SCENE/2,0}, 0);

    //on rentre dans les filles
    iterateur = iterateur->getFille(0);
    iterateur->ajouterFilleCouleur(0, {60,20}, "arm3", {0,0}, {25,HAUTEUR_SCENE/2}, 0, {50,150,100});

    iterateur = trouverRacine(*iterateur);
    iterateur = iterateur->getFille(0);
    iterateur = iterateur->getFille(1);
    iterateur->ajouterFilleCouleur(0, {60,20}, "arm4", {60,10}, {0,HAUTEUR_SCENE/2}, 0, {200,150,100});
    iterateur = iterateur->getFille(0);
    iterateur->ajouterFille(0,{100,100},"object1",{60,10},{0,10},0);
}

void dessinerScene(const Block &room)
{
    Svgfile svgout;
    /* attention il faut dessiner le room � part */
    //room.dessiner(svgout);
    toutDessiner(svgout,room);

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
            BlockCouleur* petit_fils_couleur = dynamic_cast<BlockCouleur*>(petit_fils);

            if (petit_fils_couleur)
                petit_fils_couleur->dessiner(svgout);
            else
                petit_fils->dessiner(svgout);

            toutDessiner(svgout,*petit_fils);
        }
    }
}
