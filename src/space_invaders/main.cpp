#include "stdafx.h"
#include <iostream>
#include <memory>
#include "Game.h"


void run_game() {

	my::Game my_game("Space Invaders", 400);
	my_game.run();
}

int main() {
		
	run_game();


	
	return EXIT_SUCCESS;
}