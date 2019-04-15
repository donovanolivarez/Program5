/*
 deals with creation and insertion into the graph.
 */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "cs2123p5.h"


// return a new graph
Graph newGraph()
{
    // alloc space for a new graph
    Graph graph = malloc(sizeof(GraphImp));
    return graph;
}


void setNotVisited(Graph graph)
{
    // do stuff
}

/******************** addVertex *************************
 void addVertex(Graph g, char airport[])
 Pupose:
    add a vertex that does not exist.
 Parameters:
    Graph g        -   a pointer to the graph.
    char airport   -   string representing an airport name.
 Returns:
    None
 Notes:
 
 ********************************************************/
void addVertex(Graph g, char airport[])
{
    memcpy(g->vertexM[g->iNumVertices].szAirport, airport, 5);
    g->vertexM[g->iNumVertices].predecessorList = NULL;
    g->vertexM[g->iNumVertices].successorList = NULL;
    g->iNumVertices++;
}
