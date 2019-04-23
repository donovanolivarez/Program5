/*********************************************************
 graph.c by Donovan Olivarez
 Pupose:
    This file holds functions necessary to the creation of the graph.
 Notes:
    
 *********************************************************/

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "cs2123p5.h"


/******************** newGraph *************************
 Graph newGraph()
 Pupose:
    creates and returns a new graph.
 Parameters:
 
 Returns:
    Graph graph  - a pointer to a new graph.
 Notes:
 
 ********************************************************/
Graph newGraph()
{
    // alloc space for a new graph
    Graph graph = malloc(sizeof(GraphImp));
    return graph;
}

/********************** setNotVisited *************************
void setNotVisited(Graph graph)
 Purpose:
    For each vertex in the graph, it sets the bVisited flag to FALSE.
 Parameters:
    I/O  Graph graph - a pointer to the graph of flights/airports
 Returns:
    N/A
 Notes:
    N/A
 ****************************************************************/
void setNotVisited(Graph graph)
{
    // loop through vertices, set all flags to false
    int i;
    for (i = 0; i < graph->iNumVertices; i++)
    {
        graph->vertexM[i].bVisited = FALSE;
    }
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
    // adds a new vertex to the graph.
    memcpy(g->vertexM[g->iNumVertices].szAirport, airport, 5);
    g->vertexM[g->iNumVertices].predecessorList = NULL;
    g->vertexM[g->iNumVertices].successorList = NULL;
    g->iNumVertices++;
}
