#pragma once

//STL includes
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <memory>
#include <fstream>
#include <sstream>
#include <algorithm>


struct Cell 
{ 
    Cell() : name(""), type(""), pol(0), pop(0), id(0), currAvailGoods(0), currWorkersAvail(0) {}
    std::string name;
    std::string type;
    int pol; // pollution
    int pop; // population
    int currWorkersAvail;
    int currAvailGoods;
    int id;
};

using Matrix = std::vector<std::vector<Cell>>;

struct listCell //struct to store location of cells for industrial sorting function
{
    int rowNum = 0;
    int colNum = 0;
    int popSize = 0;
};

struct com     //struct to store location of cells for commercial sorting function
{ 
    int rowNum = 0;
    int colNum = 0;
    int popSize = -1;
};

int checkSurroundingCellPop(Matrix& matrix, int pop, int x, int y);

bool checkSurroundingCells(Matrix& matrix, std::string search, int x, int y);

int totalAvailWorkers(Matrix& matrix);

int totalAvailGoods(Matrix& matrix);