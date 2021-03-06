#include "node.h"

Node::Node(int col, int row) //for a starting node
{
    if (validPoint(col) && validPoint(row))
    {
        col_ind = col;
        row_ind = row;
        parent_col = col_ind; //for starting nodes, set parent column (row)
        parent_row = row_ind; //index equal to current column (row) index
        calTotalCost();
        validity = true;
    }

    else
    {
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
            parent_col = parent_node.col_ind;
            parent_row = parent_node.row_ind;
            parent_g = parent_node.g;
            calTotalCost();
            validity = true;
        }

        else
        {
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
            parent_col = parent_node.col_ind;
            parent_row = parent_node.row_ind;
            parent_g = parent_node.g;
            calTotalCost();
            validity = true;
        }

        else
        {
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
            parent_col = parent_node.col_ind;
            parent_row = parent_node.row_ind;
            parent_g = parent_node.g;
            calTotalCost();
            validity = true;
        }

        else
        {
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
            parent_col = parent_node.col_ind;
            parent_row = parent_node.row_ind;
            parent_g = parent_node.g;
            calTotalCost();
            validity = true;
        }

        else
        {
            validity = false;
        }
        break;
    }

    default:
        validity = false;
    }
}

Node::Node(const Node &other) : col_ind(other.col_ind),
                                row_ind(other.row_ind),
                                f(other.f),
                                g(other.g),
                                h(other.h),
                                validity(other.validity),
                                parent_col(other.parent_col),
                                parent_row(other.parent_row),
                                parent_g(other.parent_g)

{
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
    parent_col = other.parent_col;
    parent_row = other.parent_row;
    parent_g = other.parent_g;
    return *this;
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
        if ((std::find(hazard_index, hazard_index + array_size, parent_row) != hazard_index + array_size) &&
            (std::find(hazard_index, hazard_index + array_size, parent_col) != hazard_index + array_size))
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

bool Node::dirChange(Node &parent)
{
    if (parent.col_ind == parent.parent_col && parent.row_ind == parent.parent_col) //if the parent node is a starting node
    {
        return false;
    }

    else
    {
        if (col_ind == parent.col_ind && parent.col_ind == parent.parent_col)
        { //current node, parent node and parent's parent node on the same column
            if ((row_ind > parent.row_ind && parent.row_ind > parent.parent_row) ||
                (row_ind < parent.row_ind && parent.row_ind < parent.parent_row) ||
                parent.row_ind == parent.parent_row) //move in the same column or the parent node is the start node
            {
                return false;
            }

            else
            {
                return true;
            }
        }

        if (row_ind == parent.row_ind && parent.row_ind == parent.parent_row)
        { //current node, parent node and parent's parent node on the same row
            if ((col_ind > parent.col_ind && parent.col_ind > parent.parent_col) ||
                (col_ind < parent.col_ind && parent.col_ind < parent.parent_col) ||
                parent.col_ind == parent.parent_col) //move in the same row or the parent node is the start node
            {
                return false;
            }

            else
            {
                return true;
            }
        }

        else
        {
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

int Node::getParentCol()
{
    return parent_col;
}

int Node::getParentRow()
{
    return parent_row;
}

int Node::getParentG()
{
    return parent_g;
}

void Node::setParent(Node &parent_node)
{
    parent_col = parent_node.col_ind;
    parent_row = parent_node.row_ind;
    parent_g = parent_node.g;
}

void Node::setCurrentCost(double cost)
{
    g = cost;
}

double Node::calculateTime(Node &parent)
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

    if (dirChange(parent))
    { //if the robot changes its direction, extra 0.5 sec is needed
        time += CHANGE_DIR_TIME;
    }

    return time;
}

void Node::calCurrentCost(Node &parent)
{
    g = parent_g + calculateTime(parent);
    calTotalCost();
}

void Node::calHeuristic(Waypoint &target_point)
{
    h = HEURISTIC_TIME * abs((target_point.col_ind - col_ind) / 5) + HEURISTIC_TIME * abs((target_point.row_ind - row_ind) / 5);
    //use HEURISTIC_TIME to estimate time left to reach target_point
    calTotalCost();
}

void Node::showInfo()
{
    if (validity == true)
    {
        std::cout << "The node is valid with col index " << col_ind << " and row index " << row_ind << std::endl;
        std::cout << "The node's current cost g is " << g << ", heuristic h is " << h << ", and total cost f is " << f << std::endl;
        std::cout << "The parent node with col index " << parent_col << " and row index " << parent_row << std::endl;
        std::cout << "The parent node's current cost g is " << parent_g << std::endl;
    }

    else
    {
        std::cout << "The node is invalid" << std::endl;
    }
}