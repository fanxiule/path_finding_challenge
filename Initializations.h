#ifndef INITIALIZATIONS_H
#define INITIALIZATIONS_H

#include <iostream>

#define HAZARD_TIME 5       //time to finish 5m in hazard zone
#define NON_HAZARD_TIME 2   //time to finish 5m in non hazard zone
#define CHANGE_DIR_TIME 0.5 //time to change robot direction

struct Waypoint
{
    int col_ind, row_ind;
    double penalty;
};

struct Map
{
    static const int COL = 10;
    static const int ROW = 10;
    double speed[10][10];

    Map()
    {
        for (int i = 0; i < ROW; i++)
        {
            for (int j = 0; j < COL; j++)
            {
                if ((i >= 3 && i <= 6) && (j >= 3 && j <= 6))
                {
                    speed[i][j] = 5 / 1; //hazard zone
                }

                else
                {
                    speed[i][j] = 5 / 2.5; //non hazard zone
                }

                std::cout << speed[i][j] << " "; //debug
            }
            std::cout << std::endl; //debug
        }
    };
};

struct Robot
{
    int posx, posy;
    double elapsed_time;
};

#endif //INITIALIZATIONS_H