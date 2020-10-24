#include <fstream>
#ifndef CLASS_SL_H
#define CLASS_SL_H
using namespace std;
class sl {
private:
	char p[1024];
	unsigned int l;
public:
	sl() {
		l = 0;
	}

	sl(const char arr[1024]) {
		l = 0;
		while (l < 1024 && arr[l] != '\0') {
				p[l] = arr[l];
				l++;
		}
	}
	
	sl& operator= (const char arr[1024]) {
		l = 0;
		while (l < 1024 && arr[l] != '\0')
			p[l] = arr[l++];
		return *this;
	}

	int getSize() {
		return l;
	}

	const char* getRaw(){
		char* temp = (char*)calloc(l,l * sizeof(char));
		for (int i = 0; i < l; i++)
			*(temp + i) = p[i];
		return temp;
	}

	void input(fstream& f) {
		l = 0;
		char s = ' ';
		f >> noskipws;
		while (!f.eof()) {
			f >> s;
			if (s != '\n' && !f.eof() && s - '0' >= 0 && s - '0' <= 9) {
				p[l] = s;
				l++;
			}
			else break;
		}
	}

	void output(fstream& out) {
		int i = 0;
		while (i < l) {
			out << p[i];
			i++;
		}
	}
};
#endif