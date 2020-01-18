#include <algorithm>
#include <stdlib.h>
#include "Initializations.h"

#ifndef NODE_H
#define NODE_H

class Node
{
private:
    //private variables
    int col_ind;   //node column index
    int row_ind;   //node row index
    double f;      //total cost, f = g + h
    double g = 0;  //cost from start to current node
    double h = 0;  //estimated cost from current to target node
    bool validity; //true - the node created is valid
    Node *parent;  //points to parent of the current node

    //private methods
    bool validPoint(int number); //check if the col or row number is valid
    bool isHazard();             //true if the current and parent nodes are both in hazard zone
    bool dirChange();            //true if the robot change direction
    void calTotalCost();         //calculate total cost f

public:
    //constructors and destructors
    Node(int row, int col);                 //constructor for a starting node
    Node(Node &parent_node, int direction); //constructor for non starting nodes
    ~Node();                                //destructor

    //setters and getters
    int getColIndex();       //get column index of the node
    int getRowIndex();       //get row index of the node
    double getCurrentCost(); //get g
    double getHeuristic();   //get h
    double getTotalCost();   //get f
    bool getValidity();      //get validity
    Node *getParent();       //get parent node of the current node

    //public methods
    double calculateTime();                   //calculate time from parent to current node
    void calCurrentCost();                    //calculate g
    void calHeuristic(Waypoint target_point); //calculate h based on target point
    void showInfo();                          //show node information
};
#endif /* NODE_H */