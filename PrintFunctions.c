/*
 source file for print functions.
*/
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "cs2123p5.h"

/************************ prtTraversal **************************
void prtTraversal(Graph graph, int iAirportVertex, int indent)
Purpose:
   Prints all the successors of a specified airport in a depth 
   first manner with indentation.
Parameters:
   I  Graph graph        - a pointer to the graph of flights/airports
   I  int iAirportVertex - the number of the current airport
   I  int indent         - amount of indents to be printed
Returns:
    N/A
Notes:
   1.  This function uses the vertex successor list to print 
       the correct data.
   2.  A warning will be printed if the airport does not exist.
   3.  This function is recursive by a depth first manner.
 ****************************************************************/
void prtTraversal(Graph graph, int iAirportVertex, int indent)
{
    // do stuff here.
}

/************************ prtTraversalChron **************************
void prtTraversalChron(Graph graph, int iVertex, int iIndent, int iPrevArrTm2400)
Purpose:
   Prints all the successors of a specified airport in a depth 
   first manner which have a time reasonably after the preceding flight
   and with indentation.
Parameters:
   I  Graph graph        - a pointer to the graph of flights/airports
   I  int iAirportVertex - the number of the current airport
   I  int indent         - amount of indents to be printed
 * I  int iPreArrTm2400  - time that the last flight arrived at
Returns:
    N/A
Notes:
   1.  This function uses the vertex successor list to print 
       the correct data.
   2.  A warning will be printed if the airport does not exist.
   3.  This function is recursive by a depth first manner.
 ****************************************************************/
void prtTraversalChron(Graph graph, int iVertex, int iIndent, int iPrevArrTm2400)
{
    // do stuff
}

/************************** prtAll *******************************
void prtAll(Graph graph)
 Purpose:
    Print all the airports as is done in PRTONE.
 Parameters:
    I  Graph graph - a pointer to the graph of flights/airports
 Returns:
    N/A
 Notes:
    1.  A warning will be printed if the airport does not exist.
 ****************************************************************/
void prtAll(Graph graph)
{
    // prtOne for every airport
    int i;
    for(i = 0; i < graph->iNumVertices; i++)
    {
        prtOne(graph, i);
        printf("\n");
    }
}

/************************** prtOne *******************************
void prtOne(Graph graph, int iVertex) 
 Purpose:
    Prints the specified airport, the flightNr/szOrigin for flights 
    that have it as a destination (assume a maximum of 8 of them), 
    and prints the flightNr-szDest of flights that have it as an 
    origin.
 Parameters:
    I  Graph graph - a pointer to the graph of flights/airports
    I  int iVertex - the number of the current vertex
 Returns:
    N/A
 Notes:
    1.  This function uses the vertex successor list to print 
        the correct data.
    2.  A warning will be printed if the airport does not exist.
 ****************************************************************/
void prtOne(Graph graph, int iVertex)
{
    int i = 0;
    int j;
    
    // prtPredecessors for each flight
    i = prtPredecessors(graph, iVertex);
    j = 8 - i;
    
    // print the dots to separate predecessors from successors
    prtDots(j);
    
    // reset i
    i = 0;
    
    // prtSuccessors for each flight
    i = prtSuccessors(graph, iVertex);
    
    j = i;
    // if no successors were printed, print dots
    if (j = 0)
        prtDots(1);
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

/********************** prtPredecessors *************************
int  prtPredecessors(Graph graph, int iVertex)
 Purpose:
    Prints the predecessors for an airport.
 Parameters:
    I  Graph graph - a pointer to the graph of flights/airports
 *  I  int iVertex - number of the current vertex/airport
 Returns:
    N/A
 Notes:
    1.  This function uses the vertex predecessor list to print 
        the correct data.
    2.  A warning will be printed if the airport does not exist.
 ****************************************************************/
int prtPredecessors(Graph graph, int iVertex)
{
    // local variable declarations
    char szAirport[MAX_TOKEN]; 
    char szFlightNr[MAX_TOKEN];
    char szOrigin[MAX_TOKEN];
    EdgeNode *e;
    int i;
    
    // copy info from airport into local
    strcpy(szAirport, graph->vertexM[iVertex].szAirport);   
    printf("%2d %s ", iVertex, szAirport);
    
    // Traverse through the predecessor list for the specified airport`
    for (e = graph->vertexM[iVertex].predecessorList; e != NULL; e = e->pNextEdge)
    {
        // copy info to local variables for each different flight
        strcpy(szFlightNr, e->flight.szFlightNr);
        strcpy(szOrigin,e->flight.szOrigin);
        
        // print the airport's predecessors
        printf("%s/%s ", szFlightNr, szOrigin);
        
        i++;
    }
    return i;
}

/********************** prtSuccessors *************************
int prtSuccessors(Graph graph, int iVertex)
 Purpose:
    Prints the successors for an airport.
 Parameters:
    I  Graph graph - a pointer to the graph of flights/airports
 *  I  int iVertex - number of the current vertex/airport
 Returns:
    N/A
 Notes:
    1.  This function uses the vertex successor list to print 
        the correct data. It is used in prtOne function.
 ****************************************************************/
int prtSuccessors(Graph graph, int iVertex)
{
    // local variable declarations
    char szAirport[MAX_TOKEN]; 
    char szFlightNr[MAX_TOKEN];
    char szDest[MAX_TOKEN];
    EdgeNode *e;
    int i = 0;
    
    strcpy(szAirport, graph->vertexM[iVertex].szAirport);   
    printf("%2d %s ", iVertex, szAirport);
    
    for (e = graph->vertexM[iVertex].successorList; e != NULL; e = e->pNextEdge)
    {
     
        strcpy(szFlightNr, e->flight.szFlightNr);
        strcpy(szDest,e->flight.szDest);
        
        // print the airport's predecessors
        printf("%s-%s\n ", szFlightNr, szDest);
        i++;
    }
    return i;
}

/****************/
void prtDots(int iCount)
{
    while(iCount != 0)
    {
        printf("..... ");
        iCount--;
    }
}
