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
