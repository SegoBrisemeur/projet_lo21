#include "etat.h"
#include "automate.h"

Etat::Etat(unsigned int l, unsigned int c): nbColonne(c), nbLigne(l){

    if (c==0 || l==0)
        throw AutomateException("Mauvaise dimension de la matrice");

    else{
        valeurs = new unsigned int*[nbLigne];
        for (unsigned int i=0; i<nbLigne; i++){
            valeurs[i] = new unsigned int[nbColonne];
            for(unsigned int j=0; j<nbColonne; ++j)
                valeurs[i][j]=0;
                }
    }
}

void Etat::setCellule(unsigned int i, unsigned int j, unsigned int val) {
	if (i >= nbLigne || j>=nbColonne)
        throw AutomateException("Cellule inexistante dimension trop �lev�e");
	valeurs[i][j] = val;
}

unsigned int Etat::getCellule(unsigned int i, unsigned int j) const{
    if (i>=nbLigne|| j>=nbColonne)
        throw AutomateException("Cellule inexistante");
    return valeurs[i][j];
}

Etat::~Etat(){

for(unsigned int i=0; i<nbLigne;++i)
        delete valeurs[i];
    delete[] valeurs;
}

Etat::Etat(const Etat& e): nbColonne(e.nbColonne), nbLigne(e.nbLigne), valeurs(nullptr){

    if(nbLigne<=0 || nbColonne<=0)
        throw AutomateException("Mauvaise dimension");

    else {
        valeurs = new unsigned int*[nbLigne];
        for(unsigned int i=0; i<nbLigne; ++i){

            valeurs[i]=new unsigned int[nbColonne];
            for(unsigned int j=0; j<nbColonne; ++j){
                valeurs[i][j]=e.valeurs[i][j];
            }
        }
    }

}

Etat& Etat::operator=(const Etat& e){
    if(this != &e){ //auto-affectation impossible
        if(nbLigne!=e.nbLigne){ //on refait tout le tableau car pas bon nombre de ligne d�s le d�but

            for(unsigned int i=0;i<nbLigne;++i)
                delete valeurs[i]; //on supprime chaque ligne
            delete[] valeurs;

            nbLigne=e.nbLigne;
            valeurs=new unsigned int*[nbLigne];
            nbColonne=e.nbColonne;

            for(unsigned int i=0; i<nbLigne;++i)
                valeurs[i]=new unsigned int[nbColonne];
            }

        else if(nbColonne!=e.nbColonne){

            nbColonne=e.nbColonne;
            for(unsigned int i=0;i<nbLigne;++i){
                delete valeurs[i];
                valeurs[i]=new unsigned int[nbColonne];
            }
        }

        for (unsigned int i=0;i<nbLigne;i++){
            for(unsigned int j=0;j<nbColonne;++j)
                valeurs[i][j]=e.valeurs[i][j];
        }
    }

    return *this;
    }

std::ostream& operator<<(std::ostream& f, const Etat& e){

    for (unsigned int i=0; i<e.getLongueur(); ++i){
        for (unsigned int j=0; j<e.getLargeur(); ++j)
            f<<e.getCellule(i,j);
        f<<endl;
    }
    return f;

}
