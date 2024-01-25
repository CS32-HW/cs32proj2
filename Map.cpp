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

//TODO copy constructor and assignment operator

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

Pair* Map::getPair(const KeyType& key) const
{
	Pair* p = head;

	while (p != nullptr) {
		if (p->key == key)
			break;
		p = p->next;
	}

	return p;
}
