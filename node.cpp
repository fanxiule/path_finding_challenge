#include "node.h"

Node::Node(int col, int row) //for a starting node
{
    if (validPoint(col) && validPoint(row))
    {
        col_ind = col;
        row_ind = row;
        parent = nullptr; //for start node, there is no parent
        calTotalCost();
        validity = true;
        std::cout << "Node created" << std::endl; //debug
    }

    else
    {
        std::cout << "Invalid node" << std::endl; //debug
        validity = false;
    }
}

Node::Node(Node &parent_node, int direction) //for all other nodes
{
    switch (direction)
    {
    case 1: //go up
    {
        if (validPoint(parent_node.row_ind + 5) && parent_node.getValidity() == true)
        {
            col_ind = parent_node.col_ind;
            row_ind = parent_node.row_ind + 5;
            parent = &parent_node;
            calTotalCost();
            validity = true;
            std::cout << "Node created" << std::endl; //debug
        }

        else
        {
            std::cout << "Invalid node" << std::endl; //debug
            validity = false;
        }
        break;
    }

    case 2: //go down
    {
        if (validPoint(parent_node.row_ind - 5) && parent_node.getValidity() == true)
        {
            col_ind = parent_node.col_ind;
            row_ind = parent_node.row_ind - 5;
            parent = &parent_node;
            calTotalCost();
            validity = true;
            std::cout << "Node created" << std::endl; //debug
        }

        else
        {
            std::cout << "Invalid node" << std::endl; //debug
            validity = false;
        }
        break;
    }

    case 3: //go left
    {
        if (validPoint(parent_node.col_ind - 5) && parent_node.getValidity() == true)
        {
            col_ind = parent_node.col_ind - 5;
            row_ind = parent_node.row_ind;
            parent = &parent_node;
            calTotalCost();
            validity = true;
            std::cout << "Node created" << std::endl; //debug
        }

        else
        {
            std::cout << "Invalid node" << std::endl; //debug
            validity = false;
        }
        break;
    }

    case 4: //go right
    {
        if (validPoint(parent_node.col_ind + 5) && parent_node.getValidity() == true)
        {
            col_ind = parent_node.col_ind + 5;
            row_ind = parent_node.row_ind;
            parent = &parent_node;
            calTotalCost();
            validity = true;
            std::cout << "Node created" << std::endl; //debug
        }

        else
        {
            std::cout << "Invalid node" << std::endl; //debug
            validity = false;
        }
        break;
    }

    default:
        std::cout << "Invalid node" << std::endl; //debug
        validity = false;
    }
}

Node::Node(const Node &other) : parent(nullptr)
{
    col_ind = other.col_ind;
    row_ind = other.row_ind;
    f = other.f;
    g = other.g;
    h = other.h;
    validity = other.validity;
    if (other.parent)
    {
        parent = new Node(*other.parent);
    }
}

Node &Node::operator=(const Node &other)
{
    if (this == &other)
    {
        return *this;
    }

    col_ind = other.col_ind;
    row_ind = other.row_ind;
    f = other.f;
    g = other.g;
    h = other.h;
    validity = other.validity;
    parent = nullptr;
    if (other.parent)
    {
        parent = new Node(*other.parent);
    }
    return *this;
}

Node::~Node()
{
    std::cout << "1" << std::endl;
    delete parent;
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
        {                                                      //if the parent is also in hazard zone
            std::cout << "moving in hazard zone" << std::endl; //debug
            return true;                                       //moving from parent to current is hazard
        }

        else
        {
            std::cout << "not moving in hazard zone" << std::endl; //debug
            return false;
        }
    }

    else
    {
        std::cout << "not moving in hazard zone" << std::endl; //debug
        return false;
    }
}

bool Node::dirChange()
{
    if (parent->parent == nullptr) //if the parent node is a starting node
    {
        std::cout << "No direction change" << std::endl; //debug
        return false;
    }

    else
    {
        if ((col_ind == parent->col_ind && parent->col_ind == parent->parent->col_ind) ||
            (row_ind == parent->row_ind && parent->row_ind == parent->parent->row_ind))
        {                                                    //if current node, its parent node and its parent's parent node are on the same row/col
            std::cout << "No direction change" << std::endl; //debug
            return false;
        }

        else
        {
            std::cout << "Direction changed" << std::endl; //debug
            return true;
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

Node *Node::getParent()
{
    return parent;
}

void Node::setParent(Node &parent_node)
{
    parent = &parent_node;
}

void Node::setCurrentCost(double cost)
{
    g = cost;
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
    {                                                       //if the robot changes its direction, extra 0.5 sec is needed
        std::cout << "additional time needed" << std::endl; //debug
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
    h = NON_HAZARD_TIME * abs((target_point.col_ind - col_ind) / 5) + NON_HAZARD_TIME * abs((target_point.row_ind - row_ind) / 5);
    //use NON_HAZARD_TIME to estimate time left to reach target_point
    calTotalCost();
}

void Node::showInfo()
{
    if (validity == true)
    {
        std::cout << "The node is valid with col index " << col_ind << " and row index " << row_ind << std::endl;
        std::cout << "The node's current cost g is " << g << ", heuristic h is " << h << ", and total cost f is " << f << std::endl;
        if (parent != nullptr)
        {
            std::cout << "The parent node has col index " << parent->col_ind << " and row index " << parent->row_ind << std::endl;
        }

        else
        {
            std::cout << "The parent node is NULL" << std::endl;
        }
    }

    else
    {
        std::cout << "The node is invalid" << std::endl;
    }
}