#include "../class/block.h"
#include "../svg/svgfile.h"
#include "../class/block_cercle.h"
#include "../class/block_bordure.h"
#include "../class/block_cercle_bordure.h"
#include "../class/liaison_glissiere.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream> /// Pour les fichiers
#include <sstream> /// Pour les ostringstream

#define HAUTEUR_SCENE 600
#define LARGEUR_SCENE 1000
#define MAX_COLOR 100

/// Definition lecture fichier :
#define FICHIERSAUV "src/rom/sauvegarde.rom"
#define FICHIERTEST "src/rom/sauvegarde2.rom"

///************************///
///SAUVEGARDE ET CHARGEMENT///
///************************///

/*Sauvegarde global de la scène */
void Block::sauvegarde()
{
    sauvegarderScene1(m_Filles);
}

/*Sauvegarde de la scène*/
// Methode qui recupere un vecteur de pointeur de block pour les sauvegarder
void Block::sauvegarderScene1(std::vector <Block*> s)
{
    std::ofstream ofs{FICHIERSAUV};

    for (auto i : s)///Niveau 0 et de marqueur 1
    {
        if ((i->m_classe) == 0)
        {
            ofs << i->m_classe <<" "<< i->m_id <<" "<< i->m_taille.getX() <<" "<< i->m_taille.getY() <<" "<< (int)i->m_couleur.getRouge()
            <<" "<< (int)i->m_couleur.getVert() <<" "<< (int)i->m_couleur.getBleu() <<" "<< i->m_liaison->getRefpos().getX()
            <<" "<< i->m_liaison->getRefpos().getY() <<" "<< i->m_liaison->getBasepos().getX() <<" "<< i->m_liaison->getBasepos().getY()
            <<" "<< (unsigned int)i->m_liaison->getPlan() << std::endl;
        }
        if ((i->m_classe) == 1)
        {
            BlockCercle* c1 = dynamic_cast<BlockCercle*>(i);
            ofs << c1->m_classe <<" "<< c1->m_id <<" "<< c1->getRayon() <<" "<< (int)c1->m_couleur.getRouge()
            <<" "<< (int)c1->m_couleur.getVert() <<" "<< (int)c1->m_couleur.getBleu() <<" "<< c1->m_liaison->getRefpos().getX()
            <<" "<< c1->m_liaison->getRefpos().getY() <<" "<< c1->m_liaison->getBasepos().getX() <<" "<< c1->m_liaison->getBasepos().getY()
            <<" "<< (unsigned int)c1->m_liaison->getPlan() << std::endl;
        }
        if ((i->m_classe) == 2)
        {
            BlockBordure* a1 = dynamic_cast<BlockBordure*>(i);
            ofs << a1->m_classe <<" "<< a1->m_id <<" "<< a1->m_taille.getX() <<" "<< a1->m_taille.getY() <<" "<< (int)a1->m_couleur.getRouge()
            <<" "<< (int)a1->m_couleur.getVert() <<" "<< (int)a1->m_couleur.getBleu() <<" "<< (int)a1->getBordure().getRouge()
            <<" "<< (int)a1->getBordure().getVert() <<" "<< (int)a1->getBordure().getBleu()<<" "<< a1->m_liaison->getRefpos().getX()
            <<" "<< a1->m_liaison->getRefpos().getY() <<" "<< a1->m_liaison->getBasepos().getX() <<" "<< a1->m_liaison->getBasepos().getY()
            <<" "<< (unsigned int)a1->m_liaison->getPlan() << std::endl;
        }
        if ((i->m_classe) == 3)
        {
            BlockCercleBordure* b1 = dynamic_cast<BlockCercleBordure*>(i);
            ofs << b1->m_classe <<" "<< b1->m_id <<" "<< b1->getRayon() <<" "<< (int)b1->m_couleur.getRouge()
            <<" "<< (int)b1->m_couleur.getVert() <<" "<< (int)b1->m_couleur.getBleu() <<" "<< (int)b1->getBordure().getRouge()
            <<" "<< (int)b1->getBordure().getVert() <<" "<< (int)b1->getBordure().getBleu()<<" "<< b1->m_liaison->getRefpos().getX()
            <<" "<< b1->m_liaison->getRefpos().getY() <<" "<< b1->m_liaison->getBasepos().getX() <<" "<< b1->m_liaison->getBasepos().getY()
            <<" "<< (unsigned int)b1->m_liaison->getPlan() << std::endl;
        }
        if ((i->m_classe) == 4)//GlissièreBordure
        {
            BlockBordure* d1 = dynamic_cast<BlockBordure*>(i);
            LiaisonGlissiere* dd1 = dynamic_cast<LiaisonGlissiere*>(d1->m_liaison);
            ofs << d1->m_classe <<" "<< d1->m_id <<" "<< d1->m_taille.getX() <<" "<< d1->m_taille.getY() <<" "<< (int)d1->m_couleur.getRouge()
            <<" "<< (int)d1->m_couleur.getVert() <<" "<< (int)d1->m_couleur.getBleu() <<" "<< (int)d1->getBordure().getRouge()
            <<" "<< (int)d1->getBordure().getVert() <<" "<< (int)d1->getBordure().getBleu()<<" "<< d1->m_liaison->getRefpos().getX()
            <<" "<< d1->m_liaison->getRefpos().getY() <<" "<< d1->m_liaison->getBasepos().getX() <<" "<< d1->m_liaison->getBasepos().getY()
            <<" "<< dd1->getFinbasepos().getX() <<" "<< dd1->getFinbasepos().getY() <<" "<< (unsigned int)d1->m_liaison->getPlan() << std::endl;
        }

        ofs << "[" << std::endl;

        for ( auto v : i->m_Filles)///Niveau 1 et de marqueur 2
        {
            if ((v->m_classe) == 0)
            {
                ofs <<"    "<< v->m_classe <<" "<< v->m_id <<" "<< v->m_taille.getX() <<" "<< v->m_taille.getY() <<" "<< (int)v->m_couleur.getRouge()
                <<" "<< (int)v->m_couleur.getVert() <<" "<< (int)v->m_couleur.getBleu() <<" "<< v->m_liaison->getRefpos().getX()
                <<" "<< v->m_liaison->getRefpos().getY() <<" "<< v->m_liaison->getBasepos().getX() <<" "<< v->m_liaison->getBasepos().getY()
                <<" "<< (unsigned int)v->m_liaison->getPlan() << std::endl;
            }
            if ((v->m_classe) == 1)
            {
                BlockCercle* c2 = dynamic_cast<BlockCercle*>(v);
                ofs <<"    "<< c2->m_classe <<" "<< c2->m_id <<" "<< c2->getRayon() <<" "<< (int)c2->m_couleur.getRouge()
                <<" "<< (int)c2->m_couleur.getVert() <<" "<< (int)c2->m_couleur.getBleu() <<" "<< c2->m_liaison->getRefpos().getX()
                <<" "<< c2->m_liaison->getRefpos().getY() <<" "<< c2->m_liaison->getBasepos().getX() <<" "<< c2->m_liaison->getBasepos().getY()
                <<" "<< (unsigned int)c2->m_liaison->getPlan() << std::endl;
            }
            if ((v->m_classe) == 2)
            {
                BlockBordure* a2 = dynamic_cast<BlockBordure*>(v);
                ofs <<"    "<< a2->m_classe <<" "<< a2->m_id <<" "<< a2->m_taille.getX() <<" "<< a2->m_taille.getY() <<" "<< (int)a2->m_couleur.getRouge()
                <<" "<< (int)a2->m_couleur.getVert() <<" "<< (int)a2->m_couleur.getBleu() <<" "<< (int)a2->getBordure().getRouge()
                <<" "<< (int)a2->getBordure().getVert() <<" "<< (int)a2->getBordure().getBleu()<<" "<< a2->m_liaison->getRefpos().getX()
                <<" "<< a2->m_liaison->getRefpos().getY() <<" "<< a2->m_liaison->getBasepos().getX() <<" "<< a2->m_liaison->getBasepos().getY()
                <<" "<< (unsigned int)a2->m_liaison->getPlan() << std::endl;
            }
            if ((v->m_classe) == 3)
            {
                BlockCercleBordure* b2 = dynamic_cast<BlockCercleBordure*>(v);
                ofs <<"    "<< b2->m_classe <<" "<< b2->m_id <<" "<< b2->getRayon() <<" "<< (int)b2->m_couleur.getRouge()
                <<" "<< (int)b2->m_couleur.getVert() <<" "<< (int)b2->m_couleur.getBleu() <<" "<< (int)b2->getBordure().getRouge()
                <<" "<< (int)b2->getBordure().getVert() <<" "<< (int)b2->getBordure().getBleu()<<" "<< b2->m_liaison->getRefpos().getX()
                <<" "<< b2->m_liaison->getRefpos().getY() <<" "<< b2->m_liaison->getBasepos().getX() <<" "<< b2->m_liaison->getBasepos().getY()
                <<" "<< (unsigned int)b2->m_liaison->getPlan() << std::endl;
            }
            if ((v->m_classe) == 4)//GlissièreBordure
            {
                BlockBordure* d2 = dynamic_cast<BlockBordure*>(v);
                LiaisonGlissiere* dd2 = dynamic_cast<LiaisonGlissiere*>(d2->m_liaison);
                ofs <<"    "<< d2->m_classe <<" "<< d2->m_id <<" "<< d2->m_taille.getX() <<" "<< d2->m_taille.getY() <<" "<< (int)d2->m_couleur.getRouge()
                <<" "<< (int)d2->m_couleur.getVert() <<" "<< (int)d2->m_couleur.getBleu() <<" "<< (int)d2->getBordure().getRouge()
                <<" "<< (int)d2->getBordure().getVert() <<" "<< (int)d2->getBordure().getBleu()<<" "<< d2->m_liaison->getRefpos().getX()
                <<" "<< d2->m_liaison->getRefpos().getY() <<" "<< d2->m_liaison->getBasepos().getX() <<" "<< d2->m_liaison->getBasepos().getY()
                <<" "<< dd2->getFinbasepos().getX() <<" "<< dd2->getFinbasepos().getY() <<" "<< (unsigned int)d2->m_liaison->getPlan() << std::endl;
            }
            if ((v->m_classe) == 5)//Glissière
                {
                    LiaisonGlissiere* ee2 = dynamic_cast<LiaisonGlissiere*>(v->m_liaison);
                    ofs <<"    "<< v->m_classe <<" "<< v->m_id <<" "<< v->m_taille.getX() <<" "<< v->m_taille.getY() <<" "<< (int)v->m_couleur.getRouge()
                    <<" "<< (int)v->m_couleur.getVert() <<" "<< (int)v->m_couleur.getBleu() <<" "<< v->m_liaison->getRefpos().getX()
                    <<" "<< v->m_liaison->getRefpos().getY() <<" "<< v->m_liaison->getBasepos().getX() <<" "<< v->m_liaison->getBasepos().getY()
                    <<" "<< ee2->getFinbasepos().getX() <<" "<< ee2->getFinbasepos().getY() <<" "<< (unsigned int)v->m_liaison->getPlan() << std::endl;
                }
            ofs << "    [" << std::endl;

            for ( auto z : v->m_Filles )///Niveau 2 et de marqueur 3
            {
                if ((z->m_classe) == 0)
                {
                    ofs <<"        "<< z->m_classe <<" "<< z->m_id <<" "<< z->m_taille.getX() <<" "<< z->m_taille.getY() <<" "<< (int)z->m_couleur.getRouge()
                    <<" "<< (int)z->m_couleur.getVert() <<" "<< (int)z->m_couleur.getBleu() <<" "<< z->m_liaison->getRefpos().getX()
                    <<" "<< z->m_liaison->getRefpos().getY() <<" "<< z->m_liaison->getBasepos().getX() <<" "<< z->m_liaison->getBasepos().getY()
                    <<" "<< (unsigned int)z->m_liaison->getPlan() << std::endl;
                }
                if ((z->m_classe) == 1)
                {
                    BlockCercle* c3 = dynamic_cast<BlockCercle*>(z);
                    ofs <<"        "<< c3->m_classe <<" "<< c3->m_id <<" "<< c3->getRayon() <<" "<< (int)c3->m_couleur.getRouge()
                    <<" "<< (int)c3->m_couleur.getVert() <<" "<< (int)c3->m_couleur.getBleu() <<" "<< c3->m_liaison->getRefpos().getX()
                    <<" "<< c3->m_liaison->getRefpos().getY() <<" "<< c3->m_liaison->getBasepos().getX() <<" "<< c3->m_liaison->getBasepos().getY()
                    <<" "<< (unsigned int)c3->m_liaison->getPlan() << std::endl;
                }
                if ((z->m_classe) == 2)
                {
                    BlockBordure* a3 = dynamic_cast<BlockBordure*>(z);
                    ofs <<"        "<< a3->m_classe <<" "<< a3->m_id <<" "<< a3->m_taille.getX() <<" "<< a3->m_taille.getY() <<" "<< (int)a3->m_couleur.getRouge()
                    <<" "<< (int)a3->m_couleur.getVert() <<" "<< (int)a3->m_couleur.getBleu() <<" "<< (int)a3->getBordure().getRouge()
                    <<" "<< (int)a3->getBordure().getVert() <<" "<< (int)a3->getBordure().getBleu()<<" "<< a3->m_liaison->getRefpos().getX()
                    <<" "<< a3->m_liaison->getRefpos().getY() <<" "<< a3->m_liaison->getBasepos().getX() <<" "<< a3->m_liaison->getBasepos().getY()
                    <<" "<< (unsigned int)a3->m_liaison->getPlan() << std::endl;
                }
                if ((z->m_classe) == 3)
                {
                    BlockCercleBordure* b3 = dynamic_cast<BlockCercleBordure*>(z);
                    ofs <<"        "<< b3->m_classe <<" "<< b3->m_id <<" "<< b3->getRayon() <<" "<< (int)b3->m_couleur.getRouge()
                    <<" "<< (int)b3->m_couleur.getVert() <<" "<< (int)b3->m_couleur.getBleu() <<" "<< (int)b3->getBordure().getRouge()
                    <<" "<< (int)b3->getBordure().getVert() <<" "<< (int)b3->getBordure().getBleu()<<" "<< b3->m_liaison->getRefpos().getX()
                    <<" "<< b3->m_liaison->getRefpos().getY() <<" "<< b3->m_liaison->getBasepos().getX() <<" "<< b3->m_liaison->getBasepos().getY()
                    <<" "<< (unsigned int)b3->m_liaison->getPlan() << std::endl;
                }
                if ((z->m_classe) == 4)//GlissièreBordure
                {
                    BlockBordure* d3 = dynamic_cast<BlockBordure*>(z);
                    LiaisonGlissiere* dd3 = dynamic_cast<LiaisonGlissiere*>(d3->m_liaison);
                    ofs <<"        "<< d3->m_classe <<" "<< d3->m_id <<" "<< d3->m_taille.getX() <<" "<< d3->m_taille.getY() <<" "<< (int)d3->m_couleur.getRouge()
                    <<" "<< (int)d3->m_couleur.getVert() <<" "<< (int)d3->m_couleur.getBleu() <<" "<< (int)d3->getBordure().getRouge()
                    <<" "<< (int)d3->getBordure().getVert() <<" "<< (int)d3->getBordure().getBleu()<<" "<< d3->m_liaison->getRefpos().getX()
                    <<" "<< d3->m_liaison->getRefpos().getY() <<" "<< d3->m_liaison->getBasepos().getX() <<" "<< d3->m_liaison->getBasepos().getY()
                    <<" "<< dd3->getFinbasepos().getX() <<" "<< dd3->getFinbasepos().getY() <<" "<< (unsigned int)d3->m_liaison->getPlan() << std::endl;
                }
                if ((z->m_classe) == 5)//Glissière
                {
                    LiaisonGlissiere* ee3 = dynamic_cast<LiaisonGlissiere*>(z->m_liaison);
                    ofs <<"        "<< z->m_classe <<" "<< z->m_id <<" "<< z->m_taille.getX() <<" "<< z->m_taille.getY() <<" "<< (int)z->m_couleur.getRouge()
                    <<" "<< (int)z->m_couleur.getVert() <<" "<< (int)z->m_couleur.getBleu() <<" "<< z->m_liaison->getRefpos().getX()
                    <<" "<< z->m_liaison->getRefpos().getY() <<" "<< z->m_liaison->getBasepos().getX() <<" "<< z->m_liaison->getBasepos().getY()
                    <<" "<< ee3->getFinbasepos().getX() <<" "<< ee3->getFinbasepos().getY() <<" "<< (unsigned int)z->m_liaison->getPlan() << std::endl;
                }
                ofs << "        [" << std::endl;

                for ( auto b : z->m_Filles )///Niveau 3 et de marqueur 4
                {
                    if ((b->m_classe) == 0)
                    {
                        ofs << "            "<< b->m_classe <<" "<< b->m_id <<" "<< b->m_taille.getX() <<" "<< b->m_taille.getY() <<" "<< (int)b->m_couleur.getRouge()
                        <<" "<< (int)b->m_couleur.getVert() <<" "<< (int)b->m_couleur.getBleu() <<" "<< b->m_liaison->getRefpos().getX()
                        <<" "<< b->m_liaison->getRefpos().getY() <<" "<< b->m_liaison->getBasepos().getX() <<" "<< b->m_liaison->getBasepos().getY()
                        <<" "<< (unsigned int)b->m_liaison->getPlan() << std::endl;
                    }
                    if ((b->m_classe) == 1)
                    {
                        BlockCercle* c4 = dynamic_cast<BlockCercle*>(b);
                        ofs << "            "<< c4->m_classe <<" "<< c4->m_id <<" "<< c4->getRayon() <<" "<< (int)c4->m_couleur.getRouge()
                        <<" "<< (int)c4->m_couleur.getVert() <<" "<< (int)c4->m_couleur.getBleu() <<" "<< c4->m_liaison->getRefpos().getX()
                        <<" "<< c4->m_liaison->getRefpos().getY() <<" "<< c4->m_liaison->getBasepos().getX() <<" "<< c4->m_liaison->getBasepos().getY()
                        <<" "<< (unsigned int)c4->m_liaison->getPlan() << std::endl;
                    }
                    if ((b->m_classe) == 2)
                    {
                        BlockBordure* a4 = dynamic_cast<BlockBordure*>(b);
                        ofs << "            "<< a4->m_classe <<" "<< a4->m_id <<" "<< a4->m_taille.getX() <<" "<< a4->m_taille.getY() <<" "<< (int)a4->m_couleur.getRouge()
                        <<" "<< (int)a4->m_couleur.getVert() <<" "<< (int)a4->m_couleur.getBleu() <<" "<< (int)a4->getBordure().getRouge()
                        <<" "<< (int)a4->getBordure().getVert() <<" "<< (int)a4->getBordure().getBleu()<<" "<< a4->m_liaison->getRefpos().getX()
                        <<" "<< a4->m_liaison->getRefpos().getY() <<" "<< a4->m_liaison->getBasepos().getX() <<" "<< a4->m_liaison->getBasepos().getY()
                        <<" "<< (unsigned int)a4->m_liaison->getPlan() << std::endl;
                    }
                    if ((b->m_classe) == 3)
                    {
                        BlockCercleBordure* b4 = dynamic_cast<BlockCercleBordure*>(b);
                        ofs << "            "<< b4->m_classe <<" "<< b4->m_id <<" "<< b4->getRayon() <<" "<< (int)b4->m_couleur.getRouge()
                        <<" "<< (int)b4->m_couleur.getVert() <<" "<< (int)b4->m_couleur.getBleu() <<" "<< (int)b4->getBordure().getRouge()
                        <<" "<< (int)b4->getBordure().getVert() <<" "<< (int)b4->getBordure().getBleu()<<" "<< b4->m_liaison->getRefpos().getX()
                        <<" "<< b4->m_liaison->getRefpos().getY() <<" "<< b4->m_liaison->getBasepos().getX() <<" "<< b4->m_liaison->getBasepos().getY()
                        <<" "<< (unsigned int)b4->m_liaison->getPlan() << std::endl;
                    }
                    if ((b->m_classe) == 4)//GlissièreBordure
                    {
                        BlockBordure* d4 = dynamic_cast<BlockBordure*>(b);
                        LiaisonGlissiere* dd4 = dynamic_cast<LiaisonGlissiere*>(d4->m_liaison);
                        ofs << "            "<< d4->m_classe <<" "<< d4->m_id <<" "<< d4->m_taille.getX() <<" "<< d4->m_taille.getY() <<" "<< (int)d4->m_couleur.getRouge()
                        <<" "<< (int)d4->m_couleur.getVert() <<" "<< (int)d4->m_couleur.getBleu() <<" "<< (int)d4->getBordure().getRouge()
                        <<" "<< (int)d4->getBordure().getVert() <<" "<< (int)d4->getBordure().getBleu()<<" "<< d4->m_liaison->getRefpos().getX()
                        <<" "<< d4->m_liaison->getRefpos().getY() <<" "<< d4->m_liaison->getBasepos().getX() <<" "<< d4->m_liaison->getBasepos().getY()
                        <<" "<< dd4->getFinbasepos().getX() <<" "<< dd4->getFinbasepos().getY() <<" "<< (unsigned int)d4->m_liaison->getPlan() << std::endl;
                    }
                    if ((b->m_classe) == 5)//Glissière
                    {
                        LiaisonGlissiere* ee4 = dynamic_cast<LiaisonGlissiere*>(b->m_liaison);
                        ofs << "            "<< b->m_classe <<" "<< b->m_id <<" "<< b->m_taille.getX() <<" "<< b->m_taille.getY() <<" "<< (int)b->m_couleur.getRouge()
                        <<" "<< (int)b->m_couleur.getVert() <<" "<< (int)b->m_couleur.getBleu() <<" "<< b->m_liaison->getRefpos().getX()
                        <<" "<< b->m_liaison->getRefpos().getY() <<" "<< b->m_liaison->getBasepos().getX() <<" "<< b->m_liaison->getBasepos().getY()
                        <<" "<< ee4->getFinbasepos().getX() <<" "<< ee4->getFinbasepos().getY() <<" "<< (unsigned int)b->m_liaison->getPlan() << std::endl;
                    }
                    ofs << "            [" << std::endl;

                    for ( auto r : b->m_Filles )///Niveau 4 et de marqueur 5
                    {
                        if ((r->m_classe) == 0)
                        {
                            ofs <<"                "<< r->m_classe <<" "<< r->m_id <<" "<< r->m_taille.getX() <<" "<< r->m_taille.getY() <<" "<< (int)r->m_couleur.getRouge()
                            <<" "<< (int)r->m_couleur.getVert() <<" "<< (int)r->m_couleur.getBleu() <<" "<< r->m_liaison->getRefpos().getX() <<" "<< r->m_liaison->getRefpos().getY()
                            <<" "<< r->m_liaison->getBasepos().getX() <<" "<< r->m_liaison->getBasepos().getY() <<" "<< (unsigned int)r->m_liaison->getPlan() << std::endl;
                        }
                        if ((r->m_classe) == 1)
                        {
                            BlockCercle* c5 = dynamic_cast<BlockCercle*>(r);
                            ofs <<"                "<< c5->m_classe <<" "<< c5->m_id <<" "<< c5->getRayon() <<" "<< (int)c5->m_couleur.getRouge()
                            <<" "<< (int)c5->m_couleur.getVert() <<" "<< (int)c5->m_couleur.getBleu() <<" "<< c5->m_liaison->getRefpos().getX()
                            <<" "<< c5->m_liaison->getRefpos().getY() <<" "<< c5->m_liaison->getBasepos().getX() <<" "<< c5->m_liaison->getBasepos().getY()
                            <<" "<< (unsigned int)c5->m_liaison->getPlan() << std::endl;
                        }
                        if ((r->m_classe) == 2)
                        {
                            BlockBordure* a5 = dynamic_cast<BlockBordure*>(r);
                            ofs <<"                "<< a5->m_classe <<" "<< a5->m_id <<" "<< a5->m_taille.getX() <<" "<< a5->m_taille.getY() <<" "<< (int)a5->m_couleur.getRouge()
                            <<" "<< (int)a5->m_couleur.getVert() <<" "<< (int)a5->m_couleur.getBleu() <<" "<< (int)a5->getBordure().getRouge()
                            <<" "<< (int)a5->getBordure().getVert() <<" "<< (int)a5->getBordure().getBleu()<<" "<< a5->m_liaison->getRefpos().getX()
                            <<" "<< a5->m_liaison->getRefpos().getY() <<" "<< a5->m_liaison->getBasepos().getX() <<" "<< a5->m_liaison->getBasepos().getY()
                            <<" "<< (unsigned int)a5->m_liaison->getPlan() << std::endl;
                        }
                        if ((r->m_classe) == 3)
                        {
                            BlockCercleBordure* b5 = dynamic_cast<BlockCercleBordure*>(r);
                            ofs <<"                "<< b5->m_classe <<" "<< b5->m_id <<" "<< b5->getRayon() <<" "<< (int)b5->m_couleur.getRouge()
                            <<" "<< (int)b5->m_couleur.getVert() <<" "<< (int)b5->m_couleur.getBleu() <<" "<< (int)b5->getBordure().getRouge()
                            <<" "<< (int)b5->getBordure().getVert() <<" "<< (int)b5->getBordure().getBleu()<<" "<< b5->m_liaison->getRefpos().getX()
                            <<" "<< b5->m_liaison->getRefpos().getY() <<" "<< b5->m_liaison->getBasepos().getX() <<" "<< b5->m_liaison->getBasepos().getY()
                            <<" "<< (unsigned int)b5->m_liaison->getPlan() << std::endl;
                        }
                        if ((r->m_classe) == 4)//GlissièreBordure
                        {
                            BlockBordure* d5 = dynamic_cast<BlockBordure*>(r);
                            LiaisonGlissiere* dd5 = dynamic_cast<LiaisonGlissiere*>(d5->m_liaison);
                            ofs <<"                "<< d5->m_classe <<" "<< d5->m_id <<" "<< d5->m_taille.getX() <<" "<< d5->m_taille.getY() <<" "<< (int)d5->m_couleur.getRouge()
                            <<" "<< (int)d5->m_couleur.getVert() <<" "<< (int)d5->m_couleur.getBleu() <<" "<< (int)d5->getBordure().getRouge()
                            <<" "<< (int)d5->getBordure().getVert() <<" "<< (int)d5->getBordure().getBleu()<<" "<< d5->m_liaison->getRefpos().getX()
                            <<" "<< d5->m_liaison->getRefpos().getY() <<" "<< d5->m_liaison->getBasepos().getX() <<" "<< d5->m_liaison->getBasepos().getY()
                            <<" "<< dd5->getFinbasepos().getX() <<" "<< dd5->getFinbasepos().getY() <<" "<< (unsigned int)d5->m_liaison->getPlan() << std::endl;
                        }
                        if ((r->m_classe) == 5)//Glissière
                        {
                            LiaisonGlissiere* ee5 = dynamic_cast<LiaisonGlissiere*>(r->m_liaison);
                            ofs <<"                "<< r->m_classe <<" "<< r->m_id <<" "<< r->m_taille.getX() <<" "<< r->m_taille.getY() <<" "<< (int)r->m_couleur.getRouge()
                            <<" "<< (int)r->m_couleur.getVert() <<" "<< (int)r->m_couleur.getBleu() <<" "<< r->m_liaison->getRefpos().getX()
                            <<" "<< r->m_liaison->getRefpos().getY() <<" "<< r->m_liaison->getBasepos().getX() <<" "<< r->m_liaison->getBasepos().getY()
                            <<" "<< ee5->getFinbasepos().getX() <<" "<< ee5->getFinbasepos().getY() <<" "<< (unsigned int)r->m_liaison->getPlan() << std::endl;
                        }
                    }
                    ofs << "            ]" << std::endl;
                }
                ofs << "        ]" << std::endl;
            }
            ofs << "    ]" << std::endl;
        }
        ofs << "]" << std::endl;
    }
}

