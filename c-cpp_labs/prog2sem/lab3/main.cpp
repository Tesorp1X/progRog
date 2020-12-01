#include <iostream>
#include <string>
#include <fstream>
#include <set>

template <typename K, typename V>
struct HashPair {
    K key;
    V value;
    const bool is_end;

    HashPair(bool is_end) : is_end(is_end) {}

    HashPair() : is_end(false) { }

    HashPair(K& k, V& v) : key(k), value(v), is_end(false) { }

    HashPair(HashPair& other) {
        this->key = other.key;
        this->value = other.value;
        this->is_end = other.is_end;
    }

    bool operator== (HashPair const & other) {
        return (this->key == other.key && this->value == other.value);
    }

    bool operator!= (HashPair const & other) {
        return !operator==(other);
    }


    HashPair& operator= (HashPair const & other) {
        this->key = other.key;
        this->value = other.value;
    }
    
};


template <typename K, typename V>
class HashMap {

private:
    HashPair<K, V> * fakeEndNote = new HashPair<K, V>(true);
    const unsigned int DEFAULT_ARRAY_SIZE = 1 << 4;
    const double OK_LOAD_FACTOR = 0.8;
    unsigned int size = DEFAULT_ARRAY_SIZE;
    unsigned int deleted = 0;
    unsigned int used = 0;


    HashPair<K, V> **items;

    explicit HashMap(size_t size)
            : size(size),used(0), deleted(0),
              items(new HashPair<K, V> *[size + 1]()) {
        items[size] = fakeEndNote;
    }


    template<typename T>
    unsigned int hashCode(T key) {
        std::hash<T> hasher;
        return hasher(key) % size;
    }

    bool rawPut(HashPair<K, V> * pair, unsigned int index, HashPair<K, V> ** _items) {

        while (_items[index] != nullptr) {

            if (index == size) {
                index = 0;

            } else if (_items[index]->key == pair->key) {
                _items[index]->value = pair->value;
                delete pair;
                return false;
            } else {
                ++index;
            }
        }

        _items[index] = pair;
        return true;
    }

    //TODO: iterator

    /**
     * Creates a new table of increased or decreased size(depends on @param to_increase)
     *     and replaces the old one, which is being properly deleted.
     * @param to_increase if true, hashmap will be extended up to two times the size of the current one.
     */
    void rehash(bool to_increase) {
        /*
         * Go through map and add all elements to new bigger map. Then delete it.
         */
        unsigned int old_size = size;
        if (to_increase) {
            size <<= 1;
        } else {
            size >>= 1;
        }

        auto new_items = new HashPair<K, V>*[size + 1]();
        new_items[size] = fakeEndNote;

        for (unsigned int i = 0; i < old_size; ++i) {

            if (items[i] != nullptr) {

                /*  Inserting old new elements. */
                unsigned int new_index = hashCode(items[i]->key);
                rawPut(items[i], new_index, new_items);

            }
        }
        delete [] items;
        items = new_items;
    }

    /**
     * @return index of HashPair in items array. If there is no such element -1 is being return.
     * */
    unsigned int findPairIndexByKey(K& key) {

        unsigned int index = hashCode(key);
        unsigned int start_index = index;
        if (items[index] != nullptr) {
            if (items[index]->key == key) {
                return index;
            }
        } else {

                while (true) {
                    if (index + 1 == size) {
                        index = 0;
                    } else  {
                        ++index;
                    }
                    if (index == start_index) {
                        return -1;

                    } else if (items[index] != nullptr && items[index]->key == key) {
                        return index;
                    }
                }
            }

        return -1;
    }

public:

    ~HashMap() {
        for (unsigned int i = 0; i < size; ++i) {
            if (items[i] != nullptr) {
                delete items[i];
            }
        }

        delete [] items;
        //delete fakeEndNote;
    }


    HashMap(): used(0), deleted(0), items(new HashPair<K, V> *[size + 1]()) {
        items[size] = fakeEndNote;
    }


    void put(K& key, V& value) {

        if ((double)used/size >= OK_LOAD_FACTOR) {
            rehash(true);
        }

        unsigned int index = hashCode(key);

        if (rawPut(new HashPair<K, V>(key, value), index, items)) {
            ++used;
        }


    }

    V& getValueByKey(K& key) {

        unsigned int index = findPairIndexByKey(key);

        if (index == -1) return nullptr;

        HashPair<K, V>* pair = items[index];
        return pair->value;

    }

    bool remove(K& key) {
        int index = findPairIndexByKey(key);
        if (index == -1) return false;
        delete items[index];
        items[index] = nullptr;
        ++deleted;
        --used;
        if ((double)deleted/size >= 100 - OK_LOAD_FACTOR) {
            rehash(false);
        }
        return true;
    }

