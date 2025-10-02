#include "core.h"

void err_mess(int line){fprintf(stderr, "Error: something went wrong at line %d\n", line);}

Msh* msh_alloc(size_t vertices_size, size_t triangles_size){
    Msh* msh = malloc(sizeof(Msh));
    if(msh == NULL){err_mess(l); exit(EXIT_FAILURE);}

    msh->triangles_size = triangles_size;
    msh->vertices_size = vertices_size;

    msh->vertices = malloc(vertices_size*sizeof(float*));
    if(msh->vertices == NULL){free(msh);err_mess(l); exit(EXIT_FAILURE);}

    for(int i = 0;i<vertices_size;i++){
        msh->vertices[i] = malloc(sizeof(float)*2);
        if(msh->vertices == NULL){
            for(int j = 0; j<i;j++){free(msh->vertices[j]);}
            free(msh->vertices);free(msh);err_mess(l); exit(EXIT_FAILURE);}
    }

    msh->triangles = malloc(sizeof(int*)*triangles_size);
    if(msh->triangles == NULL){
            for(int j = 0; j<vertices_size;j++){free(msh->vertices[j]);}
            free(msh->vertices);free(msh);err_mess(l); exit(EXIT_FAILURE);}

    for(int i = 0;i<vertices_size;i++){
        msh->triangles[i] = malloc(3*sizeof(int));
        if(msh->triangles[i] == NULL){
            for(int j = 0; j<i;j++){free(msh->triangles[j]);}
            free(msh->triangles);
            for(int j = 0; j<vertices_size;j++){free(msh->vertices[j]);}
            free(msh->vertices);free(msh);err_mess(l); exit(EXIT_FAILURE);}
    }

    return msh;
}

void msh_free(Msh* msh){
    for(int j = 0; j<msh->triangles_size;j++){free(msh->triangles[j]);}
    free(msh->triangles);
    for(int j = 0; j<msh->vertices_size;j++){free(msh->vertices[j]);}
    free(msh->vertices);free(msh);
}

void init_state_free(InitState* init){
    for(int i = 0;i<4;i++){
        free(init->infinite_points[i]);
    }
    free(init->infinite_points);
    free(init->starting_points[0]);
    free(init->starting_points[1]);
    free(init->starting_points);
    free(init);
}

float find_max(float** points, size_t points_size, int i){
    float value = FLOAT_MIN;
    for(int j = 0; j < points_size;j++){
        if(points[j][i] > value){value = points[j][i];}
    }
    return value;
}

float find_min(float** points, size_t points_size, int i){
    float value = FLOAT_MAX;
    for(int j = 0; j < points_size;j++){
        if(points[j][i] < value){value = points[j][i];}
    }
    return value;
}

InitState* find_init_points(float** points,size_t points_size, float L){
    if(L<=0){err_mess(l);exit(EXIT_FAILURE);}

    float* min_array = malloc(2*sizeof(float));
    float* max_array = malloc(2*sizeof(float));
    
    for(int i = 0; i<2;i++){
        min_array[i] = find_min(points,points_size,i);
        max_array[i] = find_max(points,points_size,i);
    }

    InitState* init = malloc(sizeof(InitState));

    init->starting_points = malloc(sizeof(float*)*2);
    init->infinite_points = malloc(sizeof(float*)*4);

    init->starting_points[0] = min_array;
    init->starting_points[1] = max_array;

    for(int i = 0; i<4;i++){
        init->infinite_points[i] = malloc(sizeof(float)*2);
    }

    init->infinite_points[0][0] = min_array[0] - L;
    init->infinite_points[0][1] = min_array[1] - L;
    init->infinite_points[1][0] = max_array[0] + L;
    init->infinite_points[1][1] = min_array[1] - L;
    init->infinite_points[2][0] = max_array[0] + L;
    init->infinite_points[2][1] = max_array[1] + L;
    init->infinite_points[3][0] = min_array[0] - L;
    init->infinite_points[3][1] = max_array[1] + L;

    return init;
}

Msh* delaunay_bowyer_watson(float** points){
    return NULL;
}
Msh* delaunay_bowyer_watson_opt(float** points){
    return NULL;
}