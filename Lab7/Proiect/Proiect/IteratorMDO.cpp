#include "IteratorMDO.h"
#include "MDO.h"

IteratorMDO::IteratorMDO(const MDO& d) : dict(d){
	this->s = stack<Nod*>();
	this->curent = dict.rad;
	
	while (this->curent != nullptr) {
		s.push(this->curent);
		this->curent = this->curent->stanga();
	}

	if (!s.empty()) {
		this->curent = s.top();
	}
}

void IteratorMDO::prim(){
	this->s = stack<Nod*>();
	this->curent = dict.rad;

	while (this->curent != nullptr) {
		s.push(this->curent);
		this->curent = this->curent->stanga();
	}

	if (!s.empty()) {
		this->curent = s.top();
	}
}

void IteratorMDO::urmator(){
	if (!valid()) {
		throw exception();
	}

	s.pop();
	if (this->curent->dreapta() != nullptr) {
		this->curent = this->curent->dreapta();

		while (this->curent != nullptr) {
			s.push(this->curent);
			this->curent = this->curent->stanga();
		}
	}

	if (!s.empty()) {
		this->curent = s.top();
	}
	else {
		this->curent = nullptr;
	}
}

bool IteratorMDO::valid() const{
	return this->curent != nullptr;
}

TElem IteratorMDO::element() const{
	if (!valid()) {
		throw exception();
	}

	return this->curent->element();
}


