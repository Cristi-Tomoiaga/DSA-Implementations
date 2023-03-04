#include "MD.h"
#include "IteratorMD.h"
#include <exception>
#include <iostream>
#include <map>

using namespace std;

void Nod::redim() {
	int cpNou = this->cp * 2;
	TValoare* eNou = new TValoare[cpNou];
	int* urmNou = new int[cpNou];

	// copiere elemente
	for (int i = 0; i < this->cp; i++) {
		eNou[i] = this->e[i];
		urmNou[i] = this->urm[i];
	}

	// reinitializare spatiu liber
	for (int i = this->cp; i < cpNou - 1; i++)
		urmNou[i] = i + 1;
	urmNou[cpNou - 1] = -1;
	this->primLiber = this->cp;

	delete[] this->e;
	delete[] this->urm;

	this->e = eNou;
	this->urm = urmNou;
	this->cp = cpNou;
}

void Nod::dealoca(int i) {
	this->urm[i] = this->primLiber;
	this->primLiber = i;
}

int Nod::aloca() {
	int i = this->primLiber;
	this->primLiber = this->urm[this->primLiber];
	return i;
}

int Nod::creeazaNod(TValoare v) {
	if (this->primLiber == -1) {
		// nu mai este spatiu liber, deci redimensionam
		this->redim();
	}

	int i = this->aloca();
	this->e[i] = v;
	this->urm[i] = -1;
	return i;
}

Nod::Nod() {
	this->c = -1;

	this->cp = CAPACITATE_INIT;
	this->e = new TValoare[this->cp];
	this->urm = new int[this->cp];
	this->prim = -1; // LSI vida

	// initializare spatiu liber
	for (int i = 0; i < this->cp - 1; i++)
		this->urm[i] = i + 1;
	this->urm[this->cp - 1] = -1;
	this->primLiber = 0;
}

Nod::Nod(TCheie c) {
	this->c = c;

	this->cp = CAPACITATE_INIT;
	this->e = new TValoare[this->cp];
	this->urm = new int[this->cp];
	this->prim = -1; // LSI vida

	// initializare spatiu liber
	for (int i = 0; i < this->cp - 1; i++)
		this->urm[i] = i + 1;
	this->urm[this->cp - 1] = -1;
	this->primLiber = 0;
}

Nod::Nod(const Nod& ot) {
	this->c = ot.c;

	this->cp = ot.cp;
	this->prim = ot.prim;
	this->primLiber = ot.primLiber;
	this->e = new TValoare[this->cp];
	this->urm = new int[this->cp];

	// copiere elemente
	for (int i = 0; i < this->cp; i++) {
		this->e[i] = ot.e[i];
		this->urm[i] = ot.urm[i];
	}
}

Nod& Nod::operator=(const Nod& ot) {
	if (this == &ot) {
		return *this; // guard against self copy
	}

	this->c = ot.c;

	this->cp = ot.cp;
	this->prim = ot.prim;
	this->primLiber = ot.primLiber;
	delete[] this->e;
	delete[] this->urm;
	this->e = new TValoare[this->cp];
	this->urm = new int[this->cp];

	// copiere elemente
	for (int i = 0; i < this->cp; i++) {
		this->e[i] = ot.e[i];
		this->urm[i] = ot.urm[i];
	}

	return *this;
}

Nod::~Nod() {
	delete[] this->e;
	delete[] this->urm;
}

TCheie Nod::cheie() const {
	return this->c;
}

vector<TValoare> Nod::valori() const {
	vector<TValoare> vec;
	int p = this->prim;

	while (p != -1) {
		vec.push_back(this->e[p]);
		p = this->urm[p];
	}

	return vec;
}

void Nod::adaugaInceput(TValoare v) {
	int i = this->creeazaNod(v);
	this->urm[i] = this->prim;
	this->prim = i;
}

bool Nod::sterge(TValoare v) {
	if (this->prim == -1)
		return false; // lista vida

	if (this->e[this->prim] == v) {
		int tmp = this->prim;
		this->prim = this->urm[this->prim];
		this->dealoca(tmp);
		return true;
	}
	else {
		int p = this->prim;
		while (this->urm[p] != -1 && this->e[this->urm[p]] != v)
			p = this->urm[p];

		if (this->urm[p] != -1) {
			int tmp = this->urm[p];
			this->urm[p] = this->urm[this->urm[p]];
			this->dealoca(tmp);
			return true;
		}
		else {
			return false;
		}
	}
}

bool Nod::vida() const {
	return this->prim == -1;
}



