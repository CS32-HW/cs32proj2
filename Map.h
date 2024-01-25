#ifndef Map_h
#define Map_h

#include <string>
using KeyType = std::string;
using ValueType = double;

class Map
{
  public:
    Map();
    ~Map();
    Map(const Map& other);
    Map& operator=(const Map& other);
    bool empty() const;
    int size() const;
    bool insert(const KeyType& key, const ValueType& value);
    bool update(const KeyType& key, const ValueType& value);
    bool insertOrUpdate(const KeyType& key, const ValueType& value);
    bool erase(const KeyType& key);
    bool contains(const KeyType& key) const;
    bool get(const KeyType& key, ValueType& value) const;
    bool get(int i, KeyType& key, ValueType& value) const;
    void swap(Map& other);
  private:
    struct Pair {
        KeyType   key;
	ValueType value;
	Pair*     prev;
	Pair*     next;
    };
    Pair *head, *tail;
    int map_size;

    Pair* getPair(const KeyType& key) const
      // returns a pointer to the Pair containing the key
      // returns nullptr if not found
    {
        Pair* p = head;

        while (p != nullptr) {
            if (p->key == key)
                break;
            p = p->next;
        }

        return p;
    }

};

bool merge(const Map& m1, const Map& m2, Map& result);
void reassign(const Map& m, Map& result);

#endif // Map_h
