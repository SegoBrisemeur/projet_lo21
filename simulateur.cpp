#include "simulateur.h"

void Simulateur::setEtatDepart(const Etat& e){
    if((typeid(automate).name()=="Automate1D" && e.getLongueur()!=1) || (typeid(automate).name()=="Automate2D" && e.getLongueur()==1))
        throw AutomateException("erreur : dimensions de l'automate et de l'etat incompatibles");
    depart = &e;
    if(etats[0]==nullptr)
        etats[0]=new Etat(e);
    else *etats[0]=e;
    reset();
}

Simulateur::Simulateur(const Automate& a, unsigned int buf): automate(a), depart(nullptr), etats(nullptr), nbMaxEtats(buf),rang(0) {
    etats = new Etat*[nbMaxEtats];
	for (unsigned int i = 0; i < nbMaxEtats; i++)
        etats[i] = nullptr;
}

Simulateur::Simulateur(const Automate& a, const Etat& dep, unsigned int buffer) : automate(a), etats(nullptr), nbMaxEtats(buffer), rang(0){
    etats = new Etat*[nbMaxEtats];
	for (unsigned int i = 0; i < nbMaxEtats; i++)
        etats[i] = nullptr;
	setEtatDepart(dep);
}


void Simulateur::build(unsigned int cellule) {
	if (cellule >= nbMaxEtats)
        throw AutomateException("erreur taille buffer");
	if (etats[cellule] == nullptr)
        etats[cellule] = new Etat;
}

void Simulateur::reset(){
    if (depart==nullptr) throw AutomateException("etat depart indefini");
	build(0); *etats[0] = *depart;
	rang = 0;
}


void Simulateur::next() {
	if (depart == nullptr)
        throw AutomateException("etat depart indefini");
	rang++;
	build(rang%nbMaxEtats);
	automate.AppliquerTransition(*etats[(rang - 1) % nbMaxEtats], *etats[rang%nbMaxEtats]);
}

void Simulateur::run(unsigned int nb_steps) {
	for (unsigned int i = 0; i < nb_steps; i++) next();
}

const Etat& Simulateur::dernier() const {
	return *etats[rang%nbMaxEtats];
}

Simulateur::~Simulateur() {
	for (unsigned int i = 0; i < nbMaxEtats; i++) delete etats[i];
	delete[] etats;
}