void MD::redim() {
	int cpNou = this->cp * 2;
	Nod* eNou = new Nod[cpNou];
	int* urmNou = new int[cpNou];

	// copiere elemente
	for (int i = 0; i < this->cp; i++) {
		eNou[i] = this->e[i];
		urmNou[i] = this->urm[i];
	}

	// reinitializare spatiu liber
	for (int i = this->cp; i < cpNou - 1; i++)
		urmNou[i] = i + 1;
	urmNou[cpNou - 1] = -1;
	this->primLiber = this->cp;

	delete[] this->e;
	delete[] this->urm;

	this->e = eNou;
	this->urm = urmNou;
	this->cp = cpNou;
}

void MD::dealoca(int i) {
	this->urm[i] = this->primLiber;
	this->primLiber = i;
}

int MD::aloca() {
	int i = this->primLiber;
	this->primLiber = this->urm[this->primLiber];
	return i;
}

int MD::creeazaNod(TCheie c) {
	if (this->primLiber == -1) {
		// nu mai este spatiu liber, deci redimensionam
		this->redim();
	}

	Nod nod{ c };
	int i = this->aloca();
	this->e[i] = nod;
	this->urm[i] = -1;
	return i;
}

MD::MD() {
	this->cp = CAPACITATE_INIT;
	this->e = new Nod[this->cp];
	this->urm = new int[this->cp];
	this->prim = -1; // LSI vida
	this->len = 0;

	// initializare spatiu liber
	for (int i = 0; i < this->cp - 1; i++)
		this->urm[i] = i + 1;
	this->urm[this->cp - 1] = -1;
	this->primLiber = 0;
}


void MD::adauga(TCheie c, TValoare v) {
	int p = this->prim;

	while (p != -1 && this->e[p].cheie() != c)
		p = this->urm[p];

	if (p == -1) {
		// cheia nu exista, o sa o adaugam
		int i = this->creeazaNod(c);
		this->urm[i] = this->prim;
		this->prim = i;
		p = i;
	}

	// adaugam valoarea la cheie
	this->e[p].adaugaInceput(v);
	this->len++;
}


bool MD::sterge(TCheie c, TValoare v) {
	int p = this->prim;
	if (p == -1)
		return false;

	if (this->e[p].cheie() == c) {
		// cheia este chiar prima
		bool res = this->e[p].sterge(v);

		if (res) {
			this->len--;

			if (this->e[p].vida()) {
				// cheia are lista de valori vida, deci o vom sterge
				this->prim = this->urm[this->prim];
				this->dealoca(p);
			}
		}

		return res;
	}

	while (this->urm[p] != -1 && this->e[this->urm[p]].cheie() != c)
		p = this->urm[p];

	if (this->urm[p] == -1)
		return false;

	bool res = this->e[this->urm[p]].sterge(v);
	if (res) {
		this->len--;

		if (this->e[this->urm[p]].vida()) {
			// cheia are lista de valori vida, deci o vom sterge
			int tmp = this->urm[p];
			this->urm[p] = this->urm[this->urm[p]];
			this->dealoca(tmp);
		}
	}

	return res;
}


vector<TValoare> MD::cauta(TCheie c) const {
	int p = this->prim;
	
	while (p != -1 && this->e[p].cheie() != c)
		p = this->urm[p];

	if (p == -1) {
		// nu am gasit cheia
		return vector<TValoare>();
	}

	return this->e[p].valori();
}


int MD::dim() const {
	return this->len;
}


bool MD::vid() const {
	return this->prim == -1;
}

TValoare MD::ceaMaiFrecventaValoare() const {
	if (this->vid())
		return NULL_TVALOARE;

	TValoare v = NULL_TVALOARE;
	int freq = 0;
	int pCheie = this->prim;
	map<TValoare, int> freqMap;
	
	while (pCheie != -1) {
		// iteram valorile asociate cheii
		int pVal = this->e[pCheie].prim;
		while (pVal != -1) {
			TValoare val = this->e[pCheie].e[pVal];

			if (freqMap.find(val) == freqMap.end()) {
				freqMap[val] = 0;
			}
			freqMap[val]++;

			pVal = this->e[pCheie].urm[pVal];
		}

		// trecem la urmatoarea cheie
		pCheie = this->urm[pCheie];
	}

	for(const auto& pair: freqMap)
		if (pair.second > freq) {
			freq = pair.second;
			v = pair.first;
		}

	return v;
}

IteratorMD MD::iterator() const {
	return IteratorMD(*this);
}


MD::~MD() {
	delete[] this->e;
	delete[] this->urm;
}