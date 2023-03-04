#include "Matrice.h"

#include <exception>

using namespace std;

int Matrice::d(Triplet e) const {
	return hashCode(e) % m;
}

int Matrice::hashCode(Triplet e) const {
	return e.l * nrCol + e.c;
}

void Matrice::actPrimLiber(){
	primLiber++;

	while (primLiber < m && (e[primLiber].l != -1 || e[primLiber].c != -1)) {
		primLiber++;
	}
}

Matrice::Matrice(int nrLinii, int nrColoane) {
	if (nrLinii <= 0 || nrColoane <= 0) {
		throw exception();
	}

	this->nrLin = nrLinii;
	this->nrCol = nrColoane;
	this->m = MAX;
	this->e = new Triplet[this->m];
	this->urm = new int[this->m];


	// initializare tabela
	for (int i = 0; i < this->m; i++) {
		this->e[i].l = -1;
		this->e[i].c = -1;
		this->e[i].val = NULL_TELEMENT;
		this->urm[i] = -1;
	}
	this->primLiber = 0;
}

Matrice::~Matrice(){
	delete[] this->e;
	delete[] this->urm;
}

int Matrice::nrLinii() const{
	return this->nrLin;
}

int Matrice::nrColoane() const{
	return this->nrCol;
}

TElem Matrice::element(int i, int j) const{
	if (i < 0 || j < 0 || i >= this->nrLin || j >= this->nrCol) {
		throw exception();
	}

	int k = this->d(Triplet{ i, j, NULL_TELEMENT }); // valoarea de dispersie 

	while (k != -1 && (e[k].l != i || e[k].c != j)) {
		k = urm[k];
	}

	if (k == -1) {
		// nu am gasit elementul, deci este clar nul
		return NULL_TELEMENT;
	}
	
	return e[k].val;
}

TElem Matrice::modifica(int i, int j, TElem e) {
	if (i < 0 || j < 0 || i >= this->nrLin || j >= this->nrCol) {
		throw exception();
	}

	// cautam tripletul pt (i, j)
	Triplet t = Triplet{ i, j, e };
	int h = this->d(t); // valoarea de dispersie

	int k = h;
	while (k != -1 && (this->e[k].l != i || this->e[k].c != j)) {
		k = urm[k];
	}

	if (k == -1) {
		// nu l-am gasit, deci este nul
		if (e != NULL_TELEMENT) {
			// il vom adauga

			k = h;
			if (this->e[k].l == -1 && this->e[k].c == -1) {
				// il putem pune chiar la pozitia valorii de dispersie
				this->e[k] = t;
				if (k == primLiber)
					actPrimLiber();
			}
			else {
				// parcurgem inlantuirea pana la final
				int p = -1; // precedent
				while (k != -1) {
					p = k;
					k = urm[k];
				}

				this->e[primLiber] = t;
				this->urm[p] = primLiber;
				actPrimLiber();
			}
		}

		return NULL_TELEMENT;
	}

	// l-am gasit, va trebui sa il modificam
	TElem val = this->e[k].val;

	if (e != NULL_TELEMENT) {
		// doar modificam valoarea asociata cheii din triplet
		this->e[k].val = e;

		return val;
	}

	// e este nul, deci vom sterge tripletul actual
	int p = -1; // precedentul lui k
	bool done = false;

	// mutam cheile ca sa pastram consistenta tabelei
	while (!done) {
		int pos = urm[k];
		int ppos = k;

		while (pos != -1 && this->d(this->e[pos]) != k) {
			ppos = pos;
			pos = urm[pos];
		}

		if (pos == -1) {
			done = true;
		}
		else {
			this->e[k] = this->e[pos];
			k = pos;
			p = ppos;
		}
	}

	if (p == -1) {
		// cautam sa vedem daca exista un precedent pt k
		int pos = 0;
		while (pos < this->m && p == -1) {
			if (urm[pos] == k) {
				p = pos;
			}
			else
				pos++;
		}
	}

	// stergere in LSI
	if (p != -1) {
		urm[p] = urm[k];
	}
	this->e[k].l = -1;
	this->e[k].c = -1;
	this->e[k].val = NULL_TELEMENT;
	this->urm[k] = -1;

	// actualizare primLiber
	if (k < primLiber)
		primLiber = k;

	return val;
}

IteratorMatrice Matrice::iterator(int coloana) const {
	if (coloana < 0 || coloana >= nrCol) {
		throw exception();
	}

	return IteratorMatrice(*this, coloana);
}
