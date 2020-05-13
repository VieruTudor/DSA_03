#include "ListIterator.h"
#include "IndexedList.h"
#include <exception>
#include <iostream>
using namespace std;

ListIterator::ListIterator(const IndexedList& list) : list(list){
   //TODO - Implementation
    first();
}

/// Complexity : O(1)
void ListIterator::first(){
    //TODO - Implementation
    this->currentElement = this->list.head;
}

/// Complexity : O(1)
void ListIterator::next(){
    //TODO - Implementation
    if (!valid())
        throw exception();
    this->currentElement = this->list.nodes[this->currentElement].next;
}

/// Complexity : O(1)
void ListIterator::prev()
{
    if (!valid())
        throw exception();
    this->currentElement = this->list.nodes[this->currentElement].prev;
}

void ListIterator::setCurrentIndex(int pos)
{
    this->currentElement = pos;
}

int ListIterator::getCurrentIndex()
{
    return this->currentElement;
}

/// Complexity : O(1)
bool ListIterator::valid() const{
    //TODO - Implementation
    return this->currentElement != -1 && !list.isEmpty();
}

/// Complexity : O(1)
TElem ListIterator::getCurrent() const{
   //TODO - Implementation
    if (!this->valid())
        throw exception();
    return this->list.nodes[this->currentElement].info;
}