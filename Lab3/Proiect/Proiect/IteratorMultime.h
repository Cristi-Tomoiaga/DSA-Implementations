#pragma once

class Nod;

class Multime;
typedef int TElem;

class IteratorMultime
{
	friend class Multime;
private:

	// Theta(1)
	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	IteratorMultime(const Multime& m);

	//contine o referinta catre containerul pe care il itereaza
	const Multime& multime;
	/* aici e reprezentarea  specifica a iteratorului */
	Nod* curent; // pointer la nodul curent din multime

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
