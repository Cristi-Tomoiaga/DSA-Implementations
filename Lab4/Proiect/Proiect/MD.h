#pragma once
#include<vector>
#include<utility>

#define CAPACITATE_INIT 20
#define NULL_TVALOARE -1

using namespace std;

typedef int TCheie;
typedef int TValoare;

typedef std::pair<TCheie, TValoare> TElem;

class IteratorMD;

// n - numarul de valori memorate
class Nod {
	friend class IteratorMD;
	friend class MD;

private:
	// Cheia
	TCheie c;
	
	// LSI pentru valorile asociate cheii
	int cp, prim, primLiber;
	TValoare* e;
	int* urm;

	// Theta(cp)
	// redimensionare vectori
	void redim();

	// Theta(1)
	// dealoca nodul de pe pozitia i
	void dealoca(int i);

	// Theta(1)
	// aloca un nou nod si returneaza pozitia lui
	int aloca();

	// Theta(1) amortizat
	// creeaza un nod nou cu informatia data si returneaza pozitia lui
	int creeazaNod(TValoare v);

public:
	// Theta(cp)
	// constructor default
	Nod();

	// Theta(cp)
	// constructor
	Nod(TCheie c);

	// Theta(cp)
	// constructor de copiere
	Nod(const Nod& ot);

	// Theta(cp)
	// operator de copy assignment
	Nod& operator=(const Nod& ot);

	// Theta(1)
	// destructor
	~Nod();

	// Theta(1)
	// getter pentru cheie
	TCheie cheie() const;

	// Theta(n)
	// getter pentru valori
	vector<TValoare> valori() const;

	// Theta(1) amortizat
	// adauga la inceput o valoare in LSI
	void adaugaInceput(TValoare v);

	// O(n)
	// sterge prima aparitie a valorii date, returneaza adevarat daca s-a sters, fals altfel
	bool sterge(TValoare v);

	// Theta(1)
	// returneaza adevarat daca lista de valori e vida, false altfel
	bool vida() const;
};

// md - numarul de elemente (cheie, valoare)
// n - numarul de chei distincte
class MD
{
	friend class IteratorMD;

private:
	/* aici e reprezentarea */
	// LSI pentru nodurile listei
	int cp, prim, primLiber;
	Nod* e;
	int* urm;
	int len;

	// Theta(cp)
	// redimensionare vectori
	void redim();

	// Theta(1)
	// dealoca nodul de pe pozitia i
	void dealoca(int i);

	// Theta(1)
	// aloca un nou nod si returneaza pozitia lui
	int aloca();

	// Theta(1) amortizat
	// creeaza un nod nou cu informatia data si returneaza pozitia lui
	int creeazaNod(TCheie c);

public:
	// Theta(cp)
	// constructorul implicit al MultiDictionarului
	MD();

	// O(n) amortizat
	// adauga o pereche (cheie, valoare) in MD	
	void adauga(TCheie c, TValoare v);

	// O(n+md)
	//cauta o cheie si returneaza vectorul de valori asociate
	vector<TValoare> cauta(TCheie c) const;

	// O(n+md)
	//sterge o cheie si o valoare 
	//returneaza adevarat daca s-a gasit cheia si valoarea de sters
	bool sterge(TCheie c, TValoare v);

	// Theta(1)
	//returneaza numarul de perechi (cheie, valoare) din MD 
	int dim() const;

	// Theta(1)
	//verifica daca MultiDictionarul e vid 
	bool vid() const;

	// Caz Favorabil: Theta(n+md)
	// Caz Defavorabil: Theta(n+md)
	// Complexitate Totala: Theta(n+md)
	// returneaza valoarea care apare cel mai frecvent în multidictionar. 
	// Daca mai multe valori apar cel mai frecvent, se returneaza una (oricare) dintre ele. 
	// Daca multidictionarul este vid, operatia returneaza NULL_TVALOARE 
	TValoare ceaMaiFrecventaValoare() const;

	// Theta(1)
	// se returneaza iterator pe MD
	IteratorMD iterator() const;

	// Theta(1)
	// destructorul MultiDictionarului	
	~MD();
};