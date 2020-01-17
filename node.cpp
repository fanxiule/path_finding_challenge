#include "node.h"

Node::Node(int col, int row) //for a starting node
{
    if (validPoint(col) && validPoint(row))
    {
        col_ind = col;
        row_ind = row;
        parent = nullptr; //for start node, there is no parent
        validity = true;
        std::cout << "Node created" << std::endl; //debug
    }

    else
    {
        std::cout << "Invalid node" << std::endl;
        validity = false;
    }
}

Node::Node(Node &parent_node, int direction) //for all other nodes
{
    switch (direction)
    {
    case 1: //go up
    {
        if (validPoint(parent_node.row_ind + 1))
        {
            col_ind = parent_node.col_ind;
            row_ind = parent_node.row_ind + 1;
            parent = &parent_node;
            validity = true;
            std::cout << "Node created" << std::endl; //debug
        }

        else
        {
            std::cout << "Invalid node" << std::endl;
            validity = false;
        }
        break;
    }

    case 2: //go down
    {
        if (validPoint(parent_node.row_ind - 1))
        {
            col_ind = parent_node.col_ind;
            row_ind = parent_node.row_ind - 1;
            parent = &parent_node;
            validity = true;
        }

        else
        {
            std::cout << "Invalid node" << std::endl;
            validity = false;
        }
        break;
    }

    case 3: //go left
    {
        if (validPoint(parent_node.col_ind - 1))
        {
            col_ind = parent_node.col_ind - 1;
            row_ind = parent_node.row_ind;
            parent = &parent_node;
            validity = true;
        }

        else
        {
            std::cout << "Invalid node" << std::endl;
            validity = false;
        }
        break;
    }

    case 4: //go left
    {
        if (validPoint(parent_node.col_ind + 1))
        {
            col_ind = parent_node.col_ind + 1;
            row_ind = parent_node.row_ind;
            parent = &parent_node;
            validity = true;
        }

        else
        {
            std::cout << "Invalid node" << std::endl;
            validity = false;
        }
        break;
    }

    default:
        std::cout << "Invalid node" << std::endl;
        validity = false;
    }
}

Node::~Node()
{
}

bool Node::validPoint(int number)
{
    if (number % 5 == 0 && number >= 0 && number <= 50)
    {
        return true;
    }

    else
    {
        return false;
    }
}

bool Node::isHazard()
{
    int hazard_index[5] = {15, 20, 25, 30, 35};
    int array_size = sizeof(hazard_index) / sizeof(hazard_index[0]);
    //if node row_ind and col_ind are in hazard_index array,
    //the node is in hazard zone

    if ((std::find(hazard_index, hazard_index + array_size, row_ind) != hazard_index + array_size) &&
        (std::find(hazard_index, hazard_index + array_size, col_ind) != hazard_index + array_size))
    { //if the current node is in hazard zone
        if ((std::find(hazard_index, hazard_index + array_size, parent->row_ind) != hazard_index + array_size) &&
            (std::find(hazard_index, hazard_index + array_size, parent->col_ind) != hazard_index + array_size))
        {                //if the parent is also in hazard zone
            return true; //moving from parent to current is hazard
        }

        else
        {
            return false;
        }
    }

    else
    {
        return false;
    }
}

bool Node::dirChange()
{
    if (parent->parent == nullptr) //if the parent node is a starting node
    {
        return false;
    }

    else
    {
        if ((col_ind == parent->col_ind && parent->col_ind == parent->parent->col_ind) ||
            (row_ind == parent->row_ind && parent->row_ind == parent->parent->row_ind))
        { //if current node, its parent node and its parent's parent node are on the same row/col
            return true;
        }

        else
        {
            return false;
        }
    }
}

void Node::calTotalCost()
{
    f = g + h;
}

int Node::getColIndex()
{
    return col_ind;
}

int Node::getRowIndex()
{
    return row_ind;
}

double Node::getCurrentCost()
{
    return g;
}

double Node::getHeuristic()
{
    return h;
}

double Node::getTotalCost()
{
    return f;
}

bool Node::getValidity()
{
    return validity;
}

double Node::calculateTime()
{
    double time; //in seconds
    if (isHazard())
    {
        time = HAZARD_TIME; //1 m/s in hazard zone -> 5 sec to travel 5 m
    }

    else
    {
        time = NON_HAZARD_TIME; //2.5 m/s in non hazard zone -> 2s to travel 5m
    }

    if (dirChange())
    { //if the robot changes its direction, extra 0.5 sec is needed
        time += CHANGE_DIR_TIME;
    }

    return time;
}

void Node::calCurrentCost()
{
    g = parent->g + calculateTime();
    calTotalCost();
}

void Node::calHeuristic(Waypoint target_point)
{
    h = NON_HAZARD_TIME * abs(target_point.col_ind - col_ind) + NON_HAZARD_TIME * abs(target_point.row_ind - row_ind);
    //use NON_HAZARD_TIME to estimate time left to reach target_point
    calTotalCost();
}