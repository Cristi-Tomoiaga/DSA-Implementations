#include "Iterator.h"
#include "Matrice.h"
#include <exception>

IteratorMatrice::IteratorMatrice(const Matrice& m, int coloana) : m(m) {
	this->col = coloana;
	this->lin = 0;
}

TElem IteratorMatrice::element() const {
	if (!valid()) {
		throw std::exception();
	}

	return m.element(lin, col);
}

bool IteratorMatrice::valid() const {
	return lin >= 0 && lin < m.nrLinii();
}

void IteratorMatrice::urmator() {
	if (!valid()) {
		throw std::exception();
	}

	lin++;
}

void IteratorMatrice::precedent() {
	if (!valid()) {
		throw std::exception();
	}

	lin--;
}

void IteratorMatrice::prim() {
	this->lin = 0;
}

void IteratorMatrice::ultim() {
	this->lin = m.nrLinii() - 1;
}

