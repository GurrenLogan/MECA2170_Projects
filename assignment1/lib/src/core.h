#ifndef CORE.H
#define CORE.H

#include <stdlib.h>
#include <stdio.h>

#define l __LINE__
#define FLOAT_MIN -1000000000
#define FLOAT_MAX 1000000000

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

Msh* msh_alloc(size_t vertices_size,size_t triangles_size);
void msh_free(Msh* msh);
void init_state_free(InitState* init);

float find_max(float** points, size_t points_size, int i);
float find_min(float** points, size_t points_size, int i);

InitState* find_init_points(float** points,size_t points_size, float L);

Msh* delaunay_bowyer_watson(float** points);
Msh* delaunay_bowyer_watson_opt(float** points);

#endif