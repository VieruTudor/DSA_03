#pragma once
#include "IndexedList.h"


class ListIterator{
    //DO NOT CHANGE THIS PART
	friend class IndexedList;
private:
	const IndexedList& list;
	//TODO - Representation
    int currentElement;
    ListIterator(const IndexedList& lista);
public:
    void first();
    void next();
    void prev();
    void setCurrentIndex(int pos);
    int getCurrentIndex();
    bool valid() const;
    TElem getCurrent() const;

};

