#include "HashTable.h"

EdgeList::EdgeList(){
    this->firstElement = NULL;
    this->lastElement = NULL;
}

HashTable::HashTable(size_t size){
    this->size = size;
    table = new EdgeList[size];
    for(size_t i = 0; i < size; ++i){
        table[i].firstElement = NULL;
        table[i].lastElement = NULL;
    }
}

int HashTable::hashFunction(triangleEdge* trEdg){
    return trEdg->p1 % size;
}

void HashTable::add(triangleEdge *trEdge){
    triangleEdge* tmpEdg = findEdge(trEdge);
    if(tmpEdg != NULL){
        tmpEdg->lastTriangle->nextElement = trEdge->firstTriangle;
        tmpEdg->lastTriangle = trEdge->lastTriangle;
        tmpEdg->lastTriangle->nextElement = NULL;
        return;
    }
    ListElement* newElement = new ListElement();
    newElement->data = trEdge;
    newElement->nextElement = NULL;
    int index = hashFunction(trEdge);
    if(table[index].firstElement == NULL){
        table[index].firstElement = newElement;
        table[index].lastElement = newElement;
    }else{
        table[index].lastElement->nextElement = newElement;
        table[index].lastElement = newElement;
    }
}

triangleEdge* HashTable::findEdge(triangleEdge* trEdg){
    int index = hashFunction(trEdg);
    ListElement* curElement = table[index].firstElement;
    while((curElement != NULL) && ((curElement->data->p1 != trEdg->p1) || (curElement->data->p2 != trEdg->p2))){
        curElement  = curElement->nextElement;
    }
    if (curElement == NULL){
        return NULL;
    }
    return curElement->data;
}
