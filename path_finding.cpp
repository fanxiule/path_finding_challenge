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

    Node node1(0, 0);
    std::cout << "node1 col ind: " << node1.getColIndex();
    std::cout << "node1 row ind: " << node1.getRowIndex();

    Node node2(1, 5);
    Node node3(-5, -10);
    Node node4(20, 60);

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