#include "core.h"

void err_mess(int line){fprintf(stderr, "Error: something went wrong at line %d\n", line);}

void trilist_init(TriIdxList* list){
    list->len = 0;
    list->memorycap = 32;
    list->data = malloc(sizeof(int*)*list->memorycap);
}
void trilist_append(TriIdxList* list, int* triangle){
    if (list->len >= list->memorycap) {
        list->memorycap *= 2;
        list->data = realloc(list->data, list->memorycap * sizeof(int*));
    }
    list->data[list->len++] = triangle;
}

void trilist_delete(TriIdxList* list, int i){
    if (i >= list->len) err_mess(l);exit(EXIT_FAILURE);

    for (size_t i = i; i < list->len - 1; i++) {
        list->data[i] = list->data[i + 1];
    }
    list->len--;

    if (list->len > 0 && list->len <= list->memorycap / 4) {
        size_t new_cap = list->memorycap / 2;
        if (new_cap < 4) new_cap = 4;
        list->data = realloc(list->data, new_cap * sizeof(int*));
        list->memorycap = new_cap;
    }
}

void pylist_init(PylikeList* list, size_t initial_capacity){
    list->len = 0;
    list->memorycap = initial_capacity;
    list->data = malloc(sizeof(int)*initial_capacity);
}
void pylist_append(PylikeList* list, int idx){
    if (list->len >= list->memorycap) {
        list->memorycap *= 2;
        list->data = realloc(list->data, list->memorycap * sizeof(int));
    }
    list->data[list->len++] = idx;
}
void pylist_delete(PylikeList* list, int i){
    if (i >= list->len || i == -1) err_mess(l);exit(EXIT_FAILURE);

    for (size_t i = i; i < list->len - 1; i++) {
        list->data[i] = list->data[i + 1];
    }
    list->len--;

    if (list->len > 0 && list->len <= list->memorycap / 4) {
        size_t new_cap = list->memorycap / 2;
        if (new_cap < 4) new_cap = 4;
        list->data = realloc(list->data, new_cap * sizeof(int));
        list->memorycap = new_cap;
    }
}

void trilist_free(TriIdxList* list){
    free(list->data);
    list->data = NULL;
    list->len = 0;
    list->memorycap = 0;
}

void pylist_free(PylikeList* list){
    free(list->data);
    list->data = NULL;
    list->len = 0;
    list->memorycap = 0;
}

void edges_init(Edges* edges, size_t size){
    edges->edges = malloc(sizeof(PylikeList*)*size);
    edges->size = size;
    edges->initial_capacity = 6;
}

void edges_append(Edges* edges,int i, int j){
    if(edges->edges[i] == NULL){edges->edges[i] = malloc(sizeof(PylikeList)); pylist_init(edges->edges[i],edges->initial_capacity);}
    if(edges->edges[j] == NULL){edges->edges[j] = malloc(sizeof(PylikeList)); pylist_init(edges->edges[j],edges->initial_capacity);}

    pylist_append(edges->edges[i],j);
    pylist_append(edges->edges[j],i);
}

int indexof(PylikeList* list, int elem){
    for(int i = 0;i<list->len;i++){if(list->data[i]==elem) return i;}
    return -1;
}

void edges_delete(Edges* edges,int i, int j){
    if(edges->edges[i] == NULL){err_mess(l);exit(EXIT_FAILURE);}
    if(edges->edges[j] == NULL){err_mess(l);exit(EXIT_FAILURE);}

    pylist_delete(edges->edges[i],indexof(edges->edges[i],j));
    pylist_delete(edges->edges[j],indexof(edges->edges[j],i));
}
void edges_free(Edges* edges){
    for(int i = 0; i< edges->size; i++){
        pylist_free(edges->edges[i]);
    }
    free(edges);
}

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
    float value = (-FLT_MAX);
    for(int j = 0; j < points_size;j++){
        if(points[j][i] > value){value = points[j][i];}
    }
    return value;
}

float find_min(float** points, size_t points_size, int i){
    float value = FLT_MAX;
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

    // for each point in pointList do // add all the points one at a time to the triangulation
    //     badTriangles := empty set


    //     for each triangle in triangulation do // first find all the triangles that are no longer valid due to the insertion
    //         if point is inside circumcircle of triangle
    //             add triangle to badTriangles


    //     polygon := empty set
    //     for each triangle in badTriangles do // find the boundary of the polygonal hole
    //         for each edge in triangle do
    //             if edge is not shared by any other triangles in badTriangles
    //                 add edge to polygon


    //     for each triangle in badTriangles do // remove them from the data structure
    //         remove triangle from triangulation


    //     for each edge in polygon do // re-triangulate the polygonal hole
    //         newTri := form a triangle from edge to point
    //         add newTri to triangulation


    // for each triangle in triangulation // done inserting points, now clean up
    //     if triangle contains a vertex from original super-triangle
    //         remove triangle from triangulation


    // return triangulation

Msh* delaunay_bowyer_watson(float** points, size_t points_size){
    //initialisation -> init points + add super triangles to mesh
    //add super triangles to triangles
    Edges* edges = malloc(sizeof(edges));
    TriIdxList* triangles = malloc(sizeof(TriIdxList));
    Trilist_init(triangles);
    //list_append() + add edges

    for(int i = 0; i<points_size;i++){

        TriIdxList* badtriangles = malloc(sizeof(TriIdxList));
        list_init(badtriangles);
        for(int j = 0; j<triangles->len;j++){
            //if point is inside circumcircle of triangle
            //        add triangle to badTriangles
        }

        //Work in progress

        list_free(badtriangles);
    }
    return NULL;
}
Msh* delaunay_bowyer_watson_opt(float** points, size_t points_size){
    return NULL;
}