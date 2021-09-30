#include <vector>
#include <iostream>

#ifndef HTDCOUNT_H
#define HTDCOUNT_H

int hdtCount_recurse(std::vector<std::vector<int>> &board,
                     int dim_x, int dim_y,
                     int squaresLeft);

int hdtCount(int dim_x, int dim_y,
             int forbid1_x, int forbid1_y,
             int forbid2_x, int forbid2_y);


#endif
