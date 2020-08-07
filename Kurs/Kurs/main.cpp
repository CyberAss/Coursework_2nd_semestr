#include <iostream>
#include "class_sl.h"
using namespace std;

int main() {
	setlocale(LC_ALL, "rus");
	sl strl("123");
	sl cur = "govno";
	cout << cur.getSize() << endl;
	cout << cur.getRaw() << endl;
	cout << strl.getSize() << endl;
	cout << strl.getRaw();
	return 0;
}