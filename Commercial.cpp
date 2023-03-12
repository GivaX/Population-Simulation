#include "Commercial.h"

void commercialSortingFunc(Matrix& matrix, std::vector<com>& comList) //M COMPLETED- function to sort commercial cells based off pop size
{
    com temp;
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {      //loop to go through matrix

            if (matrix[i][j].type == "C") {         //searching for commercial cells and inserting to vector
                temp.rowNum = i;
                temp.colNum = j;
                temp.popSize = matrix[i][j].pop;
                comList.push_back(temp);
            }

        }

    }
    for (int k = 0; k < comList.size(); k++) //sorting locations based off pop size
    {
        for (int l = k + 1; l < comList.size(); l++) {

            if (comList[k].popSize < comList[l].popSize) {
                temp = comList[k];
                comList[k] = comList[l];
                comList[l] = temp;
            }
        }
    }
}

void commercialFunc(Matrix& matrix, Matrix& prevMatrix, std::vector<com>& comList, int& availworkers, int& availgoods) //M COMPLETED - function to update commercial cells
{
    int i = 0;
    int j = 0;
    for (int f = 0; f < comList.size(); f++) {
        if (availgoods >= 1 && availworkers >= 1) {
            i = comList[f].rowNum;
            j = comList[f].colNum;
            //go thru vector and give i and j values
            if (prevMatrix[i][j].pop == 0) {      //if statement for if population is 0
                if (checkSurroundingCells(prevMatrix, "#", i, j) || checkSurroundingCells(prevMatrix, "T", i, j)) {
                    for (int z = 0; z < prevMatrix.size(); ++z) {
                        bool workergone = false;
                        for (int y = 0; y < prevMatrix[z].size(); ++y) {
                            if (prevMatrix[z][y].currWorkersAvail >= 1) {
                                matrix[z][y].currWorkersAvail--;
                                workergone = true;
                                break;
                            }
                        }
                        if (workergone) {
                            break;
                        }
                    }
                    for (int z = 0; z < prevMatrix.size(); ++z) {
                        bool goodgone = false;
                        for (int y = 0; y < prevMatrix[z].size(); ++y) {
                            if (prevMatrix[z][y].currAvailGoods >= 1) {
                                matrix[z][y].currAvailGoods--;
                                goodgone = true;
                                break;
                            }
                            if (goodgone) {
                                break;
                            }
                        }
                    }
                    availworkers -= 1;
                    availgoods -= 1;

                    matrix[i][j].pop += 1;
                    if (availgoods >= 1 && availworkers >= 1) {
                    }
                    else {
                        break;
                    }
                    //is adjacent to a powerline in the current time step, cell�s population will increase by 1 in the next time step and the available worker and available good are assigned to that job
                }
                else if (checkSurroundingCellPop(prevMatrix, 1, i, j) >= 1) {
                    for (int z = 0; z < prevMatrix.size(); ++z) {
                        bool workergone = false;
                        for (int y = 0; y < prevMatrix[z].size(); ++y) {
                            if (prevMatrix[z][y].currWorkersAvail >= 1) {
                                matrix[z][y].currWorkersAvail--;
                                workergone = true;
                                break;
                            }
                        }
                        if (workergone) {
                            break;
                        }
                    }
                    for (int z = 0; z < prevMatrix.size(); ++z) {
                        bool goodgone = false;
                        for (int y = 0; y < prevMatrix[z].size(); ++y) {
                            if (prevMatrix[z][y].currAvailGoods >= 1) {
                                matrix[z][y].currAvailGoods--;
                                goodgone = true;
                                break;
                            }
                            if (goodgone) {
                                break;
                            }
                        }
                    }
                    availworkers -= 1;
                    availgoods -= 1;
                    matrix[i][j].pop += 1;
                    if (availworkers >= 1 && availgoods >= 1) {

                    }
                    else {
                        break;
                    }
                    //is adjacent to at least one cell with a population of at least 1, cell�s population will increase by 1 in the next time step and the available worker and available good are assigned to that job
                }
            }
            else if (prevMatrix[i][j].pop >= 1) {    //if statement for if population >= 1
                if (checkSurroundingCellPop(prevMatrix, 1, i, j) >= 2) {
                    for (int z = 0; z < prevMatrix.size(); ++z) {
                        bool workergone = false;
                        for (int y = 0; y < prevMatrix[z].size(); ++y) {
                            if (prevMatrix[z][y].currWorkersAvail >= 1) {
                                matrix[z][y].currWorkersAvail--;
                                workergone = true;
                                break;
                            }
                        }
                        if (workergone) {
                            break;
                        }
                    }
                    for (int z = 0; z < prevMatrix.size(); ++z) {
                        bool goodgone = false;
                        for (int y = 0; y < prevMatrix[z].size(); ++y) {
                            if (prevMatrix[z][y].currAvailGoods >= 1) {
                                matrix[z][y].currAvailGoods--;
                                goodgone = true;
                                break;
                            }
                            if (goodgone) {
                                break;
                            }
                        }
                    }
                    availworkers -= 1;
                    availgoods -= 1;
                    matrix[i][j].pop += 1;
                    if (availworkers >= 1 && availgoods >= 1) {}
                    else {
                        break;
                    }
                    //is adjacent to at least two cells with a population of at least 1, cell�s population will increase by 1 in the next time step and the available worker and available good are assigned to that job
                }
            }
        }
    }
}