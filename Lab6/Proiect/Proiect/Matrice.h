#pragma once
#include "Iterator.h"

typedef int TElem;

#define NULL_TELEMENT 0

#define MAX 90071

class IteratorMatrice;

struct Triplet {
	int l, c;
	TElem val;
};

class Matrice {

private:
	/* aici e reprezentarea */
	// nr linii si coloane
	int nrLin;
	int nrCol;

	// numarul maxim de pozitii in tabela
	int m;

	// Elementele si legaturile
	Triplet* e;
	int* urm;
	int primLiber;

	// Functia de dispersie (hash) si hash code
	// Theta(1)
	int d(Triplet e) const; // dispersie prin diviziune
	// Theta(1)
	int hashCode(Triplet e) const;

	// Functia de actualizare a primLiber
	// O(m)
	void actPrimLiber();

public:

	//constructor
	//se arunca exceptie daca nrLinii<=0 sau nrColoane<=0
	// Theta(m)
	Matrice(int nrLinii, int nrColoane);


	//destructor
	// Theta(1)
	~Matrice();

	//returnare element de pe o linie si o coloana
	//se arunca exceptie daca (i,j) nu e pozitie valida in Matrice
	//indicii se considera incepand de la 0
	// O(m)
	// SUH: Caz mediu Theta(1)
	TElem element(int i, int j) const;


	// returnare numar linii
	// Theta(1)
	int nrLinii() const;

	// returnare numar coloane
	// Theta(1)
	int nrColoane() const;


	// modificare element de pe o linie si o coloana si returnarea vechii valori
	// se arunca exceptie daca (i,j) nu e o pozitie valida in Matrice
	// O(m)
	// SUH: Caz mediu Theta(1)
	TElem modifica(int i, int j, TElem);

	// creaza un iterator bi-directional asupra tuturor elementelor matricei pe o anumita coloana (indiferent daca acestea sunt sau nu NULL_TELEM). 
	// arunca exceptie in cazul in care coloana nu este o coloana valida
	// CT Theta(1)
	IteratorMatrice iterator(int coloana) const;
};
