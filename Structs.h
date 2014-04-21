#ifndef STRUCTS_H
#define STRUCTS_H
#include <iostream>

struct point{
    float x,y,z;
    point(float a, float b, float c): x(a), y(b), z(c){}
    point(): x(0), y(0), z(0){}
    bool operator <(const point& p) const {
        if (x < p.x) return true;
        else if (x > p.x) return false;
        if (y < p.y) return true;
        else if (y > p.y) return false;
        if (z < p.z) return true;
        return false;
    }
    bool operator >(const point& p) const {
        if (x > p.x) return true;
        else if (x > p.x) return false;
        if (y > p.y) return true;
        else if (y > p.y) return false;
        if (z > p.z) return true;
        return false;
    }
    bool operator ==(const point& p) const {
        return (x == p.x) && (y == p.y) && (z == p.z);
    }
};

struct triangle{
    int p1, p2, p3, centerP;
    triangle(int a, int b, int c): p1(a), p2(b), p3(c), centerP(-1){}
    triangle(): p1(-1), p2(-1), p3(-1), centerP(-1){}

};

struct triangleListElement{
    triangle* data;
    triangleListElement* nextElement;
};


struct triangleEdge{
    triangleListElement* firstTriangle;
    triangleListElement* lastTriangle;
    int p1, p2, centerP;
    triangleEdge(int a, int b, triangle* tr){
        p1 = a;
        p2 = b;
        if(p1 > p2){
          int tmp = p1;
          p1 = p2;
          p2 = tmp;
        }
        centerP = -1;
        firstTriangle = new triangleListElement();
        lastTriangle = firstTriangle;
        lastTriangle->data = tr;
        lastTriangle->nextElement = NULL;
    }
};


#endif // STRUCTS_H
