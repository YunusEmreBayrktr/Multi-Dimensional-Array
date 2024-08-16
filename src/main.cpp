# include "Game.h"

int main(int argc, char* args[]){

    Game game(args[1],args[2],args[3],args[4],args[5]);
    game.launch();

    return 0;
}