#ifndef AUTOCELL_H_INCLUDED
#define AUTOCELL_H_INCLUDED

#include <string>
#include <iostream>
#include<typeinfo>
#include "etat.h"

using namespace std;

class AutomateException {
public:
AutomateException(const std::string& message):info(message) {}
std::string getInfo() const { return info; }
private:
std::string info;
};

short unsigned int NumBitToNum(const std::string& num);
std::string NumToNumBit(short unsigned int num);


class Automate{
    //unsigned int nbEtat; pour l'instant seulement 2
    friend class AutomateManager;
public:
    virtual ~Automate()=default;
    Automate(){}
    //void setNbEtat(unsigned int m){nbEtat=m;}
    //unsigned short int getNbEtat() const {return nbEtat;}
    virtual void AppliquerTransition(const Etat&, Etat&) const =0; //methode virtuelle pure

};

class Automate1D : public Automate {
	unsigned short int numero;
	std::string numeroBit;
	Automate1D(unsigned short int num);
	Automate1D(const std::string& num);
    friend class AutomateManager;

public:
	unsigned short int getNumero() const { return numero; }
	const std::string& getNumeroBit() const { return numeroBit; }
	void AppliquerTransition(const Etat& dep, Etat& dest) const;

};

std::ostream& operator<<(std::ostream& f, const Automate1D& t);


class Automate2D : public Automate{
    unsigned int nbMinVivant; /*sachant une cellule vivante, cb il faut de cellule vivante minimum pour qu'elle vive à t+1*/
    unsigned int nbMaxVivant;
    unsigned int nbMinMort; /*même choix pour une cellule morte*/
    unsigned int nbMaxMort;
    Automate2D(unsigned int minV=0, unsigned int maxV=0, unsigned int minM=0, unsigned int maxM=0);
    ~Automate2D()=default;
    friend class AutomateManager;

public :
    const unsigned int getMinV()const{return nbMinVivant;}
    const unsigned int getMaxV()const{return nbMaxVivant;}
    const unsigned int getMinM()const{return nbMinMort;}
    const unsigned int getMaxM()const{return nbMaxMort;}
    void AppliquerTransition(const Etat& dep, Etat& dest) const;
    unsigned int CountVoisin(unsigned int li, unsigned int co, const Etat& e) const;
};

std::ostream& operator<<(std::ostream& f, const Automate2D& A);


class AutomateManager{ //Le manager gère un ensemble d'automate qui peut être 1D ou 2D

    static AutomateManager* instance;
    Automate1D* automates1D[256];
    Automate2D* automates2D[50]; //on ne créé pas un tableau de taille maximale car pas optimal
    unsigned int tailleTab2D=50;
    unsigned int rangDernier=0; //le rang du dernier automate 2D rentré

    AutomateManager();
    ~AutomateManager();
    AutomateManager(const AutomateManager& A)=delete; //pour qu'on ne puisse pas l'utiliser car on ne veut pas d'autres instances
    AutomateManager& operator=(const AutomateManager& A)=delete; //idem

    struct Handler{
        AutomateManager* instance;
        Handler(): instance(nullptr){}
        ~Handler(){
            delete instance;}
        };

public:
    static Handler handler;
    static AutomateManager& getInstance();
    static void libererInstance(){
        delete handler.instance;
        handler.instance=nullptr;
    }
    const Automate1D& getAutomate1D(short unsigned int num);
    const Automate1D& getAutomate1D(const string& num);
    const Automate2D& getAutomate2D(const unsigned int miniV, unsigned int maxiV, unsigned int miniM, unsigned int maxiM);
    unsigned int getDim2D()const {return tailleTab2D;}
    unsigned int getRang2D()const {return rangDernier;}
    int indice_automate(unsigned int a, unsigned int b, unsigned int c, unsigned int d) const; //retourne l'indice dans le tableau ou -1 si jamais rentré

};

#endif // AUTOCELL_H_INCLUDED
