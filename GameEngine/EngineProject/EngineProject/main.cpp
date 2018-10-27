#include <iostream>
#include "Game.h"
using namespace std;

int main() {
	Game* game = new Game(1024, 768, "Insert cool window name");

	if (game->Start()) {
		game->Loop();		
	}		
	game->Stop();

	cin.get();
	delete game;	
	return 0;
}