#ifndef INITIALIZATIONS_H
#define INITIALIZATIONS_H

#include <iostream>

#define HAZARD_TIME 5       //time in sec to finish 5m in hazard zone, 1 m/s
#define NON_HAZARD_TIME 2   //time in sec to finish 5m in non hazard zone, 2.5 m/s
#define CHANGE_DIR_TIME 0.5 //time in sec to change robot direction
#define HEURISTIC_TIME 5.5  //time in sec to use for HEURISTIC calculation
//Note that 6 is higher than any other time
struct Waypoint
{
    int col_ind, row_ind;
    double penalty;
};

#endif //INITIALIZATIONS_H