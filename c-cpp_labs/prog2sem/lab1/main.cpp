#include <iostream>
#include <fstream>
#include <istream>
#include <cstring>
#define BUFFER_SIZE 16

char* copyStr(char* dest, unsigned int orig_size, const char* orig);
char* concatString(char* dest, unsigned int from, unsigned int orig_size, const char* orig);
long firstIndexOf(char* str, unsigned int str_size, char* sub_str, unsigned int sub_str_size);


//TODO: Deal with utf-8 strings.
class String {
private:

    unsigned int size;

    unsigned int length;

    char* str;

    String(unsigned int size, const char* str)
            :  size(size), length(size), str(new char[size]) {
        //TODO: utf-8 option
        copyStr(this->str, size, str);
    }


public:
    /* Constructors */
    explicit String()
            : size(0), length(0), str(nullptr) {}

    String(char symbol)
            : size(1), length(1), str(new char[size]) {
            //TODO: utf-8 option

        str[0] = symbol;

    }


    explicit String(const char* str)
            :  size(strlen(str)), length(strlen(str)), str(new char[strlen(str)]) {
            //TODO: utf-8 option

        copyStr(this->str, length, str);

    }


    String(const String& other)
            : size(other.size), length(other.length), str(new char[other.size]) {
          //TODO: utf-8 option

        copyStr(this->str, other.size, other.str);

    }


    ~String() {
        delete[] str;
    }


    /* Operators */

    String& operator= (const String& other) {

        if (this != &other) {
            char* tmp = new char [other.size];

            copyStr(tmp, other.size, other.str);

            delete [] this->str;

            this->str = tmp;
            this->size = other.size;
            this->length = other.length;
        }

        return *this;
    }


    String operator+ (const String& other) {

        String result_str;

        result_str.str = new char[this->size + other.size];
        result_str.size = this->size + other.size;
        result_str.length = this->length + other.length;

        copyStr(result_str.str, this->size, this->str);
        concatString(result_str.str, this->size, other.size, other.str);


        return {result_str.size, result_str.str};
    }

    String& operator+= (const String& string) {

        char* tmp = new char[this->size + string.size];

        copyStr(tmp, this->size, this->str);
        concatString(tmp, this->size, string.size, string.str);

        delete [] this->str;

        this->str = tmp;
        this->size += + string.size;
        this->length += string.length;

        return *this;
    }

    friend std::ostream& operator<< (std::ostream& output, String& string) {

        for (int i = 0; i < string.length; ++i){
            output << string[i];
        }

        return output;
    }

    String operator* (unsigned int repeats) {
        String string = *this;
        for (unsigned int i = 1; i < repeats; ++i) {
            string += string;
        }

        return {this->size * repeats, string.str};
    }


    friend std::istream& operator>> (std::istream& input, String& string) {

        char c;
        unsigned int index = 0;
        unsigned int line_length = 0;
        unsigned int allocated_size = BUFFER_SIZE;
        char* line = new char[BUFFER_SIZE];

        c = input.get();
        while (!input.eof() && (c != '\n' && c != '\r')) {

            if (line_length >= allocated_size) {

                char* new_line = new char[allocated_size + BUFFER_SIZE];
                for (unsigned int i = 0; i < line_length; ++i) {
                    new_line[i] = line[i];
                }

                delete[] line;
                allocated_size += BUFFER_SIZE;
                line = new_line;
                new_line = nullptr;
                line[index++] = c;
                ++line_length;
            } else {

                line[index++] = c;
                ++line_length;
            }
            c = input.get();
        }

        string.length = line_length;
        string.size = line_length;
        delete [] string.str;
        string.str = new char[line_length];
        copyStr(string.str, line_length, line);


        delete [] line;

        return input;
    }


    String operator() (unsigned int first, unsigned int last) {

        if (first < 0 || first > this->length || last < first || last > this->length) {
            std::cout << "Function operator() :: Error: wrong arguments." << std::endl;
            std::cerr << "Function operator() :: Error: wrong arguments.";
            exit(2);
        }
        if (last == first && last != this->length - 1) {
            return {this->operator[](first)};
        }

        char* new_line = new char[last - first + 1];
        for (unsigned int i = first; i < last + 1; ++i) {
            new_line[i - first] = str[i];
        }

        return {last - first + 1, new_line};
    }


    char operator[](unsigned int index){

        if (index > this->length) {
            std::cout << "Function operator() :: Error: wrong arguments." << std::endl;
            std::cerr << "Function operator() :: Error: wrong arguments.";
            exit(2);
        }

        return this->str[index];
    }

    String operator-(String& substr) {
        unsigned int first_index = firstIndexOf(this->str, this->size, substr.str, substr.size);
        String result = *this;
        while (first_index != -1) {
            if (result.length - first_index == substr.length) {
                result = result(0, first_index - 1);
                return {result.size, result.str};
            }
            result = result(0, first_index - 1) + result(first_index + substr.length, result.length - 1);
            first_index = firstIndexOf(result.str, result.size, substr.str, substr.size);
        }

        return {result.size, result.str};
    }


    /* Getters */
    unsigned int getLength() const {
        return this->length;
    }

};


char* copyStr(char* dest, unsigned int orig_size, const char* orig) {
    for (unsigned int i = 0; i < orig_size; ++i) {
        dest[i] = orig[i];
    }

    return dest;
}

char* concatString(char* dest, unsigned int from, unsigned int orig_size, const char* orig) {
    for (unsigned int i = from; i < from + orig_size; ++i) {
        dest[i] = orig[i - from];
    }

    return dest;
}


/*  Returns first index of sub_str in str. If there is no such substring returns -1. */
long firstIndexOf(char* str, unsigned int str_size, char* sub_str, unsigned int sub_str_size) {

    bool flag = false;
    unsigned int i = 0;
    unsigned int result = 0;
    while (i < str_size - sub_str_size + 1) {
        if (str[i] == sub_str[0]) {
            result = i;
            flag = true;
            for (unsigned int sub_str_inx = 0; sub_str_inx < sub_str_size; ++sub_str_inx) {
                if (str[i] != sub_str[sub_str_inx]) {
                    flag = false;
                    break;
                } else {
                    ++i;
                    continue;
                }
            }
            if (flag) return result;
        } else {
            ++i;
        }
    }
    return -1;
}

int main() {

    String str1("Hello world!");
    String str4('h');
    String str2 = str1(6, 8);
    //String str2 = str1;
    String str3 = str1 - str2 + str4;
    //str1 += str2;
    std::cout << str1 << std::endl << str2 << std::endl << str3;
    //std::cout << str1 << std::endl << str2 << std::endl;


    return 0;
}