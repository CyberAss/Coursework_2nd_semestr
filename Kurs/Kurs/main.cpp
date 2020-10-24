#include <iostream>
#include <fstream>
#include "class_sl.h"
#include "class_block.h"
#include "class_Int.h"
using namespace std;

enum tests {Back = 0, Calculate, Check, Mul, Sum, Sub = 6, Div = 8};
char inputTerm(fstream& f) {
	char res;
	f >> res;
	return res;
}

int main() {
	setlocale(LC_ALL, "rus");
	bool flag = true;
	int test, term = 0, digit = 0, used = 0;
	fstream file, ask, quest;
	sl first, second, res;
	file.open("input.txt", ios_base::in);
	ask.open("ask.txt", ios_base::in);
	quest.open("tests.txt", ios_base::in);
	cout << "Здравствуйте!\n";
	while (true) {
		cout << "Что желаете сделать?\n 1 - Калькулятор\n 2 - Проверка знаний\n 0 - Выход\n";
		while (true) {
			cin >> test;
			if (test >= Calculate && test <= Check) break;
			if (test == Back) {
				flag = false;
				break;
			}
			else cout << "Введите корректный данные: ";
		}
		if (!flag) break;
		cout << "Введите количество знаков в одном блоке(максимально 5): ";
		while (true) {
			cin >> digit;
			if (digit > 0 && digit < 6) break;
		}
		system("cls");
		if (test == Calculate) {
			cout << "Использовать предыдущий результат?\n 1 - Да\n 2 - Нет\n";
			cin >> used;
			if (used == 2)
				first.input(file);
			Integer one(first, digit);
			term = inputTerm(file) - '\'';
			second.input(file);
			Integer two(second, digit);
			cout << one.getRaw();
			switch (term) {
			case Mul:
				cout << '*';
				one.Mul(&two);
				break;
			case Sum:
				cout << '+';
				one.Sum(&two);
				break;
			case Sub:
				cout << '-';
				one.Sub(&two);
				break;
			case Div:
				cout << '/';
				one.Div(&two);
				break;
			}
			cout << two.getRaw() << "=\n" << one.getRaw() << endl;
			first = one.getRaw();
		}
		else{
			res.input(ask);
			Integer Result(res, digit);
			first.input(quest);
			Integer one(first, digit);
			term = inputTerm(quest) - '\'';
			second.input(quest);
			Integer two(second, digit);
			switch (term) {
			case Mul:
				one.Mul(&two);
				if (!one.isEqual(&Result)) cout << "Повторите умножение\n";
				else cout << "Ошибки в умножении нет\n";
				break;
			case Sum:
				one.Sum(&two);
				if (!one.isEqual(&Result)) cout << "Повторите сложение\n";
				else cout << "Ошибки в сложении нет\n";
				break;
			case Sub:
				one.Sub(&two);
				if (!one.isEqual(&Result)) cout << "Повторите вычитание\n";
				else cout << "Ошибки в вычитании нет\n";
				break;
			case Div:
				one.Div(&two);
				if (!one.isEqual(&Result)) cout << "Повторите деление\n";
				else cout << "Ошибки в делении нет\n";
				break;
			}
		}
	}
	file.close();
	ask.close();
	quest.close();
	return 0;
}