#include "IteratorMDO.h"
#include "MDO.h"
#include <iostream>
#include <vector>

#include <exception>
using namespace std;

Nod* MDO::adaugaRec(Nod* p, TElem e){
	if (p == nullptr) {
		Nod* nou = new Nod(e, nullptr, nullptr);
		this->n++;

		return nou;
	}
	else if (r(e.first, p->e.first)) {
		p->st = adaugaRec(p->st, e);
	}
	else {
		p->dr = adaugaRec(p->dr, e);
	}

	return p;
}

TElem MDO::minim(Nod* p) {
	while (p->st != nullptr) {
		p = p->st;
	}

	return p->e;
}

Nod* MDO::stergeRec(Nod* p, TElem e){
	if (p == nullptr) {
		return nullptr;
	}
	else if (r(e.first, p->e.first) && !(r(e.first, p->e.first) && r(p->e.first, e.first) && e.second == p->e.second)) {
		// e.cheie <= p.e.cheie si e != p.e
		p->st = stergeRec(p->st, e);
		return p;
	}
	else if (!r(e.first, p->e.first)) {
		// e.cheie > p.e.cheie
		p->dr = stergeRec(p->dr, e);
		return p;
	}
	else {
		// am gasit elementul

		if (p->st != nullptr && p->dr != nullptr) {
			TElem eMin = minim(p->dr);

			p->e = eMin;
			p->dr = stergeRec(p->dr, eMin);
			return p;
		}
		else {
			Nod* repl;
			if (p->st == nullptr) {
				repl = p->dr;
			}
			else {
				repl = p->st;
			}

			delete(p);
			this->n--;
			return repl;
		}
	}
}

void MDO::distrugeRec(Nod* p){
	if (p != nullptr) {
		distrugeRec(p->st);
		distrugeRec(p->dr);
		
		delete p;
	}
}

MDO::MDO(Relatie r) {
	this->r = r;

	this->rad = nullptr;
	this->n = 0;
}

void MDO::adauga(TCheie c, TValoare v) {
	TElem e{ c, v };

	this->rad = adaugaRec(this->rad, e);
}

vector<TValoare> MDO::cauta(TCheie c) const {
	vector<TValoare> vals;

	Nod* p = this->rad;
	while (p != nullptr) {
		if (r(c, p->e.first)) {
			// verificam daca cheia este egala cu cea cautata
			if (r(c, p->e.first) && r(p->e.first, c)) { // aRb && bRa => a=b (antisimetria)
				vals.push_back(p->e.second);
			}

			p = p->st;
		}
		else {
			p = p->dr;
		}
	}

	return vals;
}

bool MDO::sterge(TCheie c, TValoare v) {
	TElem e{ c, v };

	int oldN = this->n;
	this->rad =  stergeRec(this->rad, e);

	if (oldN != this->n) {
		return true;
	}

	return false;
}

int MDO::dim() const {
	return this->n;
}

bool MDO::vid() const {
	return this->rad == nullptr;
}

vector<TValoare> MDO::colectiaValorilor() const
{
	vector<TValoare> vals;

	// parcurgem arborele (in preordine iterativ) pentru a determina toate valorile
	stack<Nod*> s;
	if (this->rad != nullptr) {
		s.push(this->rad);
	}

	while (!s.empty()) {
		Nod* p = s.top();
		s.pop();
		vals.push_back(p->e.second);

		if (p->dr != nullptr) {
			s.push(p->dr);
		}

		if (p->st != nullptr) {
			s.push(p->st);
		}
	}

	return vals;
}

IteratorMDO MDO::iterator() const {
	return IteratorMDO(*this);
}

MDO::~MDO() {
	distrugeRec(this->rad);
}
