#include <assert.h>
#include <exception>

#include "ShortTest.h"
#include "IndexedList.h"
#include "ListIterator.h"
#include <iostream>

using namespace std;


void testAll() {
    IndexedList list = IndexedList();
    assert(list.isEmpty());
    list.addToEnd(1);

    assert(list.size() == 1);
    list.addToPosition(0, 2);
    assert(list.size() == 2);
    ListIterator it = list.iterator();
    assert(it.valid());
    it.next();
    assert(it.getCurrent() == 1);
    it.first();
    assert(it.getCurrent() == 2);
    assert(list.search(1) == 1);
    assert(list.setElement(1, 3) == 1);
    assert(list.getElement(1) == 3);
    assert(list.remove(0) == 2);
    assert(list.size() == 1);

    IndexedList testList = IndexedList();
    for (int i = 0; i < 10; i++)
        testList.addToEnd(i);
    ListIterator it2 = testList.iterator();
    cout << "Forward list traversal\n";
    while (it2.valid())
    {
        int elem = it2.getCurrent();
        cout << elem << " ";
        it2.next();
    }
    cout << "\nBackward list traversal\n";
    it2.setCurrentIndex(testList.size() - 1);
    while (it2.valid())
    {
        int elem = it2.getCurrent();
        cout << elem << " ";
        it2.prev();
    }
    cout << "\n";

}
