#ifndef COULEUR_H_INCLUDED
#define COULEUR_H_INCLUDED

#include <string>
#include <cstdint>

class Couleur
{
    private :
        // uint8_t équivalent à unsigned char :
        // unsigned 8 bits (8 bits non signé)
        uint8_t m_rouge, m_vert, m_bleu;

    public :
        Couleur(uint8_t rouge, uint8_t vert, uint8_t bleu);
        Couleur();
        void afficher() const;
        void saisir();
        void muter(double amplitude);

        operator std::string() const;
        friend bool operator!=(const Couleur& c1, const Couleur& c2);

        uint8_t getRouge () const ;
        uint8_t getVert () const ;
        uint8_t getBleu () const ;
};

///************************///
///    METHODES INLINES    ///
///************************///

inline uint8_t Couleur::getRouge() const
{
    return m_rouge;
}

inline uint8_t Couleur::getBleu() const
{
    return m_bleu;
}

inline uint8_t Couleur::getVert() const
{
    return m_vert;
}

#endif // COULEUR_H_INCLUDED
