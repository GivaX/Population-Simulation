#pragma once

#include "Cell.h"

void commercialSortingFunc(Matrix& matrix, std::vector<com>& comList); //M COMPLETED- function to sort commercial cells based off pop size


void commercialFunc(Matrix& matrix, Matrix& prevMatrix, std::vector<com>& comList, int& availworkers, int& availgoods); //M COMPLETED - function to update commercial cells
