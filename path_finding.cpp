#include <string>
#include <vector>
#include <iterator>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "node.h"

int main()
{
    /*
    Map map;
    std::cout << "Number of Rows: " << map.ROW << std::endl;    //debug
    std::cout << "Number of Columns: " << map.COL << std::endl; //debug
    */

    Waypoint waypoint1;
    waypoint1.col_ind = 0;
    waypoint1.row_ind = 0;

    Node node1(15, 10);
    node1.showInfo();
    std::cout << "########################" << std::endl;
    node1.calHeuristic(waypoint1);
    node1.showInfo();

    Node node2(node1, 1);
    node2.showInfo();
    std::cout << "########################" << std::endl;
    node2.calCurrentCost();
    node2.calHeuristic(waypoint1);
    node2.showInfo();

    Node node3(node2, 1);
    node3.showInfo();
    std::cout << "########################" << std::endl;
    node3.calCurrentCost();
    node3.calHeuristic(waypoint1);
    node3.showInfo();

    Node node4(node3, 3);
    node4.showInfo();
    std::cout << "########################" << std::endl;
    node4.calCurrentCost();
    node4.calHeuristic(waypoint1);
    node4.showInfo();

    /*
    Node node2(node1, 1);
    node2.showInfo();
    node2.calCurrentCost();
    std::cout << "node2 current cost is g = " << node2.getCurrentCost() << " total cost is f = " << node2.getTotalCost() << std::endl;
   
    std::cout << "########################" << std::endl;
    Node node3(node2, 3);
    node3.showInfo();
    node3.calCurrentCost();
    std::cout << "node3 current cost is g = " << node3.getCurrentCost() << " total cost is f = " << node3.getTotalCost() << std::endl;

    std::cout << "########################" << std::endl;
    Node node4(node3, 1);
    node4.showInfo();
    node4.calCurrentCost();
    std::cout << "node4 current cost is g = " << node4.getCurrentCost() << " total cost is f = " << node4.getTotalCost() << std::endl;

    std::cout << "########################" << std::endl;
    Node node5(node4, 1);
    node5.showInfo();
    node5.calCurrentCost();
    std::cout << "node3 current cost is g = " << node5.getCurrentCost() << " total cost is f = " << node5.getTotalCost() << std::endl;
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