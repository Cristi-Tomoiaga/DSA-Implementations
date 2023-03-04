#include "Multime.h"
#include "IteratorMultime.h"

#include <iostream>

Nod::Nod(TElem element, Nod* urmator) {
	this->e = element;
	this->urm = urmator;
}

TElem Nod::element() {
	return e;
}

Nod* Nod::urmator() {
	return urm;
}

Multime::Multime() {
	prim = nullptr;
}


bool Multime::adauga(TElem elem) {
	bool succes = false;

	if (prim == nullptr) {
		// lista este vida
		Nod* p = new Nod(elem, nullptr);
		prim = p;
		succes = true;
	}
	else {
		// lista nevida - o parcurgem si daca nu gasim elem il adaugam la final
		Nod* q = prim;
		while (q->urm != nullptr && q->e != elem) {
			q = q->urm;
		}

		if (q->urm == nullptr && q->e != elem) {
			// nu exista elem in lista, deci il adaugam
			Nod* p = new Nod(elem, nullptr);
			q->urm = p;
			succes = true;
		}
	}

	return succes;
}


bool Multime::sterge(TElem elem) {
	bool succes = false;
	
	if (prim != nullptr) {
		// nu e vida lista

		if (prim->e == elem) {
			// este primul element din lista
			Nod* tmp = prim;
			prim = prim->urm;
			delete tmp;
			succes = true;
		}
		else {
			Nod* q = prim;
			while (q->urm != nullptr && q->urm->e != elem) {
				q = q->urm;
			}

			if (q->urm != nullptr) {
				// exista in lista
				Nod* tmp = q->urm;
				q->urm = tmp->urm;
				delete tmp;
				succes = true;
			}
		}
	}

	return succes;
}


bool Multime::cauta(TElem elem) const {
	Nod* p = prim;
	while (p != nullptr && p->e != elem) {
		p = p->urm;
	}

	return p != nullptr;
}


int Multime::dim() const {
	Nod* p = prim;
	int size = 0;
	while (p != nullptr) {
		size++;
		p = p->urm;
	}

	return size;
}

bool Multime::vida() const {
	return prim == nullptr;
}

int Multime::diferentaMaxMin() const {
	TElem dif = -1;

	if (!vida()) {
		// putem calcula max-min acum, initializam min si max cu 'primul' element din multime
		TElem min = prim->e;
		TElem max = prim->e;
		
		Nod* q = prim->urm;
		while (q != nullptr) {
			if (q->e > max)
				max = q->e;
			if (q->e < min)
				min = q->e;
			q = q->urm;
		}
		
		dif = max - min;
	}

	return dif; 
}


Multime::~Multime() {
	while (prim != nullptr) {
		Nod* tmp = prim;
		prim = prim->urm;
		delete tmp;
	}
}



IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
}