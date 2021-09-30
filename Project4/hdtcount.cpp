#include "hdtcount.h"

using std::vector;

int hdtCount_recurse(vector<vector<int>> &board,
                     int dim_x, int dim_y,
                     int squaresLeft)
{
  if(squaresLeft == 0) return 1; // board is solved

  int total = 0;

  for( int i = 0; i < dim_y; ++i ) {
    for( int k = 0; k < dim_x; ++k ) {

      // [k, i]

      if(board[k][i] == 1) continue;

      // try horizontal if we aren't at the end of the board
      if( k < dim_x - 1 ) {
        if(board[k + 1][i] == 0) {
          // place a domino
          board[k][i] = 1;
          board[k+1][i] = 1;
          total += hdtCount_recurse(board, dim_x, dim_y, squaresLeft - 2);
          board[k][i] = 0;
          board[k+1][i] = 0;
        }
      }

      // try vertical if we aren't at the bottom of the board
      if( i < dim_y - 1 ) {
        if(board[k][i + 1] == 0) {
          // place a domino
          board[k][i] = 1;
          board[k][i+1] = 1;
          total += hdtCount_recurse(board, dim_x, dim_y, squaresLeft - 2);
          board[k][i] = 0;
          board[k][i+1] = 0;
        }
      }

      // break the loops
      i = dim_y;
      k = dim_x;

    }
  }

  return total;

}

int hdtCount(int dim_x, int dim_y,
             int forbid1_x, int forbid1_y,
             int forbid2_x, int forbid2_y)
{
  vector<vector<int>> board( dim_x, vector<int>(dim_y, 0) );
  int squaresLeft = dim_x * dim_y - 2;

  if(squaresLeft%2 != 0) return 0; // can't solve the board if odd # squares left

  board[forbid1_x][forbid1_y] = 1;
  board[forbid2_x][forbid2_y] = 1;

  return hdtCount_recurse(board, dim_x, dim_y, squaresLeft);
}
