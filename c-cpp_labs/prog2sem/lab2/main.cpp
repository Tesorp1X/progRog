#include <iostream>
#include <string>
#include <fstream>
#include<algorithm>

unsigned int countSetBits(unsigned int n)
{
    unsigned int count = 0;
    /*for(size_t i = 0; i < CHAR_BIT * sizeof n; ++i)
    {
        if ((n & (1 << i)) == 1)
            ++count;
    }
*/

    while (n) {
        if (n % 2 == 1) ++count;
        n /= 2;
    }

    return count;
}


int countLength(int n) {
    int count = 0;
    while (n) {
        ++count;
        n /= 10;
    }

    return count;
}

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}


class Order{

public:
    virtual void sort(int* array, unsigned int size) = 0;
    virtual bool comparator(int a, int b) = 0;

};


class Ascending : public Order {

public:
    bool comparator(int a, int b) override {
        return (a <= b);
    }

    void sort(int* array, unsigned int size) override {
        /*std::sort(array, array + size,
                  [this](int x, int y) { return comparator(x, y); });*/

        for (unsigned int i = 0; i < size - 1; ++i) {
            for (unsigned int j = 0; j < size - i - 1; ++j) {

                if (!this->comparator(array[j], array[j + 1])) {
                    swap(&array[j], &array[j + 1]);
                }
            }
        }
    }

};

class Descending : public Order {

public:
    bool comparator(int a, int b) override {
        return (a >= b);
    }

    void sort(int* array, unsigned int size) override {
        /*std::sort(array, array + size,
                  [this](int x, int y) { return comparator(x, y); });*/
        for (unsigned int i = 0; i < size - 1; ++i) {
            for (unsigned int j = 0; j < size - i - 1; ++j) {
                if (!this->comparator(array[j], array[j + 1]))
                    swap(&array[j], &array[j + 1]);
            }
        }
    }

};

class ByLength : public Order {

protected:
    Order* order;

public:
    ByLength(Order* order)
        : order(order) {}

    bool comparator(int a, int b) override {

        return order->comparator(countLength(a), countLength(b));
    }

    void sort(int* array, unsigned int size) override {
        /*std::sort(array, array + size,
                  [this](int x, int y) { return comparator(x, y); });*/
        for (unsigned int i = 0; i < size - 1; ++i) {
            for (unsigned int j = 0; j < size - i - 1; ++j) {
                if (!this->comparator(array[j], array[j + 1]))
                    swap(&array[j], &array[j + 1]);
            }
        }
    }
};


class ByBitCount : public Order {

protected:
    Order* order;

public:
    ByBitCount(Order* order)
        : order(order) {}

    bool comparator(int a, int b) override {
/*
        unsigned int count_a = 0;
        while (a) {
            count_a += a & 1;
            a >>= 1;
        }

        unsigned int count_b = 0;
        while (b) {
            count_b += b & 1;
            b >>= 1;
        }
        */
        return order->comparator(countSetBits(a), countSetBits(b));
    }


    void sort(int* array, unsigned int size) override {
        /*std::sort(array, array + size,
                  [this](int x, int y) { return comparator(x, y); });*/
        for (unsigned int i = 0; i < size - 1; ++i) {
            for (unsigned int j = 0; j < size - i - 1; ++j) {
                if (!this->comparator(array[j], array[j + 1]))
                    swap(&array[j], &array[j + 1]);
            }
        }
    }
};


Order* getTheRightOrder(std::string order_line) {
    Order* order;
    switch (order_line[0]) {

        case 'A':

            order = new Ascending();
            break;

        case 'D':

            order = new Descending();
            break;

        case 'L':

            if (order_line[1] == 'A') {

                order = new ByLength(new Ascending());

            } else if (order_line[1] == 'D') {

                order = new ByLength(new Descending());

            }else if (order_line[1] == 'L' || order_line[1] == 'B') {

                order = new ByLength(getTheRightOrder(order_line.substr(1, order_line.length() - 1)));

            }else {
                std::cerr << "Function getTheRightOrder(std::string order_line) :: Error: wrong arguments.";
                exit(2);
            }

            break;

        case 'B':

            if (order_line[1] == 'A') {

                order = new ByBitCount(new Ascending());

            } else if (order_line[1] == 'D') {

                order = new ByBitCount(new Descending());

            } else if (order_line[1] == 'L' || order_line[1] == 'B') {

                order = new ByBitCount(getTheRightOrder(order_line.substr(1, order_line.length() - 1)));
            } else {
                std::cerr << "Function getTheRightOrder(std::string order_line) :: Error: wrong arguments.";
                exit(2);
            }

            break;

    }

    return order;

}


std::string arrayToString(int* array, unsigned int size) {

    std::string str = "";

    for (unsigned int i = 0; i < size; ++i) {
        str += std::to_string(array[i]) + " ";
    }

    return str;
}


int main() {

    std::string order_line;
    unsigned int size;


    std::ifstream fin("input.txt");
    fin >> order_line >> size;
    int* array = new int[size];

    for (unsigned int i = 0; i < size; ++i) {
        fin >> array[i];
    }

    fin.close();


    Order* order = getTheRightOrder(order_line);



    order->sort(array, size);

    std::ofstream fout("output.txt");
    fout << arrayToString(array, size);
    fout.close();

    return 0;
}