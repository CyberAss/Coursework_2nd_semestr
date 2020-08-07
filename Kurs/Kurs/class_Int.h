#include "class_block.h"
#include "class_sl.h"
#ifndef CLASS_INT_H
#define CLASS_INT_H
using namespace std;
class Integer{
private:
	unsigned int size; //Количество разрядов в числе
	block* begin, *end, *ptr; //Представление числа по разрядам - в begin младшие, в end старшие
public:
	Integer(block* int_begin, block* int_end) {
		begin = int_begin;
		end = int_end;
	}

	Integer(sl Int) {
		
	}

	void setBegin(block* int_begin) {
		begin = int_begin;
	}

	void setEnd(block* int_end) {
		end = int_end;
	}

	unsigned int getSize() {
		return size;
	}
};
#endif