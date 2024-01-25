#include "Map.h"

Map::Map()
{
	head = tail = nullptr;
	map_size = 0;
}

Map::~Map()
{
	Pair* curr = head;
	Pair* next;

	// traverse the linked list and delete every node
	while (curr != nullptr) {
		next = curr->next;
		delete curr;
		curr = next;
	}
}

Map::Map(const Map& other) : Map() // constructor delegation
{
	KeyType k;
	ValueType v;
	// iterate through other's linked list and copy keys and values
	for (int i = 0; i < other.size(); i++) {
		other.get(i, k, v);
		insert(k, v);
	}
}

Map& Map::operator=(const Map& other)
{
	Pair* curr = head;
	Pair* next;

	// traverse the linked list and delete every node
	while (curr != nullptr) {
		next = curr->next;
		delete curr;
		curr = next;
	}

	head = tail = nullptr;
	map_size = 0;

	KeyType k;
	ValueType v;
	// iterate through other's linked list and copy keys and values
	for (int i = 0; i < other.size(); i++) {
		other.get(i, k, v);
		insert(k, v);
	}

	return *this;
}

bool Map::empty() const
{
	return map_size == 0;
}

int Map::size() const
{
	return map_size;
}

bool Map::insert(const KeyType& key, const ValueType& value)
{
	if (getPair(key) != nullptr) // key already exists
		return false;

	Pair* p = new Pair;
	p->key = key;
	p->value = value;

	if (head == nullptr) { // empty list
		p->prev = p->next = nullptr;
		head = tail = p;
		map_size++;
		return true;
	}

	Pair* curr = head;
	// iterate over list and stop when on the node
	// below of where we want to insert
	while (curr != nullptr) {
		if (key < curr->key)
			break;
		curr = curr->next;
	}

	if (curr == nullptr) { // insert at end of list
		p->prev = tail;
		p->next = nullptr;
		tail = tail->next = p;
	} else if (curr == head) { // insert at beginning of list
		p->prev = nullptr;
		p->next = head;
		head = head->prev = p;
	} else { // insert in middle of list
		p->next = curr;
		p->prev = curr->prev;
		curr->prev->next = p;
		curr->prev = p;
	}

	map_size++;
	return true;
}

bool Map::update(const KeyType& key, const ValueType& value)
{
	Pair* p = getPair(key);
	if (p == nullptr) // key doesn't exist
		return false;

	p->value = value;
	return true;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
	// insert will only fail if key already exists
	if (!insert(key, value))
		update(key,value);
	return true;
}

bool Map::erase(const KeyType& key)
{
	Pair* p = getPair(key);
	if (p == nullptr) // key doesn't exist
		return false;

	if (p == head) { // delete top node
		p->next->prev = nullptr;
		head = p->next;
	} else if (p == tail) { // delete bottom node
		p->prev->next = nullptr;
		tail = p->prev;
	} else { // delete middle node
		p->prev->next = p->next;
		p->next->prev = p->prev;
	}
	delete p;

	map_size--;
	return true;
}

bool Map::contains(const KeyType& key) const
{
	return getPair(key) != nullptr;
}

bool Map::get(const KeyType& key, ValueType& value) const
{
	Pair* p = getPair(key);
	if (p == nullptr) // key doesn't exist
		return false;

	value = p->value;
	return true;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{
	if (i < 0 || i >= map_size)
		return false;

	Pair* p = head;
	int count = 0;
	// traverse the list i times
	while (p != nullptr && count < i) {
		p = p->next;
		count++;
	}

	key = p->key;
	value = p->value;
	return true;
}

void Map::swap(Map& other)
{
	Pair* tmp;

	// swap head pointer
	tmp = other.head;
	other.head = head;
	head = tmp;

	// swap tail pointer
	tmp = other.tail;
	other.tail = tail;
	tail = tmp;

	// swap map_size
	int tmp_size;
	tmp_size = other.map_size;
	other.map_size = map_size;
	map_size = tmp_size;
}

bool merge(const Map& m1, const Map& m2, Map& result)
{
	bool retval = true;
	KeyType k;
	ValueType v, v2;

	// erase all nodes in result
	for (int i = 0; i < result.size(); i++) {
		result.get(i, k, v);
		result.erase(k);
	}

	// interate over every node in m1
	for (int i = 0; i < m1.size(); i++) {
		m1.get(i, k, v);
		if (!m2.get(k, v2) || v == v2)
			result.insert(k, v);
		else
			retval = false;
	}

	// iterate over every node in m2
	for (int i = 0; i < m2.size(); i++) {
		m2.get(i, k, v);
		if (!m1.get(k, v2) || v == v2)
			result.insert(k, v);
		else
			retval = false;
	}

	return retval;
}

void reassign(const Map& m, Map& result)
{
	KeyType k1, k2;
	ValueType v1, v2;

	// erase all nodes in result
	for (int i = 0; i < result.size(); i++) {
		result.get(i, k1, v1);
		result.erase(k1);
	}

	if (m.size() <= 0) {
		; // do nothing
	} else if (m.size() == 1) {
		m.get(0, k1, v1);
		result.insert(k1, v1);
	} else {
		// shifts all the values up (but keys stay in place)
		m.get(0, k1, v1);
		for (int i = 1; i < m.size(); i++) {
			m.get(i, k2, v2);
			result.insert(k1, v2);
			k1 = k2;
			v1 = v2;
		}
		m.get(0, k1, v1);
		result.insert(k2, v1);
	}

	return;
}

// TODO check for aliasing
