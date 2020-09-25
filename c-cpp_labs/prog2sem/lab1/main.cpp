#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string.h>


class String {
private:

	char* str;

	size_t size;

	String(size_t size) {
		this->size = size;
		str = new char[size + 1];
		str[0] = '\0';
	}

public:

	String() {
		size = 0;
		str = new char[size + 1];
		str[0] = '\0';
	}

	String(char symbol) {
		size = 1;
		str = new char[size + 1];
		str[0] = symbol;
	}

	String(size_t size, const char* str) {
		this->size = size;
		this->str = new char[size + 1];
		strcpy(this->str, str);
	}

	~String() {
		delete [] str;
	}

	String operator+(const String& other) {
		String* new_str = new String(this->size + other.size);
		strcat(strcat(new_str->str, this->str), other.str);
		return *new_str;
	}

	/*String operator=(const String& other) {
		delete this;
		return { other.size, other.str };
	}
	*/

	void printLine() const{
		std::cout << this->str;
	}

	void prinLineIntoFile(std::ofstream fout) const{
		fout << this->str;
	}

	void readLineFromFile(std::ifstream fin) {
		
	}

	size_t length() const{
		return this->size;
	}

};



int main() {
	char a[] = "aaaaa\0";

	String* str1 = new String(strlen(a), a);
	String* str2 = new String('s');
	String str3 = *str1 + *str2;


	str3.printLine();
	std::cout << "\n" << str3.length();
	return 0;
}