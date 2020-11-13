/**
 * Antekeland 2020
 * Author: TBA
 * Mail: TBA@esat-alumni.com
 * University Development @ESAT
 */

#ifndef __GRID_H__
#define __GRID_H__ 1

#include "gamemanager.h"

const int kChanceToMove = 721;
const unsigned char kSearchRange = (Board::Board::kBoardSize/4)*3;
static int repeats = 0;

void CreateBoard();
void InitLogic();
unsigned char CheckSingleNeighbour(unsigned char pos, const int desp);
unsigned char MatrixNxM(const Tile layer[Board::kBoardSize][Board::kBoardSize],
                      const unsigned char row, const unsigned char col, const unsigned char n,
                      const unsigned char m, const unsigned char state);
unsigned char CheckNeighbours(const Tile layer[Board::kBoardSize][Board::kBoardSize],
                              const unsigned char row, const unsigned char col, const unsigned char n,
                              const unsigned char m, const unsigned char state);
unsigned char CheckNeighboursType(const Tile layer[Board::kBoardSize][Board::kBoardSize],
                                  unsigned char row, unsigned char col, const unsigned char n,
                                  const unsigned char m, unsigned char state,
                                  unsigned char check_type);
unsigned char CheckCrossNeighbours(const Tile layer[Board::kBoardSize][Board::kBoardSize],
                                   unsigned char row, unsigned char col, unsigned char state);
void SwapCells(Tile layer[Board::kBoardSize][Board::kBoardSize],
               unsigned char row1, unsigned char col1, unsigned char state1,
               unsigned char row2, unsigned char col2, unsigned char state2);
signed char TemporalSwap(Tile layer[Board::kBoardSize][Board::kBoardSize],
                         unsigned char row1, unsigned char col1, unsigned char state1,
                         unsigned char row2, unsigned char col2, unsigned char state2);
signed char CalculateGain(Tile layer[Board::kBoardSize][Board::kBoardSize],
                          unsigned char row1, unsigned char col1,
                          unsigned char row2, unsigned char col2);                                                                             
void EraseTile(Tile layer[Board::kBoardSize][Board::kBoardSize],
               Tile aux_layer[Board::kBoardSize][Board::kBoardSize],
               unsigned char row, unsigned char col, unsigned char state);
void PickCell(Tile layer[Board::kBoardSize][Board::kBoardSize],
              const unsigned char original_row, const unsigned char original_col,
              const unsigned char orig_gain);
void ChangeTileType(Tile layer[Board::kBoardSize][Board::kBoardSize],
                    Tile aux_layer[Board::kBoardSize][Board::kBoardSize],
                    unsigned char row, unsigned char col, unsigned char state);
void CreateMap();                                                                                                                             

#endif  // __GRID_H__