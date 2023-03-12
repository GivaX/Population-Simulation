//Group - 7

//Our includes
#include "Cell.h"
#include "Pollution.h"
#include "Residential.h"
#include "Industrial.h"
#include "Commercial.h"
#include "Analysis.h"

using namespace std;


void matrixCorrector(vector<vector<Cell>>& matrix) { //A - COMPLETED: function that updates matrix names
    for (int i = 0; i < matrix.size(); ++i) {
        for (int k = 0; k < matrix[i].size(); ++k) { //loops that go through every single  matrix value and "correct" it (changing name and type)
            if (isdigit(matrix[i][k].name[0])) {
                matrix[i][k].name = to_string(matrix[i][k].pop);
                continue;
            }
            char key = matrix[i][k].name[0];
            switch (key) {
            case 'R':
                matrix[i][k].type = 'R';
                if (matrix[i][k].pop != 0) {
                    matrix[i][k].name = to_string(matrix[i][k].pop);
                }
                break;

            case 'I':
                matrix[i][k].type = 'I';
                if (matrix[i][k].pop != 0) {
                    matrix[i][k].name = to_string(matrix[i][k].pop);
                }
                break;

            case 'C':
                matrix[i][k].type = 'C';
                if (matrix[i][k].pop != 0) {
                    matrix[i][k].name = to_string(matrix[i][k].pop);
                }
                break;
            case 'P':
                matrix[i][k].type = 'P';
                break;
            case '#':
                matrix[i][k].type = 'T';
                break;
            case 'T':
                matrix[i][k].type = 'T';
                break;
            }
        }
    }
}

string readInLine(string line) {//A, H - COMPLETED: reads in data after colon
    bool colon = false;
    string data = "";
#ifdef _WIN32                                               //We need this pre-processor directive because the cell machines are weird
    for (int i = 0; i < line.size(); ++i) {
        if (colon) {
            data += line[i];
        }
        if (line[i] == ':') {
            colon = true;
        }
    }
#elif defined(__linux__)
    for (int i = 0; i < line.size() - 1; ++i) {
        if (colon) {
            data += line[i];
        }
        if (line[i] == ':') {
            colon = true;
        }
    }
#endif
    return data;
}

void displayMatrix(vector<vector<Cell>>& matrix) {//A - COMPLETED: displays matrix
    for (int i = 0; i < matrix.size(); ++i) 
    {
        for (int k = 0; k < matrix[i].size(); ++k) 
        {
            cout << matrix[i][k].name << " ";
        }
        cout << endl;
    }
}

void displayMatrixPollution(vector<vector<Cell>>& matrix) {//A - COMPLETED: displays matrix pollution
    for (int i = 0; i < matrix.size(); ++i) 
    {
        for (int k = 0; k < matrix[i].size(); ++k) 
        {
            cout << matrix[i][k].pol << " ";
        }
        cout << endl;
    }
}

int main() {
    vector<vector<Cell>> matrix; // 2d array
    vector<com> comList; //vector for commercial zones
    vector<listCell> indusList; //vector for industrial zones
    pair<int,int> topLeft;
    pair<int,int> bottomRight;

    ifstream inF;
    int availWorkers = 0;
    int availGoods = 0;
    int currTimeStep = 0;


    string configFileName;
    string regionFileName = "";

    int timeLimit;
    string tempTimeLimit = "";

    int refreshRate;
    string tempRefreshRate = "";


    cout << "Enter config file name: ";
    cin >> configFileName;

    inF.open(configFileName);
    if (inF.fail()) { // if file doesn't exist
        cout << "Config file does not exist." << endl;
        return 0;
    }

    string line;
    getline(inF, line);
    regionFileName = readInLine(line); //reading in region layout file name

    getline(inF, line);
    tempTimeLimit = readInLine(line); //reading in timeLimit
    stringstream temp(tempTimeLimit); //converting to int
    temp >> timeLimit;

    getline(inF, line);
    tempRefreshRate = readInLine(line); //reading in refreshRate
    stringstream temp1(tempRefreshRate); //converting to int
    temp1 >> refreshRate;
    inF.close();
    inF.open(regionFileName);
    if (inF.fail()) { //if file doesn't exist
        cout << "Region file does not exist." << endl;
        return 0;
    }

    //getting data from file
    int i = 0;
    int j = 0;
    while (getline(inF, line)) { //grabbing lines from region file
        Cell data;
        stringstream ls(line);
        string fileInput;
        matrix.push_back(vector<Cell>());
        while (getline(ls, fileInput, ',')) { //grabbing individual letters
            data.name = fileInput;
            data.id = j++;
            matrix[i].push_back(data);
        }
        ++i;
    }
    inF.close();

    matrixCorrector(matrix); //correcting matrix

    Pollution pollution = Pollution(matrix, j);

    //display initial region
    cout << endl << "Initial Region Layout:" << endl;
    displayMatrix(matrix);
    displayMatrixPollution(matrix);
    cout << endl;

    while (currTimeStep < timeLimit) { //loop to go through each timestep
        vector<vector<Cell>> prevMatrix = matrix;
        currTimeStep++;

        availWorkers = totalAvailWorkers(prevMatrix);
        availGoods = totalAvailGoods(prevMatrix);

        commercialSortingFunc(prevMatrix, comList);
        commercialFunc(matrix, prevMatrix, comList, availWorkers, availGoods);

        availWorkers = totalAvailWorkers(matrix);
        availGoods = totalAvailGoods(matrix);
        industrialSortingFunc(prevMatrix, indusList);
        industrialFunc(matrix, prevMatrix, indusList, availWorkers);

        availWorkers = totalAvailWorkers(matrix);
        availGoods = totalAvailGoods(matrix);

        commercialFunc(matrix, matrix, comList, availWorkers, availGoods);
        residentialFunc(matrix);

        pollution.OnUpdate(matrix);

        matrixCorrector(matrix);

        //comparing previous matrix to current matrix
        bool matrixChanges = false;
        for (int i = 0; i < matrix.size(); ++i) {
            for (int k = 0; k < matrix[i].size(); ++k) {
                if (prevMatrix[i][k].name != matrix[i][k].name) {
                    matrixChanges = true;
                    break;
                }
            }
        }
        if (currTimeStep == timeLimit || !matrixChanges) {
            cout << "Final Region Configuration" << endl;
            displayMatrix(matrix);
            cout << "\nFinal Regional Pollution Configuration" << endl;
            displayMatrixPollution(matrix);
            cout << endl;
            cout << "NO NEW CHANGES\n" << endl;
            break;
        }

        if (currTimeStep % refreshRate == 0) {//display code based on timestep
            cout << "Time Step " << currTimeStep << endl;
            cout << "City:" << endl;
            displayMatrix(matrix);
            cout << endl << "Pollution:" << endl;
            displayMatrixPollution(matrix);
            cout << endl;
        }
        comList.clear();
        indusList.clear();
    }
    displayAllPopulations(matrix);
    analyzeRegion(matrix, topLeft, bottomRight);

    return 0;
}
