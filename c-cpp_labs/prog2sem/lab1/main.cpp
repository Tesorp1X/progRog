#include <iostream>
#include <fstream>
#include <istream>
#include <cstring>
#include <ctime>
#define BUFFER_SIZE 16

char* copyStr(char* dest, unsigned int orig_size, const char* orig);
char* concatString(char* dest, unsigned int from, unsigned int orig_size, const char* orig);
long firstIndexOf(const char* str, unsigned int str_size, const char* sub_str, unsigned int sub_str_size);




class String {
private:

    bool is_wide = false;

    unsigned int size;

    unsigned int length;

    char* str;




    String(unsigned int size, const char* str)
            : size(size), length(0), str(new char[size]) {

        bool flag = false;

        /* Computing the right length. */
        for (unsigned int i = 0; i < this->size;) {

            if (((unsigned char)str[i]) >> 7 == 0) {
                this->length++;
                i++;
            } else if (((unsigned char)str[i]) >> 5 == 6) {
                this->length++;
                i += 2;
                flag = true;
            } else if (((unsigned char)str[i]) >> 4 == 14) {
                this->length++;
                i += 3;
                flag = true;
            } else if (((unsigned char)str[i]) >> 3 == 30) {
                this->length++;
                i += 4;
                flag = true;
            }
        }
        this->is_wide = flag;
        copyStr(this->str, size, str);
    }


    String(unsigned int size)
            : size(size), length(size), str(new char[size]) {}


    String(unsigned int size, char wide_flag)
            : is_wide(wide_flag == 'w'), size(size), length(size), str(new char[size]) {}


public:
    /* Constructors */
    explicit String()
            : size(0), length(0), str(nullptr) {}


    String(char symbol)
            : size(1), length(1), str(new char[size]) {

        str[0] = symbol;

    }


    explicit String(const char* str)
            :  size(strlen(str)), length(strlen(str)), str(new char[strlen(str)]) {

        copyStr(this->str, length, str);

    }




    String(const String& other)
            :  is_wide(other.is_wide), size(other.size), length(other.length), str(new char[other.size]) {

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

            this->is_wide = other.is_wide;
            this->str = tmp;
            this->size = other.size;
            this->length = other.length;

        }

        return *this;
    }


    String operator+ (const String& other) {

        String result_str(this->size + other.size);

        copyStr(result_str.str, this->size, this->str);
        concatString(result_str.str, this->size, other.size, other.str);


        return {result_str.size, result_str.str};
    }


    /*  original_str is C-style string!  */
    String operator+ (const char* original_str) {

        String string(original_str);

        return *this + string;
    }

    String& operator+= (const String& string) {


        String temp(this->size + string.size);

        copyStr(temp.str, this->size, this->str);
        concatString(temp.str, this->size, string.size, string.str);

        *this = temp;

        return *this;
    }

    friend std::ostream& operator<< (std::ostream& output, String& string) {

        for (int i = 0; i < string.size; ++i) {

            output << string.str[i];
        }

        return output;
    }

    String operator* (unsigned int repeats) {

        String string = *this;
        String result = *this;
        for (unsigned int i = 1; i < repeats; ++i) {

            result += string;
        }


        return result;
    }


    friend std::istream& operator>> (std::istream& input, String& string) {

        char c;
        unsigned int index = 0;
        unsigned int line_length = 0;
        unsigned int line_size = 0;
        unsigned int allocated_size = BUFFER_SIZE;
        char* line = new char[BUFFER_SIZE];

        c = input.get();
        while (!input.eof() && (c != '\n' && c != '\r')) {

            if (line_length >= allocated_size) {

                char* new_line = new char[allocated_size + BUFFER_SIZE];
                copyStr(new_line, line_size, line);

                delete[] line;
                allocated_size += BUFFER_SIZE;
                line = new_line;
                new_line = nullptr;
                line[index++] = c;
                ++line_size;
            } else {

                line[index++] = c;
                ++line_size;
            }
            c = input.get();
        }


        String result(line_size, line);
        string = result;

        delete[] line;

        return input;
    }


    String operator() (unsigned int first, unsigned int last) const{

        if (first < 0 || first > this->length || last < first || last > this->length) {
            std::cout << "Function operator() :: Error: wrong arguments." << std::endl;
            std::cerr << "Function operator() :: Error: wrong arguments.";
            exit(2);
        }
        if (last == first) {
            return {(*this)[first]};
        }

        String new_line(last - first + 1);
        for (unsigned int i = first; i < last + 1; ++i) {
            new_line[i - first] = str[i];
        }

        return {last - first + 1, new_line.str};
    }


    char& operator[] (unsigned int index) const{

        if (index > this->length) {
            std::cout << "Function operator() :: Error: wrong arguments." << std::endl;
            std::cerr << "Function operator() :: Error: wrong arguments.";
            exit(2);
        }

        if (!this->is_wide) return this->str[index];

        unsigned int i = 0, len_so_far = 0;

        for ( ; i < this->size && len_so_far != index; ) {
            if (((unsigned char)str[i]) >> 7 == 0) {
                len_so_far++;
                i++;
            } else if (((unsigned char)str[i]) >> 5 == 6) {
                len_so_far++;
                i += 2;
            } else if (((unsigned char)str[i]) >> 4 == 14) {
                len_so_far++;
                i += 3;
            } else if (((unsigned char)str[i]) >> 3 == 30) {
                len_so_far++;
                i += 4;
            }

        }

        return this->str[len_so_far];

    }

    

    String operator- (String& substr) {

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


    bool operator== (String& other) const{

        if (this->length != other.length) return false;

        for (unsigned int i = 0; i < other.length; ++i) {
            if ((*this)[i] != other[i]) return false;
        }

        return true;

    }

    bool operator!= (String& other) const{

        return !(*this == other);
    }


    void replace (String& pattern, String& replace, unsigned int start_index) {

        if (pattern == replace) return;

        String result;

        if (start_index == 0 && start_index + pattern.length == this->length) {

            result = replace;

        } else if (start_index == 0) {

            result = replace + (*this)(start_index + pattern.length, this->length - 1);

        } else if (start_index + pattern.length == this->length) {

            result = (*this)(0, start_index - 1) + replace;

        } else {

            result = this->operator()(0, start_index - 1)
                            + replace
                            + (*this)(start_index + pattern.length, this->length - 1);

        }

        *this = result;

    }

    void replace(String& pattern, String& replace) {

        String result = *this;

        unsigned int start_index = firstIndexOf(result.str, result.size, pattern.str, pattern.size);

        result.replace(pattern, replace, start_index);

        *this = result;

    }


    /* Getters */
    unsigned int getLength() const {
        return this->length;
    }

    unsigned int getSize() const {
        return this->size;
    }

    String replaceAll(String& pattern, String& replacement) {

        if (pattern == replacement) return *this;

        String result = *this;
        long first_index = firstIndexOf(result.str, result.size, pattern.str, pattern.size);

        while (first_index != -1) {

            result.replace(pattern, replacement, first_index);
            first_index = firstIndexOf(result.str, result.size, pattern.str, pattern.size);

        }

        return {result.size, result.str};
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
long firstIndexOf(const char* str, unsigned int str_size, const char* sub_str, unsigned int sub_str_size) {

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

    String string;
    String pattern;
    String replacement;

    std::ifstream fin("input.txt");

    fin >> string >> pattern >> replacement;
    fin.close();

    //String result = string.replaceAll(pattern, replacement);

    String * str = new String();
    std::ofstream fout("output.txt");

    //fout << result;
    fout << string << std::endl << string.getLength() << std::endl << string.getSize();
    fout.close();


    return 0;
}