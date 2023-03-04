#include "IteratorMD.h"
#include "MD.h"

using namespace std;

IteratorMD::IteratorMD(const MD& _md): md(_md) {
	this->posC = this->md.prim;

	if (this->posC != -1)
		this->posV = this->md.e[this->posC].prim;
	else
		this->posV = -1;
}

TElem IteratorMD::element() const{
	if (!valid())
		throw std::exception();

	TCheie c = this->md.e[this->posC].cheie();
	TValoare v = this->md.e[this->posC].e[this->posV];

	return std::make_pair(c, v);
}

bool IteratorMD::valid() const {
	return this->posC != -1;
}

void IteratorMD::urmator() {
	if (!valid())
		throw std::exception();

	this->posV = this->md.e[this->posC].urm[this->posV];

	if (this->posV == -1) {
		this->posC = this->md.urm[this->posC];

		if (this->posC != -1)
			this->posV = this->md.e[this->posC].prim;
	}
}

void IteratorMD::prim() {
	this->posC = this->md.prim;

	if (this->posC != -1)
		this->posV = this->md.e[this->posC].prim;
	else
		this->posV = -1;
}

