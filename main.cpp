#include <iostream>
#include <stdio.h>
#include <string>
#include <cmath>
#include <algorithm>
#include "Structs.h"
#include "HashTable.h"
#include <queue>
#include <vector>

using namespace std;

vector<point*> points;
vector<triangle*> triangles;
vector<triangle*> newTriangles;
HashTable* table;

int pointsCount;
int n;

float getRange(point* p1, point* p2){
    float range = sqrt(pow(p1->x - p2->x, 2) + pow(p1->y - p2->y, 2) + pow(p1->z - p2->z, 2));
    return range;
}

void createNewTriangles(){
    for(size_t i = 0; i < table->size; ++i){
        ListElement* curElement = table->table[i].firstElement;
        while(curElement != NULL){
            if (-1 == curElement->data->centerP){
                point* p1 = points[curElement->data->p1];
                point* p2 = points[curElement->data->p2];
                point* centerP = new point((p1->x + p2->x) / 2, (p1->y + p2->y) / 2, (p1->z + p2->z) / 2);
                points.push_back(centerP);
                curElement->data->centerP = points.size() - 1;
            }
            triangleListElement* curTriangle = curElement->data->firstTriangle;
            while(curTriangle != NULL){
                if (-1 == curTriangle->data->centerP){
                    point* p1 = points[curTriangle->data->p1];
                    point* p2 = points[curTriangle->data->p2];
                    point* p3 = points[curTriangle->data->p3];
                    point* centerP = new point((p1->x + p2->x + p3->x) / 3, (p1->y + p2->y + p3->y) / 3, (p1->z + p2->z + p3->z) / 3);
                    points.push_back(centerP);
                    curTriangle->data->centerP = points.size() - 1;
                }
                newTriangles.push_back(new triangle(curElement->data->p1, curElement->data->centerP, curTriangle->data->centerP));
                newTriangles.push_back(new triangle(curElement->data->p2, curElement->data->centerP, curTriangle->data->centerP));
                curTriangle = curTriangle->nextElement;
            }
            curElement = curElement->nextElement;
        }
    }
}

void input(){
    //FILE *input = fopen("newTriangles.brs", "r");
    //FILE *input = fopen("input.txt", "r");
    FILE *input = fopen("input.brs", "r");
    //FILE *input = fopen("input_v1.brs", "r");
    if (input == NULL){
        printf("file not open\n");
    }

    fscanf(input, "%d", &pointsCount);
    for(int i = 0; i < pointsCount; ++i){
        point* tmpPoint = new point();
        fscanf(input, "%f %f %f", &tmpPoint->x, &tmpPoint->y, &tmpPoint->z);
        points.push_back(tmpPoint);
    }

    fscanf(input, "%d", &n);
    table = new HashTable(n);
    for(int i = 0; i < n; ++i){
        triangle* tmpTrinagle = new triangle();
        triangles.push_back(tmpTrinagle);
        int p1, p2, p3;
        fscanf(input, "%d %d %d", &p1, &p2, &p3);
        tmpTrinagle->p1 = p1;
        tmpTrinagle->p2 = p2;
        tmpTrinagle->p3 = p3;
        tmpTrinagle->centerP = -1;
        triangleEdge* triangleEdge1 = new triangleEdge(p1, p2, tmpTrinagle);
        triangleEdge* triangleEdge2 = new triangleEdge(p2, p3, tmpTrinagle);
        triangleEdge* triangleEdge3 = new triangleEdge(p3, p1, tmpTrinagle);
        table->add(triangleEdge1);
        table->add(triangleEdge2);
        table->add(triangleEdge3);
    }
    fclose(input);
}

void output(){
    FILE* out = fopen("newTriangles.brs", "w");
    int pointsCount = points.size();
    fprintf(out, "%d\n", pointsCount);
    for(int i = 0; i < pointsCount; ++i){
        fprintf(out, "%f %f %f\n", points[i]->x, points[i]->y, points[i]->z);
    }
    int trianglesCount = newTriangles.size();
    fprintf(out, "%d\n", trianglesCount);
    for(int i = 0; i < trianglesCount; ++i){
        fprintf(out, "%d %d %d\n", newTriangles[i]->p1, newTriangles[i]->p2, newTriangles[i]->p3);
    }

    fclose(out);
}

int main()
{
    input();
    createNewTriangles();
    output();

    return 0;
}

