#include "src/interface/menu.h"
#define FICHIER "src/rom/sauvegarde.rom"

int main()
{
    Block room;
    Block* blockIterateur = &room;
    ajouterBlock(room, 0, "room", {LARGEUR_SCENE,HAUTEUR_SCENE}, {50,200,200}, {0,0}, {0,0});
    room.chargementScene();

    bool fin = false;

    bool afficherLiaisons = false;
    bool afficherId = false;
    unsigned int plan = 3;

    bool* ptafficherId = &afficherId;
    bool* ptafficherLiaisons = &afficherLiaisons;
    unsigned int* ptplan = &plan;

    ///** Boucle du menu **
    while(!fin)
    {
        dessinerScene(room, ptafficherLiaisons, ptafficherId, ptplan);
        fin = menu(blockIterateur, ptafficherLiaisons, ptafficherId, ptplan);

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
    }
    return 0;
}
