#include <assert.h>
#include "Matrice.h"
#include "TestExtins.h"
#include <iostream>
#include <exception>
#include "Iterator.h"

using namespace std;

void testIteratorColoana() {
	Matrice m(3, 3);

	// testam aruncarea de exceptii pentru coloane invalide
	try {
		IteratorMatrice it = m.iterator(-1);
		assert(false);
	}
	catch (const exception&) {
		assert(true);
	}

	try {
		IteratorMatrice it = m.iterator(4);
		assert(false);
	}
	catch (const exception&) {
		assert(true);
	}

	// adaugam elemente in matrice
	m.modifica(0, 0, 2); // coloana 0
	assert(m.element(0, 0) == 2);
	assert(m.element(1, 0) == NULL_TELEMENT);
	assert(m.element(2, 0) == NULL_TELEMENT);

	m.modifica(0, 1, 1); // coloana 1
	m.modifica(1, 1, 2);
	m.modifica(2, 1, 4);
	assert(m.element(0, 1) == 1);
	assert(m.element(1, 1) == 2);
	assert(m.element(2, 1) == 4);

	m.modifica(1, 2, 10); // coloana 2
	assert(m.element(0, 2) == NULL_TELEMENT);
	assert(m.element(1, 2) == 10);
	assert(m.element(2, 2) == NULL_TELEMENT);

	// iteram intr-o directie coloana 0
	IteratorMatrice it1 = m.iterator(0);
	assert(it1.valid());
	assert(it1.element() == 2);
	it1.urmator();
	assert(it1.valid());
	assert(it1.element() == NULL_TELEMENT);
	it1.urmator();
	assert(it1.valid());
	assert(it1.element() == NULL_TELEMENT);
	it1.urmator();
	assert(!it1.valid());

	// iteratorul este invalid
	try {
		it1.urmator();
		assert(false);
	}
	catch (const exception&) {
		assert(true);
	}

	try {
		it1.precedent();
		assert(false);
	}
	catch (const exception&) {
		assert(true);
	}

	// iteram coloana 1 in directie inversa
	IteratorMatrice it2 = m.iterator(1);
	it2.ultim();
	assert(it2.valid());
	assert(it2.element() == 4);
	it2.precedent();
	assert(it2.valid());
	assert(it2.element() == 2);
	it2.precedent();
	assert(it2.valid());
	assert(it2.element() == 1);
	it2.precedent();
	assert(!it2.valid());

	// iteratorul este invalid
	try {
		it2.urmator();
		assert(false);
	}
	catch (const exception&) {
		assert(true);
	}

	try {
		it2.precedent();
		assert(false);
	}
	catch (const exception&) {
		assert(true);
	}

	// iteram coloana 2 in ambele directii
	IteratorMatrice it3 = m.iterator(2);
	assert(it3.valid());
	assert(it3.element() == NULL_TELEMENT);
	it3.urmator();
	assert(it3.valid());
	assert(it3.element() == 10);
	it3.urmator();
	assert(it3.valid());
	assert(it3.element() == NULL_TELEMENT);
	it3.precedent();
	assert(it3.valid());
	assert(it3.element() == 10);
	it3.precedent();
	assert(it3.valid());
	assert(it3.element() == NULL_TELEMENT);

	// verificare extremitati
	it3.ultim();
	assert(it3.valid());
	assert(it3.element() == NULL_TELEMENT);

	it3.prim();
	assert(it3.valid());
	assert(it3.element() == NULL_TELEMENT);
}

void testCreeaza() {
	Matrice m(10,10);
	assert(m.nrLinii() == 10);
	assert(m.nrColoane() == 10);
	for(int i=0; i<m.nrLinii(); i++)
	  for(int j=0; j<m.nrColoane(); j++)
		assert(m.element(i,j) == NULL_TELEMENT);
}

void testAdauga() {
	Matrice m(10,10);
	for(int j=0; j<m.nrColoane(); j++)
		m.modifica(4,j,3);
	for(int i=0; i<m.nrLinii(); i++)
           for(int j=0; j<m.nrColoane(); j++)
		if (i==4)
		  assert(m.element(i,j) == 3);
		else
		  assert(m.element(i,j) == NULL_TELEMENT);
}

void testQuantity() {//scopul e sa adaugam multe date
	Matrice m(300,300);
	for(int i=m.nrLinii()/2; i<m.nrLinii(); i++){
           for(int j=0; j<m.nrColoane()/2; j++)
	   {	
		int v1=j;
		int v2=m.nrColoane()-v1-1;
		if (i%2==0 && v1%2==0)
		     m.modifica(i, v1, i*v1);
		else
	            if (v1%3==0)
			m.modifica(i, v1, i+v1);
		if (i%2==0 && v2%2==0)
		     m.modifica(i, v2, i*v2);
		else
	            if (v2%3==0)
			m.modifica(i, v2, i+v2);
	   }
	}
	for(int i=0; i<=m.nrLinii()/2; i++){
           for(int j=0; j<m.nrColoane()/2; j++)
	   {	
		int v1=j;
		int v2=m.nrColoane()-v1-1;
		if (i%2==0 && v1%2==0)
		     m.modifica(i, v1, i*v1);
		else
	            if (v1%3==0)
			m.modifica(i, v1, i+v1);
		if (i%2==0 && v2%2==0)
		     m.modifica(i, v2, i*v2);
		else
	            if (v2%3==0)
			m.modifica(i, v2, i+v2);
	   }
	}		
	for(int i=0; i<m.nrLinii(); i++)
           for(int j=0; j<m.nrColoane(); j++)
		if (i%2==0 && j%2==0)
		     assert(m.element(i,j) == i*j);
		else
	            if (j%3==0)
			 assert(m.element(i,j) == i+j);
				else assert(m.element(i,j) == 0);
}

void testExceptii() {
	Matrice m(10,10);
	try {
		m.element(-1,-1);
	}
	catch (exception&) {
		assert(true); //ar trebui sa arunce exceptie
	}
    try {
		m.modifica(12,0,1);
	}
	catch (exception&) {
		assert(true); //ar trebui sa arunce exceptie
	}
	try {
		assert(m.nrLinii());
	}
	catch (exception&) {
		assert(false); //nu ar trebui sa arunce exceptie
	}
}



void testAllExtins() {
	testCreeaza();
	testAdauga();
	testQuantity();
	testExceptii();
	testIteratorColoana();
}
