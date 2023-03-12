#include "Residential.h"

//A - COMPLETED: residential function
void residentialFunc(Matrix& matrix) 
{
    Matrix matrix2 = matrix;
    for (int i = 0; i < matrix.size(); ++i) {
        for (int k = 0; k < matrix[i].size(); ++k) {
            if (matrix2[i][k].type == "R") {
                if ((matrix2[i][k].pop == 0) && (checkSurroundingCells(matrix2, "#", i, k) || checkSurroundingCells(matrix2, "T", i, k))) {
                    matrix[i][k].pop = 1;
                    matrix[i][k].currWorkersAvail = 1;
                    continue;
                }
                if ((matrix2[i][k].pop == 0) && (checkSurroundingCellPop(matrix2, 1, i, k) >= 1)) {
                    matrix[i][k].pop = 1;
                    matrix[i][k].currWorkersAvail = 1;
                    continue;
                }
                if ((matrix2[i][k].pop == 1) && (checkSurroundingCellPop(matrix2, 1, i, k) >= 2)) {
                    matrix[i][k].pop = 2;
                    matrix[i][k].currWorkersAvail++;
                    continue;
                }
                if ((matrix2[i][k].pop == 2) && (checkSurroundingCellPop(matrix2, 2, i, k) >= 4)) {
                    matrix[i][k].pop = 3;
                    matrix[i][k].currWorkersAvail++;
                    continue;
                }
                if ((matrix2[i][k].pop == 3) && (checkSurroundingCellPop(matrix2, 3, i, k) >= 6)) {
                    matrix[i][k].pop = 4;
                    matrix[i][k].currWorkersAvail++;
                    continue;
                }
                if ((matrix2[i][k].pop == 4) && (checkSurroundingCellPop(matrix2, 4, i, k) >= 8)) {
                    matrix[i][k].pop = 5;
                    matrix[i][k].currWorkersAvail++;
                    continue;
                }
            }
        }
    }
}