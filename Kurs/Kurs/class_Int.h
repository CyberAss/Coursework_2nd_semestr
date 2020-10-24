#include "class_block.h"
#include "class_sl.h"
#include <algorithm>
#ifndef CLASS_INT_H
#define CLASS_INT_H
using namespace std;
class Integer{
private:
	unsigned int size; //Количество разрядов в числе
	unsigned int digit;//Количество цифр в разряде (Основание)
	block* begin, *end, *ptr; //Представление числа по разрядам - в begin младшие, в end старшие
public:
	Integer(block* int_begin, unsigned int int_digit) {
		size = 1;
		digit = int_digit;
		begin = int_begin;
		ptr = begin;
		while (!int_begin->isLast()) {
			int_begin = int_begin->getNext();
			size++;
		}
		end = int_begin;
	}

	Integer(sl Int, unsigned int int_digit) {
		int unit = 0, i = Int.getSize();
		digit = int_digit;
		char* temp = (char*)calloc(digit, digit * sizeof(char));
		while (i > 0) {
			for (unit = 0; unit < digit; unit++) {
				if (Int.getRaw()[i - digit + unit] - '0' < 0 || Int.getRaw()[i - digit + unit] - '0' > 9) temp[unit] = '0';
				else temp[unit] = Int.getRaw()[i - digit + unit];
			}
			unit = atoi(temp);
			if (i == Int.getSize()) {//Создание первого элемента
				block* cur = new block(unit, NULL);
				ptr = cur;
				begin = cur;
				end = cur;
			}
			else {
				block* cur = new block(unit, ptr);
				ptr = cur; //Создание промежуточных элементов
				if (i <= digit) end = cur;//Создание последних элементов
			}
			i -= digit;
			size++;
		}
	}

	const char* getRaw() {
		int junk = pow(10, digit - 1);
		int total = size * digit, i = 0;
		ptr = end;
		while (ptr->getUnit() < junk) {
			junk /= 10;
			total--;
		}
		if (total == 1) total = 2;
		char* temp = (char*)calloc(total, total * sizeof(char));
		ptr = begin;
		while(total > 0){
			if (ptr == end) 
				for (i = 0; i < total; i++)
					temp[i] = fmod(ptr->getUnit() / pow(10, total - i - 1), 10) + '0';
			else
				for (i = 0; i < digit; i++)
					temp[total - digit + i] = fmod(ptr->getUnit() / pow(10, digit - i - 1), 10) + '0'; //Заполняем строку, беря по цифре из каждого юнита
			total -= digit;
			if (ptr != end)ptr = ptr->getNext();
			else break;
		}
		return temp;
	}

	void setBegin(block* int_begin) {
		begin = int_begin;
	}

	void setEnd(block* int_end) {
		end = int_end;
	}

	void setSize(unsigned int int_size) {
		size = int_size;
	}

	void incSize() {
		size++;
	}

	unsigned int getSize() {
		return size;
	}

	block* getBegin() {
		return begin;
	}

	block* getEnd() {
		return end;
	}

	unsigned int getDigit() {
		return digit;
	}

	void Sum(Integer* second) {
		int junk = pow(10, digit);
		ptr = begin;
		block* second_ptr = second->getBegin();
		for (int i = size; i < second->getSize(); i++) {
			block* cur = new block(0, end);
			end = cur;
			size++;
		}
		while (true) {
			ptr->setUnit(ptr->getUnit() + second_ptr->getUnit());
			if (ptr->getUnit() >= junk) {
				if (ptr->isLast()) {
					block* cur = new block(0, ptr);
					end = cur;
					size++;
				}
				ptr->getNext()->setUnit(ptr->getNext()->getUnit() + ptr->getUnit() / junk);
				ptr->setUnit(fmod(ptr->getUnit(), junk));
			}
			if (second_ptr->isLast()) break;
			ptr = ptr->getNext();
			second_ptr = second_ptr->getNext();
		}
		ptr = begin;
		while (true) {
			if (ptr->getUnit() >= junk) {
				if (ptr->isLast()) {
					block* cur = new block(0, ptr);
					end = cur;
					size++;
				}
				ptr->getNext()->setUnit(ptr->getNext()->getUnit() + ptr->getUnit() / junk);
				ptr->setUnit(fmod(ptr->getUnit(), junk));
			}
			if (ptr->isLast()) break;
			ptr = ptr->getNext();
		}
	}

