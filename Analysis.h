#pragma once

#include "Cell.h"

int totalPopulationRegion(Matrix &matrix, std::string region); //Calculates total population in each region

int totalPopulationRegion(Matrix &matrix, std::string region, std::pair<int,int> topLeft, std::pair<int,int> bottomRight); //Overloaded totalPopulationRegion to calculate population of regions in user specified region

int totalPopulation(Matrix &matrix); //Calculates total population

int totalPopulation(Matrix &matrix, std::pair<int,int> topLeft, std::pair<int,int> bottomRight); //Overloaded totalPopulation to calculate total population of user specified region

void displayAllPopulations(Matrix &matrix);// Displays all of the populations after the final region is displayed

bool boundsCheck(Matrix &matrix, std::pair<int,int> topLeft, std::pair<int,int> bottomRight);// Checks whether the user defined region is within bounds

void analyzeRegion(Matrix &matrix, std::pair<int,int> topLeft, std::pair<int,int> bottomRight); //analyses region and outputs total population and total population of each region