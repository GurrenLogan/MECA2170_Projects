#ifndef CORE.H
#define CORE.H

typedef struct accessiblesizes{
    int dim;
    int vertices_size;
    int triangle_indexes_size;
}Sizes;

typedef struct triangularmsh{
    Vertex** vertices;
    Sparse faces;
    Halfedge** halfedges;
}TriangularMesh;

typedef struct sparse{
    //according to the ... standard
}Sparse; 

typedef struct vertex{
    float* coord;
    int index;
    int halfedge_idx;
}Vertex;

typedef struct face{
    int index;
    int halfedge_idx;
}Face;

typedef struct halfedge{
    int opposite_idx;
    int next_idx;
    int prev_idx;
    int vertex_idx;
    int face_idx;
    int index;
}Halfedge;

void err_mess(int line);

void* msh_alloc();
void* vertex_alloc();
void* halfedge_alloc();
void* face_alloc();

void msh_free(TriangularMesh* msh_ptr);
void vertex_free(Vertex* vertex_ptr);
void halfedge_free(Halfedge* he_ptr);
void face_free(Face* face_ptr);

TriangularMesh* msh_create(float** vertices,int vertices_size, int** triangle_indexes, int triangle_indexes_size, int dim);
Vertex* vertex_create(int index, float* coords, int coords_size);
void vertex_add_halfedge(Vertex vertex, Halfedge halfedge);
Face* face_create(int index);
void face_add_halfedge(Face face, Halfedge halfedge);
Halfedge* halfedge_create();
void halfedge_add_index(int index);
void halfedge_add_vertex(Vertex vertex);
void halfedge_add_face(Face face);

TriangularMesh* delaunay_bowyer_watson(float** points);
TriangularMesh* delaunay_bowyer_watson_opt(float** points);

#endif