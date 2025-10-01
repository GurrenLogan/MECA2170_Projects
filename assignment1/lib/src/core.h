#ifndef CORE.H
#define CORE.H

#include <stdlib.h>
#include <stdio.h>

#define l __LINE__

void err_mess(int line);

typedef struct msh{
    float** vertices;
    size_t vertices_size;
    size_t dim;
    int** triangles;
    size_t triangles_size;
}Msh;

typedef struct initstate{
    int* starting_points;
    int* infinite_points;
}InitState;

Msh* msh_alloc(size_t vertices_size,size_t dim,size_t triangles_size);
void msh_free(Msh* msh);

int* find_supertriangle(float** points);
InitState* find_init_points(float** points,int points_size, int dim, float L);

Msh* delaunay_bowyer_watson(float** points);
Msh* delaunay_bowyer_watson_opt(float** points);

#endif