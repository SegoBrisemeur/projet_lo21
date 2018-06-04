#ifndef AUTOCELL_H_INCLUDED
#define AUTOCELL_H_INCLUDED

#include <string>
#include <iostream>

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

class Etat1D {
	unsigned int nbColonnes;
	bool* valeur;
public:
	Etat1D():nbColonnes(0), valeur(nullptr) {}
	Etat1D(unsigned int n);
	~Etat1D() { delete[] valeur; }
	Etat1D(const Etat1D& e);
	Etat1D& operator=(const Etat1D& e);
	void setCellule(unsigned int i, bool val);
	bool getCellule(unsigned int) const;
	unsigned int getNbColonnes() const { return nbColonnes; }
};

std::ostream& operator<<(std::ostream& f, const Etat1D& e);

class Automate1D {
	unsigned short int numero;
	std::string numeroBit;
	//friend class AutomateManager;
public:
    Automate1D(unsigned short int num);
	Automate1D(const std::string& num);
    ~Automate1D(){}
    Automate1D(const Automate1D& a);
    Automate1D& operator=(const Automate1D& a);
	unsigned short int getNumero() const { return numero; }
	const std::string& getNumeroBit() const { return numeroBit; }
	void appliquerTransition(const Etat1D& dep, Etat1D& dest) const;
};

std::ostream& operator<<(std::ostream& f, const Automate1D& t);

class Simulateur1D {
	const Automate1D& automate;
    Etat1D** etats;
    const Etat1D* depart;
	unsigned int nbMaxEtats;
    unsigned int rang;
	void build(unsigned int c);
    Simulateur1D(const Simulateur1D& s);
    Simulateur1D& operator=(const Simulateur1D& s);
public:
	Simulateur1D(const Automate1D& a, unsigned int buffer = 2);
	Simulateur1D(const Automate1D& a, const Etat1D& dep, unsigned int buffer = 2);
	void setEtatDepart(const Etat1D& e);
	void run(unsigned int nbSteps); // g�n�re les n prochains �tats
	void next(); // g�n�re le prochain �tat
	const Etat1D& dernier() const;
	unsigned int getRangDernier() const { return rang; }
	void reset(); // revenir � l'�tat de d�part
	~Simulateur1D();
};

class Etat2D{ //grille de l'application

    unsigned int nbLigne=0;
    unsigned int nbColonne=0;
    bool** valeurs;

public:

    Etat2D(unsigned int nbL=0, unsigned int nbC=0);
    const unsigned int getCol()const {return nbColonne;}
    const unsigned int getRow()const {return nbLigne;}
    bool getCellule(unsigned int i, unsigned int j) const;
    void setCellule(unsigned int i, unsigned int j, bool val);
    ~Etat2D();
    void afficherGrille() const;
    Etat2D(const Etat2D& e);
    Etat2D& operator=(const Etat2D& e);
    unsigned int CountVoisin(unsigned int li, unsigned int co) const;
};

std::ostream& operator<<(std::ostream& f, const Etat2D& e);

class Automate2D{

    unsigned int nbMinVivant; /*sachant une cellule vivante, cb il
    faut de cellule vivante minimum pour qu'elle vive � t+1*/
    unsigned int nbMaxVivant;
    unsigned int nbMinMort; /*m�me choix pour une cellule morte*/
    unsigned int nbMaxMort;
    //--> v�rifier que min<max
public :
    Automate2D(unsigned int minV=0, unsigned int maxV=0, unsigned int
               minM=0, unsigned int maxM=0) : nbMinVivant(minV),
               nbMaxVivant(maxV), nbMinMort(minM), nbMaxMort(maxM){}
    const unsigned int getMinV()const{return nbMinVivant;}
    const unsigned int getMaxV()const{return nbMaxVivant;}
    const unsigned int getMinM()const{return nbMinMort;}
    const unsigned int getMaxM()const{return nbMaxMort;}
    ~Automate2D()=default;
    void AppliquerTransition(const Etat2D& dep, Etat2D& dest) const;
};

class Simulateur2D{

    const Automate2D& automate;
    const Etat2D* depart=nullptr;
    Etat2D** etats=nullptr;
    unsigned int nbMaxEtats=0; //nb max qu'on sauvegarde dans le tableau etats
    unsigned int rang=0;

public :
    void setEtatDepart(const Etat2D& e);
    Simulateur2D(const Automate2D& a, unsigned int buf=2);
    Simulateur2D(const Automate2D& a, const Etat2D& dep, unsigned int buffer=2);
    void next();
    void run(unsigned int nbSteps);
    void reset();
    const Etat2D& dernier() const;
    unsigned int getRangDernier()const;
    ~Simulateur2D();

};

#endif // AUTOCELL_H_INCLUDED
