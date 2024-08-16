#include "Game.h"
#include <sstream>
#include <fstream>
using namespace std;

Game::Game(string mapMatrixSize, string keyMatrixSize, string mapMatrixName, string keyMatrixName, string outputName) {
    //Splitting matrix size and parsing to int.
    stringstream row(mapMatrixSize.substr(0,mapMatrixSize.find('x')));
    mapMatrixSize.erase(0, mapMatrixSize.find('x') + 1);
    stringstream column(mapMatrixSize);
    stringstream keySize(keyMatrixSize);
    //Assigning the values.
    row >> Game::mapMatrixSize[0];
    column >> Game::mapMatrixSize[1];
    keySize >> Game::keyMatrixSize;
    Game::mapMatrixName = mapMatrixName;
    Game::keyMatrixName = keyMatrixName;
    Game::outputName = outputName;
    Game::keyLoc[0] = Game::keyMatrixSize/2;
    Game::keyLoc[1] = Game::keyLoc[0];
}

void Game::createMapMatrix() {
    //creating 2d dynamic matrix
    Game::mapMatrix = new int*[Game::mapMatrixSize[0]];
    for (int i=0; i<Game::mapMatrixSize[0]; i++){
        Game::mapMatrix[i] = new int[Game::mapMatrixSize[1]];
    }
    //opening map matrix file
    fstream file;
    file.open(Game::mapMatrixName, ios::in);
    //filling the 2d dynamic matrix cells according to the file
    if(file.is_open()){
        for(int i=0; i<Game::mapMatrixSize[0]; i++){
            for(int j=0; j<Game::mapMatrixSize[1]; j++){
                file >> mapMatrix[i][j];
            }
        }
    }
    file.close();
}

void Game::createKeyMatrix() {
    //creating 2d dynamic matrix
    Game::keyMatrix = new int*[Game::keyMatrixSize];
    for (int i=0; i<keyMatrixSize; i++){
        Game::keyMatrix[i] = new int[Game::keyMatrixSize];
    }
    //opening key matrix file
    fstream file;
    file.open(Game::keyMatrixName, ios::in);
    //filling the 2d dynamic matrix cells according to the file
    if(file.is_open()){
        for(int i=0; i<Game::keyMatrixSize; i++){
            for(int j=0; j<Game::keyMatrixSize; j++){
                file >> keyMatrix[i][j];
            }
        }
    }
    file.close();
}

int Game::multiply() {
    //multiplying the matrices
    int result = 0;
    for(int i=0; i<Game::keyMatrixSize; i++){
        for(int j=0; j<Game::keyMatrixSize; j++){
            result += keyMatrix[i][j] * mapMatrix[keyLoc[0]-(keyMatrixSize/2)+j][keyLoc[1]-(keyMatrixSize/2)+i];
        }
    }
    while(result<0){
        result+=5;
    }
    Game::output += (to_string(keyLoc[0]) + "," + to_string(keyLoc[1]) + ":" + to_string(result) + "\n");
    return result;
}

void Game::move(int direction) {
    //checking bound exceptions
    if((direction == 1) && (Game::keyLoc[0] - Game::keyMatrixSize < 0)){
        direction = 2;
    }
    if((direction == 2) && (Game::keyLoc[0] + Game::keyMatrixSize > Game::mapMatrixSize[0])){
        direction = 1;
    }
    if((direction == 3) && (Game::keyLoc[1] + Game::keyMatrixSize > Game::mapMatrixSize[1])){
        direction = 4;
    }
    if((direction == 4) && (Game::keyLoc[1] - Game::keyMatrixSize < 0)){
        direction = 3;
    }
    //moving the key matrix to the given direction
    switch (direction) {
        case 0:
            Game::treasureFound = true;
            break;
        case 1:
            Game::keyLoc[0] -= Game::keyMatrixSize;
            break;
        case 2:
            Game::keyLoc[0] += Game::keyMatrixSize;
            break;
        case 3:
            Game::keyLoc[1] += Game::keyMatrixSize;
            break;
        case 4:
            Game::keyLoc[1] -= Game::keyMatrixSize;
            break;
    }
}

void Game::search() {
    //searching the treasure recursively
    int result = Game::multiply();
    Game::move(result % 5);
    if(treasureFound){
        return;
    }
    Game::search();
}

void Game::printOutput() {
    //prints the output into the file
    fstream file;
    file.open(Game::outputName, ios::out);

    if(file.is_open()){
        file << Game::output;
    }
    file.close();
}

void Game::deleteMatrix() {

    for(int i=0; i<mapMatrixSize[0]; i++){
        delete[] mapMatrix[i];
    }
    delete mapMatrix;
    mapMatrix = nullptr;

    for(int i=0; i<keyMatrixSize; i++){
        delete[] keyMatrix[i];
    }
    delete keyMatrix;
    keyMatrix = nullptr;
}

void Game::launch() {
    //starts the game
    Game::createMapMatrix();
    Game::createKeyMatrix();
    Game::search();
    Game::printOutput();
    Game::deleteMatrix();
}