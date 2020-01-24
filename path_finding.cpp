#include <string>
#include <vector>
#include <iterator>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "Astar.h"

int main()
{
    std::string input; //to store input as a string
    std::vector<Waypoint> waypoints;
    Waypoint start; //define the starting point
    start.col_ind = start.row_ind = start.penalty = 0;
    Waypoint end; //define the goal point
    end.col_ind = end.row_ind = 50;
    end.penalty = 0;

    waypoints.push_back(start); //push the starting point to the list of waypoints
    while (input != "FINISH")
    {
        std::cout << "Type input in the following form: col_ind row_ind penalty, or type FINISH when no mor points are needed" << std::endl;
        std::getline(std::cin, input);

        std::vector<std::string> info;
        boost::algorithm::split(info, input, boost::algorithm::is_any_of(" "));

        if (info.size() != 3)
        {
            std::cout << "Invalid input or no input" << std::endl;
        }

        else
        {
            Waypoint waypoint_temp;
            waypoint_temp.col_ind = std::atoi(info[0].c_str());
            waypoint_temp.row_ind = std::atoi(info[1].c_str());
            waypoint_temp.penalty = std::atof(info[2].c_str());
            Node temp(waypoint_temp.col_ind, waypoint_temp.row_ind);
            if (temp.validPoint(temp.getColIndex()) && temp.validPoint(temp.getRowIndex()))
            { //if the input is valid
                waypoints.push_back(waypoint_temp); //push waypoint obtained from input to the list
            }

            else
            {
                std::cout << "Input coordinate not valid" << std::endl;
            }
            
        }
    }
    waypoints.push_back(end); //push the target point to the list

    double total_time = 0;
    double skip_time = 0;
    bool skip = false;      //to flag if skipping a waypoint occurs
    int skip_num = 0;       //to record how many waypoints skipped since moving to the last waypoint
    Node parent_node(0, 0); //to store the last node from the previous Astar

    for (int i = 0; i < waypoints.size() - 1; i++)
    {
        skip = false;
        //Waypoint order start ----> next ----> next_skip
        std::vector<Node> closed_list_no_skip1; //closed list for start ---> next
        std::vector<Node> closed_list_no_skip2; //closed list for next ---> next_skip
        std::vector<Node> closed_list_skip;     //closed list for start ---> next_skip
        double time_no_skip = 0;                //time for start ---> next ---> next_skip
        double time_skip_node = 0;              //time for start ---> next_skip + penalty;
        Waypoint start = waypoints[i - skip_num];
        Waypoint next = waypoints[i + 1];
        Astar(start, next, closed_list_no_skip1); //A* for start ---> next
        Waypoint next_skip;
        Node check_dir(0, 0);
        //to check if there is direction change from last iteration to this iteration

        if (i < waypoints.size() - 2)
        {
            //not skipping the node
            next_skip = waypoints[i + 2];
            Astar(next, next_skip, closed_list_no_skip2); //A* for next ---> next_skip
            time_no_skip = closed_list_no_skip1[closed_list_no_skip1.size() - 1].getTotalCost() + closed_list_no_skip2[closed_list_no_skip2.size() - 1].getTotalCost();

            //skipping node
            Astar(start, next_skip, closed_list_skip); //A* for start ---> next_skip
            time_skip_node = closed_list_skip[closed_list_skip.size() - 1].getTotalCost() + next.penalty;

            if (time_skip_node < time_no_skip)
            { //if skipping a node takes less time
                skip = true;
                check_dir = closed_list_skip[1];
                if (check_dir.dirChange(parent_node))
                {
                    time_skip_node += 0.5;
                }
                skip_time = time_skip_node;
                skip_num++;
            }

            else
            { //if skipping a node doesn't take less time
                skip = false;
                check_dir = closed_list_no_skip1[1];
                if (check_dir.dirChange(parent_node))
                {
                    total_time += 0.5;
                }
                parent_node = closed_list_no_skip1[closed_list_no_skip1.size() - 1];
                total_time += closed_list_no_skip1[closed_list_no_skip1.size() - 1].getTotalCost();
                skip_time = 0;
                skip_num = 0;
            }
        }

        else
        { //this happens at the last waypoint
            skip = false;
            check_dir = closed_list_no_skip1[1];
            if (check_dir.dirChange(parent_node))
            {
                total_time += 0.5;
            }
            parent_node = closed_list_no_skip1[closed_list_no_skip1.size() - 1];
            total_time += closed_list_no_skip1[closed_list_no_skip1.size() - 1].getTotalCost();
            skip_time = 0;
            skip_num = 0;
        }
    }

    std::cout << "The total time is: " << total_time << " sec." << std::endl;
    return 0;
}