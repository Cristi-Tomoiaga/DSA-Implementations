#pragma once
#include "Matrice.h"

class Matrice;
typedef int TElem;

class IteratorMatrice {
	friend class Matrice;
private:
	//contine o referinta catre containerul pe care il itereaza
	const Matrice& m;

	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container de pe coloana data
	// CT Theta(1)
	IteratorMatrice(const Matrice& m, int coloana);

	/*aici e reprezentarea specifica a iteratorului*/
	// linia si coloana elementului curent
	int col;
	int lin;
public:
	//returneaza valoarea elementului din container referit de iterator
	//arunca exceptie daca iteratorul nu e valid
	// CF Theta(1) CD Theta(m) CT O(m)
	// SUH: CM Theta(1)
	TElem element() const;

	//verifica daca iteratorul e valid (indica un element al containerului)
	// CT Theta(1)
	bool valid() const;

	//muta iteratorul la elementul urmator in container
	//arunca exceptie daca iteratorul nu e valid
	// CT Theta(1)
	void urmator();

	//muta iteratorul la elementul anterior in container
	//arunca exceptie daca iteratorul nu e valid
	// CT Theta(1)
	void precedent();

	//reseteaza pozitia iteratorului la inceputul containerului
	// CT Theta(1)
	void prim();

	//reseteaza pozitia iteratorului la sfarsitul containerului
	// CT Theta(1)
	void ultim();
};

