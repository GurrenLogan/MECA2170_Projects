#ifndef CORE.H
#define CORE.H

#include <stdlib.h>
#include <stdio.h>
#include <float.h>

#define l __LINE__

void err_mess(int line);

typedef struct msh{
    float** vertices;
    size_t vertices_size;
    int** triangles;
    size_t triangles_size;
}Msh;

typedef struct initstate{
    float** starting_points;
    float** infinite_points;
}InitState;

typedef struct triidxlist{
    size_t len;
    size_t memorycap;
    int** data;
}TriIdxList;

typedef struct pylikelist{
    size_t len;
    size_t memorycap;
    int* data;
}PylikeList;

typedef struct edges{
    int** edges;
    size_t size;
    size_t initial_capacity;
}Edges;

void trilist_init(TriIdxList* list);
void trilist_append(TriIdxList* list, int* triangle);
void trilist_delete(TriIdxList* list, int i);
void trilist_free(TriIdxList* list);

void pylist_init(PylikeList* list, size_t initial_capacity);
void pylist_append(PylikeList* list, int idx);
void pylist_delete(PylikeList* list, int i);
void pylist_free(PylikeList* list);

void edges_init(Edges* edges,size_t size);
void edges_append(Edges* edges,int i, int j);
void edges_delete(Edges* edges,int i, int j);
void edges_free(Edges* edges);

Msh* msh_alloc(size_t vertices_size,size_t triangles_size);
void msh_free(Msh* msh);
void init_state_free(InitState* init);

float find_max(float** points, size_t points_size, int i);
float find_min(float** points, size_t points_size, int i);

InitState* find_init_points(float** points,size_t points_size, float L);

Msh* delaunay_bowyer_watson(float** points, size_t points_size);
Msh* delaunay_bowyer_watson_opt(float** points, size_t points_size);

#endif