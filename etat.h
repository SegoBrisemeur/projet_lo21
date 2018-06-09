#ifndef ETAT_H_INCLUDED
#define ETAT_H_INCLUDED

#include <string>
#include <iostream>
using namespace std;

class Etat{

    unsigned int nbColonne;
    unsigned int nbLigne; // =1 quand 1D
    bool** valeurs;

public:
    Etat(unsigned int c, unsigned int l);
    Etat() : nbColonne(0), nbLigne(0), valeurs(nullptr) {}
    unsigned int getLargeur()const {return nbColonne;}
    unsigned int getLongueur()const {return nbLigne;}
    //utile de faire une fonction quelle_dim ?
    ~Etat();
    bool getCellule(unsigned int i, unsigned int j) const;
    void setCellule(unsigned int i, unsigned int j, bool val);
	Etat(const Etat& e);
	Etat& operator=(const Etat& e);

};

std::ostream& operator<<(std::ostream& f, const Etat& e);

#endif // ETAT_H_INCLUDED