	void Sub(Integer* second) {
		int junk = pow(10, digit);
		ptr = begin;
		block* second_ptr = second->getBegin();
		while (true) {
			if (ptr->getUnit() < second_ptr->getUnit())
			{
				block* temp = ptr->getNext();
				while (temp->getUnit() == 0)
					temp = temp->getNext();
				while (temp != ptr) {
					temp->setUnit(temp->getUnit() - 1);
					temp->getPrev()->setUnit(temp->getPrev()->getUnit() + junk);
					temp = temp->getPrev();
				}
			}
			ptr->setUnit(ptr->getUnit() - second_ptr->getUnit());
			if (second_ptr->isLast()) break;
			ptr = ptr->getNext();
			second_ptr = second_ptr->getNext();
		}
		ptr = end;
		while (!ptr->isHead() && ptr->getUnit() == 0) {
			ptr = ptr->getPrev();
			end = ptr;
			size--;
		}
	}

	void Mul(Integer* second) {
		sl temp("0");
		Integer res(temp, digit);
		int junk = pow(10, digit);
		ptr = begin;
		block* res_ptr = res.getBegin();
		block* second_ptr = second->getBegin();
		block* back_ptr = res_ptr; //Указатель на разряд, в котором начинается умножение в столбик
		while (true) {
			res_ptr = back_ptr;
			ptr = begin;
			while (true) {
				res_ptr->setUnit(res_ptr->getUnit() + ptr->getUnit() * second_ptr->getUnit());
				if (res_ptr->getUnit() >= junk) {
					if (res_ptr->isLast()) {
						block* cur = new block(0, res_ptr);
						res.setEnd(cur);
						res.incSize();
					}
					res_ptr->getNext()->setUnit(res_ptr->getNext()->getUnit() + res_ptr->getUnit() / junk);
					res_ptr->setUnit(fmod(res_ptr->getUnit(), junk));
				}
				if (ptr->isLast()) break;
				ptr = ptr->getNext();
				if (res_ptr->isLast()) {
					block* cur = new block(0, res_ptr);
					res.setEnd(cur);
					res.incSize();
				}
				res_ptr = res_ptr->getNext();
			}
			back_ptr = back_ptr->getNext();
			if(second_ptr->isLast()) break;
			second_ptr = second_ptr->getNext();
		}
		size = res.getSize();
		digit = res.getDigit();
		begin = res.getBegin();
		ptr = begin;
		end = res.getEnd();
	}
	
	void Div(Integer* second) {
		sl temp("0");
		Integer res(temp, digit);
		temp = "1";
		Integer one(temp, digit);
		ptr = end;
		block* second_ptr = second->getEnd();
		bool flag = false;
		while (!flag) {
			ptr = end;
			second_ptr = second->getEnd();
			Sub(second);
			res.Sum(&one);
			if (size < second->getSize()) flag = true;
			if (size == second->getSize()) {
				while (!flag) {
					if (ptr->getUnit() < second_ptr->getUnit()) {
						flag = true;
						break;
					}
					else {
						if (ptr->getUnit() > second_ptr->getUnit()) break;
					}
					if (ptr->isHead()) break;
					ptr = ptr->getPrev();
					second_ptr = second_ptr->getPrev();
				}
			}
		}
		size = res.getSize();
		digit = res.getDigit();
		begin = res.getBegin();
		ptr = begin;
		end = res.getEnd();
	}

	bool isEqual(Integer* second) {
		if (size != second->getSize()) return false;
		block* second_ptr = second->getBegin();
		ptr = begin;
		while (!ptr->isLast()) {
			if (ptr->getUnit() != second_ptr->getUnit()) {
				return false;
				break;
			}
			ptr = ptr->getNext();
			second_ptr = second_ptr->getNext();
		}
		return true;
	}
};
#endif