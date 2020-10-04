#include <iostream>
#include <fstream>
#include <istream>
#include <cstring>
#define BUFFER_SIZE 16

//TODO: Deal with utf-8 strings.
class String {
private:

    unsigned int size;

    unsigned int length;

    char* str;

    String(unsigned int size, const char* str)
            :  size(size), length(size), str(new char[size]) {
        //TODO: utf-8 option

        for (unsigned int i = 0; i < size; ++i) {
            this->str[i] = str[i];
        }
    }


public:
    /* Constructors */
    explicit String()
            : size(0), length(0), str(nullptr) {}

    explicit String(char symbol)
            : size(1), length(1), str(new char[size]) {
            //TODO: utf-8 option
        str[0] = symbol;

    }


    String(const char* str)
            :  size(strlen(str)), length(strlen(str)), str(new char[strlen(str)]) {
            //TODO: utf-8 option

        for (unsigned int i = 0; i < this->size; ++i) {
            this->str[i] = str[i];
        }
    }


    String(const String& other)
            : size(other.size), length(other.length), str(new char[other.size]) {
          //TODO: utf-8 option

        for (unsigned int i = 0; i < size; ++i) {
            this->str[i] = other.str[i];
        }

    }


    ~String() {
        delete[] str;
    }


    /* Operators */
    //TODO: operator- deleting all substrings in this->str

    String& operator= (const String& other) {

        if (this != &other) {
            char* tmp = new char [other.size];

            for (unsigned int i = 0; i < size; ++i) {
                tmp[i] = other.str[i];
            }
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

        for (int i = 0; i < this->size; ++i) {
            result_str.str[i] = this->str[i];
        }
        for (int i = this->size; i < this->size + other.size; ++i) {
            result_str.str[i] = other.str[i - this->size];
        }

        return {result_str.size, result_str.str};
            
    }

    String& operator+= (const String& string) {

        char* tmp = new char[this->size + string.size];

        for (unsigned int i = 0; i < this->size; ++i) {
            tmp[i] = str[i];
        }
        for (unsigned int i = this->size; i < this->size + string.size; ++i) {
            tmp[i] = string.str[i - this->size];
        }

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
        for (unsigned int i = 0; i < line_length; ++i) {
            string.str[i] = line[i];
        }

        delete [] line;

        return input;
    }


    String operator() (unsigned int first, unsigned int last) {

        if (first < 0 || first > this->length || last < first || last > this->length) {
            std::cout << "Function operator() :: Error: wrong arguments." << std::endl;
            std::cerr << "Function operator() :: Error: wrong arguments.";
            exit(2);
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

    /* Getters */
    unsigned int getLength() const {
        return this->length;
    }

};



int main() {

    String str1("Hello world!");
    //String str1('h');
    String str2 = str1(6, 11);
    //String str2 = str1;
    String str3 = str2 * 3;
    //str1 += str2;
    std::cout << str1 << std::endl << str2 << std::endl << str3;
    //std::cout << str1 << std::endl << str2 << std::endl;


    return 0;
}