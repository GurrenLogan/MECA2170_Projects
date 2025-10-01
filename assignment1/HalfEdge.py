import sys
import math
#import gmsh
import numpy as np
from typing import List

# Vertices is define such as [Vertex0, ...] so j=0 => vertex0 and so on
# t[i] = j => vertexj gives the index of the node of the i-th vertex of the triangle
# vertexj.halfedge => index 
# edge of t[i] and t[i+1%3] => stock that in a sparse matrix
# face.index = j and face.halfedge = index

class TriangularMesh:

    def __init__(self, vertices : List[List[3]], triangles : List[int[3]]):

        self.vertices = []
        j = 0
        for v in vertices :
            self.vertices.append(Vertex(v[0],v[1],v[2],j,None))
            j = j+1

        self.faces = []
        self.halfedges = []
        edges = {}
        j = 0
        index = 0

        for t in triangles :
            indices = [index, index+1, index + 2]
            index = index + 3
            for i in range (3) :
                self.vertices[t[i]].halfedge = indices[i]
                self.halfedges.append(Halfedge(indices[(i+1)%3], None, indices[(i+2)%3],t[i], j, indices[i]))
                edges[(t[i], t[(i+1)%3])] = indices[i]
            self.faces.append(Face(j,indices[0]))
            j = j+1

        for e,ind1 in edges.items() :
            if (e[1],e[0]) in edges :
                ind2 = edges[(e[1],e[0])]
                self.halfedges[ind1].opposite = ind2
                self.halfedges[ind2].opposite = ind1

class Vertex:
    def __init__(self, x=0, y=0, z=0, index : int = None, halfedge : int = None):
        self.x = x
        self.y = y
        self.z = z
        self.index = index
        self.halfedge = halfedge

class Face:
    def __init__(self, index : int = None, halfedge : int = None):
        self.index = index
        # halfedge going ccw around this facet.
        self.halfedge = halfedge

class Halfedge:
    def __init__(self, next : int = None, opposite : int = None, prev : int = None, vertex : Vertex = None, facet : int = None, index : int = None):
        self.opposite = opposite
        self.next = next
        self.prev = prev
        self.vertex = vertex
        self.facet = facet
        self.index = index
