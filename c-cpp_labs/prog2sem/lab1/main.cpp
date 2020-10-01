#include <iostream>
#include <fstream>
#include <istream>
#define BUFFER_SIZE 16

//TODO: Deal with utf-8 strings.
class String {
private:

    unsigned int size;

    unsigned int length;

    char* str;


public:
    /* Constructors */
    explicit String()
            : size(0), length(0), str(nullptr) {}

    explicit String(char symbol)
            : size(1), length(1), str(new char[size]) {

        str[0] = symbol;

    }

    String(unsigned int length, const char* str)
            :  size(length + 1), length(length), str(new char[size]) {
            //TODO: constructor for line of given length
    }


    String(String& other)
            : size(other.size), length(other.length), str(new char[other.size]) {
                //TODO: Copy constructor
    }




    ~String() {
        delete[] str;
    }

    /* Operators */
    String operator+(const String& other) {
            //TODO: String concatenation via + operator
    }

    friend std::ostream& operator<< (std::ostream& output, String& string) {

        for (int i = 0; i < string.length; ++i){
            output << string[i];
        }

        return output;
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
                for (int i = 0; i < line_length; ++i) {
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
        for (int i = 0; i < line_length; ++i) {
            string.str[i] = line[i];
        }

        delete [] line;

        return input;
    }

    //TODO: operator() (unsigned int left, unsigned int right)


    char operator[](unsigned int index){
        return this->str[index];
    }

    /* Getters */
    unsigned int getLength() const {
        return this->length;
    }

};



int main() {

    String str1('f');
    std::cout << str1 << std::endl;

    String str2;
    std::cin >> str2;
    std::cout << str2 << std::endl;

    return 0;
}