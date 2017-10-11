#pragma once

#include "Types.h"
#include "GameElement.h"
#include "AnimatedSprite.h"
#include "Destroyable.h"

namespace my {

	namespace gelements {

		using namespace std;
		using namespace sf;

		//Inimigo comum
		class Enemy :
			public Destroyable
		{
		
		public:
			//Retorna quanto o inimigo vale caso destruído
			virtual int value() = 0;
		};

	};
}