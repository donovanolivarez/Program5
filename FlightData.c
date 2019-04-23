/*
 functions that use/manipulate the flight data.
 */
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "cs2123p5.h"

EdgeNode * insertOrderedLL(EdgeNode **list, Flight flight, int iOrigin, int iDest);
EdgeNode *searchLL(EdgeNode *list, char flightNr[], EdgeNode **ppPrecedes);
EdgeNode *allocNodeLL(EdgeNode *list, Flight flight);

/******************** calcArr2400 *******************
 int calcArr2400(int iDepTime2400, int iDurationMins, int iZoneChange)
 Purpose:
 *  Calculate arrival of a flate given its departure time, zone change, and duration
 Parameters:
 *  I int iDepTime2400 - departure time
 *  I int iDurationMins - flight length
 *  I int iZoneChange - how many zones to roll back/forth time?
 Returns:
 *  int Arrival time
 Notes:
 *  None
 *****************************************************/
int calcArr2400(int iDepTime2400, int iDurationMins, int iZoneChange) 
{
    // get the hours and minutes of iDepTime2400, calculate total minutes since midnight.
    int iHours = iDepTime2400 / 100;
    int iMinutes = iDepTime2400 % 100;
    int iTotalMinutes = iHours * 60 + iMinutes;
    
    // get zone change in minutes.
    int iZoneChangeMins = (iZoneChange * 60);
    
    // calculate iArrival and convert from minutes to a 2400 time.
    int iArrival = iTotalMinutes + iDurationMins + iZoneChangeMins;
    int iArrHours2400 = iArrival/60 * 100;
    int iArrMins2400 = iArrival % 60;
    iArrival = iArrHours2400 + iArrMins2400;
    
    return iArrival;    
}


/**************** findAirport ******
 int findAirport(Graph g, char airport[])
 Purpose:
 *  Find an airport by name
 Parameters:
 *  I Graph g - graph to search
 *  I char airport[] - airport to search for
 Returns:
 *  Index of airport or -1 if it couldn't find it
 Notes:
 *  None
 */

int findAirport(Graph g, char airport[]){
    int i;
    for(i = 0; i < g->iNumVertices; i++){
        Vertex V = g->vertexM[i];
        if(strcmp(V.szAirport, airport) == 0){
            return i;
        }
    }
    return -1;
}


int insertFlight(Graph graph, Flight flight)
{
    // get origin points
    int origin, dest;
    origin = findAirport(graph, flight.szOrigin);
    dest = findAirport(graph, flight.szDest);
    
    // insert flights in correct order.
    insertOrderedLL(&graph->vertexM[origin].successorList, flight, origin, dest);
    insertOrderedLL(&graph->vertexM[dest].predecessorList, flight, origin, dest);
}

    


EdgeNode * insertOrderedLL(EdgeNode **list, Flight flight, int iOrigin, int iDest)
{
    // pPrecedes gets set to NULL in searchLL if list is empty.
    EdgeNode *pNew, *pFind, *pPrecedes;
    pFind = searchLL(*list, flight.szFlightNr, &pPrecedes);
    
    // if duplicate is found
    if (pFind != NULL)
    {
        return NULL;
    }
    
    // create new edge with flight info.
    pNew = allocNodeLL(*list, flight);
    pNew->iOriginVertex = iOrigin;
    pNew->iDestVertex = iDest;
    
    // edge to be inserted at beginning of the list if pPrecedes is NULL
    if (pPrecedes == NULL)
    {
        pNew->pNextEdge = *list;
        *list = pNew;
    }
    else
    {
        pNew->pNextEdge = pPrecedes->pNextEdge;
        pPrecedes->pNextEdge = pNew;
    }
    return pNew;
}


EdgeNode *searchLL(EdgeNode *list, char flightNr[], EdgeNode **ppPrecedes)
{
    EdgeNode *p;
    // NULL used when list is empty or when we need to insert at beginning.
    *ppPrecedes = NULL;
    // traverse though the list looking for where the key belongs or the end of the list.
    
    for (p = list; p != NULL; p = p->pNextEdge)
    {
        // found flight in list already.
        if (strcmp(flightNr, p->flight.szFlightNr) == 0)
            return p;
        if (strcmp(flightNr, p->flight.szFlightNr) < 0)
            return NULL;
        
        *ppPrecedes = p;
    }
    
    return NULL;
}


EdgeNode *allocNodeLL(EdgeNode *list, Flight flight)
{
    EdgeNode *pNew;
    pNew = (EdgeNode *) malloc(sizeof(EdgeNode));
    
    if (pNew == NULL)
        errExit("could not allocate nodeLL");
    
    
    pNew->flight = flight;
    pNew->pNextEdge = NULL;
    
    return pNew;
}
