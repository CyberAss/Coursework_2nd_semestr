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
	cout << "������������!\n";
	while (true) {
		cout << "��� ������� �������?\n 1 - �����������\n 2 - �������� ������\n 0 - �����\n";
		while (true) {
			cin >> test;
			if (test >= Calculate && test <= Check) break;
			if (test == Back) {
				flag = false;
				break;
			}
			else cout << "������� ���������� ������: ";
		}
		if (!flag) break;
		cout << "������� ���������� ������ � ����� �����(����������� 5): ";
		while (true) {
			cin >> digit;
			if (digit > 0 && digit < 6) break;
		}
		system("cls");
		if (test == Calculate) {
			cout << "������������ ���������� ���������?\n 1 - ��\n 2 - ���\n";
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
				if (!one.isEqual(&Result)) cout << "��������� ���������\n";
				else cout << "������ � ��������� ���\n";
				break;
			case Sum:
				one.Sum(&two);
				if (!one.isEqual(&Result)) cout << "��������� ��������\n";
				else cout << "������ � �������� ���\n";
				break;
			case Sub:
				one.Sub(&two);
				if (!one.isEqual(&Result)) cout << "��������� ���������\n";
				else cout << "������ � ��������� ���\n";
				break;
			case Div:
				one.Div(&two);
				if (!one.isEqual(&Result)) cout << "��������� �������\n";
				else cout << "������ � ������� ���\n";
				break;
			}
		}
	}
	file.close();
	ask.close();
	quest.close();
	return 0;
}