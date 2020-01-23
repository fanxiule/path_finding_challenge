#include <string>
#include <vector>
#include <iterator>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "node.h"

Node nodeLowestCost(std::vector<Node> &node_list, Waypoint &end)
{
    //std::cout << "breaker 1" << std::endl;
    Node node_least_cost = node_list[0]; //initialize node_least_cost with first element of node_list;
    node_least_cost.calHeuristic(end);
    //std::cout << "breaker 2" << std::endl;
    for (int i = 0; i < node_list.size(); i++)
    {
        //std::cout << "breaker 3" << std::endl;
        node_list[i].calHeuristic(end);
        //std::cout << "breaker 4" << std::endl;
        //node_list[i].showInfo(); //debug
        //std::cout << "############" << std::endl;
        if (node_list[i].getTotalCost() < node_least_cost.getTotalCost())
        {
            //std::cout << "breaker 5" << std::endl;
            node_least_cost = node_list[i];
            //std::cout << "breaker 6" << std::endl;
        }
    }

    //std::cout << "breaker 7" << std::endl;
    return node_least_cost;
}

bool inVector(Node &current_node, std::vector<Node> &node_list)
{
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
{
    Node return_node(0, 0);
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
{
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
{
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
{
    std::vector<Node> open_list;

    Node node_start(start.col_ind, start.row_ind);
    node_start.calHeuristic(end);
    open_list.push_back(node_start);

    while (open_list.size() > 0)
    {
        std::cout << "start of another loop" << std::endl;
        Node current_node = nodeLowestCost(open_list, end);
        std::cout << "breaker 8" << std::endl;
        int index = returnIndex(current_node, open_list);
        std::cout << "breaker 9" << std::endl;
        open_list.erase(open_list.begin() + index);
        std::cout << "breaker 10" << std::endl;

        if (current_node.getColIndex() == end.col_ind && current_node.getRowIndex() == end.row_ind)
        { //if the current node is the target waypoint
            closed_list.push_back(current_node);
            break;
        }

        std::cout << "parent node is: " << std::endl;
        current_node.showInfo();
        std::vector<Node> successors = createSuccessors(current_node);
        std::cout << "successor size " << successors.size() << std::endl;
        for (int i = 0; i < successors.size(); i++)
        {
            successors[i].calCurrentCost(current_node);
            successors[i].calHeuristic(end);
            successors[i].showInfo();
            if (inVector(successors[i], open_list))
            {
                Node node_in_open = returnInVector(successors[i], open_list);
                if (node_in_open.getCurrentCost() <= successors[i].getCurrentCost())
                {
                    continue;
                }
            }

            else if (inVector(successors[i], closed_list))
            {
                Node node_in_closed = returnInVector(successors[i], closed_list);
                if (node_in_closed.getCurrentCost() <= successors[i].getCurrentCost())
                {
                    continue;
                }
                open_list.push_back(successors[i]);
                closed_list.erase(closed_list.begin() + returnIndex(successors[i], closed_list));
            }

            else
            {
                successors[i].calHeuristic(end);
                open_list.push_back(successors[i]);
            }
        }

        current_node.showInfo();
        std::cout << std::endl;
        closed_list.push_back(current_node);
        std::cout << "open_list size " << open_list.size() << std::endl;
        std::cout << "closed_list size " << closed_list.size() << std::endl;
        std::cout << "!!!!" << std::endl;
    }
}

int main()
{
    Waypoint waypoint_start;
    waypoint_start.row_ind = waypoint_start.col_ind = 0;

    Waypoint waypoint_end;
    waypoint_end.row_ind = 5;
    waypoint_end.col_ind = 50;
    std::vector<Node> closed_list;
    Astar(waypoint_start, waypoint_end, closed_list);
    std::cout << closed_list.size() << std::endl;

    for (int i = 0; i < closed_list.size(); i++)
    {
        closed_list[i].showInfo();
        std::cout << std::endl;
    }
    //closed_list[0].showInfo();

    /*
    //for getting input
    std::string input;
    std::vector<int> x_pos, y_pos;
    std::vector<double> penalty;
    std::vector<Waypoint> waypoints;
    Waypoint start;
    start.col_ind = start.row_ind = start.penalty = 0;
    Waypoint end;
    end.col_ind = end.row_ind = 50;
    end.penalty = 0;
    waypoints.push_back(start);

    while (input != "exit")
    {
        std::cout << "Type input in the following form: x_coordinate y_coordiante penalty, or type exit to finish input" << std::endl;
        std::getline(std::cin, input);

        std::vector<std::string> info;
        boost::algorithm::split(info, input, boost::algorithm::is_any_of(" "));

        if (info.size() != 3)
        {
            std::cout << "Invalid input" << std::endl;
        }

        else
        {
            Waypoint waypoint_temp;
            waypoint_temp.col_ind = std::atoi(info[0].c_str());
            waypoint_temp.row_ind = std::atoi(info[1].c_str());
            waypoint_temp.penalty = std::atof(info[2].c_str());

            waypoints.push_back(waypoint_temp);
        }
    }
    waypoints.push_back(waypoint_end);
    */

    return 0;
}