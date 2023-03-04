#include "IteratorMultime.h"
#include "Multime.h"

#include <exception>


IteratorMultime::IteratorMultime(const Multime& m) : multime(m){
	curent = multime.prim;
}


void IteratorMultime::prim() {
	curent = multime.prim;
}


void IteratorMultime::urmator() {
	if (!valid())
		throw std::exception();

	curent = curent->urmator();
}


TElem IteratorMultime::element() const {
	if (!valid())
		throw std::exception();

	return curent->element();
}

bool IteratorMultime::valid() const {
	return curent != nullptr;
}
