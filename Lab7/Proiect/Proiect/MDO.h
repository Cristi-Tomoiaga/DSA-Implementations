#pragma once

#include <vector>

typedef int TCheie;
typedef int TValoare;

#include <utility>
typedef std::pair<TCheie, TValoare> TElem;

using namespace std;

class IteratorMDO;

typedef bool(*Relatie)(TCheie, TCheie);

class MDO;

class Nod {
private:
	TElem e;
	Nod* st;
	Nod* dr;
public:
	friend class MDO;

	// constructor pentru nod
	// Theta(1)
	Nod(TElem e, Nod* st, Nod* dr) : e{ e }, st{ st }, dr{ dr } {}

	// getter pentru element
	// Theta(1)
	TElem element() const {
		return this->e;
	}

	// getter pentru referinta stanga
	// Theta(1)
	Nod* stanga() const {
		return this->st;
	}
	 
	// getter pentru referinta dreapta
	// Theta(1)
	Nod* dreapta() const {
		return this->dr;
	}
};

// n - numarul de elemente din MDO
// h - inaltimea ABC-ului, log_2(n) <= h <= n
class MDO {
	friend class IteratorMDO;
private:
	/* aici e reprezentarea */
	// relatia
	Relatie r;

	// referinta la radacina
	Nod* rad;
	// numar de elemente
	int n;

	// adauga recursiv elementul e in subarborele de radacina p
	// O(h)
	Nod* adaugaRec(Nod* p, TElem e);

	// determina elementul cu cheia minima, in raport cu relatia, din subarborele de radacina p
	// O(h)
	TElem minim(Nod* p);

	// sterge recursiv elementul e din subarborele de radacina p
	// O(h)
	Nod* stergeRec(Nod* p, TElem e);

	// distruge recursiv subarborele de radacina p
	// Theta(n)
	void distrugeRec(Nod* p);
public:

	// constructorul implicit al MultiDictionarului Ordonat
	// Theta(1)
	MDO(Relatie r);

	// adauga o pereche (cheie, valoare) in MDO
	// O(h)
	void adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza vectorul de valori asociate
	// O(h)
	vector<TValoare> cauta(TCheie c) const;

	//sterge o cheie si o valoare 
	//returneaza adevarat daca s-a gasit cheia si valoarea de sters
	// O(h)
	bool sterge(TCheie c, TValoare v);

	//returneaza numarul de perechi (cheie, valoare) din MDO 
	// Theta(1)
	int dim() const;

	//verifica daca MultiDictionarul Ordonat e vid 
	// Theta(1)
	bool vid() const;

	// returneaza un vector cu toate valorile din MultidictionarOrdonat  
	// CF=CD=CM=CT: Theta(n)
	vector<TValoare> colectiaValorilor() const;

	// se returneaza iterator pe MDO
	// iteratorul va returna perechile in ordine in raport cu relatia de ordine
	// Theta(1)
	IteratorMDO iterator() const;

	// destructorul 	
	// Theta(n)
	~MDO();

};
