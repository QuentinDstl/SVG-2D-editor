#include "src/interface/menu.h"

///Main Version CHARGEMENT depuis fichier
/*int main()
{
    Block room;
    Block* blockIterateur = &room;

    ajouterBlock(room, 0, "room", {LARGEUR_SCENE,HAUTEUR_SCENE}, {50,200,200}, {0,0}, {0,0});

    room.chargementScene();

    return 0;
}*/


/*
///Main version CREATION puis sauvegarde
int main()
{
    ///** Declaration et Initialisation **

    Block room;
    Block* blockIterateur = &room;
    bool fin = false;

    ///** Boucle du menu **
    while(!fin)
    {
        creerScene(blockIterateur);
        fin = menu(blockIterateur);

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
        fin = true;
    }

    return 0;
}*/

///Main version CREATION puis sauvegarde
int main()
{
    Block room;
    Block* blockIterateur = &room;

    creerScene(blockIterateur);

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
