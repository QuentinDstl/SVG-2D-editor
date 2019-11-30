#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>

#include "../class/block_cercle.h"
#include "../class/coords.h"
#include "../class/liaison.h"
#include "../class/block_bordure.h"
#include "../util/util.h"
#include "../class/block_cercle_bordure.h"

/// Lecture fichier
#define FICHIER "src/rom/sauvegarde.rom"

/// Define scene
#define HAUTEUR_SCENE 600
#define LARGEUR_SCENE 1000

bool menu(Block *iterateur);
void creerScene(Block* room);
void dessinerScene(const Block &room);
void toutDessiner(Svgfile &svgout, const Block &room);
void toutDessinerPlan(Svgfile &svgout,const Block &room, unsigned int plan);

#endif // MENU_H_INCLUDED
