#include <exception>

#include "IndexedList.h"
#include "ListIterator.h"

#include <iostream>
using namespace std;

IndexedList::IndexedList() {
	this->nodes = new DLLANode;
	this->listSize = 0;
	this->capacity = 1;
	this->head = -1;
	this->tail = -1;
	this->firstEmpty = 0;
}

/// Complexity : Theta(Capacity)
void IndexedList::resize()
{
	this->capacity *= 2;
	DLLANode* newNodes = new DLLANode[this->capacity];

	for (int i = 0; i < this->capacity / 2; i++)
		newNodes[i] = this->nodes[i];

	delete[] this->nodes;
	this->nodes = newNodes;
	this->firstEmpty = this->listSize;
	for (int i = this->listSize; i < this->capacity - 1; ++i)
	{
		this->nodes[i].prev = -1;
		this->nodes[i].next = i + 1;
	}
	this->nodes[this->capacity - 1].prev = -1;
	this->nodes[this->capacity - 1].next = -1;
}

/// Complexity : Theta(1)
int IndexedList::size() const {
	return this->listSize;
}

/// Complexity : Theta(1)
bool IndexedList::isEmpty() const {
	return this->listSize == 0;
}

/*
Best case : Theta(1)
Worst case : Theta(capacity)
Average case : O(capacity)
*/
TElem IndexedList::getElement(int pos) const {
	if (pos < 0 || pos >= this->listSize)
		throw exception();

	int currentNode = this->head;
	for (int i = 0; i < pos; i++)
		currentNode = this->nodes[currentNode].next;
	return this->nodes[currentNode].info;
}

/*
Best case : Theta(1)
Worst case : Theta(capacity)
Average case : O(capacity)
*/
TElem IndexedList::setElement(int pos, TElem e) {
	if (pos < 0 || pos >= this->listSize)
		throw exception();

	int currentNode = this->head;
	for (int i = 0; i < pos; i++)
		currentNode = this->nodes[currentNode].next;
	
	TElem oldValue = this->nodes[currentNode].info;
	this->nodes[currentNode].info = e;
	return oldValue;
}
/*
Best case : Theta(1)
Average case : Theta(1) amortized (?)
Worst case : Theta(capacity) - since we have to resize
*/
void IndexedList::addToEnd(TElem e) {
	if (this->tail == -1) 
		this->head = this->firstEmpty;
	if (this->listSize == this->capacity)
		this->resize();

	this->nodes[this->tail].next = this->firstEmpty;
	this->nodes[this->firstEmpty].prev = this->tail;
	this->tail = this->firstEmpty;
	this->firstEmpty = this->nodes[this->firstEmpty].next;

	this->nodes[this->tail].info = e;
	this->nodes[this->tail].next = -1;

	this->listSize++;
}

/*
Best case : O(1)
Average case : O(n)
Worst case : O(n)
*/
void IndexedList::addToPosition(int pos, TElem e) {
	if (pos < 0 || pos >= this->listSize) 
		throw exception();
	if (this->listSize == this->capacity) 
		this->resize();

	int node = this->firstEmpty;
	this->firstEmpty = this->nodes[node].next;
	this->nodes[node].info = e;
	int currentNode = this->head;

	for (int i = 0; i < pos; i++)
		currentNode = this->nodes[currentNode].next;

	this->nodes[node].next = currentNode;
	this->nodes[node].prev = this->nodes[currentNode].prev;

	int prevNode = this->nodes[currentNode].prev;
	this->nodes[currentNode].prev = node;

	if (prevNode != -1)
		this->nodes[prevNode].next = node;
	else
		this->head = node;

	this->listSize++;
}
/*
Best case : Theta(1)
Worst case : Theta(capacity)
Average case : O(capacity)
*/
TElem IndexedList::remove(int pos) {
	if (pos < 0 || pos >= this->listSize) 
		throw exception();
	TElem removed;
	int currentNode = this->head, node;

	for (int i = 0; i < pos; i++)
		currentNode = this->nodes[currentNode].next;
	removed = this->nodes[currentNode].info;

	if (pos == 0) 
		this->head = this->nodes[currentNode].next;

	if (pos == this->listSize - 1) 
		this->tail = this->nodes[currentNode].prev;

	node = this->nodes[currentNode].prev;
	if (node != -1) 
		this->nodes[node].next = this->nodes[currentNode].next;
	node = this->nodes[currentNode].next;
	if (node != -1) 
		this->nodes[node].prev = this->nodes[currentNode].prev;

	this->nodes[currentNode].next = this->firstEmpty;
	this->nodes[currentNode].prev = -1;
	this->firstEmpty = currentNode;

	this->listSize--;

	return removed;
}

/*
Best case : Theta(1)
Worst case : Theta(capacity)
Average case : O(capacity)
*/
int IndexedList::search(TElem e) const {
	int currentNode = this->head;
	for (int index = 0; index < this->listSize; index++)
	{
		if (this->nodes[currentNode].info == e)
			return index;
		currentNode = this->nodes[currentNode].next;
	}
	return -1;
}

ListIterator IndexedList::iterator() const {
	return ListIterator(*this);
}

IndexedList::~IndexedList() {
	delete[] this->nodes;
}