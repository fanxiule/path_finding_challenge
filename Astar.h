#ifndef ASTAR_H
#define ASTAR_H

#include "node.h"

Node nodeLowestCost(std::vector<Node> &node_list, Waypoint &end, int &index)
{                                        //return the node with lowest cost in a list
    Node node_least_cost = node_list[0]; //initialize node_least_cost with first element of node_list;
    node_least_cost.calHeuristic(end);   //calculate cost of the node
    for (int i = 0; i < node_list.size(); i++)
    {
        node_list[i].calHeuristic(end); //calculate cost of the node in the list
        if (node_list[i].getTotalCost() < node_least_cost.getTotalCost())
        {
            index = i;
            node_least_cost = node_list[i];
        }
    }
    return node_least_cost;
}

bool inVector(Node &current_node, std::vector<Node> &node_list)
{ //check if a node is in the list
    for (int i = 0; i < node_list.size(); i++)
    {
        if (current_node.getRowIndex() == node_list[i].getRowIndex() &&
            current_node.getColIndex() == node_list[i].getColIndex())
        {
            return true;
        }

        else
        {
            return false;
        }
    }
}

Node returnInVector(Node &current_node, std::vector<Node> &node_list)
{                           //return the node with the same row and col indices as the current_node from the list
    Node return_node(0, 0); //Initialize a node
    if (inVector(current_node, node_list))
    {
        for (int i = 0; i < node_list.size(); i++)
        {
            if (current_node.getRowIndex() == node_list[i].getRowIndex() &&
                current_node.getColIndex() == node_list[i].getColIndex())
            {
                return_node = node_list[i];
                break;
            }
        }
    }
    return return_node;
}

int returnIndex(Node current_node, std::vector<Node> &node_list)
{ //return index of the node which has the same row and col indices as current_node in the list
    int index;
    if (inVector(current_node, node_list))
    {
        for (index = 0; index < node_list.size(); index++)
        {
            if (current_node.getRowIndex() == node_list[index].getRowIndex() &&
                current_node.getColIndex() == node_list[index].getColIndex())
            {
                break;
            }
        }
    }
    return index;
}

std::vector<Node> createSuccessors(Node &current_node)
{ //create children of the current_node
    std::vector<Node> successors;
    Node node_up(current_node, 1);
    Node node_down(current_node, 2);
    Node node_left(current_node, 3);
    Node node_right(current_node, 4);

    if (node_up.getValidity() == true)
    {
        successors.push_back(node_up);
    }

    if (node_down.getValidity() == true)
    {
        successors.push_back(node_down);
    }

    if (node_left.getValidity() == true)
    {
        successors.push_back(node_left);
    }

    if (node_right.getValidity() == true)
    {
        successors.push_back(node_right);
    }

    return successors;
}

void Astar(Waypoint &start, Waypoint &end, std::vector<Node> &closed_list)
{ //Astar algorithm
    std::vector<Node> open_list;

    Node node_start(start.col_ind, start.row_ind);
    node_start.calHeuristic(end);
    open_list.push_back(node_start); //push the start node to open list

    while (open_list.size() > 0)
    {
        int index = 0;
        Node current_node = nodeLowestCost(open_list, end, index); //find the node with lowest cost from the open_list
        open_list.erase(open_list.begin() + index);                //remove such node from open_list

        if (current_node.getColIndex() == end.col_ind && current_node.getRowIndex() == end.row_ind)
        {                                        //if the current node is the target waypoint
            closed_list.push_back(current_node); //push current_node to closed_list
            break;
        }

        std::vector<Node> successors = createSuccessors(current_node); //create children for the current_node
        for (int i = 0; i < successors.size(); i++)
        {
            successors[i].calCurrentCost(current_node);
            successors[i].calHeuristic(end); //calculate child's cost

            if (inVector(successors[i], open_list))
            {                                                                 //if the child is also in open_list
                Node node_in_open = returnInVector(successors[i], open_list); //find the node from open_list
                if (node_in_open.getCurrentCost() <= successors[i].getCurrentCost())
                { //if the node in the list has lower cost than the child
                    continue;
                }
            }

            else if (inVector(successors[i], closed_list))
            {                                                                     //if the child is in closed_list
                Node node_in_closed = returnInVector(successors[i], closed_list); //find the node from closed_list
                if (node_in_closed.getCurrentCost() <= successors[i].getCurrentCost())
                { //if node in the closed_list has lower cost than the child
                    continue;
                }
                open_list.push_back(successors[i]); //move the child from closed_list to open_list
                closed_list.erase(closed_list.begin() + returnIndex(successors[i], closed_list));
            }

            else
            {
                successors[i].calHeuristic(end);
                open_list.push_back(successors[i]); //move the child to open_list
            }
        }

        closed_list.push_back(current_node); //move current_node to closed_list
    }
}
#endif /* ASTAR_H */