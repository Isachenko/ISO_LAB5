#pragma once;
#include <stdio.h>
#include <iostream>
#include "Structs.h"

struct ListElement{
    triangleEdge* data;
    ListElement* nextElement;
};

struct EdgeList{
    ListElement* firstElement;
    ListElement* lastElement;
    EdgeList();
};

class HashTable{
public:
    HashTable(size_t size);
    void add(triangleEdge* trEdge);
    triangleEdge* findEdge(triangleEdge* trEdge);
    size_t size;
    EdgeList* table;
private:
    int hashFunction(triangleEdge *trEdg);
};
