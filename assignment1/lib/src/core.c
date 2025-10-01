#include "core.h"

void err_mess(int line){fprintf(stderr, "Error: something went wrong at line %d\n", line);}

Msh* msh_alloc(size_t vertices_size, size_t dim, size_t triangles_size){
    Msh* msh = malloc(sizeof(Msh));
    if(msh == NULL){err_mess(l); exit(EXIT_FAILURE);}

    msh->dim = dim;
    msh->triangles_size = triangles_size;
    msh->vertices_size = vertices_size;

    msh->vertices = malloc(vertices_size*sizeof(float*));
    if(msh->vertices == NULL){free(msh);err_mess(l); exit(EXIT_FAILURE);}

    for(int i = 0;i<vertices_size;i++){
        msh->vertices[i] = malloc(sizeof(float)*dim);
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

InitState* find_init_points(float** points,int points_size, int dim, float L){
    if(L<=0){err_mess(l);exit(EXIT_FAILURE);}

    int idx_max = 0, idx_min = 0;

    float* best_point_min = points[0];
    float* best_point_max = points[0];

    for(int i = 1; i<points_size;i++){
        int is_max = 1;
        int is_min = 1;
        for(int j = 0; j<dim;j++){
            if(points[i][j]<best_point_max[j]){is_max = 0;}
            if(points[i][j]>best_point_min[j]){is_min = 0;}
        }
        if(is_max){idx_max = i; best_point_max = points[i];}
        if(is_min){idx_min = i; best_point_min = points[i];}
    }
    //Work in progress....
}

Msh* delaunay_bowyer_watson(float** points){
    return NULL;
}
Msh* delaunay_bowyer_watson_opt(float** points){
    return NULL;
}