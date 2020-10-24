#include <iostream>
#ifndef CLASS_BLOCK_H
#define CLASS_BLOCK_H
using namespace std;
class block {
private:
	unsigned int unit;
	block* next, *prev;
public:
	block(unsigned int block_unit,  block* block_prev) {
		setUnit(block_unit);
		setPrev(block_prev);
		if(!this->isHead()) block_prev->setNext(this);
		setNext(NULL);
	}

	bool isHead() {
		if (this->prev == NULL) return true;
		else return false;
	}

	bool isLast() {
		if (this->next == NULL) return true;
		else return false;
	}

	void setUnit(unsigned int block_unit) {
		unit = block_unit;
	}

	void setNext(block* block_next) {
		next = block_next;
	}

	void setPrev(block* block_prev) {
		prev = block_prev;
	}
	
	block* getNext() {
		return next;
	}

	block* getPrev() {
		return prev;
	}

	unsigned int getUnit() {
		return unit;
	}
};
#endif