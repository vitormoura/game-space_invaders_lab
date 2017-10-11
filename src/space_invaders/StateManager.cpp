#include "StateManager.h"
#include <iostream>
#include <fstream>

namespace my {

	StateManager::StateManager(void)
	{
	}

	StateManager::~StateManager(void)
	{
	}

	bool StateManager::saveMaxScore( int score ) {
		
		std::ofstream file;
		file.open("scores.dat", std::ios::out);

		if(file.is_open()) {
			file << score;
		}

		file.close();

		return true;
	}

	int	StateManager::loadMaxScore() {

		int max_score = 0;

		std::ifstream file;
		file.open("scores.dat", std::ios::in);

		if(file.is_open()) {
			file >> max_score;
		}

		file.close();

		return max_score;
	}

}