#ifndef BBM203_GAME_H
#define BBM203_GAME_H
#include <iostream>
using std::string;

class Game {
private:
    int mapMatrixSize[2];
    int keyMatrixSize;
    string mapMatrixName;
    string keyMatrixName;
    string outputName;
    int** mapMatrix;
    int** keyMatrix;
    int keyLoc[2];
    bool treasureFound = false;
    string output;

public:
    Game(string mapMatrixSize, string keyMatrixSize, string mapMatrixName, string keyMatrixName, string outputName );
    void launch();
    void createMapMatrix();
    void createKeyMatrix();
    int multiply();
    void move(int result);
    void search();
    void printOutput();
    void deleteMatrix();

};

#endif //BBM203_GAME_H