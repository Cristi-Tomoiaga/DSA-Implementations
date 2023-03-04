#include "Colectie.h"
#include "IteratorColectie.h"
#include <exception>
#include <iostream>

using namespace std;

void Colectie::redimD() {
	TElem* newD = new TElem[2 * cpD];

	for (int i = 0; i < nD; i++)
		newD[i] = d[i];
	cpD = 2 * cpD;
	delete[] d;
	d = newD;
}

void Colectie::redimP() {
	int* newP = new int[2 * cpP];

	for (int i = 0; i < nP; i++)
		newP[i] = p[i];
	cpP = 2 * cpP;
	delete[] p;
	p = newP;
}

Colectie::Colectie() {
	cpD = CP_INIT;
	cpP = CP_INIT;
	nD = 0;
	nP = 0;
	d = new TElem[cpD];
	p = new int[cpP];
}


void Colectie::adauga(TElem elem) {
	int pos = 0;
	while (pos < nD && d[pos] != elem)
		pos++;

	if (pos < nD) {
		// elem exista deja in D
		if (nP == cpP)
			redimP();
		p[nP++] = pos;
	}
	else {
		// elem nu exista in D
		if (nD == cpD)
			redimD();
		d[nD++] = elem;

		if (nP == cpP)
			redimP();
		p[nP++] = nD - 1;
	}
}


bool Colectie::sterge(TElem elem) {
	bool sters = false;
	int pos = 0;
	while (pos < nD && d[pos] != elem)
		pos++;

	if (pos < nD) {
		// elem exista in D
		int firstPos = -1;
		int freqPos = 0;
		for(int i = 0; i < nP; i++)
			if (p[i] == pos) {
				freqPos++;
				if (firstPos < 0)
					firstPos = i;
			}

		// stergem din P prima aparitie a lui pos
		for (int i = firstPos; i < nP - 1; i++)
			p[i] = p[i + 1];
		nP--;
		freqPos--;
		sters = true;

		// daca freqPos este 0 inseamna ca nu mai avem in colectie elemente egale cu elem
		// stergem elem din D
		if (freqPos == 0) {
			for (int i = pos; i < nD - 1; i++)
				d[i] = d[i + 1];
			nD--;

			// actualizam pozitiile din P
			for (int i = 0; i < nP; i++)
				if (p[i] > pos)
					p[i]--;
		}
	}
	
	return sters;
}


bool Colectie::cauta(TElem elem) const {
	int pos = 0;
	while (pos < nD && d[pos] != elem)
		pos++;

	return pos < nD;
}

int Colectie::nrAparitii(TElem elem) const {
	int nr = 0;
	int pos = 0;
	while (pos < nD && d[pos] != elem)
		pos++;

	if (pos < nD) {
		// elem apare in D deci are numar nenul de aparitii
		for (int i = 0; i < nP; i++)
			if (p[i] == pos)
				nr++;
	}

	return nr;
}


int Colectie::dim() const {
	return nP;
}


bool Colectie::vida() const {
	return dim() == 0;
}

IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}


Colectie::~Colectie() {
	delete[] d;
	delete[] p;
}