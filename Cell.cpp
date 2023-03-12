#include "Cell.h"

int checkSurroundingCellPop(Matrix& matrix, int pop, int x, int y) //A - COMPLETED: function that checks surrounding cell populations and returns how many cells have that population
{ 
    int count = 0;
    for (int i = x - 1; i <= x + 1; ++i) 
    {
        for (int k = y - 1; k <= y + 1; ++k) 
        {
            if ((!(k == y && i == x)) && (i >= 0 && i < matrix.size()) && (k >= 0 && k < matrix[i].size())) 
            {
                if (matrix[i][k].pop >= pop) 
                {
                    count++;
                }
            }
        }
    }
    return count;
}

bool checkSurroundingCells(Matrix& matrix, std::string search, int x, int y)  //A - COMPLETED: function that searches surrounding cells for a specific character/string
{
    for (int i = x - 1; i <= x + 1; ++i) 
    {
        for (int k = y - 1; k <= y + 1; ++k) 
        {
            if ((!(k == y && i == x)) && (i >= 0 && i < matrix.size()) && (k >= 0 && k < matrix[i].size())) 
            {
                if (matrix[i][k].name == search) 
                {
                    return true;
                }
            }
        }
    }
    return false;
}

int totalAvailWorkers(Matrix& matrix) //A - COMPLETED: sums up available workers
{
    int sum = 0;
    for (int i = 0; i < matrix.size(); ++i) {
        for (int k = 0; k < matrix[i].size(); ++k) {
            sum += matrix[i][k].currWorkersAvail;
        }
    }
    return sum;
}

int totalAvailGoods(Matrix& matrix)  //J - COMPLETED: sums up available goods in the industrial zone
{ 
    int sum = 0;
    for (int i = 0; i < matrix.size(); ++i) {
        for (int k = 0; k < matrix[i].size(); ++k) {
            sum += matrix[i][k].currAvailGoods;
        }
    }
    return sum;
}
