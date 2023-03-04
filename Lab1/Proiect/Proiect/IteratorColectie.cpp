#include "IteratorColectie.h"
#include "Colectie.h"
#include <exception>


IteratorColectie::IteratorColectie(const Colectie& c): col(c) {
	pos = 0;
}

void IteratorColectie::prim() {
	pos = 0;
}


void IteratorColectie::urmator() {
	if (!valid())
		throw std::exception();

	pos++;
}


bool IteratorColectie::valid() const {
	return pos < col.dim();
}



TElem IteratorColectie::element() const {
	if (!valid())
		throw std::exception();

	return col.d[col.p[pos]];
}
