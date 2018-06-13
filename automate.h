#ifndef AUTOMATE_H_INCLUDED
#define AUTOMATE_H_INCLUDED

#include <string>
#include <iostream>
#include<typeinfo>
#include "etat.h"
#include <cstdlib> //pour le rand()
#include <vector>

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
    unsigned int nbEtats;
    friend class AutomateManager;
protected:
	Automate(unsigned int n) : nbEtats(n){}
public:
    //virtual ~Automate()=0;
    //void setNbEtat(unsigned int m){nbEtat=m;}
    unsigned int getNbEtats() const {return nbEtats;}
    virtual void AppliquerTransition(const Etat&, Etat&) const =0; //methode virtuelle pure --> la classe est abstraite donc non instanciable

};

class Automate1D : public Automate {
    unsigned short int numero;
    std::string numeroBit;
    Automate1D(unsigned short int num, unsigned int nbE=2);
    Automate1D(const std::string& num, unsigned int nbE=2);
    friend class AutomateManager;

public:
    unsigned short int getNumero() const { return numero; }
    const std::string& getNumeroBit() const { return numeroBit; }
    void AppliquerTransition(const Etat& dep, Etat& dest) const;

};

std::ostream& operator<<(std::ostream& f, const Automate1D& t);


class Automate2D : public Automate{
    unsigned short int nbMinVivant; /*sachant une cellule vivante, cb il faut de cellule vivante minimum pour qu'elle vive � t+1*/
    unsigned short int nbMaxVivant;
    unsigned short int nbMinMort; /*m�me choix pour une cellule morte*/
    unsigned short int nbMaxMort;
    Automate2D(unsigned short int minV=0, unsigned short int maxV=0, unsigned short int minM=0, unsigned short int maxM=0, unsigned int nbE=2);
    friend class AutomateManager;

public :
    unsigned short int getMinV()const{return nbMinVivant;}
    unsigned short int getMaxV()const{return nbMaxVivant;}
    unsigned short int getMinM()const{return nbMinMort;}
    unsigned short int getMaxM()const{return nbMaxMort;}
	unsigned short int CountVoisin(unsigned int li, unsigned int co, const Etat& e) const;
    void AppliquerTransition(const Etat& dep, Etat& dest) const;
};

std::ostream& operator<<(std::ostream& f, const Automate2D& A);



class AutomateEpidemie : public Automate {

    unsigned short int chance1; //�tant malade, chance /10 de mourir
	unsigned short int chance2; //�tant sain, chance /10 de tomber malade	
    friend class AutomateManager;
	AutomateEpidemie(unsigned int c1 = 0, unsigned int c2 = 0, unsigned int nbE = 4);
public :
    //~AutomateEpidemie() = delete;
    unsigned short int getChance1() const { return chance1; }
	unsigned short int getChance2() const { return chance2; }
	unsigned short int CountVoisinMalade(unsigned int li, unsigned int co, const Etat& e) const;
    void AppliquerTransition(const Etat& dep, Etat& dest) const;

};


std::ostream& operator<<(std::ostream& f, const AutomateEpidemie& A);


class AutomateManager{ //Le manager g?re un ensemble d'automate qui peut ?tre 1D ou 2D

    static AutomateManager* instance;

    //Trois tableaux o? on stocke les diff�rents automates :
    Automate1D* automates1D[256];
    Automate2D** automates2D; //on ne cr�� pas un tableau de taille maximale car pas optimal
    //Automate2D est le jeu de la vie
    AutomateEpidemie** automatesEp;

    //Attributs pour le tableau d'automates 2D
    unsigned int tailleTab2D;
    unsigned int nb2DStockes; //le rang du dernier automate 2D rentr�

    //Attributs pour le tableau d'automates Epidemie
    unsigned int tailleTabEp;
    unsigned int nbEpStockes;

    AutomateManager();
    ~AutomateManager();
    AutomateManager(const AutomateManager& A);//=delete; //pour qu'on ne puisse pas l'utiliser car on ne veut pas d'autres instances
    AutomateManager& operator=(const AutomateManager& A);//=delete; //idem

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
	
	std::vector<string> TypesAutomates;
	
    //fonctions pour r�cup�rer un automate stock� par le simulateur ou le construire s'il n'existe pas
    const Automate1D& getAutomate1D(short unsigned int num);
    const Automate1D& getAutomate1D(const string& num);
    const Automate2D& getAutomate2D(unsigned int miniV, unsigned int maxiV, unsigned int miniM, unsigned int maxiM);
	const AutomateEpidemie& getAutomateEp(unsigned int c1, unsigned int c2);

    unsigned int getDim2D() const {return tailleTab2D;}
    unsigned int getNb2DStockes() const {return nb2DStockes;}
    int indice_automate2D(unsigned int a, unsigned int b, unsigned int c, unsigned int d) const; //retourne l'indice dans le tableau ou -1 si jamais rentr�
    const Automate2D& getElem2D(unsigned int n) const;

	unsigned int getDimEp() const { return tailleTabEp; }
	unsigned int getNbEpStockes() const { return nbEpStockes; }
	int indice_automateEp(unsigned int c1, unsigned int c2) const;
    const AutomateEpidemie& getElemEp(unsigned int n) const;

};

#endif // AUTOMATE_H_INCLUDED
