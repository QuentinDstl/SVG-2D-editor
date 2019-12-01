#include "src/interface/menu.h"
#define FICHIER "src/rom/sauvegarde.rom"
#define RELOAD "src/rom/sauvegardeoptimale.rom"

int main()
{
    Block room;
    Block* blockIterateur = &room; //variable permettant de se balader dans l'arbre de Block
    ajouterBlock(room, 0, "room", {LARGEUR_SCENE,HAUTEUR_SCENE}, {196,255,255}, {0,0}, {0,0}); //creation de la room qui est le Block racine de l'arbre
    room.chargementScene(); //chargement de la scene depuis la sauvegarde

    bool fin = false; //variable de fin de la boucle de jeu
    bool afficherLiaisons = false; //affichage des liaisons sur le svg si true
    bool afficherId = false; //affichage des id sur le svg si true
    unsigned int plan = 3;

    bool* ptafficherId = &afficherId;
    bool* ptafficherLiaisons = &afficherLiaisons;
    unsigned int* ptplan = &plan;

    std::ofstream file {FICHIER};
    if (!file)
    {
        std::cerr << "Ouverture impossible du fichier : " << FICHIER;
    }

    std::cout << std::endl << "Veuillez taper !h pour afficher les commandes a realiser." << std::endl << std::endl;

    ///** Boucle du menu **
    while(!fin) //boucle de jeu
    {
        dessinerScene(room, ptafficherLiaisons, ptafficherId, ptplan);
        room.sauvegarde(); //sauvegarde realisee a chaque de boucle afin de pouvoir faire des UNDO REDO
        fin = menu(blockIterateur, ptafficherLiaisons, ptafficherId, ptplan); //menu utilisateur
    }
    room.sauvegarde(); //sauvegarde de fin de jeu
    return 0;
}
