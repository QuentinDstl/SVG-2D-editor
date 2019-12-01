#include "src/interface/menu.h"
#define FICHIER "src/rom/sauvegarde.rom"
#define RELOAD "src/rom/sauvegardeoptimale.rom"

int main()
{
    Block room;
    Block* blockIterateur = &room;
    ajouterBlock(room, 0, "room", {LARGEUR_SCENE,HAUTEUR_SCENE}, {196,255,255}, {0,0}, {0,0});
    room.chargementScene();

    bool fin = false;
    bool afficherLiaisons = false;
    bool afficherId = false;
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
    while(!fin)
    {
        dessinerScene(room, ptafficherLiaisons, ptafficherId, ptplan);
        room.sauvegarde();
        fin = menu(blockIterateur, ptafficherLiaisons, ptafficherId, ptplan);
    }
    room.sauvegarde();
    return 0;
}
