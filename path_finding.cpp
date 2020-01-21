#include <string>
#include <vector>
#include <iterator>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "node.h"

Node *nodeLowestCost(std::vector<Node> &node_list)
{
    Node *pNode_least_cost;
    for (int i = 0; i < node_list.size(); i++)
    {
        if (i == 0)
        {
            pNode_least_cost = &node_list[i];
        }

        else
        {
            if (node_list[i].getTotalCost() < pNode_least_cost->getTotalCost())
            {

                pNode_least_cost = &node_list[i];
            }
        }
    }

    return pNode_least_cost;
}

bool inVector(Node current_node, std::vector<Node> node_list)
{

    bool flag;
    for (int i = 0; i < node_list.size(); i++)
    {
        if (current_node.getRowIndex() == node_list[i].getRowIndex() &&
            current_node.getColIndex() == node_list[i].getColIndex())
        {
            flag = true;
            break;
        }

        else
        {
            flag = false;
        }
    }
    return flag;
}

Node *returnInVector(Node current_node, std::vector<Node> &node_list)
{
    Node *return_pNode = nullptr;
    if (inVector(current_node, node_list))
    {
        for (int i = 0; i < node_list.size(); i++)
        {
            if (current_node.getRowIndex() == node_list[i].getRowIndex() &&
                current_node.getColIndex() == node_list[i].getColIndex())
            {
                return_pNode = &node_list[i];
                break;
            }
        }
    }

    return return_pNode;
}

int returnIndex(Node current_node, std::vector<Node> &node_list)
{
    int index;

    if (inVector(current_node, node_list))
    {

        for (int i = 0; i < node_list.size(); i++)
        {
            if (current_node.getRowIndex() == node_list[i].getRowIndex() &&
                current_node.getColIndex() == node_list[i].getColIndex())
            {
                index = i;
                break;
            }
        }
    }

    return index;
}

std::vector<Node> createSuccessors(Node current_node)
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

void Astar(Waypoint start, Waypoint end, std::vector<Node> &closed_list)
{
    std::vector<Node> open_list;

    Node node_start(start.col_ind, start.row_ind);
    open_list.push_back(node_start);

    while (open_list.size() != 0)
    {
        Node *pNode_current = nodeLowestCost(open_list);
        pNode_current->showInfo();
        std::cout << "1" << std::endl;
        Node node_current(0, 0);
        node_current = *pNode_current;
        std::cout << "2" << std::endl;
        node_current.showInfo();
        int open_list_ind = returnIndex(node_current, open_list);
        std::cout << "index is " << open_list_ind << std::endl;
        std::cout << "3" << std::endl;
        node_current.showInfo();
        open_list.erase(open_list.begin() + open_list_ind);
        std::cout << "4" << std::endl;
        pNode_current->showInfo();
        std::cout << "5" << std::endl;
        node_current.showInfo();

        if (node_current.getColIndex() == end.col_ind && node_current.getRowIndex() == start.row_ind)
        {
            break;
        }

        std::vector<Node> successors = createSuccessors(node_current);

        for (int i = 0; i < successors.size(); i++)
        {
            std::cout << std::endl;
            successors[i].showInfo();
            std::cout << std::endl;

            bool flag = false;
            double suc_current_cost = node_current.getCurrentCost() + successors[i].calculateTime();
            std::cout << "current cost is " << suc_current_cost << std::endl;
            if (inVector(successors[i], open_list))
            {
                Node suc_in_open = *returnInVector(node_current, open_list);
                if (suc_in_open.getCurrentCost() <= suc_current_cost)
                {
                    flag = true;
                }
            }

            else if (inVector(successors[i], closed_list))
            {
                Node suc_in_close = *returnInVector(successors[i], closed_list);
                if (suc_in_close.getCurrentCost() <= suc_current_cost)
                {
                    flag = true;
                }

                else
                {
                    int index = returnIndex(node_current, closed_list);
                    closed_list.erase(closed_list.begin() + index);
                    open_list.push_back(suc_in_close);
                }
            }

            else
            {
                open_list.push_back(successors[i]);
            }
            if (!flag)
                successors[i].setCurrentCost(suc_current_cost);
        }
        closed_list.push_back(node_current);
    }
}

int main()
{
    Node node1(0, 0);
    node1.showInfo();

    std::cout << "################" << std::endl;
    Node node2(node1, 1);
    node2.showInfo();

    std::cout << "################" << std::endl;
    Node node3 = node2;
    node3.showInfo();
    Node* address = node3.getParent();
    std::cout << address << std::endl;

    std::cout << "################" << std::endl;
    Node node4(node3, 4);
    node4.showInfo();

    std::cout << "################" << std::endl;
    node4 = node3;
    node4.showInfo();

    std::cout << "################" << std::endl;
    node3.~Node();
    node4.showInfo();
    /*
    //uisng A*
    Waypoint waypoint_start;
    waypoint_start.row_ind = waypoint_start.col_ind = 0;

    Waypoint waypoint_end;
    waypoint_end.row_ind = 0;
    waypoint_end.col_ind = 10;

    std::vector<Node> closed_list;
    Astar(waypoint_start, waypoint_end, closed_list);
    std::cout << closed_list.size() << std::endl;
    closed_list[0].showInfo();
    closed_list[1].showInfo();
    */

    /*
    //for getting input
    std::string input;
    std::vector<int> x_pos, y_pos;
    std::vector<double> penalty;
    std::vector<Waypoint> waypoints;

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
    */

    return 0;
}