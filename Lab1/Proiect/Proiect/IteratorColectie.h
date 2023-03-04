#pragma once
#include "Colectie.h"

class Colectie;
typedef int TElem;

class IteratorColectie
{
	friend class Colectie;
private:
	// Theta(1)
	//constructorul primeste o referinta catre Container
    //iteratorul va referi primul element din container
	IteratorColectie(const Colectie& c);

    //contine o referinta catre containerul pe care il itereaza
	const Colectie& col;
	/* aici e reprezentarea specifica a iteratorului*/
	int pos; // pozitia curenta in vectorul P

public:

		// Theta(1)
		//reseteaza pozitia iteratorului la inceputul containerului
		void prim();

		// Theta(1)
		//muta iteratorul in container
		// arunca exceptie daca iteratorul nu e valid
		void urmator();

		// Theta(1)
		//verifica daca iteratorul e valid (indica un element al containerului)
		bool valid() const;

		// Theta(1)
		//returneaza valoarea elementului din container referit de iterator
		//arunca exceptie daca iteratorul nu e valid
		TElem element() const;
};

