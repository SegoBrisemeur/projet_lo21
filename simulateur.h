#ifndef SIMULATEUR_H_INCLUDED
#define SIMULATEUR_H_INCLUDED

#include "etat.h"
#include "automate.h"

using namespace std;

class Simulateur{

    const Automate& automate;
    const Etat* depart;
    Etat** etats;
    unsigned int nbMaxEtats=0; //nb max qu'on sauvegarde dans le tableau etats
    unsigned int rang=0;
    void build(unsigned int c);
    Simulateur(const Simulateur& s)=delete;
    Simulateur& operator=(const Simulateur& s)=delete;
public :
    Simulateur(const Automate& a, unsigned int buf=2);
    Simulateur(const Automate& a, const Etat& dep, unsigned int buffer=2);
    void setEtatDepart(const Etat& e);
    void next();
    void run(unsigned int nbSteps);
    void reset();
    const Etat& dernier() const;
    unsigned int getRangDernier()const{return rang;}
    ~Simulateur();

    class Iterator {
		friend class Simulateur;
        Simulateur* sim;
        int i;
		Iterator(Simulateur* s):sim(s), i(s->rang){}
	public:
        Iterator():sim(nullptr),i(0) {}
		bool isDone() const {
			return ((sim == nullptr) ||
				   (i == -1 && sim->rang<sim->nbMaxEtats) ||
				   (i == sim->rang - sim->nbMaxEtats));
		}
		Iterator& operator++() {
			if (isDone())
				throw AutomateException("error, next on an iterator which is done");
			i--;
			if (i == -1 && sim->rang >= sim->nbMaxEtats) i = sim->nbMaxEtats - 1;
			return *this;
		}
		Etat& operator* () const {
			if (isDone())
				throw AutomateException("error, indirection on an iterator which is done");
			return *sim->etats[i%sim->nbMaxEtats];
		}
	};
	Iterator getIterator() {
		return Iterator(this);
	}

	class ConstIterator {
		friend class Simulateur;
        const Simulateur* sim;
        int i;
		ConstIterator(Simulateur* s):sim(s), i(s->rang){}
	public:
        ConstIterator():sim(nullptr),i(0) {}
		bool isDone() const {
			return ((sim == nullptr) ||
				   (i == -1 && sim->rang<sim->nbMaxEtats) ||
				   (i == sim->rang - sim->nbMaxEtats));
		}
		ConstIterator& operator++() {
			if (isDone())
				throw AutomateException("error, next on a constiterator which is done");
			i--;
			if (i == -1 && sim->rang >= sim->nbMaxEtats) i = sim->nbMaxEtats - 1;
			return *this;
		}
		Etat& operator* () const {
			if (isDone())
				throw AutomateException("error, indirection on an iterator which is done");
			return *sim->etats[i%sim->nbMaxEtats];
		}
	};
	ConstIterator getConstIterator() {
		return ConstIterator(this);
	}
};


#endif // SIMULATEUR_H_INCLUDED