    std::set<K> * getKeySet() const {

        auto keySet = new std::set<K>();

        for (int i = 0; i < size; ++i) {
            if (items[i] != nullptr) {
                keySet->insert(items[i]->key);
            }
        }

        return keySet;
    }

    std::set<V> * getValueSet() const {

        auto valueSet = new std::set<V>();

        for (int i = 0; i < size; ++i) {
            if (items[i] != nullptr) {
                valueSet->insert(items[i]->value);
            }
        }

        return valueSet;
    }

    unsigned int getSize() const {
        return size;
    }

    unsigned int amountOfUsed() const {
        return used;
    }

    unsigned int amountOfUnique() const {

        std::set<V> * valueSet = getValueSet();
        unsigned int res = valueSet->size();
        delete valueSet;

        return res;
    }

    void print() {
        std::cout << "Hash map size = " << size
        << " used = " << used << std::endl;
        int count = 0;
        for (auto i = 0; i < size; ++i) {
            if (items[i] != nullptr) {
                std::cout << i << " "
                          << items[i]->key << " "
                          << items[i]->value << std::endl;
                ++count;
            } else {
                std::cout << i << "NULL" << std::endl;
            }
        }
        std::cout << count << std::endl;
    }


    //iterator
    class iterator {
    private:
        HashPair<K, V> ** node_ptr;


    public:
        //++it. it->

        iterator(iterator const &start) : node_ptr(start.node_ptr) {}


        iterator(HashPair<K, V> ** pair_ptr, bool flag) : node_ptr(pair_ptr) {}

        HashPair<K, V> * operator*() const {
            return *node_ptr;
        }

        HashPair<K, V> * operator->() const {
            return *node_ptr;
        }

        iterator& operator++() {
            ++(this->node_ptr);
            //std::cout << "Address for operator++ " << this << std::endl;
            while(*(this->node_ptr) == nullptr) {
                ++(this->node_ptr);
                //std::cout << "Skipped address : " << this << std::endl;

            }

            return *this;
        }

        bool operator!=(const iterator& other) const {
            if (this->node_ptr != nullptr && this->node_ptr == other.node_ptr) {
                return false;
            }

            return true;
        }



    };

    HashMap<K, V>::iterator begin() const {
        HashPair<K, V> ** ptr = items;
        while (*ptr == nullptr) {
            ptr++;
        }

        return { ptr, true };
    }

    HashMap<K, V>::iterator end() const { return {items + size, true}; }
   
};

template <typename K, typename V>
HashMap<K ,V> * constructHashMap(std::istream& in, int n) {

    auto hashMap = new HashMap<K, V>();
    char action;
    K k; V v;
    for (int i = 0; i < n; ++i) {

        in >> action;

        switch (action) {
            case 'A':
                in >> k >> v;
                hashMap->put(k, v);
                break;
            case 'R':
                in >> k;

                if (!hashMap->remove(k)) {
                    std::cerr << "No such element in the table." << std::endl;
                }
                break;
            default:
                break;
        }

    }

    return hashMap;
}

template <typename K>
void solve_task(const char* type_str, int n, std::istream& fin, std::ostream& fout) {
    switch (type_str[1]) {
        case 'I': {
            HashMap<K, int> *hashMap = constructHashMap<K, int>(fin, n);
            fout << hashMap->amountOfUsed() << " " << hashMap->amountOfUnique();

            for (auto it : *hashMap) {
                std::cout << "key: " << it->key << " val: " << it->value << std::endl;
            }

            delete hashMap;
            break;
        }
        case 'D': {
            HashMap<K, double> *hashMap = constructHashMap<K, double>(fin, n);
            fout << hashMap->amountOfUsed() << " " << hashMap->amountOfUnique();

            for (auto it : *hashMap) {
                std::cout << "key: " << it->key << " val: " << it->value << std::endl;
            }

            delete hashMap;
            break;
        }
        case 'S': {
            HashMap<K, std::string> *hashMap = constructHashMap<K, std::string>(fin, n);
            fout << hashMap->amountOfUsed() << " " << hashMap->amountOfUnique();

            for (auto it : *hashMap) {
                std::cout << "key: " << it->key << " val: " << it->value << std::endl;
            }

            delete hashMap;
            break;
        }
    }
}

int main() {

    char type_str[2];
    std::ifstream fin("input.txt");
    fin >> type_str[0] >> type_str[1];

    int n;
    fin >> n;

    std::ofstream fout("output.txt");

    if (type_str[0] == 'I') {

        solve_task<int>(type_str, n, fin, fout);

    } else if (type_str[0] == 'D') {

        solve_task<double>(type_str, n, fin, fout);

    } else if (type_str[0] == 'S') {

        solve_task<std::string>(type_str, n, fin, fout);

    }

    fin.close();
    fout.close();

    return 0;
}
