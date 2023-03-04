#pragma once

#define CP_INIT 20

#define NULL_TELEM -1
typedef int TElem;

class IteratorColectie;

class Colectie
{
	friend class IteratorColectie;

private:
	/* aici e reprezentarea */
	// capacitatile vectorilor D si P
	int cpD, cpP; 

	// numarul efectiv de elemente din vectorii D si P
	int nD, nP; 

	// cei doi vectori D si P
	TElem* d;
	int* p;

	// redimensionare vectori
	// Theta(nD)
	void redimD();
	// Theta(nP)
	void redimP();

public:
		// Theta(1)
		//constructorul implicit
		Colectie();

		// O(nD+nP)
		//adauga un element in colectie
		void adauga(TElem e);

		// O(nD+nP)
		//sterge o aparitie a unui element din colectie
		//returneaza adevarat daca s-a putut sterge
		bool sterge(TElem e);

		// O(nD)
		//verifica daca un element se afla in colectie
		bool cauta(TElem elem) const;

		// O(nD+nP)
		//returneaza numar de aparitii ale unui element in colectie
		int nrAparitii(TElem elem) const;

		// Theta(1)
		//intoarce numarul de elemente din colectie;
		int dim() const;

		// Theta(1)
		//verifica daca colectia e vida;
		bool vida() const;

		// Theta(1)
		//returneaza un iterator pe colectie
		IteratorColectie iterator() const;

		// Theta(1)
		// destructorul colectiei
		~Colectie();

};

