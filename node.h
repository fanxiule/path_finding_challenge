#include <algorithm>
#include <stdlib.h>
#include "Initializations.h"

#ifndef NODE_H
#define NODE_H

class Node
{
private:
    //private variables
    //information for current node
    int col_ind;   //node column index
    int row_ind;   //node row index
    double f;      //total cost, f = g + h
    double g = 0;  //cost from start to current node
    double h = 0;  //estimated cost from current to target node
    bool validity; //true - the node created is valid
    //information for parent node
    int parent_col;      //parent node column index
    int parent_row;      //parent node row index
    double parent_g = 0; //cost from start to parent cost
public:
    //private methods
    bool validPoint(int number);  //check if the col or row number is valid
    bool isHazard();              //true if the current and parent nodes are both in hazard zone
    bool dirChange(Node &parent); //true if the robot change direction
    void calTotalCost();          //calculate total cost f

public:
    //constructors and destructors
    Node(int row, int col);                 //constructor for a starting node
    Node(Node &parent_node, int direction); //constructor for non starting nodes
    Node(const Node &other);                //copy constructor
    Node &operator=(const Node &other);     //assignment operator
    ~Node();                                //destructor

    //setters and getters
    int getColIndex();                 //get column index of the node
    int getRowIndex();                 //get row index of the node
    double getCurrentCost();           //get g
    double getHeuristic();             //get h
    double getTotalCost();             //get f
    bool getValidity();                //get validity
    int getParentCol();                //get parent column index
    int getParentRow();                //get parent row index
    int getParentG();                  //get parent current cost
    void setParent(Node &parent_node); //set parent
    void setCurrentCost(double cost);  //set current cost g

    //public methods
    double calculateTime(Node &parent);        //calculate time from parent to current node
    void calCurrentCost(Node &parent);         //calculate g
    void calHeuristic(Waypoint &target_point); //calculate h based on target point
    void showInfo();                           //show node information
};
#endif /* NODE_H */