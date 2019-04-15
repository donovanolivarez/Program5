/*
 source file for print functions.
*/
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "cs2123p5.h"

void prtTraversal(Graph graph, int iAirportVertex, int indent)
{
    // do stuff here.
}

void prtTraversalChron(Graph graph, int iVertex, int iIndent, int iPrevArrTm2400)
{
    // do stuff
}

void prtAll(Graph graph)
{
    // do stuff
}

void prtOne(Graph graph, int iVertex)
{
    // do stuff
}
/********************** prtFlightsByOrigin ************************
 void prtFlightsByOrigin(Graph graph)
 Purpose:
    for each airport, prints out the flights where it is the origin.
 Parameters:
    I  Graph graph - a pointer to the graph.
 Returns:
    Nothing
 Notes:
    Uses the vertex successor list to print correct data.
 ****************************************************************/
void prtFlightsByOrigin(Graph graph)
{
    // local variables to hold flight information 
    int i,j, iDeparture, iArrival, iDuration, iFirst, iZoneChange;
    char szAirport[MAX_TOKEN]; 
    char szFlightNr[MAX_TOKEN];
    char szDest[MAX_TOKEN];
    EdgeNode *p;
    
    for (i = 0; i < graph->iNumVertices; i++)
    {
        
        // represents that we are at the first node in the list
        iFirst = TRUE;
        
        for (p = graph->vertexM[i].successorList; p != NULL; p = p->pNextEdge)
        {

            // copy info to local variables
            strcpy(szAirport, graph->vertexM[i].szAirport);
            strcpy(szFlightNr, p->flight.szFlightNr);
            strcpy(szDest,p->flight.szDest);
            iDeparture = p->flight.iDepTm2400;
            iDuration = p->flight.iDurationMins;
            iZoneChange = p->flight.iZoneChange;
            iArrival = calcArr2400(iDeparture, iDuration, iZoneChange);
    
            // if first node in list, print out with appropriate format
            if (iFirst == TRUE)
                printf("%-s %s %s %4d %4d %4d\n", szAirport, szFlightNr,szDest,iDeparture, iArrival, iDuration );
            
            // if not first node, print out with appropriate format
            if (iFirst == FALSE)
                printf("%6s %s %4d %4d %4d\n", szFlightNr,szDest,iDeparture, iArrival,iDuration );
            
            iFirst = FALSE;   
        }
    }
}
/********************** prtFlightsByDest ************************
 void prtFlightsByDest(Graph graph)
 Purpose:
    for each airport, prints out the flights where it is the destination.
 Parameters:
    I   Graph graph - a pointer to the graph.
 Returns:
    Nothing
 Notes:
    Uses the vertex predecessor list to print correct data.
 ****************************************************************/
void prtFlightsByDest(Graph graph)
{   
    int i, iFirst, iDeparture, iDuration, iZoneChange, iArrival;
    char szAirport[MAX_TOKEN];
    char szFlightNr[MAX_TOKEN];
    char szOrigin[MAX_TOKEN];
    EdgeNode *p;
    
    // iterate through the vertices.
    for (i = 0; i < graph->iNumVertices; i++)
    {
        // we are at the first node in the list at this point.
        iFirst = TRUE;
        
        // iterate through the nodes of the predecessor list.
        for (p = graph->vertexM[i].predecessorList; p != NULL; p = p->pNextEdge)
        {
            // copy info to local variables
            strcpy(szAirport, graph->vertexM[i].szAirport);
            strcpy(szFlightNr, p->flight.szFlightNr);
            strcpy(szOrigin,p->flight.szOrigin);
            iDeparture = p->flight.iDepTm2400;
            iDuration = p->flight.iDurationMins;
            iZoneChange = p->flight.iZoneChange;
            iArrival = calcArr2400(iDeparture, iDuration, iZoneChange);
            
            if (iFirst == TRUE)
                printf("%-s %3s %3s %4d %4d %3d\n", szAirport, szOrigin,szFlightNr, iDeparture, iArrival, iDuration );
            
            if (iFirst == FALSE)
                printf("%7s %3s %4d %4d %3d\n", szOrigin,szFlightNr,iDeparture, iArrival,iDuration );
            
            iFirst = FALSE;
        }
    }
}


