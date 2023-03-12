#include "Industrial.h"

void industrialSortingFunc(Matrix& matrix, std::vector<listCell>& indusList) //J COMPLETED- function to sort industrial cells based off pop size
{
    listCell temp;
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {      //loop to go through matrix
            if (matrix[i][j].type == "I") {         //searching for Industrial cells and inserting to vector
                temp.rowNum = i;
                temp.colNum = j;
                temp.popSize = matrix[i][j].pop;
                indusList.push_back(temp);
            }
        }
    }
    for (int k = 0; k < indusList.size(); k++) //sorting locations based off pop size
    {
        for (int l = k + 1; l < indusList.size(); l++) {

            if (indusList[k].popSize < indusList[l].popSize) { // swapping 
                temp = indusList[k];
                indusList[k] = indusList[l];
                indusList[l] = temp;
            }
        }
    }
}

void industrialFunc(Matrix& matrix, Matrix& matrix2, std::vector<listCell> indusList, int& availWorkers) //J - COMPLETED: Industial Function
{
    int i = 0;
    int j = 0;
    for (int f = 0; f < indusList.size(); f++) {
        if (availWorkers >= 2) { //goes in only if more than 2 workers available
            i = indusList[f].rowNum;
            j = indusList[f].colNum; //gets location of cell in matrix from the list
            if ((matrix2[i][j].pop == 0) && (checkSurroundingCells(matrix2, "#", i, j) || checkSurroundingCells(matrix2, "T", i, j))) { //population increased by 1 if there's a 0 pop and its adjacent to a powerline
                matrix[i][j].pop++;
                matrix[i][j].currAvailGoods++;
                availWorkers -= 2;
                int remainingTakeAwayWorkers = 2;
                for (int z = 0; z < matrix2.size(); ++z) {
                    bool workergone = false;
                    for (int y = 0; y < matrix2[z].size(); ++y) {
                        if (matrix2[z][y].currWorkersAvail >= 1) {
                            matrix[z][y].currWorkersAvail--;
                            remainingTakeAwayWorkers--;
                            if (remainingTakeAwayWorkers <= 0) {
                                workergone = true;
                                break;
                            }
                        }
                    }
                    if (workergone) {
                        break;
                    }
                }

                continue;
            }
            if ((matrix2[i][j].pop == 0) && (checkSurroundingCellPop(matrix2, 1, i, j) >= 1)) { //population increased by 1 if the pop is 1, adjacent to > 1 cells with a pop > 1
                matrix[i][j].pop++;
                matrix[i][j].currAvailGoods++;
                availWorkers -= 2;
                int remainingTakeAwayWorkers = 2;
                for (int z = 0; z < matrix2.size(); ++z) {
                    bool workergone = false;
                    for (int y = 0; y < matrix2[z].size(); ++y) {
                        if (matrix2[z][y].currWorkersAvail >= 1) {
                            matrix[z][y].currWorkersAvail--;
                            remainingTakeAwayWorkers--;
                            if (remainingTakeAwayWorkers <= 0) {
                                workergone = true;
                                break;
                            }
                        }
                    }
                    if (workergone) {
                        break;
                    }
                }
                continue;
            }
            if ((matrix2[i][j].pop == 1) && (checkSurroundingCellPop(matrix2, 1, i, j) >= 2)) {//population increased by 1 if the pop is 1, adjacent to > 2 cells with a pop > 1
                matrix[i][j].pop++;
                matrix[i][j].currAvailGoods++;
                availWorkers -= 2;
                int remainingTakeAwayWorkers = 2;
                for (int z = 0; z < matrix2.size(); ++z) {
                    bool workergone = false;
                    for (int y = 0; y < matrix2[z].size(); ++y) {
                        if (matrix2[z][y].currWorkersAvail >= 1) {
                            matrix[z][y].currWorkersAvail--;
                            remainingTakeAwayWorkers--;
                            if (remainingTakeAwayWorkers <= 0) {
                                workergone = true;
                                break;
                            }
                        }
                    }
                    if (workergone) {
                        break;
                    }
                }
                continue;
            }
            if ((matrix2[i][j].pop == 2) && (checkSurroundingCellPop(matrix2, 2, i, j) >= 4)) { //population increased by 1 if the pop is 1, adjacent to > 4 cells with a pop > 2
                matrix[i][j].pop++;
                matrix[i][j].currAvailGoods++;
                availWorkers -= 2;
                int remainingTakeAwayWorkers = 2;
                for (int z = 0; z < matrix2.size(); ++z) {
                    bool workergone = false;
                    for (int y = 0; y < matrix2[z].size(); ++y) {
                        if (matrix2[z][y].currWorkersAvail >= 1) {
                            matrix[z][y].currWorkersAvail--;
                            remainingTakeAwayWorkers--;
                            if (remainingTakeAwayWorkers <= 0) {
                                workergone = true;
                                break;
                            }
                        }
                    }
                    if (workergone) {
                        break;
                    }
                }
                continue;
            }
        }
    }
}

