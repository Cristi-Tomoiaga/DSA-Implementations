#pragma once

#define NULL_TELEM -1
typedef int TElem;

class Multime;

// reprezinta un nod dintr-o LSI
class Nod {
private:
	TElem e;
	Nod* urm;
public:
	friend class Multime;

	// Theta(1)
	// constructor
	Nod(TElem element, Nod* urmator);

	// getteri pt e si urm
	// Theta(1)
	TElem element();

	// Theta(1)
	Nod* urmator();
};

class IteratorMultime;

class Multime {
	friend class IteratorMultime;

    private:
		/* aici e reprezentarea */
		Nod* prim; // pointer spre primul element din lista

    public:
		// Theta(1)
 		//constructorul implicit
		Multime();

		// O(n)
		//adauga un element in multime
		//returneaza adevarat daca elementul a fost adaugat (nu exista deja in multime)
		bool adauga(TElem e);

		// O(n)
		//sterge un element din multime
		//returneaza adevarat daca elementul a existat si a fost sters
		bool sterge(TElem e);

		// O(n)
		//verifica daca un element se afla in multime
		bool cauta(TElem elem) const;

		// Theta(n)
		//intoarce numarul de elemente din multime;
		int dim() const;

		// Theta(1)
		//verifica daca multimea e vida;
		bool vida() const;

		// Caz favorabil: Theta(n)
		// Caz defavorabil: Theta(n)
		// Caz mediu: Theta(n)
		// Complexitate totala: Theta(n)
		// returneaza diferenta dintre valoarea maxima si cea minima (presupunem valori întregi) 
		// daca multimea este vida, se returneaza -1 
		int diferentaMaxMin() const;

		// Theta(1)
		//returneaza un iterator pe multime
		IteratorMultime iterator() const;

		// Theta(n)
		// destructorul multimii
		~Multime();
};




