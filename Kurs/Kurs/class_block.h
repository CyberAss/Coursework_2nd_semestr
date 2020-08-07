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
		block_prev->setNext(this);
		setNext(NULL);
	}

	bool isEmpty(block* cur) {
		if (cur == NULL) return true;
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
	
};
#endif