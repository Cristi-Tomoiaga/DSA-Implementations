#pragma once

#include <stack>
#include "MDO.h"

class IteratorMDO{
	friend class MDO;
private:

	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	// O(h)
	IteratorMDO(const MDO& dictionar);

	//contine o referinta catre containerul pe care il itereaza
	const MDO& dict;
	/* aici e reprezentarea  specifica a iteratorului */
	// referinta la nodul curent
	Nod* curent;

	// stiva folosita pentru parcurgerea in inordine
	stack<Nod*> s;

public:

		//reseteaza pozitia iteratorului la inceputul containerului
		// O(h)
		void prim();

		//muta iteratorul in container
		// arunca exceptie daca iteratorul nu e valid
		// O(h)
		void urmator();

		//verifica daca iteratorul e valid (indica un element al containerului)
		// Theta(1)
		bool valid() const;

		//returneaza valoarea elementului din container referit de iterator
		//arunca exceptie daca iteratorul nu e valid
		// Theta(1)
		TElem element() const;
};

