#include "Analysis.h"

int totalPopulationRegion(Matrix &matrix, std::string region){ //Calculates total population in each region
    int sum = 0;
    for (int i = 0; i < matrix.size(); ++i){
        for (int k = 0; k < matrix[i].size(); ++k){

            if (matrix[i][k].type == region){
                sum += matrix[i][k].pop;
            }
        }
    }
    return sum;
}

int totalPopulationRegion(Matrix &matrix, std::string region, std::pair<int,int> topLeft, std::pair<int,int> bottomRight){ //Overloaded totalPopulationRegion to calculate population of reagions in user specified region
    int sum = 0;
    for (int i = topLeft.first; i <= bottomRight.first; ++i){
        for (int j = topLeft.second; j <= bottomRight.second; ++j){

            if (matrix[i][j].type == region){
                sum += matrix[i][j].pop;
            }
        }
    }
    return sum;
}

int totalPopulation(Matrix &matrix){ //Calculates total population
    int sum = 0;
    for (int i = 0; i < matrix.size(); ++i){
        for (int k = 0; k < matrix[i].size(); ++k){
            sum += matrix[i][k].pop;
        }
    }
    return sum;
}

int totalPopulation(Matrix &matrix, std::pair<int,int> topLeft, std::pair<int,int> bottomRight){ //Overloaded totalPopulation to calculate total population of user specified region
    int sum = 0;
    for (int i = topLeft.first; i <= bottomRight.first; ++i){
        for (int j = topLeft.second; j <= bottomRight.second; ++j){
            sum += matrix[i][j].pop;
        }
    }
    return sum;
}

void displayAllPopulations(Matrix &matrix){// Displays all of the populations after the final region is displayed
    std::cout << "Total Population: " << totalPopulation(matrix) << std::endl;
    std::cout << "Residential Population: " << totalPopulationRegion(matrix, "R") << std::endl;
    std::cout << "Industrial Population: "<< totalPopulationRegion(matrix, "I") << std::endl;
    std::cout << "Commercial Population: "<< totalPopulationRegion(matrix, "C") << std::endl;
}

bool boundsCheck(Matrix &matrix, std::pair<int,int> topLeft, std::pair<int,int> bottomRight){// Checks whether the user defined region is within bounds
    int i = 0;
    bool flag = true;

    if (topLeft.first < 0 || topLeft.first >= (matrix.size())){
        std::cout << "Top Left X Out of Bounds, Range between 0 and " << (matrix.size() - 1) << std::endl;
        flag = false;
    }
    if (topLeft.second < 0 || topLeft.second >= (matrix[i].size())){
        std::cout << "Top Left Y Out of Bounds, Range between 0 and " << (matrix[i].size() - 1) << std::endl;
        flag = false;
    }
    if (bottomRight.first < 0 || bottomRight.first >= (matrix.size())){
        std::cout << "Bottom Right X Out of Bounds, Range between 0 and " << (matrix.size() - 1) << std::endl;
        flag = false;
    }
    if (bottomRight.second < 0 || bottomRight.second >= (matrix[i].size())){
        std::cout << "Bottom Right Y Out of Bounds, Range between 0 and " << (matrix[i].size() - 1) << std::endl;
        flag = false;
    }
    return flag;
}

void analyzeRegion(Matrix &matrix, std::pair<int,int> topLeft, std::pair<int,int> bottomRight){ //analyses region and outputs total population and total population of each region
    bool boundsFlag = true;
    do{
        std::cout << std::endl;
        std::cout << "ANALYSIS - Give the coordinates of the rectangular region you want to analyze" << std::endl;
        int x = 0;
        int y = 0;
        
        std::cout << "What are the coordinates of the top-left corner of the rectangle";
        std::cout << "\nX: ";
        std::cin >> x;
        std::cout << "Y: ";
        std::cin >> y;
        topLeft = {x,y};
        
        std::cout << "What are the coordinates of the bottom-right corner of the rectangle";
        std::cout << "\nX: ";
        std::cin >> x;
        std::cout << "Y: ";
        std::cin >> y;
        bottomRight = {x,y};
        boundsFlag = boundsCheck(matrix, topLeft, bottomRight);
    }while(!boundsFlag);
    
    std::cout << "Total Population in Analyzed Region: " << totalPopulation(matrix, topLeft, bottomRight) << std::endl;
    std::cout << "Residential Population in Analyzed Region: " << totalPopulationRegion(matrix, "R", topLeft, bottomRight) << std::endl;
    std::cout << "Industrial Population in Analyzed Region: "<< totalPopulationRegion(matrix, "I", topLeft, bottomRight) << std::endl;
    std::cout << "Commercial Population in Analyzed Region: "<< totalPopulationRegion(matrix, "C", topLeft, bottomRight) << std::endl;
}