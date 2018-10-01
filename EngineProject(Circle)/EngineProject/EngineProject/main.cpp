#include <iostream>
#include "Game.h"
using namespace std;

int main() {
	Game* game = new Game(640, 480, "Insert cool window name");

	if (game->Start()) {
		game->Loop();		
	}		
	game->Stop();

	cin.get();
	delete game;	
	return 0;
}