/*Chargement de la scène depuis le fichier de sauvegarde*/
void Block::chargementScene()
{
    int niveau = 0;
    int compteurniv1 = 0; int compteurniv2 = 0; int compteurniv3 = 0; int compteurniv4 = 0;
    int suiteniv1 = 0; int suiteniv2 = 0; int suiteniv3 = 0; int suiteniv4 = 0; int suiteniv5 = 0;
    /// Ouverture d'un fichier en lecture (ifstream => input file stream)
    std::ifstream ifs{FICHIERSAUV};

    /// Lecture ligne par ligne : TRES IMPORTANT
    std::string ligne;
    std::getline(ifs, ligne);

    /// On a une ligne avec contenu, avec on va fabriquer un "flot chaîne"
    /// pour lire dedans comme si c'était une saisie clavier !
    std::istringstream iss{ligne};
    double classe,tailleX,tailleY,refposX,refposY,baseposX,baseposY,rayon,baseposfinX,baseposfinY;
    int rouge,vert,bleu,rougeb,vertb,bleub;
    std::string id;
    unsigned int plan3D,planTempo;
    bool planfinal;
    /// l'objet  iss  se comporte comme std::cin !
    iss >> classe ;
    iss >> id >> tailleX >> tailleY >> rouge >> vert >> bleu >> rougeb >> vertb >> bleub >> refposX >> refposY >> baseposX >> baseposY >> plan3D;
    planTempo = plan3D;

    ajouterFilleBordure(classe, id, {tailleX,tailleY}, {(uint8_t)rouge,(uint8_t)vert,(uint8_t)bleu}, {(uint8_t)rougeb,(uint8_t)vertb,(uint8_t)bleub},{refposX,refposY}, {baseposX,baseposY}, true);
    while ( std::getline(ifs, ligne) )
    {
        /*Niv 1*/if ( ligne.size()>=1 && ligne[0]=='[' && niveau==0 )
        {
            niveau = 1;
            std::getline(ifs, ligne);
        }
        if ( ligne[0]==']' && niveau == 1 )
        {
            niveau = 0;
            compteurniv1 = compteurniv1 -1;
        }
        if ( ligne[4]!='[' && ligne[4]!=']' && niveau == 1 )
        {
            suiteniv1 = suiteniv1 +1;
            suiteniv3 = 0;
            suiteniv2 = 0;
            std::istringstream iss{ligne};
            iss >> classe ;
            if (classe == 0)
            {
                iss >> id >> tailleX >> tailleY >> rouge >> vert >> bleu >> refposX >> refposY >> baseposX >> baseposY >> plan3D;
                if (suiteniv1 > 1) { planfinal = true; }
                else if ((plan3D == planTempo) && (suiteniv1 == 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D < planTempo) && (suiteniv1== 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D != planTempo) && (suiteniv1 == 1)) { planfinal = true; planTempo = plan3D; }
                getFille(0)->ajouterFille(classe, id, {tailleX,tailleY}, {(uint8_t)rouge,(uint8_t)vert,(uint8_t)bleu}, {refposX,refposY}, {baseposX,baseposY}, planfinal);
            }
            if (classe == 1)
            {
                iss >> id >> rayon >> rouge >> vert >> bleu >> refposX >> refposY >> baseposX >> baseposY >> plan3D;
                if (suiteniv1 > 1) { planfinal = true; }
                else if ((plan3D == planTempo) && (suiteniv1 == 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D < planTempo) && (suiteniv1== 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D != planTempo) && (suiteniv1 == 1)) { planfinal = true; planTempo = plan3D; }
                getFille(0)->ajouterFilleCercle(classe, id, rayon, {(uint8_t)rouge,(uint8_t)vert,(uint8_t)bleu}, {refposX,refposY}, {baseposX,baseposY}, planfinal);
            }
            if (classe == 2)
            {
                iss >> id >> tailleX >> tailleY >> rouge >> vert >> bleu >> rougeb >> vertb >> bleub >> refposX >> refposY >> baseposX >> baseposY >> plan3D;
                if (suiteniv1 > 1) { planfinal = true; }
                else if ((plan3D == planTempo) && (suiteniv1 == 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D < planTempo) && (suiteniv1== 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D != planTempo) && (suiteniv1 == 1)) { planfinal = true; planTempo = plan3D; }
                getFille(0)->ajouterFilleBordure(classe, id, {tailleX,tailleY}, {(uint8_t)rouge,(uint8_t)vert,(uint8_t)bleu}, {(uint8_t)rougeb,(uint8_t)vertb,(uint8_t)bleub},{refposX,refposY}, {baseposX,baseposY}, planfinal);
            }
            if (classe == 3)
            {
                iss >> id >> rayon >> rouge >> vert >> bleu >> rougeb >> vertb >> bleub >> refposX >> refposY >> baseposX >> baseposY >> plan3D;
                if (suiteniv1 > 1) { planfinal = true; }
                else if ((plan3D == planTempo) && (suiteniv1 == 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D < planTempo) && (suiteniv1== 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D != planTempo) && (suiteniv1 == 1)) { planfinal = true; planTempo = plan3D; }
                getFille(0)->ajouterFilleCercleBordure(classe, id, rayon, {(uint8_t)rouge,(uint8_t)vert,(uint8_t)bleu}, {(uint8_t)rougeb,(uint8_t)vertb,(uint8_t)bleub},{refposX,refposY}, {baseposX,baseposY}, planfinal);
            }
            if (classe == 4) //GlissièreBordure
            {
                iss >> id >> tailleX >> tailleY >> rouge >> vert >> bleu >> rougeb >> vertb >> bleub >> refposX >> refposY >> baseposX >> baseposY >> baseposfinX >> baseposfinY >> plan3D;
                if (suiteniv1 > 1) { planfinal = true; }
                else if ((plan3D == planTempo) && (suiteniv1 == 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D < planTempo) && (suiteniv1== 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D != planTempo) && (suiteniv1 == 1)) { planfinal = true; planTempo = plan3D; }
                getFille(0)->ajouterFilleGlissiereBordure(classe, id, {tailleX,tailleY}, {(uint8_t)rouge,(uint8_t)vert,(uint8_t)bleu}, {(uint8_t)rougeb,(uint8_t)vertb,(uint8_t)bleub},{refposX,refposY}, {baseposX,baseposY},{baseposfinX,baseposfinY}, planfinal);
            }
            if (classe == 5) //Glissière
            {
                iss >> id >> tailleX >> tailleY >> rouge >> vert >> bleu >> refposX >> refposY >> baseposX >> baseposY >> baseposfinX >> baseposfinY >> plan3D;
                if (suiteniv1 > 1) { planfinal = true; }
                else if ((plan3D == planTempo) && (suiteniv1 == 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D < planTempo) && (suiteniv1== 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D != planTempo) && (suiteniv1 == 1)) { planfinal = true; planTempo = plan3D; }
                getFille(0)->ajouterFilleGlissiere(classe, id, {tailleX,tailleY}, {(uint8_t)rouge,(uint8_t)vert,(uint8_t)bleu}, {refposX,refposY}, {baseposX,baseposY},{baseposfinX,baseposfinY}, planfinal);
            }
        }

        //Niv 2
        if ( ligne.size()>=4 && ligne[4]=='[' && niveau==1 )
        {
            niveau = 2;
            std::getline(ifs, ligne);
        }
        if (ligne[4]==']' && niveau == 2 )
        {
            niveau = 1;
            compteurniv1 = compteurniv1 +1;
            compteurniv2 = compteurniv2 -1;
        }
        if ( ligne[8]!='[' && ligne[8]!=']' && niveau == 2 )
        {
            suiteniv1 = 0;
            suiteniv2 = suiteniv2 +1;
            suiteniv3 = 0;
            std::istringstream iss{ligne};
            iss >> classe ;
            if (classe == 0)
            {
                iss >> id >> tailleX >> tailleY >> rouge >> vert >> bleu >> refposX >> refposY >> baseposX >> baseposY >> plan3D;
                if (suiteniv2 > 1) { planfinal = true; }
                else if ((plan3D == planTempo) && (suiteniv2 == 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D < planTempo) && (suiteniv2== 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D != planTempo) && (suiteniv2 == 1)) { planfinal = true; planTempo = plan3D; }
                getFille(0)->getFille(compteurniv1)->ajouterFille(classe, id, {tailleX,tailleY}, {(uint8_t)rouge,(uint8_t)vert,(uint8_t)bleu}, {refposX,refposY}, {baseposX,baseposY}, planfinal);
            }
            if (classe == 1)
            {
                iss >> id >> rayon >> rouge >> vert >> bleu >> refposX >> refposY >> baseposX >> baseposY >> plan3D;
                if (suiteniv2 > 1) { planfinal = true; }
                else if ((plan3D == planTempo) && (suiteniv2 == 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D < planTempo) && (suiteniv2== 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D != planTempo) && (suiteniv2 == 1)) { planfinal = true; planTempo = plan3D; }
                getFille(0)->getFille(compteurniv1)->ajouterFilleCercle(classe, id, rayon, {(uint8_t)rouge,(uint8_t)vert,(uint8_t)bleu}, {refposX,refposY}, {baseposX,baseposY}, planfinal);
            }
            if (classe == 2)
            {
                iss >> id >> tailleX >> tailleY >> rouge >> vert >> bleu >> rougeb >> vertb >> bleub >> refposX >> refposY >> baseposX >> baseposY >> plan3D;
                if (suiteniv2 > 1) { planfinal = true; }
                else if ((plan3D == planTempo) && (suiteniv2 == 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D < planTempo) && (suiteniv2== 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D != planTempo) && (suiteniv2 == 1)) { planfinal = true; planTempo = plan3D; }
                getFille(0)->getFille(compteurniv1)->ajouterFilleBordure(classe, id, {tailleX,tailleY}, {(uint8_t)rouge,(uint8_t)vert,(uint8_t)bleu}, {(uint8_t)rougeb,(uint8_t)vertb,(uint8_t)bleub},{refposX,refposY}, {baseposX,baseposY}, planfinal);
            }
            if (classe == 3)
            {
                iss >> id >> rayon >> rouge >> vert >> bleu >> rougeb >> vertb >> bleub >> refposX >> refposY >> baseposX >> baseposY >> plan3D;
                if (suiteniv2 > 1) { planfinal = true; }
                else if ((plan3D == planTempo) && (suiteniv2 == 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D < planTempo) && (suiteniv2== 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D != planTempo) && (suiteniv2 == 1)) { planfinal = true; planTempo = plan3D; }
                getFille(0)->getFille(compteurniv1)->ajouterFilleCercleBordure(classe, id, rayon, {(uint8_t)rouge,(uint8_t)vert,(uint8_t)bleu}, {(uint8_t)rougeb,(uint8_t)vertb,(uint8_t)bleub},{refposX,refposY}, {baseposX,baseposY}, planfinal);
            }
            if (classe == 4)//GlissièreBordure
            {
                iss >> id >> tailleX >> tailleY >> rouge >> vert >> bleu >> rougeb >> vertb >> bleub >> refposX >> refposY >> baseposX >> baseposY >> baseposfinX >> baseposfinY >> plan3D;
                if (suiteniv2 > 1) { planfinal = true; }
                else if ((plan3D == planTempo) && (suiteniv2 == 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D < planTempo) && (suiteniv2== 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D != planTempo) && (suiteniv2 == 1)) { planfinal = true; planTempo = plan3D; }
                getFille(0)->getFille(compteurniv1)->ajouterFilleGlissiereBordure(classe, id, {tailleX,tailleY}, {(uint8_t)rouge,(uint8_t)vert,(uint8_t)bleu}, {(uint8_t)rougeb,(uint8_t)vertb,(uint8_t)bleub},{refposX,refposY}, {baseposX,baseposY},{baseposfinX,baseposfinY}, planfinal);
            }
            if (classe == 5) //Glissière
            {
                iss >> id >> tailleX >> tailleY >> rouge >> vert >> bleu >> refposX >> refposY >> baseposX >> baseposY >> baseposfinX >> baseposfinY >> plan3D;
                if (suiteniv2 > 1) { planfinal = true; }
                else if ((plan3D == planTempo) && (suiteniv2 == 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D < planTempo) && (suiteniv2== 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D != planTempo) && (suiteniv2 == 1)) { planfinal = true; planTempo = plan3D; }
                getFille(0)->getFille(compteurniv1)->ajouterFilleGlissiere(classe, id, {tailleX,tailleY}, {(uint8_t)rouge,(uint8_t)vert,(uint8_t)bleu}, {refposX,refposY}, {baseposX,baseposY},{baseposfinX,baseposfinY}, planfinal);
            }
        }

        //Niv 3
        if ( ligne.size()>=8 && ligne[8]=='[' && niveau==2 )
        {
            niveau = 3;
            std::getline(ifs, ligne);
        }
        if (ligne[8]==']' && niveau == 3 )
        {
            niveau = 2;
            compteurniv2 = compteurniv2 +1;
            compteurniv3 = compteurniv3 -1;
        }
        if ( ligne[12]!='[' && ligne[12]!=']' && niveau == 3 )
        {
            suiteniv2 = 0;
            suiteniv1 = 0;
            suiteniv3 = suiteniv3 + 1;
            std::istringstream iss{ligne};
            iss >> classe ;
            if (classe == 0)
            {
                iss >> id >> tailleX >> tailleY >> rouge >> vert >> bleu >> refposX >> refposY >> baseposX >> baseposY >> plan3D;
                if (suiteniv3 > 1) { planfinal = true; }
                else if ((plan3D == planTempo) && (suiteniv3 == 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D < planTempo) && (suiteniv3== 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D != planTempo) && (suiteniv3 == 1)) { planfinal = true; planTempo = plan3D; }
                getFille(0)->getFille(compteurniv1)->getFille(compteurniv2)->ajouterFille(classe, id, {tailleX,tailleY}, {(uint8_t)rouge,(uint8_t)vert,(uint8_t)bleu}, {refposX,refposY}, {baseposX,baseposY}, planfinal);
            }
            if (classe == 1)
            {
                iss >> id >> rayon >> rouge >> vert >> bleu >> refposX >> refposY >> baseposX >> baseposY >> plan3D;
                if (suiteniv3 > 1) { planfinal = true; }
                else if ((plan3D == planTempo) && (suiteniv3 == 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D < planTempo) && (suiteniv3== 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D != planTempo) && (suiteniv3 == 1)) { planfinal = true; planTempo = plan3D; }
                getFille(0)->getFille(compteurniv1)->getFille(compteurniv2)->ajouterFilleCercle(classe, id, rayon, {(uint8_t)rouge,(uint8_t)vert,(uint8_t)bleu}, {refposX,refposY}, {baseposX,baseposY}, planfinal);
            }
            if (classe == 2)
            {
                iss >> id >> tailleX >> tailleY >> rouge >> vert >> bleu >> rougeb >> vertb >> bleub >> refposX >> refposY >> baseposX >> baseposY >> plan3D;
                if (suiteniv3 > 1) { planfinal = true; }
                else if ((plan3D == planTempo) && (suiteniv3 == 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D < planTempo) && (suiteniv3== 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D != planTempo) && (suiteniv3 == 1)) { planfinal = true; planTempo = plan3D; }
                getFille(0)->getFille(compteurniv1)->getFille(compteurniv2)->ajouterFilleBordure(classe, id, {tailleX,tailleY}, {(uint8_t)rouge,(uint8_t)vert,(uint8_t)bleu}, {(uint8_t)rougeb,(uint8_t)vertb,(uint8_t)bleub},{refposX,refposY}, {baseposX,baseposY}, planfinal);
            }
            if (classe == 3)
            {
                iss >> id >> rayon >> rouge >> vert >> bleu >> rougeb >> vertb >> bleub >> refposX >> refposY >> baseposX >> baseposY >> plan3D;
                if (suiteniv3 > 1) { planfinal = true; }
                else if ((plan3D == planTempo) && (suiteniv3 == 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D < planTempo) && (suiteniv3== 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D != planTempo) && (suiteniv3 == 1)) { planfinal = true; planTempo = plan3D; }
                getFille(0)->getFille(compteurniv1)->getFille(compteurniv2)->ajouterFilleCercleBordure(classe, id, rayon, {(uint8_t)rouge,(uint8_t)vert,(uint8_t)bleu}, {(uint8_t)rougeb,(uint8_t)vertb,(uint8_t)bleub},{refposX,refposY}, {baseposX,baseposY}, planfinal);
            }
            if (classe == 4) //GlissièreBordure
            {
                iss >> id >> tailleX >> tailleY >> rouge >> vert >> bleu >> rougeb >> vertb >> bleub >> refposX >> refposY >> baseposX >> baseposY >> baseposfinX >> baseposfinY >> plan3D;
                if (suiteniv3 > 1) { planfinal = true; }
                else if ((plan3D == planTempo) && (suiteniv3 == 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D < planTempo) && (suiteniv3== 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D != planTempo) && (suiteniv3 == 1)) { planfinal = true; planTempo = plan3D; }
                getFille(0)->getFille(compteurniv1)->getFille(compteurniv2)->ajouterFilleGlissiereBordure(classe, id, {tailleX,tailleY}, {(uint8_t)rouge,(uint8_t)vert,(uint8_t)bleu}, {(uint8_t)rougeb,(uint8_t)vertb,(uint8_t)bleub},{refposX,refposY}, {baseposX,baseposY},{baseposfinX,baseposfinY}, planfinal);
            }
            if (classe == 5) //Glissière
            {
                iss >> id >> tailleX >> tailleY >> rouge >> vert >> bleu >> refposX >> refposY >> baseposX >> baseposY >> baseposfinX >> baseposfinY >> plan3D;
                if (suiteniv3 > 1) { planfinal = true; }
                else if ((plan3D == planTempo) && (suiteniv3 == 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D < planTempo) && (suiteniv3== 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D != planTempo) && (suiteniv3 == 1)) { planfinal = true; planTempo = plan3D; }
                getFille(0)->getFille(compteurniv1)->getFille(compteurniv2)->ajouterFilleGlissiere(classe, id, {tailleX,tailleY}, {(uint8_t)rouge,(uint8_t)vert,(uint8_t)bleu}, {refposX,refposY}, {baseposX,baseposY},{baseposfinX,baseposfinY}, planfinal);
            }
        }

        //Niv 4
        if ( ligne.size()>=12 && ligne[12]=='[' && niveau==3 )
        {
            niveau = 4;
            std::getline(ifs, ligne);
        }
        if (ligne[12]==']' && niveau == 4 )
        {
            niveau = 3;
            compteurniv3 = compteurniv3 +1;
            compteurniv4 = compteurniv4 -1;
        }
        if ( ligne[16]!='[' && ligne[16]!=']' && niveau == 4 )
        {
            suiteniv3 = 0;
            suiteniv4 = suiteniv4+1;
            suiteniv2 = 0;
            suiteniv1 = 0;
            std::istringstream iss{ligne};
            iss >> classe ;
            if (classe == 0)
            {
                iss >> id >> tailleX >> tailleY >> rouge >> vert >> bleu >> refposX >> refposY >> baseposX >> baseposY >> plan3D;
                if (suiteniv4 > 1) { planfinal = true; }
                else if ((plan3D == planTempo) && (suiteniv4 == 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D < planTempo) && (suiteniv4== 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D != planTempo) && (suiteniv4 == 1)) { planfinal = true; planTempo = plan3D; }
                getFille(0)->getFille(compteurniv1)->getFille(compteurniv2)->getFille(compteurniv3)->ajouterFille(classe, id, {tailleX,tailleY}, {(uint8_t)rouge,(uint8_t)vert,(uint8_t)bleu}, {refposX,refposY}, {baseposX,baseposY}, planfinal);
            }
            if (classe == 1)
            {
                iss >> id >> rayon >> rouge >> vert >> bleu >> refposX >> refposY >> baseposX >> baseposY >> plan3D;
                if (suiteniv4 > 1) { planfinal = true; }
                else if ((plan3D == planTempo) && (suiteniv4 == 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D < planTempo) && (suiteniv4== 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D != planTempo) && (suiteniv4 == 1)) { planfinal = true; planTempo = plan3D; }
                getFille(0)->getFille(compteurniv1)->getFille(compteurniv2)->getFille(compteurniv3)->ajouterFilleCercle(classe, id, rayon, {(uint8_t)rouge,(uint8_t)vert,(uint8_t)bleu}, {refposX,refposY}, {baseposX,baseposY}, planfinal);
            }
            if (classe == 2)
            {
                iss >> id >> tailleX >> tailleY >> rouge >> vert >> bleu >> rougeb >> vertb >> bleub >> refposX >> refposY >> baseposX >> baseposY >> plan3D;
                if (suiteniv4 > 1) { planfinal = true; }
                else if ((plan3D == planTempo) && (suiteniv4 == 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D < planTempo) && (suiteniv4== 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D != planTempo) && (suiteniv4 == 1)) { planfinal = true; planTempo = plan3D; }
                getFille(0)->getFille(compteurniv1)->getFille(compteurniv2)->getFille(compteurniv3)->ajouterFilleBordure(classe, id, {tailleX,tailleY}, {(uint8_t)rouge,(uint8_t)vert,(uint8_t)bleu}, {(uint8_t)rougeb,(uint8_t)vertb,(uint8_t)bleub},{refposX,refposY}, {baseposX,baseposY}, planfinal);
            }
            if (classe == 3)
            {
                iss >> id >> rayon >> rouge >> vert >> bleu >> rougeb >> vertb >> bleub >> refposX >> refposY >> baseposX >> baseposY >> plan3D;
                if (suiteniv4 > 1) { planfinal = true; }
                else if ((plan3D == planTempo) && (suiteniv4 == 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D < planTempo) && (suiteniv4== 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D != planTempo) && (suiteniv4 == 1)) { planfinal = true; planTempo = plan3D; }
                getFille(0)->getFille(compteurniv1)->getFille(compteurniv2)->getFille(compteurniv3)->ajouterFilleCercleBordure(classe, id, rayon, {(uint8_t)rouge,(uint8_t)vert,(uint8_t)bleu}, {(uint8_t)rougeb,(uint8_t)vertb,(uint8_t)bleub},{refposX,refposY}, {baseposX,baseposY}, planfinal);
            }
            if (classe == 4) //GlissièreBordure
            {
                iss >> id >> tailleX >> tailleY >> rouge >> vert >> bleu >> rougeb >> vertb >> bleub >> refposX >> refposY >> baseposX >> baseposY >> baseposfinX >> baseposfinY >> plan3D;
                if (suiteniv4 > 1) { planfinal = true; }
                else if ((plan3D == planTempo) && (suiteniv4 == 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D < planTempo) && (suiteniv4== 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D != planTempo) && (suiteniv4 == 1)) { planfinal = true; planTempo = plan3D; }
                getFille(0)->getFille(compteurniv1)->getFille(compteurniv2)->getFille(compteurniv3)->ajouterFilleGlissiereBordure(classe, id, {tailleX,tailleY}, {(uint8_t)rouge,(uint8_t)vert,(uint8_t)bleu}, {(uint8_t)rougeb,(uint8_t)vertb,(uint8_t)bleub},{refposX,refposY}, {baseposX,baseposY},{baseposfinX,baseposfinY}, planfinal);
            }
            if (classe == 5) //Glissière
            {
                iss >> id >> tailleX >> tailleY >> rouge >> vert >> bleu >> refposX >> refposY >> baseposX >> baseposY >> baseposfinX >> baseposfinY >> plan3D;
                if (suiteniv4 > 1) { planfinal = true; }
                else if ((plan3D == planTempo) && (suiteniv4 == 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D < planTempo) && (suiteniv4== 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D != planTempo) && (suiteniv4 == 1)) { planfinal = true; planTempo = plan3D; }
                getFille(0)->getFille(compteurniv1)->getFille(compteurniv2)->getFille(compteurniv3)->ajouterFilleGlissiere(classe, id, {tailleX,tailleY}, {(uint8_t)rouge,(uint8_t)vert,(uint8_t)bleu}, {refposX,refposY}, {baseposX,baseposY},{baseposfinX,baseposfinY}, planfinal);
            }
        }

        //Niv 5
        if ( ligne.size()>=16 && ligne[16]=='[' && niveau==4 )
        {
            niveau = 5;
            std::getline(ifs, ligne);
        }
        if (ligne[16]==']' && niveau == 5 )
        {
            niveau = 4;
            compteurniv4 = compteurniv4 +1;
        }
        if ( ligne[20]!='[' && ligne[20]!=']' && niveau == 5 )
        {
            suiteniv3 = 0;
            suiteniv4 = 0;
            suiteniv2 = 0;
            suiteniv1 = 0;
            suiteniv5 = suiteniv5 +1;
            std::istringstream iss{ligne};
            iss >> classe ;
            if (classe == 0)
            {
                iss >> id >> tailleX >> tailleY >> rouge >> vert >> bleu >> refposX >> refposY >> baseposX >> baseposY >> plan3D;
                if (suiteniv5 > 1) { planfinal = true; }
                else if ((plan3D == planTempo) && (suiteniv5 == 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D < planTempo) && (suiteniv5== 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D != planTempo) && (suiteniv5 == 1)) { planfinal = true; planTempo = plan3D; }
                getFille(0)->getFille(compteurniv1)->getFille(compteurniv2)->getFille(compteurniv3)->getFille(compteurniv4)->ajouterFille(classe, id, {tailleX,tailleY}, {(uint8_t)rouge,(uint8_t)vert,(uint8_t)bleu}, {refposX,refposY}, {baseposX,baseposY}, planfinal);
            }
            if (classe == 1)
            {
                iss >> id >> rayon >> rouge >> vert >> bleu >> refposX >> refposY >> baseposX >> baseposY >> plan3D;
                if (suiteniv5 > 1) { planfinal = true; }
                else if ((plan3D == planTempo) && (suiteniv5 == 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D < planTempo) && (suiteniv5== 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D != planTempo) && (suiteniv5 == 1)) { planfinal = true; planTempo = plan3D; }
                getFille(0)->getFille(compteurniv1)->getFille(compteurniv2)->getFille(compteurniv3)->getFille(compteurniv4)->ajouterFilleCercle(classe, id, rayon, {(uint8_t)rouge,(uint8_t)vert,(uint8_t)bleu}, {refposX,refposY}, {baseposX,baseposY}, planfinal);
            }
            if (classe == 2)
            {
                iss >> id >> tailleX >> tailleY >> rouge >> vert >> bleu >> rougeb >> vertb >> bleub >> refposX >> refposY >> baseposX >> baseposY >> plan3D;
                if (suiteniv5 > 1) { planfinal = true; }
                else if ((plan3D == planTempo) && (suiteniv5 == 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D < planTempo) && (suiteniv5== 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D != planTempo) && (suiteniv5 == 1)) { planfinal = true; planTempo = plan3D; }
                getFille(0)->getFille(compteurniv1)->getFille(compteurniv2)->getFille(compteurniv3)->getFille(compteurniv4)->ajouterFilleBordure(classe, id, {tailleX,tailleY}, {(uint8_t)rouge,(uint8_t)vert,(uint8_t)bleu}, {(uint8_t)rougeb,(uint8_t)vertb,(uint8_t)bleub},{refposX,refposY}, {baseposX,baseposY}, planfinal);
            }
            if (classe == 3)
            {
                iss >> id >> rayon >> rouge >> vert >> bleu >> rougeb >> vertb >> bleub >> refposX >> refposY >> baseposX >> baseposY >> plan3D;
                if (suiteniv5 > 1) { planfinal = true; }
                else if ((plan3D == planTempo) && (suiteniv5 == 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D < planTempo) && (suiteniv5== 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D != planTempo) && (suiteniv5 == 1)) { planfinal = true; planTempo = plan3D; }
                getFille(0)->getFille(compteurniv1)->getFille(compteurniv2)->getFille(compteurniv3)->getFille(compteurniv4)->ajouterFilleCercleBordure(classe, id, rayon, {(uint8_t)rouge,(uint8_t)vert,(uint8_t)bleu}, {(uint8_t)rougeb,(uint8_t)vertb,(uint8_t)bleub},{refposX,refposY}, {baseposX,baseposY}, planfinal);
            }
            if (classe == 4) //GlissièreBordure
            {
                iss >> id >> tailleX >> tailleY >> rouge >> vert >> bleu >> rougeb >> vertb >> bleub >> refposX >> refposY >> baseposX >> baseposY >> baseposfinX >> baseposfinY >> plan3D;
                if (suiteniv5 > 1) { planfinal = true; }
                else if ((plan3D == planTempo) && (suiteniv5 == 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D < planTempo) && (suiteniv5== 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D != planTempo) && (suiteniv5 == 1)) { planfinal = true; planTempo = plan3D; }
                getFille(0)->getFille(compteurniv1)->getFille(compteurniv2)->getFille(compteurniv3)->getFille(compteurniv4)->ajouterFilleGlissiereBordure(classe, id, {tailleX,tailleY}, {(uint8_t)rouge,(uint8_t)vert,(uint8_t)bleu}, {(uint8_t)rougeb,(uint8_t)vertb,(uint8_t)bleub},{refposX,refposY}, {baseposX,baseposY},{baseposfinX,baseposfinY}, planfinal);
            }
            if (classe == 5) //Glissière
            {
                iss >> id >> tailleX >> tailleY >> rouge >> vert >> bleu >> refposX >> refposY >> baseposX >> baseposY >> baseposfinX >> baseposfinY >> plan3D;
                if (suiteniv5 > 1) { planfinal = true; }
                else if ((plan3D == planTempo) && (suiteniv5 == 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D < planTempo) && (suiteniv5== 1)) { planfinal = false; planTempo = plan3D; }
                else if ((plan3D != planTempo) && (suiteniv5 == 1)) { planfinal = true; planTempo = plan3D; }
                getFille(0)->getFille(compteurniv1)->getFille(compteurniv2)->getFille(compteurniv3)->getFille(compteurniv4)->ajouterFilleGlissiere(classe, id, {tailleX,tailleY}, {(uint8_t)rouge,(uint8_t)vert,(uint8_t)bleu}, {refposX,refposY}, {baseposX,baseposY},{baseposfinX,baseposfinY}, planfinal);
            }
        }
    }
}
