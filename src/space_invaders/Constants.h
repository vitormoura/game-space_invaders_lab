#pragma once

#define DEBUG_MODE 0

namespace my {

	//Velocidade padrão de jogo
	const static float DEFAULT_GAME_SPEED = 60.0f;

	const static int DEFAULT_TRIES = 3;

	const static int ENEMY_POINTS = 1;

	const static int BONUS_ENEMY_POINTS = (ENEMY_POINTS * 10);

	namespace dir {
		const int LEFT = -1;
		const int UP = -1;
		const int RIGHT = 1;
		const int DOWN = 1;
	}

	enum class Directions {
		Left,  
		Right,
		Up,
		Down
	};


}